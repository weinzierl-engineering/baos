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
#include "kdrive/connector/ConnectorNotificationHandler.h"
#include "kdrive/connector/Connector.h"
#include "kdrive/connector/Packet.h"
#include "kdrive/connector/PacketNotification.h"
#include "kdrive/utility/Logger.h"
#include <Poco/Exception.h>
#include <thread>

using namespace kdrive::connector;
using Poco::Exception;

CLASS_LOGGER("kdrive.connector.ConnectorNotificationHandler")

/*****************************
** ConnectorNotificationHandler
******************************/

ConnectorNotificationHandler::ConnectorNotificationHandler(Connector& connector)

	: connector_(connector),
	  enabled_(0),
	  queueSignalTrigger_(25),
	  previousQueueSize_(0)
{
}

ConnectorNotificationHandler::~ConnectorNotificationHandler()
{
	try
	{
		disableSignals();
	}
	catch (...)
	{
	}
}

void ConnectorNotificationHandler::enableSignals(bool enabled)
{
	enabled_ = enabled;
}

void ConnectorNotificationHandler::disableSignals()
{
	enableSignals(false);
}

bool ConnectorNotificationHandler::areSignalsEnabled() const
{
	return enabled_ ? true : false;
}

void ConnectorNotificationHandler::setQueueSignalTrigger(int queueSignalTrigger)
{
	queueSignalTrigger_ = queueSignalTrigger;
}

void ConnectorNotificationHandler::routeRx(Packet::Ptr packet)
{
	emitRouteRx(packet);
}

void ConnectorNotificationHandler::routeTx(Packet::Ptr packet)
{
	emitRouteTx(packet);
}

void ConnectorNotificationHandler::routeEvent(unsigned long e)
{
	emitRouteEvent(e);
}

void ConnectorNotificationHandler::routeQueueSignal(int current, int previous)
{
	emitRouteQueueSignal(current, previous);
}

int ConnectorNotificationHandler::getQueueSignalTrigger() const
{
	return queueSignalTrigger_;
}

Connector& ConnectorNotificationHandler::getConnector()
{
	return connector_;
}

void ConnectorNotificationHandler::setPreviousQueueSize(int previousQueueSize)
{
	previousQueueSize_ = previousQueueSize;
}

int ConnectorNotificationHandler::getPreviousQueueSize() const
{
	return previousQueueSize_;
}

void ConnectorNotificationHandler::emitRouteRx(Packet::Ptr packet)
{
	Connector::PacketSignal& packetSignal = connector_.getPacketSignal();
	packetSignal(packet, Connector::Rx);

	Connector::PacketSignalRx& packetSignalRx = connector_.getPacketSignalRx();
	packetSignalRx(packet);
}

void ConnectorNotificationHandler::emitRouteTx(Packet::Ptr packet)
{
	Connector::PacketSignal& packetSignal = connector_.getPacketSignal();
	packetSignal(packet, Connector::Tx);

	Connector::PacketSignalTx& packetSignalTx = connector_.getPacketSignalTx();
	packetSignalTx(packet);
}

void ConnectorNotificationHandler::emitRouteEvent(unsigned long e)
{
	Connector::EventSignal& eventSignal = connector_.getEventSignal();
	eventSignal(e);
}

void ConnectorNotificationHandler::emitRouteQueueSignal(int current, int previous)
{
	Connector::QueueSignal& queueSignal = connector_.getQueueSignal();
	queueSignal(current, previous);
}

/*****************************
** AsyncConnectorNotificationHandler
******************************/

#define BIND_CALLBACK() \
	std::bind(&AsyncConnectorNotificationHandler::onThreadCallback, this)

AsyncConnectorNotificationHandler::AsyncConnectorNotificationHandler(Connector& connector)

	: ConnectorNotificationHandler(connector),
	  callbackThread_(BIND_CALLBACK(), 0, "AsyncConnectorNotificationHandler"),
	  callbackThreadManager_(callbackThread_, false, true),
	  notifyQueueEmpty_(false),
	  queueIsEmpty_(false)
{
}

AsyncConnectorNotificationHandler::~AsyncConnectorNotificationHandler()
{
	try
	{
		disableSignals();
	}
	catch (...)
	{
	}
}

/*
	When we disable the signals we want that the callbackThreadManager
	route the previous events from the queue.
	For this we enable notifyQueueEmpty and wait for queueIsEmpty.

	The callback function set queueIsEmpty when notifyQueueEmpty is enabled.

	NOTE:
	It's not possible that we do this here in this thread because
	we could produce deadlock when our application assumed then the
	notifications are in the notification thread and not in this
	thread context!
*/
void AsyncConnectorNotificationHandler::enableSignals(bool enabled)
{
	if (enabled != areSignalsEnabled())
	{
		ConnectorNotificationHandler::enableSignals(enabled);

		if (enabled)
		{
			callbackThreadManager_.start();
		}
		else
		{
			// wait until the queue is empty
			queueIsEmpty_ = false;
			notifyQueueEmpty_ = true;
			while (std::atomic_exchange_explicit(&queueIsEmpty_, true, std::memory_order_acquire))
			{
				// spin until acquired
				std::this_thread::yield();
			}
			notifyQueueEmpty_ = false;

			// the queue is empty so we could stop the callback thread
			callbackThreadManager_.stop();
		}
	}
}

void AsyncConnectorNotificationHandler::routeRx(Packet::Ptr packet)
{
	if (areSignalsEnabled())
	{
		PacketNotification::Ptr notification = std::make_shared<PacketNotification>(packet, Connector::Rx);
		enqueue(notification);
	}
}

void AsyncConnectorNotificationHandler::routeTx(Packet::Ptr packet)
{
	if (areSignalsEnabled())
	{
		PacketNotification::Ptr notification = std::make_shared<PacketNotification>(packet, Connector::Tx);
		enqueue(notification);
	}
}

void AsyncConnectorNotificationHandler::routeEvent(unsigned long e)
{
	if (areSignalsEnabled())
	{
		PacketNotification::Ptr notification = std::make_shared<PacketNotification>(e);
		enqueue(notification);
	}
}

void AsyncConnectorNotificationHandler::enqueue(PacketNotification::Ptr notification)
{
	queue_.push(notification);
}

void AsyncConnectorNotificationHandler::onThreadCallback()
{
	try
	{
		if (!queue_.empty())
		{
			const int queueSignalTrigger = getQueueSignalTrigger();
			const int queueSize = queue_.size();
			const int count = queueSize > queueSignalTrigger ? queueSignalTrigger : queueSize;
			int size = queueSize;
			int previousQueueSize = getPreviousQueueSize();

			for (int iter = 0; iter < count; ++iter)
			{
				--size;

				if (!(size % queueSignalTrigger) && (size != previousQueueSize))
				{
					poco_warning_f2(LOGGER(), "Queue Signal now %d was %d", size, previousQueueSize);
					emitRouteQueueSignal(size, previousQueueSize);
					setPreviousQueueSize(size);
				}

				PacketNotification::Ptr notification = queue_.front();
				queue_.pop();

				if (notification)
				{
					onNotification(notification);
				}
			}

			if (queue_.empty() && previousQueueSize)
			{
				// indicate that the queue is now empty
				poco_information_f1(LOGGER(), "Queue Empty was %d", previousQueueSize);
				emitRouteQueueSignal(0, previousQueueSize);
				setPreviousQueueSize(0);
			}
		}
		else
		{
			PacketNotification::Ptr notification = queue_.wait(100);
			if (notification)
			{
				onNotification(notification);
			}
		}
	}
	catch (Exception& exception)
	{
		poco_error_f1(LOGGER(), "onSignal: %s", exception.displayText());
	}
	catch (...)
	{
		poco_error(LOGGER(), "onSignal: unhandled exception");
	}

	if (queue_.empty() && notifyQueueEmpty_)
	{
		std::atomic_store_explicit(&queueIsEmpty_, false, std::memory_order_release);
	}
}

void AsyncConnectorNotificationHandler::onNotification(PacketNotification::Ptr notification)
{
	if (notification->isEventNotification())
	{
		emitRouteEvent(notification->getEvent());
	}
	else
	{
		Packet::Ptr packet = notification->getPacket();
		const int direction = notification->getDirection();

		if (direction == Connector::Rx)
		{
			emitRouteRx(packet);
		}
		else if (direction == Connector::Tx)
		{
			emitRouteTx(packet);
		}

		return;
	}
}
