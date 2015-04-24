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

#ifndef __KDRIVE_CONNECTOR_CONNECTOR_H__
#define __KDRIVE_CONNECTOR_CONNECTOR_H__

#include "kdrive/connector/Config.h"
#include "kdrive/connector/Forwards.h"
#include "kdrive/connector/PacketFactory.h"
#include "kdrive/utility/PropertyCollection.h"
#include <Poco/Semaphore.h>
#include <Poco/Mutex.h>
#include <boost/signals2.hpp>
#include <string>
#include <vector>
#include <memory>

namespace kdrive
{
namespace connector
{

class ConnectorNotificationHandler;

/*!
	\class Connector

	A Connector can send and receive packets. This is an abstract
	interface and doesn't define a medium for the transmission
	and reception of packets.

	A Connector has a packet factory
	It is assumed that a raw rx buffer (unsigned char for example)
	is used to receive a packet from the wire and we convert the
	buffer into a packet with the packet factory.
	Packet Factory is mandatory, and if the default constructor is
	called a default packet factory is created, which will simply
	create an unknown Packet (Packet).

	A Connector has a number of packet signals (boost signals)
	The packet signals can be used to notify of rx and tx packets events
	and support multiple listeners. The signals are called from the
	NotificationHandler (see ConnectorNotificationHandler). By default
	the connector uses the AsyncConnectorNotificationHandler
	so all notifications are called from a dedicated notification thread.
	Use ConnectorNotificationHandler to invoke the notifications synchronously
	(i.e. from the thread context that they were raised in). You can also
	set a custom notification handler.
*/
class kdriveConnector_API Connector : public kdrive::utility::PropertyCollection
{
public:
	typedef std::shared_ptr<Connector> Ptr;
	typedef std::shared_ptr<ConnectorNotificationHandler> NotificationHandlerPtr;
	typedef boost::signals2::signal<void (std::shared_ptr<Packet>, int)> PacketSignal;
	typedef boost::signals2::signal<void (std::shared_ptr<Packet>)> PacketSignalDirectional;
	typedef boost::signals2::signal<void (unsigned long)> EventSignal;
	typedef boost::signals2::signal<void (int, int)> QueueSignal; /*!< Called when the queue grows with current and previous sizes */
	typedef PacketSignalDirectional PacketSignalRx;
	typedef PacketSignalDirectional PacketSignalTx;
	typedef kdrive::utility::PropertyCollection PropertyCollection;

	/*!
		When port enumeration is performed a property collection
		for each found / valid port is returned. This list
		is defined as a vector of PropertyCollection and is
		defined as Ports
	*/
	typedef std::vector<PropertyCollection> Ports;

	enum PacketDirection
	{
	    Rx = 0,
	    Tx = 1
	};

	/*!
		Creates a default Connector with a standard Packet Factory
	*/
	Connector();

	/*!
		Creates a Connector with a specified packet factory
	*/
	Connector(PacketFactory::Ptr packetFactory);

	/*!
		Copy constructor
	*/
	Connector(const Connector& connector);

	/*!
		Destructs the Connector
	*/
	virtual ~Connector();

	/*!
		assignment operator
	*/
	Connector& operator=(const Connector& connector);

	/*!
		Opens an Connector.
		Most connectors will require one or more parameters
		to identify the remote port, such as an IP Address or
		device name. This information is managed by the property
		system. Derived connectors can provide an open with
		the requested parameters (device name etc) which should be
		saved as properties followed by a call to open(). Open
		looks to ensure that the connector isn't already open
		and calls openImpl() to handle the device specific open
		(handled by derived classes).

		The default implementation is to do nothing (in openImpl)
		and simply set the open flag to true. If a port is already open
		nothing happens, and the function simply returns.

		It invokes the openingSignal before opening the connector
		(before the call to openImpl) and after the port has been opened
		(after openImpl successfully returns) openedSignal will be invoked.
		In the event of	an error the derived class may thrown an exception,
		in which case the openedSignal will not be called.

		\note there is a special case where you can get into a deadlock when
		wrapping a connector and the event signal notification with a mutex
		You have to ensure that the destructor can be run from outside of the mutex
		for example: doing this is potentially bad:

		\code
			void my_open()
			{
				ScopedLock<FastMutex> lock(mutex_);
				Connector::Ptr port = std::make_shared<TunnelingPort>();
				port->open(ip_);

				// assign to the access port only if successfully opened
				port_ = port;
			}

			void notification_signal(int e)
			{
				ScopedLock<FastMutex> lock(mutex_);
				do_something_with_event(e);
			}
		\endcode

		The deadlock occurs in this instance int the destructor of the TunnelingPort
		when open is not successful. The destructor calls close which
		raises the Notification Event (Closing, Closed etc). However the mutex is
		already locked in my_open, and the boost signal instance can't be destructed
		until the signal handler has finished, which blocks on the mutex...

		Resolution:

		Simply ensure that Connector::Ptr port is declared outside of the mutex.
		For example:

		\code
			void my_open()
			{
				Connector::Ptr port = std::make_shared<TunnelingPort>();
				port->open(ip_);

				// assign to the access port only if successfully opened
				ScopedLock<FastMutex> lock(mutex_);
				port_ = port;
			}
		\endcode
	*/
	virtual void open();

	/*!
		Closes a connector. Close is implemented by derived classes
		by overriding closeImpl. The default implementation is to do
		nothing and simply set the open flag to false.
		If a port is already closed nothing happens.
		Sends signal closing and closed.
	*/
	virtual void close();

	/*!
		Returns true if a port is open, false otherwise.
		We can't simply return the open flag as the port
		may have closed at some point, so we call isOpenImpl
		which can be implemented by the derived class.
		Otherwise we simply return the current open status.
	*/
	virtual bool isOpen() const;

	/*!
		Sends the contents of the packet
	*/
	virtual void send(std::shared_ptr<Packet> packet);

	/*!
		If this is supported by the connector it will
		block until a packet is received
		If this is not supported by the connector it will
		immediately return a null std::shared_ptr<Packet>
	*/
	virtual std::shared_ptr<Packet> receive();

	/*!
		If this is supported by the connector it will
		block until a packet it received or
		the timeout (milliseconds) elapses
		throws TimeoutException if a packet is
		not received in the specified time
		If this is not supported by the connector it will
		immediately return a null std::shared_ptr<Packet>
	*/
	virtual std::shared_ptr<Packet> waitReceive(long milliseconds);

	/*!
		Empty the receive queue/buffer etc, implementation specific
		This function does nothing unless overridden
	*/
	virtual void clearRx();

	/*!
		Empty the transmit queue/buffer etc, implementation specific
		This function does nothing unless overridden
	*/
	virtual void clearTx();

	/*!
		Returns a formatted connector description
	*/
	virtual std::string getDescription();

	/*!
		Copy and overwrite properties (typically obtained from port enumeration)
		to the internal property map.
	 */
	void setProperties(const PropertyCollection& propertyCollection);

	/*!
		Resets the properties to the default values or rather remove it from the property collection
		Use this if you want to reopen with another interface.

		For example:

		\code
			TunnelingPort::Ptr port = std::make_shared<TunnelingPort>();
			port->open("192.168.1.35", "192.168.1.1");

			// ...

			port->close();
			port->resetProperties();

			port->open("192.168.1.50", "192.168.1.1");

			// ...
		\endcode
	*/
	void resetProperties();

	/*!
		Enumerate the ports for the specific Access Port Type.
		Return a list with possible ports.
		This must be supported by the derived class type
		otherwise an empty list will be returned.
	*/
	void enumerate(Ports& ports);

	/*!
		Returns the access port type
	*/
	std::string getConnectorType() const;

	/*!
		Set the preferred port settings
	*/
	void setPreferredSettings();

	/*!
		Returns the last error code.
	*/
	unsigned int getLastErrorCode() const;

	/*!
		Returns the last error message.
	*/
	std::string getLastErrorMessage() const;

	/*!
		Returns the packet signal
	*/
	PacketSignal& getPacketSignal();

	/*!
		Returns the Rx packet signal
	*/
	PacketSignalRx& getPacketSignalRx();

	/*!
		Returns the Tx packet signal
	*/
	PacketSignalTx& getPacketSignalTx();

	/*!
		Returns the Event signal
	*/
	EventSignal& getEventSignal();

	/*!
		Returns the Queue signal
	*/
	QueueSignal& getQueueSignal();

	/*!
		Signals can be enabled or disabled.
		If enabled the notification signals are started
		If disabled the notification signals are stopped
		Signal notification is disabled by default
	*/
	void enableSignals(bool enable = true);

	/*!
		Disables the notification signals
	*/
	void disableSignals();

	/*!
		Returns true if the notification signals
		are enabled otherwise false.
	*/
	bool areSignalsEnabled() const;

	/*!
		Sets the packet factory
		Precondition: packetFactory is not NULL
	*/
	void setPacketFactory(PacketFactory::Ptr packetFactory);

	/*!
		returns the packet factory
	*/
	PacketFactory::Ptr getPacketFactory();

	/*!
		Locks the connector
		If the connector is shared across multiple threads
		you can use the wait and set mechanism to restrict
		access (i.e. using a semaphore)
	*/
	void waitSem();

	/*!
		Locks the connector
		Throws a TimeoutException if wait can not
		lock the connector within the timeout
	*/
	void waitSem(long milliseconds);

	/*!
		Tries to lock the semaphore within the specified period
		Returns true if the semaphore was locked, false otherwise
		No exception is thrown
	*/
	bool tryWaitSem(long milliseconds);

	/*!
		Sets the semaphore
	*/
	void setSem();

	/*!
		Used to determine when to call the Queue overloaded Signal
		Used as: queue size % trigger
		If 0 (i.e. the queue size is a multiple of trigger) the signal
		will be called. Set initially (by default) to 25
	*/
	void setQueueSignalTrigger(int queueSignalTrigger);

	/*!
		Routes a rx packet to the notification signal
		If the signal notifcation thread is active
		the packet will be placed on the notification queue
		and handled in the notification thread
		Otherwise it will be ignored
	*/
	virtual void routeRx(std::shared_ptr<Packet> packet);

	/*!
		Routes a tx packet to the notification signal
		If the signal notifcation thread is active
		the packet will be placed on the notification queue
		and handled in the notification thread
		Otherwise it will be ignored
	*/
	virtual void routeTx(std::shared_ptr<Packet> packet);

	/*!
		Routes an event to the notification signal
		If the signal notifcation thread is active
		the event will be placed on the notification queue
		and handled in the notification thread
		Otherwise it will be ignored
	*/
	virtual void routeEvent(unsigned long e);

	/*!
		Sets a custom NotificationHandler
	*/
	void setNotificationHandler(NotificationHandlerPtr notificationHandler);

public:
	static const std::string PortType;
	static const std::string ConnectorTypeLabel;
	static const std::string LastErrorCode;			/*!< Property Key for LastErrorCode */
	static const std::string LastErrorMessage;		/*!< Property Key for LastErrorMessage */

protected:
	/*!
		Called when a property is modified
		We raise the PropertyModified event
	*/
	virtual void setPropertyUnsafe(const std::string& key, const Poco::Dynamic::Var& value);

	/*!
		Calls the packet factory to create a Packet from the raw buffer
	*/
	virtual std::shared_ptr<Packet> create(const unsigned char* buffer, std::size_t bufferLength);

	/*!
		Returns the connector notification handler
		If the notification handler is null it creates a default
		AsyncConnectorNotificationHandler
	*/
	ConnectorNotificationHandler& getNotificationHandler();

	/*!
		Returns the connector notification handler
		If the notification handler is null it creates a default
		AsyncConnectorNotificationHandler
	*/
	const ConnectorNotificationHandler& getNotificationHandler() const;

	/*!
		Closes the connection
		Unsafe because it isn't protected by the mutex
		This function is typically called from close
	*/
	void closeUnsafe();

	/*!
		Sets the last error code.
	*/
	void setLastErrorCode(unsigned int errorCode);

	/*!
		Sets the last error message.
	*/
	void setLastErrorMessage(const std::string& errorMessage);

	/*!
		Sets the properties LastErrorCode and LastErrorMessage,
		Sends an error event and re-throws the Exception.
	*/
	void raiseError(const Poco::Exception& exception);

	/*!
		Should be overridden by derived classes that need to handle resetProperties
		The default removes all proeprties and readded following properties with default values:
		- PropertyKeys::PortType: AccessPort::AccessPortTypeLabe
		- LastErrorCode: AccessPortErrorCodes::None
		- LastErrorMessage: ""
	*/
	virtual void resetPropertiesImpl();

	/*!
		Should be overridden by derived classes that need to handle enumerate
		The default is to do nothing
	*/
	virtual void enumerateImpl(Ports& ports);

	/*!
		Should be overridden by derived classes that need to handle open
		The default is to do nothing
	*/
	virtual void openImpl();

	/*!
		Should be overridden by derived classes that need to handle close
		The default is to do nothing
	*/
	virtual void closeImpl();

	/*!
		Should be overridden by derived classes that need to handle isOpen
		The default is to simply return the current open status
	*/
	virtual bool isOpenImpl() const;

	/*!
		Should be overridden by derived classes that need to handle setPreferredSettings
		The default is to do nothing
	*/
	virtual void setPreferredSettingsImpl();

private:
	void setPacketProperties(std::shared_ptr<Packet> packet);

private:
	mutable Poco::FastMutex mutex_;
	PacketFactory::Ptr packetFactory_;
	Poco::Semaphore semaphore_;
	PacketSignal packetSignal_;
	PacketSignalRx packetSignalRx_;
	PacketSignalTx packetSignalTx_;
	EventSignal eventSignal_;
	QueueSignal queueSignal_;
	mutable bool open_;
	mutable NotificationHandlerPtr notificationHandlerPtr_;
	friend kdriveConnector_API void raiseError(Connector& connector, const Poco::Exception& exception);

	// semaphore defaults, change as required,
	// not exposed to the outside world
	static const int n = 1;
	static const int max = 10;
};

/*!
	Sets the properties LastErrorCode and LastErrorMessage,
	Sends an error event and re-throws the Exception.
*/
kdriveConnector_API void raiseError(Connector& connector, const Poco::Exception& exception);

}
} // end namespace kdrive::connector

#endif // __KDRIVE_CONNECTOR_CONNECTOR_H__
