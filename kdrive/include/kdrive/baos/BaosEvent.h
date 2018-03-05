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

#ifndef __KDRIVE_BAOS_EVENT_H__
#define __KDRIVE_BAOS_EVENT_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/Forwards.h"
#include "kdrive/connector/Packet.h"
#include <Poco/Mutex.h>
#include <boost/signals2.hpp>
#include <functional>

namespace kdrive
{
namespace baos
{

class BaosDatapoint;

/*!
	\class BaosEvent

	BaosEvent connects to the rx packet signals from the BaosConnector
	and filters the received packets to forward the datapoint value indications
	and the datapoint get value responses to a single handler. This has the advantage
	that you can handle the asynchronous events from the bus as well as the responses
	to a read request (for example at application startup) with the same code handler.
*/
class kdriveRPC_baos_API BaosEvent
{
public:
	/*!
		Creates a default BaosEvent
		It is disabled by default and must be enabled
		once the connector is set
	*/
	BaosEvent();

	/*!
		Creates a BaosEvent class associated
		with a connection
	*/
	BaosEvent(std::shared_ptr<BaosConnector> connector, bool enabled = true);

	/*!
		Destroys the BaosEvent.
		The connector will be released.
	*/
	~BaosEvent();

	/*!
		Callback function called when a datapoint value is changed.
		This can be either via a DatapointIndication or one
		of the services, such as DatapointValueSet.
	*/
	typedef std::function<void (BaosDatapoint&)> DatapointEvent;
	void setDatapointEvent(DatapointEvent datapointEvent);

	/*!
		Callback function called when a server value indication is
		received.
	*/
	typedef std::function<void(unsigned short, const std::vector<unsigned char>&)> ServerItemEvent;
	void setServerItemEvent(ServerItemEvent serverItemEvent);

	/*!
		Callback function called when a server value indication is
		received to indicate whether the bus is connected or not
	*/
	typedef std::function<void (bool)> BusConnectedEvent;
	void setBusConnectedEvent(BusConnectedEvent busConnectedEvent);

	/*!
		Callback function called when the connector is disconnected
	*/
	typedef std::function<void ()> ConnectorClosedEvent;
	void setConnectorClosedEvent(ConnectorClosedEvent connectorClosedEvent);

	/*!
		Sets the baos connector. If a connector has already been
		set we disconnect from its signals
	*/
	void setConnector(std::shared_ptr<BaosConnector> connector, bool enabled = true);

	/*!
		Enable/disable the events.
	*/
	void enable(bool enabled = true);

	/*!
		Disable the events
	*/
	void disable();

	/*!
		\return true if enabled, false otherwise
	*/
	bool isEnabled() const;

private:
	/*!
		Connects to the packet signals
	*/
	void connect();

	/*!
		Disconnect from the packet signals
	*/
	void disconnect();

	/*!
		Called when a packet is received from the connector
	*/
	void onPacket(connector::Packet::Ptr packet);

	/*!
		Called when a baos data packet is received from the connector
	*/
	void onDataPacket(std::shared_ptr<DataPacket> dataPacket);

	/*!
		Called when a SetDatapointValue request is sent or a
		GetDatapointValue response is received
	*/
	void onDatapointValue(std::shared_ptr<DataPacket> dataPacket);

	/*!
		Called when a ServerItemIndication is received
	*/
	void onServerItemIndication(std::shared_ptr<DataPacket> dataPacket);

	/*!
		Called when the connector receive thread is stopped
	*/
	void onCallbackThreadEvent();

	/*!
		Sets the enabled status.
		If enabled we connect to the connector signals
		otherwise we disconnect from them.
		precondition: if enabled is true, connector is not null
	*/
	void setEnabled(bool enabled);

private:
	std::shared_ptr<BaosConnector> connector_;
	DatapointEvent datapointEvent_;
	ServerItemEvent serverItemEvent_;
	BusConnectedEvent busConnectedEvent_;
	ConnectorClosedEvent connectorClosedEvent_;
	mutable Poco::FastMutex mutex_;
	bool enabled_;
	boost::signals2::scoped_connection packetSignalConnection_; /*! Signal connection for packet signal. */
	boost::signals2::scoped_connection connectorConnected_; /*! Signal connection for packet signal. */
	boost::signals2::scoped_connection connectorDisconnected_; /*! Signal connection for packet signal. */
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_EVENT_H__
