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

#ifndef __KDRIVE_BAOS_STREAM_STREAM_CONNECTOR_H__
#define __KDRIVE_BAOS_STREAM_STREAM_CONNECTOR_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/BaosConnector.h"
#include "kdrive/baos/core/Forwards.h"
#include "kdrive/baos/core/API.h"
#include <Poco/Timer.h>
#include <Poco/Timestamp.h>
#include <Poco/Mutex.h>
#include <Poco/Net/StreamSocket.h>
#include <array>
#include <memory>
#include <string>
#include <tuple>

namespace kdrive
{
namespace baos
{

/*!
	\class StreamConnector
	\brief The StreamConnector is responsible for creating
	a TCP/IP stream connection with the baos server

	The StreamConnector is responsible for creating a TCP/IP socket connection
	to the remote BAOS device. It requires the IP Address of the device.

	It implements a connect and a disconnect signal. These signals are invoked
	when the stream connection is connector and disconnected respectively.

	StreamConnector automatically keeps the TCP/IP connection alive.
	The remote device will close the connection if not activity is
	noticed within a 2 minute period.
*/

class kdriveRPC_baos_API StreamConnector : public BaosConnector
{
public:
	typedef std::shared_ptr<StreamConnector> Ptr;

	StreamConnector() = delete;
	StreamConnector(unsigned char version);
	StreamConnector(unsigned char version, const std::string& remoteHost, unsigned short port = StreamProtocolConstants::Port);
	StreamConnector(const StreamConnector&) = delete;
	virtual ~StreamConnector();

	StreamConnector& operator=(const StreamConnector&) = delete;

	/*!
		Opens a connection
		using the IpAddress and IpPort properties
	*/
	using BaosConnector::open;

	/*!
		Opens a connection
	*/
	void open(const std::string& remoteHost, unsigned short port = StreamProtocolConstants::Port);

	/*!
		Returns a formatted port description.
		Format: Baos on <IpAddress>
		e.g. 192.168.1.200
	*/
	virtual std::string getDescription();

	/*!
		Sets the IPv4 address from a BAOS device.
		This function do not read/write anything from/to the BAOS device.
		This property do not changed the IP address of a BAOS device.
		It were used to specified to which device should connect on open().
		\warning Should only set if the connection is closed.
		\param[in] ipAddress The IPv4 address. e.g. "192.168.1.30"
	*/
	void setIpAddress(const std::string& ipAddress);

	/*!
		Gets the IPv4 address from the BAOS device.
		This function do not read/write anything from/to the BAOS device.
		\return The IPv4 address. e.g. "192.168.1.30"
	*/
	std::string getIpAddress() const;

	/*!
		Sets the port number from the server (BAOS device).
		This function do not read/write anything from/to the BAOS device.
		This property do not changed the port number of a BAOS device.
		It were used to specified to which device should connect on open().
		The default value is 12004 = BAOS Port Number
		\warning Should only set if the connection is closed.
		\param[in] port The port number. e.g. 12004
	*/
	void setIpPort(unsigned short port);

	/*!
		Gets the port number from the server (BAOS device).
		This function do not read/write anything from/to the BAOS device.
		\return The port number. e.g. 12004
	*/
	unsigned short getIpPort() const;

public:
	static const std::string ConnectorTypeLabel;
	static const std::string IpAddress; /*!< Property Key for device IPv4 address. */
	static const std::string IpPort; /*!< Property Key for device IPv4 port */

protected:
	int readFromSocket(unsigned char* buffer, int maxBytesToRead);
	int readFromSocket(unsigned char* buffer, std::size_t bufferSize, int bytesToRead, bool validate);

	enum Defaults
	{
	    BufferSize = 2048,
	};

private:
	/*
		Opens the socket, starts the rx thread and the heartbeat
	*/
	virtual void openImpl();

	/*
		Closes the socket, stops the rx thread and the heartbeat
	*/
	virtual void closeImpl();

	/*!
		Calls resetPropertiesImpl from BaosConnector and
		readded following properties with default values:
		- StreamConnector::PortType: StreamConnector::ConnectorTypeLabel
		- IpAddress: ""
		- IpPort: StreamProtocolConstants::Port
	*/
	virtual void resetPropertiesImpl();

	/*!
		Encapsulate the packet and send it to the socket
	*/
	virtual void txImpl(connector::Packet::Ptr packet);

	/*!
		Encapsulate the packet to the specific BAOS version
	*/
	virtual std::size_t encapsulate(const connector::Packet::Ptr packet, unsigned char* buffer, std::size_t bufferSize) = 0;

	/*!
		Starts the heartbeat timer
	*/
	void startHeartbeatTimer();

	/*!
		Shutdown the socket
	*/
	void shutdownSocket();

	/*!
		Do the heartbeat. Sends for this a GetServerItem request and waits for the response
	*/
	void doHeartbeat();

	/*!
		Will called from the heartbeat timer
	*/
	void onHeartbeatTimer(Poco::Timer& timer);

private:
	mutable Poco::FastMutex txMutex_;
	Poco::Net::StreamSocket socket_;
	std::array<unsigned char, BufferSize> txBuffer_;
	Poco::Timer heartbeatTimer_;
	Poco::Timestamp timestampLastSend_;
};

/*!
	StreamConnectorFactory
*/

struct StreamConnectorFactory
{
	static BaosConnector::Ptr create(unsigned char version, const std::string remoteHost, unsigned short port);
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_STREAM_STREAM_CONNECTOR_H__
