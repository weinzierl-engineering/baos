//
// Copyright (c) 2002-2016 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//

#include "pch/kdrive_pch.h"
#include "kdrive/baos/BaosEnumerator.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/baos/core/String.h"
#include "kdrive/utility/Logger.h"
#include "kdrive/utility/LoggerFormatter.h"
#include <Poco/Exception.h>
#include <Poco/Format.h>
#include <Poco/Logger.h>
#include <Poco/String.h>
#include <Poco/StringTokenizer.h>
#include <Poco/NumberParser.h>
#include <Poco/Net/NetworkInterface.h>
#include <Poco/Net/MulticastSocket.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/IPAddress.h>
#include <boost/assert.hpp>

using namespace kdrive::baos;
using kdrive::utility::LoggerFormatter;
using Poco::TimeoutException;
using Poco::Timespan;
using Poco::format;
using Poco::icompare;
using Poco::trim;
using Poco::StringTokenizer;
using Poco::NumberParser;
using Poco::Net::NetworkInterface;
using Poco::Net::MulticastSocket;
using Poco::Net::SocketAddress;
using Poco::Net::IPAddress;

CLASS_LOGGER("kdrive.baos.BaosEnumerator")

/*********************************
** Anonymnous namespace
**********************************/

namespace
{

enum
{
    RxBufferLength = 300,
    DefaultMulticastTTL = 16,
    SearchResponseTimeout = 500 /*!< Timeout for get a search response in ms. */
};

} // end anonymous namespace

/**************************************
** BaosEnumerator
***************************************/

BaosEnumerator::BaosEnumerator(bool autoScan)
{
	if (autoScan)
	{
		scan();
	}
}

BaosEnumerator::~BaosEnumerator()
{
}

const BaosEnumerator::Devices& BaosEnumerator::scan()
{
	devices_.clear();

	NetworkInterface::NetworkInterfaceList interfaces = NetworkInterface::list();
	for (const auto& networkInterface : interfaces)
	{
		if (!networkInterface.address().isLoopback() && networkInterface.supportsIPv4())
		{
			scanInterface(networkInterface);
		}
	}

	return devices_;
}

const BaosEnumerator::Devices& BaosEnumerator::getDevices() const
{
	return devices_;
}

const BaosEnumerator::Device& BaosEnumerator::find(const std::string& name) const
{
	for (const auto& device : devices_)
	{
		if (!icompare(getName(device), name))
		{
			return device;
		}
	}

	throw ClientException("Device Not Found");
}

const BaosEnumerator::Device& BaosEnumerator::findByAddress(const std::string& ipAddress) const
{
	for (const auto& device : devices_)
	{
		if (!icompare(getAddress(device), ipAddress))
		{
			return device;
		}
	}

	throw ClientException("Device Not Found");
}

const std::string& BaosEnumerator::getName(const Device& device) const
{
	return std::get<BaosDeviceAttr::Name>(device);
}

const std::string& BaosEnumerator::getInterfaceAddress(const Device& device) const
{
	return std::get<BaosDeviceAttr::InterfaceAddress>(device);
}

const std::string& BaosEnumerator::getAddress(const Device& device) const
{
	return std::get<BaosDeviceAttr::Address>(device);
}

unsigned char BaosEnumerator::getVersion(const Device& device) const
{
	return std::get<BaosDeviceAttr::Version>(device);
}

/*!
	Scans an interface and enumerates all baos devices.
	It sends a search request as outlined in the BAOS 1.2 protcol
	documentation and waits for the responses. There are lots of
	magic numbers here and hardcoded offsets... See the spec
	for more information on what is happening here...

	We implement a receive timeout, and keep receiving until this
	timeout elapses. If this timeout is too fast, increase it to 500
	or 1000 for example.
*/
void BaosEnumerator::scanInterface(const NetworkInterface& networkInterface)
{
	poco_information(LOGGER(),
	                 format("Search devices on interface: %s (%s)",
	                        networkInterface.displayName(),
	                        networkInterface.address().toString()));

	try
	{
		// initialize socket
		MulticastSocket socket;
		socket.setReceiveTimeout(Timespan(SearchResponseTimeout * 1000));
		socket.bind(SocketAddress(networkInterface.address(), 0));
		socket.setTimeToLive(DefaultMulticastTTL);

		// builds and sends a SEARCH_REQUEST to the socket
		sendSearchRequestFrame(socket);

		// wait for SEARCH_RESPONSES and collect it
		waitForSearchResponseFrames(socket);
	}
	catch (Poco::Exception& e)
	{
		poco_warning(LOGGER(), format("... search failed with error: %s", e.displayText()));
	}
}

void BaosEnumerator::sendSearchRequestFrame(MulticastSocket& socket)
{
	const IPAddress& address = socket.address().host();
	StringTokenizer stringTokenizer(address.toString(), ".");
	BOOST_ASSERT(stringTokenizer.count() == 4 && "Invalid IP Address");

	const unsigned short port = socket.address().port();

	// build SEARCH_REQUEST frame
	const std::vector<unsigned char> request =
	{
		0x06, 0x10, 0x02, 0x01, 0x00, 0x0E, 0x08, 0x01,
		static_cast<unsigned char>(NumberParser::parse(stringTokenizer[0])),
		static_cast<unsigned char>(NumberParser::parse(stringTokenizer[1])),
		static_cast<unsigned char>(NumberParser::parse(stringTokenizer[2])),
		static_cast<unsigned char>(NumberParser::parse(stringTokenizer[3])),
		static_cast<unsigned char>((port >> 8) & 0xFF),
		static_cast<unsigned char>(port & 0xFF)
	};

	// send to socket
	const SocketAddress destAddress(MulticastProtocolConstants::Address, MulticastProtocolConstants::Port);
	socket.sendTo(&request.at(0), static_cast<int>(request.size()), destAddress);
}

void BaosEnumerator::waitForSearchResponseFrames(MulticastSocket& socket)
{
	std::vector<unsigned char> buffer;
	while (waitForRx(socket, buffer))
	{
		poco_trace(LOGGER(), format("Received search response: %s", LoggerFormatter::toHex(buffer)));
		addDevice(buffer, socket.address().host());
	}
}

bool BaosEnumerator::waitForRx(MulticastSocket& socket, std::vector<unsigned char>& buffer)
{
	const Timespan timeout = SearchResponseTimeout * 1000;
	if (socket.poll(timeout, Poco::Net::Socket::SELECT_READ))
	{
		buffer.resize(RxBufferLength);
		SocketAddress deviceAddress;
		std::size_t size = socket.receiveFrom(&buffer.at(0), buffer.size(), deviceAddress);
		buffer.resize(size);
		return true;
	}

	return false;
}

void BaosEnumerator::addDevice(const std::vector<unsigned char>& buffer, const IPAddress& networkInterface)
{
	if (buffer.size() > 68)
	{
		const int svcdiblen = buffer.at(68);
		const std::string ipAddress = format("%d.%d.%d.%d", (int) buffer.at(8), (int) buffer.at(9), (int) buffer.at(10), (int) buffer.at(11));
		const std::string deviceName = extract(&buffer.at(38), 30);
		const int manOffset = 68 + svcdiblen;

		if (static_cast<std::size_t>(manOffset + 7) < buffer.size())
		{
			const unsigned int mancode = buffer.at(manOffset + 2) << 8 | buffer.at(manOffset + 3);
			const unsigned char protocol = buffer.at(manOffset + 6);
			const unsigned char version = buffer.at(manOffset + 7);

			if (mancode == 0x00C5 && protocol == 0xF0)
			{
				poco_information(LOGGER(),
				                 format("Found: %s %s %d",
				                        deviceName, ipAddress, static_cast<int>(version)));

				devices_.push_back(std::make_tuple(deviceName, networkInterface.toString(), ipAddress, version));
			}
		}
	}
}
