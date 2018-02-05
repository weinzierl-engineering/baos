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

#ifndef __KDRIVE_CONNECTOR_QUEUE_CONNECTOR_H__
#define __KDRIVE_CONNECTOR_QUEUE_CONNECTOR_H__

#include "kdrive/connector/Config.h"
#include "kdrive/connector/Connector.h"
#include "kdrive/connector/CallbackThread.h"
#include <Poco/Mutex.h>
#include <vector>
#include <memory>

namespace kdrive
{
namespace connector
{

class PacketNotificationQueue;
class CallbackThread;

/***********************************
** QueueConnector
************************************/

/*!
	\class QueueConnector

	QueueConnector implements separate Rx and Tx notification queues
	and optional Rx and Tx threads

	Send is implemented either via adding the packet to the Tx queue (if enabled)
	or by calling txImpl directly. The Tx thread waits on a packet and calls
	txImpl so derived classes can handle txImpl without having to know whether
	it is called from the thread or not. In this way we can quickly change between
	blocking sends and async send (with a thread)

	Receive is always implemented via the Rx Queue, regardless of whether the
	rx thread is enabled or not.
*/
class kdriveConnector_API QueueConnector : public Connector
{
public:
	using Ptr = std::shared_ptr<QueueConnector>;
	using NotificationQueue = PacketNotificationQueue;

	/*!
		Creates a default Connector with standard Packet Factory

		The Rx thread is disabled and the Rx queue is disabled
		The Tx thread is disabled and the Tx queue is disabled
	*/
	QueueConnector();

	/*!
		Creates a Connector with a specified packet factory

		The Rx thread is disabled and the Rx queue is disabled
		The Tx thread is disabled and the Tx queue is disabled
	*/
	QueueConnector(PacketFactory::Ptr packetFactory);

	/*!
		Destructs the Connector
	*/
	virtual ~QueueConnector();

	/*******************************************
	** Connector Interface for send and receive
	********************************************/

	/*!
		Sends a packet on the connector
		If the tx queue is enabled we add the packet to the queue
		And the tx thread will wait on the queue and call txImpl
		If the tx queue is not enabled we call txImpl directly.
	*/
	void send(std::shared_ptr<Packet> packet) override;

	/*!
		Default implementation of receive.
		Simply waits on the Rx queue
		Note: for this function to work you have to call
		enableRxQueue(true) before calling this function
	*/
	std::shared_ptr<Packet> receive() override;

	/*!
		Default implementation of a timed receive.
		Waits on the Rx queue
		Note: for this function to work you have to call
		enableRxQueue(true) before calling this function
	*/
	std::shared_ptr<Packet> waitReceive(long milliseconds) override;

	/*!
		clears the receive queue
	*/
	void clearRx() override;

	/*!
		clears the transmit queue
	*/
	void clearTx() override;

	/*******************************************
	** Thread Management
	********************************************/

	/*!
		Starts the tx thread. We use the connector ActiveFunction
		to handle the thread management, it starts a thread and periodically calls
		sendTx until we call stopSendThread
		We enable the tx queue so we can wait on it in our thread.
	*/
	virtual void startTxThread(long threadDelay = 0);

	/*!
		Stops the Tx thread
	*/
	virtual void stopTxThread();

	/*!
		Returns the Tx callback thread
		Use this if you need to set the thread signals
	*/
	CallbackThread& getTxCallbackThread();

	/*!
		Returns the Tx callback thread
		Use this if you need to set the thread signals
	*/
	const CallbackThread& getTxCallbackThread() const;

	/*!
		Starts the Rx thread, periodically calls rxImpl
		rxImpl should handle receiving the packet and calling route rx
	*/
	virtual void startRxThread(long threadDelay = 0);

	/*!
		Stops the Rx thread
	*/
	virtual void stopRxThread();

	/*!
		Returns the Rx callback thread
		Use this if you need to set the thread signals
	*/
	CallbackThread& getRxCallbackThread();

	/*!
		Returns the Rx callback thread
		Use this if you need to set the thread signals
	*/
	const CallbackThread& getRxCallbackThread() const;

	/*******************************************
	** Queue Management
	********************************************/

	/*!
		Sets the maximum number of items that can be pushed
		to either the Rx or Tx queue
		By default this is 255
	*/
	void setMaxQueueItems(int maxQueueItems);

	/*!
		Enables the Rx queue. If disabled the queue will not accept a packet
		You can disabled a queue if your application does not need it
		i.e. for example, if you use the packet notification signals to receive
		a packet you can safely disable the queues
	*/
	void enableRxQueue(bool enabled = true);

	/*!
		Enables the Tx queue. If disabled the queue will not accept a packet
		You can disabled a queue if your application does not need it
		i.e. for example, if you use the packet notification signals to receive
		a packet you can safely disable the queues
	*/
	void enableTxQueue(bool enabled = true);

	/*!
		Returns true if the Rx queue is enabled
	*/
	bool isRxQueueEnabled() const;

	/*!
		Returns true if the Tx queue is enabled
	*/
	bool isTxQueueEnabled() const;

	/*!
		Returns true if the Rx queue is full
		That is, queue size is equal to max queue items
	*/
	bool isRxQueueFull() const;

	/*!
		Returns true if the Tx queue is full
		That is, queue size is equal to max queue items
	*/
	bool isTxQueueFull() const;

	/*!
		Returns the number of items in the rx queue
	*/
	int rxQueueSize() const;

	/*!
		Returns the number of items in the tx queue
	*/
	int txQueueSize() const;

	/*!
		Wake up the rx queue : unblock the listener waiting on the queue
	*/
	void wakeUpAllRxQueue();

	/*!
		Wake up the tx queue : unblock the listener waiting on the queue
	*/
	void wakeUpAllTxQueue();

	/*******************************************
	** External Queue Management
	********************************************/

	/*!
		Adds a new queue to the list of Rx notification queues
	*/
	void addQueue(NotificationQueue* notificationQueue);

	/*!
		Removes a queue from the list of Rx notification queues
	*/
	void removeQueue(NotificationQueue* notificationQueue);

	/*!
		Waits on a queue, if validate it true throws and exception
		otherwise returns a null packet
	*/
	std::shared_ptr<Packet> waitQueue(NotificationQueue* notificationQueue, long milliseconds, bool validate = true);

	/*!
		When we route a rx packet we add it to the rx queue (if enabled)
		and give it to the connector to give to the notification thread
	*/
	void routeRx(std::shared_ptr<Packet> packet) override;

protected:
	/*!
		closeImpl
		Closes the rx and tx threads
	*/
	void closeImpl() override;

	/*!
		Returns the rx queue
	*/
	NotificationQueue& getRxQueue();

	/*!
		Returns the (const) rx queue
	*/
	const NotificationQueue& getRxQueue() const;

	/*!
		Returns the tx queue
	*/
	NotificationQueue& getTxQueue();

	/*!
		Returns the (const) tx queue
	*/
	const NotificationQueue& getTxQueue() const;

	/*!
		Adds a packet to the rx queue if enabled
	*/
	void pushRx(std::shared_ptr<Packet> packet);

	/*!
		Adds a packet to the tx queue if enabled
	*/
	void pushTx(std::shared_ptr<Packet> packet);

	/*!
		Timed wait on a queue
		If validate is true and exception will be thrown if a packet is not received
	*/
	std::shared_ptr<Packet> wait(NotificationQueue& queue, long milliseconds, bool validate = true);

private:
	/*!
		Send Implementation function
		This function is called from the Tx Thread if enabled
		If not, send will call this function directly.
		Derived classes should override this to send
	*/
	virtual void txImpl(std::shared_ptr<Packet> packet);

	/*!
		Receive Implementation function
		This function is called from the Rx Thread if enabled
		Derived classes should handle receiving the packet
		(i.e. raw bytes) creating the packet with the packet
		factory and calling route rx.
		We do nothing here but sleep a bit...
	*/
	virtual void rxImpl();

	/*!
		Called periodically from the Tx Thread when it is active
		We wait on the Tx buffer and if we have a packet we pass it onto
		txImpl(...)
	*/
	void onTxThreadCallback();

	/*!
		Adds a packet to a queue, if enabled
	*/
	void pushUnsafe(NotificationQueue& queue, std::shared_ptr<Packet> packet, int direction);

	/*!
		Adds a new queue to the list of notification queues
		Does not check for duplicates!
	*/
	void addQueueUnsafe(NotificationQueue* notificationQueue);

	/*!
		Removes a queue from the list of notification queues
		If the queue is not in the list nothing happens
	*/
	void removeQueueUnsafe(NotificationQueue* notificationQueue);

	/*!
		Validates that a queue pointer exists
		Throws a NullPointerException if notificationQueue is null
	*/
	void validate(NotificationQueue* notificationQueue);

private:
	std::shared_ptr<NotificationQueue> rxQueue_;
	std::shared_ptr<NotificationQueue> txQueue_;
	std::vector<NotificationQueue*> queues_;
	bool rxQueueEnabled_;
	bool txQueueEnabled_;
	std::size_t maxQueueItems_;
	static const int timeout_ = 1000;
	ActiveFunction txCallback_;
	ActiveFunction rxCallback_;
	mutable Poco::FastMutex mutex_;
};

/***********************************
** ScopedQueueConnectorRxQueue
************************************/

/*!
	ScopedQueueConnectorRxQueue
*/
class kdriveConnector_API ScopedQueueConnectorRxQueue : public Connector
{
public:
	ScopedQueueConnectorRxQueue(QueueConnector& queueConnector);
	~ScopedQueueConnectorRxQueue();

	/*!
		Sends the contents of the packet
	*/
	void send(std::shared_ptr<Packet> packet) override;

	/*!
		generates a packet, blocks until a packet is received
	*/
	std::shared_ptr<Packet> receive() override;

	/*!
		generates a packet
		throws TimeoutException if a packet is
		not received in the specified time
	*/
	std::shared_ptr<Packet> waitReceive(long milliseconds) override;

private:
	QueueConnector& queueConnector_;
	std::shared_ptr<QueueConnector::NotificationQueue> queue_;
};

}
} // end namespace kdrive::connector

#endif // __KDRIVE_CONNECTOR_QUEUE_CONNECTOR_H__
