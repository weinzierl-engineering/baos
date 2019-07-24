//
// Copyright (c) 2002-2019 WEINZIERL ENGINEERING GmbH
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
#include "kdrive/baos/BaosConnection.h"
#include "kdrive/baos/stream/StreamConnector.h"
#include "kdrive/baos/ft12/FT12Connector.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/protocols/Protocol12.h"
#include "kdrive/baos/BaosEnumerator.h"
#include "kdrive/utility/Logger.h"
#include <Poco/Exception.h>
#include <Poco/Format.h>
#include <Poco/Net/StreamSocket.h>
#include <boost/assert.hpp>

using Poco::Exception;
using Poco::format;
using Poco::NullPointerException;
using Poco::Net::SocketAddress;
using namespace kdrive::connector;
using namespace kdrive::baos;

CLASS_LOGGER("kdrive.baos.BaosConnection")

BaosConnection::BaosConnection()
{
}

BaosConnection::~BaosConnection()
{
}

BaosConnector::Ptr BaosConnection::getConnector()
{
	if (!baosConnector_)
	{
		throw NullPointerException("Not connected");
	}

	return baosConnector_;
}

void BaosConnection::connectIp(const std::string remoteHost, unsigned char version, bool decodeProtocol)
{
	connectIpImpl(remoteHost, StreamProtocolConstants::Port, version, decodeProtocol);
}

void BaosConnection::connectIp(const BaosDevice& baosDevice, bool decodeProtocol)
{
	connectIpImpl(std::get<BaosDeviceAttr::Address>(baosDevice),
	              StreamProtocolConstants::Port,
	              std::get<BaosDeviceAttr::Version>(baosDevice),
	              decodeProtocol);
}

void BaosConnection::connectIpByName(const std::string& name, bool decodeProtocol)
{
	BaosEnumerator baosEnumerator;
	const BaosEnumerator::Device device = baosEnumerator.find(name);
	connectIp(device, decodeProtocol);
}

void BaosConnection::connectIpByAddress(const std::string& ipAddress, bool decodeProtocol)
{
	BaosEnumerator baosEnumerator;
	const BaosEnumerator::Device device = baosEnumerator.findByAddress(ipAddress);
	connectIp(device, decodeProtocol);
}

void BaosConnection::connectIpNat(const std::string& ipAddress,
                                  unsigned short port,
                                  unsigned char version,
                                  bool decodeProtocol)
{
	connectIpImpl(ipAddress, port, version, decodeProtocol);
}

void BaosConnection::connectSerial(const std::string& serialDeviceName, bool decodeProtocol)
{
	connectSerialImpl(serialDeviceName, decodeProtocol);
}

void BaosConnection::disconnect()
{
	if (baosConnector_)
	{
		poco_information(LOGGER(), "Disconnect");
		baosConnector_->close();
		baosConnector_.reset();
	}
}

bool BaosConnection::isConnected() const
{
	return baosConnector_ ? true : false;
}

BaosConnection::ConnectSignal& BaosConnection::getConnectSignal()
{
	CallbackThread& callbackThread = baosConnector_->getRxCallbackThread();
	return callbackThread.getSignals().start;
}

BaosConnection::DisconnectSignal& BaosConnection::getDisconnectSignal()
{
	CallbackThread& callbackThread = baosConnector_->getRxCallbackThread();
	return callbackThread.getSignals().stop;
}

unsigned char BaosConnection::lookupVersion(const std::string remoteHost, unsigned char version)
{
	BaosEnumerator baosEnumerator;
	const BaosEnumerator::Device device = baosEnumerator.findByAddress(remoteHost);
	return std::get<BaosDeviceAttr::Version>(device);
}

void BaosConnection::connectIpImpl(const std::string remoteHost,
                                   unsigned short port,
                                   unsigned char version,
                                   bool decodeProtocol)
{
	disconnect();

	if (!version)
	{
		version = lookupVersion(remoteHost, version);
	}

	baosConnector_ = StreamConnectorFactory::create(version, remoteHost, port);

	if (decodeProtocol)
	{
		protocolDecoder_.connect(*baosConnector_);
	}

	const int major = (version >> 4) & 0x0F;
	const int minor = version & 0x0F;
	poco_information_f3(LOGGER(), "Connect %s v%d.%d", remoteHost, major, minor);
	baosConnector_->open();
}

void BaosConnection::connectSerialImpl(const std::string serialDeviceName, bool decodeProtocol)
{
	disconnect();

	FT12Connector::Ptr connector = std::make_shared<FT12Connector>();
	baosConnector_ = connector;

	if (decodeProtocol)
	{
		protocolDecoder_.connect(*baosConnector_);
	}

	poco_information_f1(LOGGER(), "Connect %s", serialDeviceName);
	connector->open(serialDeviceName);
}

/******************************
** ScopedBaosConnection
*******************************/

ScopedBaosConnection::ScopedBaosConnection(const std::string& name, bool decodeProtocol)
{
	connectIpByName(name, decodeProtocol);
}

ScopedBaosConnection::ScopedBaosConnection(const std::string remoteHost, unsigned char version, bool decodeProtocol)
{
	connectIp(remoteHost, version, decodeProtocol);
}

ScopedBaosConnection::ScopedBaosConnection(const BaosDevice& baosDevice, bool decodeProtocol)
{
	connectIp(baosDevice, decodeProtocol);
}

ScopedBaosConnection::~ScopedBaosConnection()
{
	try
	{
		disconnect();
	}
	catch (...)
	{
	}
}

/******************************
** ScopedSerialBaosConnection
*******************************/

ScopedSerialBaosConnection::ScopedSerialBaosConnection(const std::string& name, bool decodeProtocol)
{
	connectSerial(name, decodeProtocol);
}

ScopedSerialBaosConnection::~ScopedSerialBaosConnection()
{
	try
	{
		disconnect();
	}
	catch (...)
	{
	}
}
