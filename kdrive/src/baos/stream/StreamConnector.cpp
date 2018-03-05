//
// Copyright (c) 2002-2018 WEINZIERL ENGINEERING GmbH
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
#include "kdrive/baos/stream/StreamConnector.h"
#include "kdrive/baos/stream/StreamConnector12.h"
#include "kdrive/baos/stream/StreamConnector2x.h"
#include "kdrive/baos/core/DataPacket.h"
#include "kdrive/baos/core/BaosConnector.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/baos/services/GetServerItem.h"
#include "kdrive/connector/QueueConnector.h"
#include "kdrive/connector/Events.h"
#include "kdrive/utility/Logger.h"
#include <Poco/Format.h>
#include <Poco/ScopedLock.h>

using namespace kdrive::baos;
using namespace kdrive::connector;
using Poco::Net::StreamSocket;
using Poco::Net::SocketAddress;
using Poco::Exception;
using Poco::TimeoutException;
using Poco::TimerCallback;
using Poco::format;

CLASS_LOGGER("kdrive.baos.StreamConnector")

/**************************************
** Anonymous namespace
***************************************/

namespace
{

enum Defaults
{
	ReceiveTimeout_us = 150000, /*!< 150ms in microsecond */
	SendHeartbeatTimeout_ms = 60000, /*!< 60s in milliseconds */
	SendHeartbeatTimeout_us = SendHeartbeatTimeout_ms * 1000 /*!< 60s in microsecond */
};

void initProperties(kdrive::utility::PropertyCollection& collection)
{
	collection.setProperty(StreamConnector::PortType, StreamConnector::ConnectorTypeLabel);
	collection.setProperty(StreamConnector::IpAddress, "192.168.1.1");
	collection.setProperty(StreamConnector::IpPort, static_cast<unsigned short>(StreamProtocolConstants::Port));

}

struct null_deleter
{
	void operator()(void const*) const
	{
	}
};

} // end anonymous namespace

/******************************
** StreamConnectorFactory
*******************************/

BaosConnector::Ptr StreamConnectorFactory::create(unsigned char version, const std::string remoteHost, unsigned short port)
{
	BaosConnector::Ptr connector;

	if (ProtocolVersions::is1x(version))
	{
		connector.reset(new StreamConnector12(remoteHost, port));
	}
	else if (ProtocolVersions::is2x(version))
	{
		connector.reset(new StreamConnector2x(remoteHost, port));
		connector->setVersion(version);
	}

	if (!connector)
	{
		throw ClientException("Protocol Version Not Supported");
	}

	return connector;
}

/**********************************
** StreamConnector
***********************************/

const std::string StreamConnector::ConnectorTypeLabel = "baos.tcp";
const std::string StreamConnector::IpAddress = "baos.tcp.ip_address";
const std::string StreamConnector::IpPort = "baos.tcp.ip_port";
const std::string StreamConnector::DeviceName = "baos.tcp.device_name";

StreamConnector::StreamConnector(unsigned char version)

	: StreamConnector(version, "", StreamProtocolConstants::Port)
{
	initProperties(*this);
}

StreamConnector::StreamConnector(unsigned char version, const std::string& remoteHost, unsigned short port)

	: BaosConnector(version)
{
	initProperties(*this);

	setProperty(IpAddress, remoteHost);
	setProperty(IpPort, port);
}

StreamConnector::~StreamConnector()
{
	try
	{
		close();
	}
	catch (...)
	{
	}
}

void StreamConnector::open(const std::string& remoteHost, unsigned short port)
{
	setIpAddress(remoteHost);
	setIpPort(port);
	BaosConnector::open();
}

std::string StreamConnector::getDescription()
{
	if (hasPropertyKey(DeviceName))
	{
		return format("%s %s", getIpAddress(), getProperty(DeviceName).toString());
	}
	else
	{
		return getIpAddress();
	}
}

void StreamConnector::setIpAddress(const std::string& ipAddress)
{
	setProperty(IpAddress, ipAddress);
}

std::string StreamConnector::getIpAddress() const
{
	return getProperty(IpAddress);
}

void StreamConnector::setIpPort(unsigned short port)
{
	setProperty(IpPort, port);
}

unsigned short StreamConnector::getIpPort() const
{
	return getProperty(IpPort);
}

int StreamConnector::readFromSocket(unsigned char* buffer, int maxBytesToRead)
{
	int received = 0;

	if (socket_.poll(Poco::Timespan(0, ReceiveTimeout_us), Poco::Net::Socket::SELECT_READ))
	{
		received = socket_.receiveBytes(buffer, maxBytesToRead);
	}

	return received;
}

int StreamConnector::readFromSocket(unsigned char* buffer, std::size_t bufferSize, int bytesToRead, bool validate)
{
	if (bytesToRead > static_cast<int>(bufferSize))
	{
		poco_warning(LOGGER(), "Requested read too big for buffer");
		throw ClientException("Potential Buffer Overrun");
	}

	int received = 0;

	while (received < bytesToRead)
	{
		if (!socket_.poll(Poco::Timespan(0, ReceiveTimeout_us), Poco::Net::Socket::SELECT_READ))
		{
			break;
		}

		int rxLength = socket_.receiveBytes(buffer + received, bytesToRead - received);
		if (rxLength > 0)
		{
			received += rxLength;
		}
		else
		{
			throw ClientException("Socket Error");
		}
	}

	if (validate && received != bytesToRead)
	{
		poco_warning(LOGGER(), format("Read mismatch: expected %d, received", bytesToRead, received));
		throw ClientException("Failed to read expected bytes", received);
	}

	return received;
}

void StreamConnector::openImpl()
{
	try
	{
		socket_.connect(SocketAddress(getIpAddress(), getIpPort()), ReceiveTimeout_us);
		socket_.setKeepAlive(true);
		startRxThread();

		// try to send here the "heartbeat" to test the communication
		doHeartbeat();

		// start the timer after all (because it's not needed to start it when e.g. the device do not answer)
		startHeartbeatTimer();
	}
	catch (Poco::Exception& e)
	{
		heartbeatTimer_.stop();
		stopRxThread();
		socket_.close();
		throw ClientException("Could not open: " + e.displayText());
	}
	catch (...)
	{
		heartbeatTimer_.stop();
		stopRxThread();
		socket_.close();
		throw ClientException("Could not open: Unhandled exception");
	}
}

void StreamConnector::closeImpl()
{
	heartbeatTimer_.stop();
	stopRxThread();
	shutdownSocket();
	socket_.close();
}

void StreamConnector::txImpl(Packet::Ptr packet)
{
	try
	{
		{
			Poco::ScopedLock<Poco::FastMutex> lock(txMutex_);
			unsigned char* buffer = &txBuffer_.at(0);
			txBuffer_.fill(0);
			const std::size_t size = encapsulate(packet, buffer, BufferSize);
			socket_.sendBytes(buffer, static_cast<int>(size));
		}

		timestampLastSend_.update();

		routeTx(packet);
	}
	catch (Exception& exception)
	{
		poco_warning(LOGGER(), exception.displayText());
		throw;
	}
}

void StreamConnector::resetPropertiesImpl()
{
	BaosConnector::resetPropertiesImpl();
	initProperties(*this);
}

/*
	\note Not call this in the timer thread!!
*/
void StreamConnector::startHeartbeatTimer()
{
	timestampLastSend_.update();

	TimerCallback<StreamConnector> callback(*this, &StreamConnector::onHeartbeatTimer);
	heartbeatTimer_.stop();
	heartbeatTimer_.setPeriodicInterval(SendHeartbeatTimeout_ms);
	startTimer(heartbeatTimer_, callback);
}

void StreamConnector::shutdownSocket()
{
	try
	{
		socket_.shutdown();
	}
	catch (Exception& exception)
	{
		poco_warning(LOGGER(), "Error while shutdown socket: " + exception.displayText());
	}
	catch (...)
	{
		poco_warning(LOGGER(), "Error while shutdown socket: Unhandled exception");
	}
}

void StreamConnector::doHeartbeat()
{
	StreamConnector::Ptr connector(this, null_deleter());
	GetServerItem service(connector);
	try
	{
		service.rpc(ServerItemProperties::TimeSinceReset, 1);
	}
	catch (TimeoutException&)
	{
		throw ClientException("No heartbeat response from device");
	}
}

/*
	On error route an Terminated event but do not (re)throw the exception.
	We do not want to have an exception in the timer thread.
	Do only stop the timer with restart 0.
*/
void StreamConnector::onHeartbeatTimer(Poco::Timer& timer)
{
	try
	{
		if (isOpenImpl())
		{
			const Poco::Timestamp::TimeDiff elapsed_us = timestampLastSend_.elapsed();

			if (elapsed_us >= SendHeartbeatTimeout_us)
			{
				doHeartbeat();
			}

			const long elapsed_ms = static_cast<long>(elapsed_us / 1000);
			const long nextInterval = (elapsed_ms < SendHeartbeatTimeout_ms) ?
			                          (SendHeartbeatTimeout_ms - elapsed_ms) :
			                          static_cast<long>(SendHeartbeatTimeout_ms);
			timer.setPeriodicInterval(nextInterval);
		}
		else
		{
			timer.restart(0);
		}
	}
	catch (Exception& exception)
	{
		poco_error_f1(LOGGER(), "Error in onHeartbeatTimer, %s", exception.displayText());
		routeEvent(ConnectorEvents::Terminated);
		timer.restart(0);
	}
	catch (...)
	{
		poco_error(LOGGER(), "Unhandled error in onHeartbeatTimer");
		routeEvent(ConnectorEvents::Terminated);
		timer.restart(0);
	}
}
