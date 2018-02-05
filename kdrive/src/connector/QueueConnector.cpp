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
#include "kdrive/connector/QueueConnector.h"
#include "kdrive/connector/Packet.h"
#include "kdrive/connector/PacketNotification.h"
#include "kdrive/utility/Logger.h"
#include <Poco/Thread.h>
#include <Poco/Exception.h>

using Poco::Exception;
using Poco::NullPointerException;
using Poco::TimeoutException;
using Poco::FastMutex;
using Poco::ScopedLock;
using Poco::Thread;
using namespace kdrive::connector;

/***********************************
** QueueConnector
************************************/

CLASS_LOGGER("kdrive.connector.QueueConnector")

QueueConnector::QueueConnector()

	: rxQueue_(std::make_shared<NotificationQueue>()),
	  txQueue_(std::make_shared<NotificationQueue>()),
	  rxQueueEnabled_(false),
	  txQueueEnabled_(false),
	  maxQueueItems_(255),
	  txCallback_(std::bind(&QueueConnector::onTxThreadCallback, this), 0, "QueueConnector Tx", false),
	  rxCallback_(std::bind(&QueueConnector::rxImpl, this), 0, "QueueConnector Rx", false)
{
}

QueueConnector::QueueConnector(const PacketFactory::Ptr packetFactory)

	: Connector(packetFactory),
	  rxQueue_(std::make_shared<NotificationQueue>()),
	  txQueue_(std::make_shared<NotificationQueue>()),
	  rxQueueEnabled_(false),
	  txQueueEnabled_(false),
	  maxQueueItems_(255),
	  txCallback_(std::bind(&QueueConnector::onTxThreadCallback, this), 0, "QueueConnector Tx", false),
	  rxCallback_(std::bind(&QueueConnector::rxImpl, this), 0, "QueueConnector Rx", false)
{
}

QueueConnector::~QueueConnector()
{
}

void QueueConnector::send(Packet::Ptr packet)
{
	try
	{
		if (isTxQueueEnabled())
		{
			pushTx(packet);
		}
		else
		{
			txImpl(packet);
		}
	}
	catch (Exception& exception)
	{
		poco_error(LOGGER(), exception.displayText());
		throw;
	}
}

Packet::Ptr QueueConnector::receive()
{
	Packet::Ptr packet;
	while (!packet)
	{
		packet = wait(*rxQueue_, 1000, false);
	}
	return packet;
}

Packet::Ptr QueueConnector::waitReceive(long milliseconds)
{
	return wait(*rxQueue_, milliseconds);
}

void QueueConnector::clearRx()
{
	rxQueue_->clear();
}

void QueueConnector::clearTx()
{
	txQueue_->clear();
}

void QueueConnector::startTxThread(long threadDelay)
{
	enableTxQueue(true);
	txCallback_.start(threadDelay);
}

void QueueConnector::stopTxThread()
{
	enableTxQueue(false);
	txCallback_.stop();
}

CallbackThread& QueueConnector::getTxCallbackThread()
{
	return txCallback_.getCallbackThread();
}

const CallbackThread& QueueConnector::getTxCallbackThread() const
{
	return txCallback_.getCallbackThread();
}

void QueueConnector::startRxThread(long threadDelay)
{
	rxCallback_.start(threadDelay);
}

void QueueConnector::stopRxThread()
{
	rxCallback_.stop();
}

CallbackThread& QueueConnector::getRxCallbackThread()
{
	return rxCallback_.getCallbackThread();
}

const CallbackThread& QueueConnector::getRxCallbackThread() const
{
	return rxCallback_.getCallbackThread();
}

void QueueConnector::setMaxQueueItems(int maxQueueItems)
{
	ScopedLock<FastMutex> lock(mutex_);
	maxQueueItems_ = maxQueueItems;
}

void QueueConnector::enableRxQueue(bool enabled)
{
	ScopedLock<FastMutex> lock(mutex_);

	if (rxQueueEnabled_ != enabled)
	{
		rxQueueEnabled_ = enabled;

		if (rxQueueEnabled_)
		{
			addQueueUnsafe(rxQueue_.get());
		}
		else
		{
			removeQueueUnsafe(rxQueue_.get());
		}
	}
}

void QueueConnector::enableTxQueue(bool enabled)
{
	ScopedLock<FastMutex> lock(mutex_);
	txQueueEnabled_ = enabled;
}

bool QueueConnector::isRxQueueEnabled() const
{
	ScopedLock<FastMutex> lock(mutex_);
	return rxQueueEnabled_;
}

bool QueueConnector::isTxQueueEnabled() const
{
	ScopedLock<FastMutex> lock(mutex_);
	return txQueueEnabled_;
}

bool QueueConnector::isRxQueueFull() const
{
	ScopedLock<FastMutex> lock(mutex_);
	return rxQueue_->size() >= maxQueueItems_ ? true : false;
}

bool QueueConnector::isTxQueueFull() const
{
	ScopedLock<FastMutex> lock(mutex_);
	return txQueue_->size() >= maxQueueItems_ ? true : false;
}

int QueueConnector::rxQueueSize() const
{
	ScopedLock<FastMutex> lock(mutex_);
	return rxQueue_->size();
}

int QueueConnector::txQueueSize() const
{
	ScopedLock<FastMutex> lock(mutex_);
	return txQueue_->size();
}

void QueueConnector::wakeUpAllRxQueue()
{
	rxQueue_->wakeUpAll();
}

void QueueConnector::wakeUpAllTxQueue()
{
	txQueue_->wakeUpAll();
}

void QueueConnector::addQueue(NotificationQueue* notificationQueue)
{
	ScopedLock<FastMutex> lock(mutex_);
	addQueueUnsafe(notificationQueue);
}

void QueueConnector::removeQueue(NotificationQueue* notificationQueue)
{
	ScopedLock<FastMutex> lock(mutex_);
	removeQueueUnsafe(notificationQueue);
}

Packet::Ptr QueueConnector::waitQueue(NotificationQueue* notificationQueue, long milliseconds, bool validate)
{
	QueueConnector::validate(notificationQueue);
	return wait(*notificationQueue, milliseconds, validate);
}

void QueueConnector::routeRx(Packet::Ptr packet)
{
	if (packet)
	{
		pushRx(packet);
		Connector::routeRx(packet);
	}
}

void QueueConnector::closeImpl()
{
	stopRxThread();
	stopTxThread();
}

QueueConnector::NotificationQueue& QueueConnector::getRxQueue()
{
	return *rxQueue_;
}

const QueueConnector::NotificationQueue& QueueConnector::getRxQueue() const
{
	return *rxQueue_;
}

QueueConnector::NotificationQueue& QueueConnector::getTxQueue()
{
	return *txQueue_;
}

const QueueConnector::NotificationQueue& QueueConnector::getTxQueue() const
{
	return *txQueue_;
}

void QueueConnector::pushRx(Packet::Ptr packet)
{
	ScopedLock<FastMutex> lock(mutex_);

	for (NotificationQueue* q : queues_)
	{
		pushUnsafe(*q, packet, Connector::Rx);
	}
}

void QueueConnector::pushTx(Packet::Ptr packet)
{
	ScopedLock<FastMutex> lock(mutex_);

	if (txQueueEnabled_)
	{
		pushUnsafe(*txQueue_, packet, Connector::Tx);
	}
}

Packet::Ptr QueueConnector::wait(NotificationQueue& queue, long milliseconds, bool throwOnNullPacket)
{
	Packet::Ptr packet;
	PacketNotification::Ptr notification(queue.wait(milliseconds));

	if (notification)
	{
		// we assume all notifications on this queue are packet notifications
		// and not event notifications
		// if an event notification packet will be null
		packet = notification->getPacket();
	}

	if (!packet && throwOnNullPacket)
	{
		poco_trace(LOGGER(), "Timeout on waiting for packet queue notification");
		throw TimeoutException();
	}

	return packet;
}

void QueueConnector::txImpl(Packet::Ptr packet)
{
	poco_warning(LOGGER(), "txImpl default implementation, packet not sent");
}

void QueueConnector::rxImpl()
{
	poco_warning(LOGGER(), "rxImpl default implementation, packet not received");
	Thread::sleep(timeout_);
}

void QueueConnector::onTxThreadCallback()
{
	try
	{
		Packet::Ptr packet = wait(getTxQueue(), timeout_, false);

		if (packet)
		{
			txImpl(packet);
		}
	}
	catch (Exception& exception)
	{
		poco_error_f1(LOGGER(), "txImpl (thread) failed: %s", exception.displayText());
	}
}

void QueueConnector::pushUnsafe(NotificationQueue& queue, Packet::Ptr packet, int direction)
{
	if (queue.size() < maxQueueItems_)
	{
		PacketNotification::Ptr notification = std::make_shared<PacketNotification>(packet, direction);
		queue.push(notification);
	}
}

void QueueConnector::addQueueUnsafe(NotificationQueue* notificationQueue)
{
	queues_.push_back(notificationQueue);
}

void QueueConnector::removeQueueUnsafe(NotificationQueue* notificationQueue)
{
	std::vector<NotificationQueue*>::iterator i =
	    std::find(queues_.begin(), queues_.end(), notificationQueue);

	if (i != queues_.end())
	{
		queues_.erase(i);
	}
}

void QueueConnector::validate(NotificationQueue* notificationQueue)
{
	if (!notificationQueue)
	{
		poco_error(LOGGER(), "Precondition Failed: NotificationQueue is null");
		throw NullPointerException("NotificationQueue");
	}
}

/***********************************
** ScopedQueueConnectorRxQueue
************************************/

ScopedQueueConnectorRxQueue::ScopedQueueConnectorRxQueue(QueueConnector& queueConnector)

	: queueConnector_(queueConnector),
	  queue_(std::make_shared<QueueConnector::NotificationQueue>())
{
	queueConnector_.addQueue(queue_.get());
}

ScopedQueueConnectorRxQueue::~ScopedQueueConnectorRxQueue()
{
	queueConnector_.removeQueue(queue_.get());
}

void ScopedQueueConnectorRxQueue::send(Packet::Ptr packet)
{
	queueConnector_.send(packet);
}

Packet::Ptr ScopedQueueConnectorRxQueue::receive()
{
	Packet::Ptr packet;
	while (!packet)
	{
		packet = queueConnector_.waitQueue(queue_.get(), 1000, false);
	}
	return packet;
}

Packet::Ptr ScopedQueueConnectorRxQueue::waitReceive(long milliseconds)
{
	return queueConnector_.waitQueue(queue_.get(), milliseconds, true);
}
