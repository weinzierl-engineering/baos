//
// Copyright (c) 2002-2015 WEINZIERL ENGINEERING GmbH
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
#include "kdrive/baos/ft12/FT12Connector.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/DataPacket.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/baos/protocols/Protocol20.h"
#include "kdrive/baos/protocols/Protocol12.h"
#include "kdrive/knx/defines/FT12Constants.h"
#include "kdrive/utility/Logger.h"

using namespace kdrive::connector;
using namespace kdrive::baos;
using namespace kdrive::ft12;
using Poco::Exception;
using kdrive::knx::ft12::FT12Constants;

CLASS_LOGGER("kdrive.baos.FT12Connector")

/**************************************
** Anonymous namespace
***************************************/

namespace
{

enum Defaults
{
    DefaultBaudrate = 19200,
    RxBufferLength = 30
};

void initProperties(kdrive::utility::PropertyCollection& collection)
{
	collection.setProperty(FT12Connector::PortType, FT12Connector::ConnectorTypeLabel);
	collection.setProperty(FT12Connector::SerialDeviceName, "");
}

} // end anonymous namespace

/**************************************
** FT12Connector
***************************************/

#define BIND_SENDER() \
	std::bind(&FT12_Packetizer::sendBuffer, &packetizer_, std::placeholders::_1, std::placeholders::_2)

#define BIND_USER_DATA_CALLBACK() \
	std::bind(&FT12Connector::onTelegramInd, this, std::placeholders::_1)

const std::string FT12Connector::ConnectorTypeLabel = "baos.serial.ft12";
const std::string FT12Connector::SerialDeviceName = "baos.serial.device_name";

FT12Connector::FT12Connector()

	: BaosConnector(ProtocolVersions::V20),
	  txBuffer_(FT12Constants::MaxBufferSize),
	  rxBuffer_(FT12Constants::MaxBufferSize),
	  packetizer_(serialPort_, 50)
{
	initProperties(*this);

	ft12_.setSender(BIND_SENDER());
	ft12_.setUserDataCallback(BIND_USER_DATA_CALLBACK());
}

FT12Connector::~FT12Connector()
{
	try
	{
		close();
	}
	catch (...)
	{
	}
}

void FT12Connector::open(const std::string& serialDeviceName, unsigned char version)
{
	setProperty(SerialDeviceName, serialDeviceName);
	setVersion(version);
	BaosConnector::open();
}

std::string FT12Connector::getDescription()
{
	return getSerialDeviceName();
}

std::string FT12Connector::getSerialDeviceName() const
{
	return getProperty(SerialDeviceName);
}

void FT12Connector::openImpl()
{
	BaosPacketFactory::Ptr packetFactory;
	if (getVersion() == ProtocolVersions::V20)
	{
		packetFactory = std::make_shared<PacketFactory20>();
	}
	else if (getVersion() == ProtocolVersions::V12)
	{
		packetFactory = std::make_shared<PacketFactory12>();
	}
	else
	{
		throw ClientException("Could not open: Unsupported protocol version");
	}

	setPacketFactory(packetFactory);

	serialPort_.open(getSerialDeviceName(), DefaultBaudrate, "8E1", kdrive::io::serial::SerialPort::FLOW_NONE);
	startRxThread();
	ft12_.init();
}

void FT12Connector::closeImpl()
{
	stopRxThread();
	serialPort_.close();
}

bool FT12Connector::isOpenImpl() const
{
	return serialPort_.isOpen();
}

void FT12Connector::resetPropertiesImpl()
{
	BaosConnector::resetPropertiesImpl();
	initProperties(*this);
}

void FT12Connector::txImpl(Packet::Ptr packet)
{
	try
	{
		unsigned char* buffer = &txBuffer_.at(0);
		std::memset(buffer, 0, FT12Constants::MaxBufferSize);
		const std::size_t size = packet->writeToBuffer(buffer, FT12Constants::MaxBufferSize);
		ft12_.sendVariableLengthFrame(buffer, size);
		routeTx(packet);
	}
	catch (Exception& exception)
	{
		poco_warning_f1(LOGGER(), "Error in txImpl, %s", exception.displayText());
		raiseError(exception);
	}
}

void FT12Connector::rxImpl()
{
	try
	{
		unsigned char* ptr = &rxBuffer_.at(0);
		const std::size_t length = packetizer_.get(ptr, rxBuffer_.size());

		if (length)
		{
			ft12_.onReceive(ptr, length);
		}
	}
	catch (Exception& exception)
	{
		poco_information_f1(LOGGER(), "Error in rxImpl, %s", exception.displayText());
		raiseError(exception);
	}
}

void FT12Connector::onTelegramInd(const std::vector<unsigned char>& buffer)
{
	if (!buffer.empty())
	{
		Packet::Ptr packet = create(&buffer.at(0), buffer.size());
		routeRx(packet);
	}
}
