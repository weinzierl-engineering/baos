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
#include "kdrive/baos/BaosEvent.h"
#include "kdrive/baos/BaosDatapoint.h"
#include "kdrive/baos/core/BaosConnector.h"
#include "kdrive/baos/core/DataPacket.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/ServerItem.h"
#include "kdrive/baos/protocols/Protocol.h"
#include "kdrive/utility/Logger.h"
#include <Poco/Exception.h>
#include <boost/assert.hpp>

using namespace kdrive::baos;
using namespace kdrive::connector;
using Poco::Exception;
using Poco::FastMutex;
using Poco::ScopedLock;

#define BIND_PACKET_SIGNAL(function) \
	std::bind(&BaosEvent::function, this, std::placeholders::_1)

#define BIND_THREAD_STOP_SIGNAL(function) \
	std::bind(&BaosEvent::function, this)

CLASS_LOGGER("kdrive.baos.BaosEvent")

BaosEvent::BaosEvent()

	: enabled_(false)
{
}

BaosEvent::BaosEvent(BaosConnector::Ptr connector, bool enabled)

	: connector_(connector),
	  enabled_(enabled)
{
	if (enabled)
	{
		connect();
	}
}

BaosEvent::~BaosEvent()
{
	try
	{
		connectorDisconnected_.disconnect();
		connectorConnected_.disconnect();
		packetSignalConnection_.disconnect();
	}
	catch (...)
	{
	}
}

void BaosEvent::setDatapointEvent(DatapointEvent datapointEvent)
{
	ScopedLock<FastMutex> lock(mutex_);
	datapointEvent_ = datapointEvent;
}

void BaosEvent::setServerItemEvent(ServerItemEvent serverItemEvent)
{
	ScopedLock<FastMutex> lock(mutex_);
	serverItemEvent_ = serverItemEvent;
}

void BaosEvent::setBusConnectedEvent(BusConnectedEvent busConnectedEvent)
{
	ScopedLock<FastMutex> lock(mutex_);
	busConnectedEvent_ = busConnectedEvent;
}

void BaosEvent::setConnectorClosedEvent(ConnectorClosedEvent connectorClosedEvent)
{
	ScopedLock<FastMutex> lock(mutex_);
	connectorClosedEvent_ = connectorClosedEvent;
}

void BaosEvent::setConnector(BaosConnector::Ptr connector, bool enabled)
{
	ScopedLock<FastMutex> lock(mutex_);
	setEnabled(false);
	connector_ = connector;
	setEnabled(enabled);
}

void BaosEvent::enable(bool enabled)
{
	ScopedLock<FastMutex> lock(mutex_);
	setEnabled(enabled);
}

void BaosEvent::disable()
{
	ScopedLock<FastMutex> lock(mutex_);
	setEnabled(false);
}

bool BaosEvent::isEnabled() const
{
	ScopedLock<FastMutex> lock(mutex_);
	return enabled_;
}

void BaosEvent::connect()
{
	if (!connector_)
	{
		throw ClientException("Invalid Connector");
	}
	BaosConnector::PacketSignal& s = connector_->getPacketSignal();
	packetSignalConnection_ = s.connect(BIND_PACKET_SIGNAL(onPacket));

	CallbackThread& callbackThread = connector_->getRxCallbackThread();
	connectorDisconnected_ = callbackThread.getSignals().stop.connect(BIND_THREAD_STOP_SIGNAL(onCallbackThreadEvent));
}

void BaosEvent::disconnect()
{
	connectorDisconnected_.disconnect();
	connectorConnected_.disconnect();
	packetSignalConnection_.disconnect();
}

void BaosEvent::onPacket(Packet::Ptr packet)
{
	try
	{
		DataPacket::Ptr dataPacket = std::dynamic_pointer_cast<DataPacket>(packet);
		if (dataPacket)
		{
			onDataPacket(dataPacket);
		}
	}
	catch (Exception& exception)
	{
		poco_error(LOGGER(), exception.displayText());
	}
}

void BaosEvent::onDataPacket(DataPacket::Ptr dataPacket)
{
	switch (dataPacket->getSubService())
	{
		case ResponseFunctions::GetDatapointValue:
		case IndicationFunctions::DatapointValueIndication:
			onDatapointValue(dataPacket);
			break;

		case IndicationFunctions::ServerItemIndication:
			onServerItemIndication(dataPacket);
			break;
	}
}

void BaosEvent::onDatapointValue(DataPacket::Ptr dataPacket)
{
	if (datapointEvent_)
	{
		ProtocolFormatter::ServerItems serverItems;
		ProtocolFormatter::decodeGetDatapointValue_Res(dataPacket, serverItems);

		for (const auto& serverItem : serverItems)
		{
			BaosDatapoint baosDatapoint(connector_, serverItem);
			datapointEvent_(baosDatapoint);
		}
	}
}

void BaosEvent::onServerItemIndication(DataPacket::Ptr dataPacket)
{
	if (busConnectedEvent_ || serverItemEvent_)
	{
		ProtocolFormatter::ServerItems serverItems;
		ProtocolFormatter::decodeServerItem_Ind(dataPacket, serverItems);

		for (const auto& serverItem : serverItems)
		{
			if (serverItemEvent_)
			{
				serverItemEvent_(serverItem.id, serverItem.data);
			}

			if (busConnectedEvent_ && (serverItem.id == ServerItemProperties::BusConnected) &&
			    (serverItem.length == 1))
			{
				const bool busConnected = serverItem.data.at(0) ? true : false;
				busConnectedEvent_(busConnected);
			}
		}
	}
}

void BaosEvent::onCallbackThreadEvent()
{
	if (connectorClosedEvent_)
	{
		connectorClosedEvent_();
	}
}

void BaosEvent::setEnabled(bool enabled)
{
	if (enabled_ != enabled)
	{
		enabled ? connect() : disconnect();
		enabled_ = enabled;
	}
}
