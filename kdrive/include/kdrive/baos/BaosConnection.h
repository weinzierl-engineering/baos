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

#ifndef __KDRIVE_BAOS_BAOS_CONNECTION_H__
#define __KDRIVE_BAOS_BAOS_CONNECTION_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/BaosProtocolDecoder.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/Forwards.h"
#include <boost/signals2.hpp>
#include <memory>

namespace kdrive
{
namespace baos
{

/*!
	\class BaosConnection
	\brief The BaosConnection is responsible for creating a TCP/IP stream
	or a FT 1.2 connection with the baos server

	The BaosConnection is responsible for creating a TCP/IP socket connection or
	FT 1.2 connection to the remote BAOS device.
	For IP it requires the IP Address of the device and for FT 1.2 Serial the
	name of the serial port.
	The BaosConnection is a wrapper around the Connector which is used throughout
	the baos rpc library.

	It implements a connect and a disconnect signal. These signals are invoked
	when the stream connection is connector and disconnected respectively.
	Note: a stream connection can be auto-disconnected if the tcp/ip connection
	is terminated by the remote peer (baos device). This may occur if a connection
	timeout occurs (i.e. no socket activity for a couple of minutes).
	\sa BaosHeartbeat
*/
class kdriveRPC_baos_API BaosConnection
{
public:
	typedef std::shared_ptr<BaosConnector> BaosConnectorPtr;

	/*!
		Creates a default (disconnected) BaosConnection
	*/
	BaosConnection();

	BaosConnection(const BaosConnection&) = delete;
	BaosConnection& operator=(const BaosConnection&) = delete;

	/*!
		Destroys the StreamConnection.
		If no other hold an reference to the Connector (the normal case),
		the destructor of Connector will called which closed
		the TCP/IP socket connection respectively the serial port.
	*/
	virtual ~BaosConnection();

	/*!
	    returns the connector
	    throws a NullPointerException exception
	    if the connector is not connected
	*/
	BaosConnectorPtr getConnector();

	/*!
		Connects to a remote IP BAOS device
	*/
	void connectIp(const std::string remoteHost, unsigned char version, bool decodeProtocol = false);

	/*!
		Connects to a remote IP BAOS device
	*/
	void connectIp(const BaosDevice& baosDevice, bool decodeProtocol = false);

	/*!
		Connects to a remote IP BAOS device
		It gets the IP address and protocol version via a KNXnet/IP Search Request/Response
	*/
	void connectIpByName(const std::string& name, bool decodeProtocol = false);

	/*!
		Connects to a remote IP BAOS device
		It gets the protocol version via a KNXnet/IP Search Request/Response
	*/
	void connectIpByAddress(const std::string& ipAddress, bool decodeProtocol = false);

	/*!
		Connects to a remote IP BAOS device with NAT
	*/
	void connectIpNat(const std::string& ipAddress, unsigned short port, unsigned char version, bool decodeProtocol = false);

	/*!
		Connects to a Serial FT1.2 BAOS device
		\param serialDeviceName is the platform specific device name, e.g. COM1 or /dev/ttyS0
	*/
	void connectSerial(const std::string& serialDeviceName, unsigned char version = ProtocolVersions::V20, bool decodeProtocol = false);

	/*!
		Disconnects the connection to a remote device
	*/
	void disconnect();

	/*!
		Returns true if the connection is established, false otherwise
	*/
	bool isConnected() const;

	typedef boost::signals2::signal<void ()> ConnectSignal;
	typedef boost::signals2::signal<void ()> DisconnectSignal;

	/*!
		Returns the connect signal
		This is invoked when the connector thread is started
	*/
	ConnectSignal& getConnectSignal();

	/*!
		Returns the disconnect signal
		This is invoked when the connector thread is stopped
	*/
	DisconnectSignal& getDisconnectSignal();

private:
	unsigned char lookupVersion(const std::string remoteHost, unsigned char version);
	void connectIpImpl(const std::string remoteHost, unsigned short port,
	                   unsigned char version, bool decodeProtocol);
	void connectSerialImpl(const std::string serialDeviceName, unsigned char version, bool decodeProtocol);

private:
	BaosConnectorPtr baosConnector_;
	ProtocolDecoder protocolDecoder_;
};

/*!
	\class ScopedBaosConnection
	\brief Auto-connect and disconnect of the StreamConnection

	RAII for BaosConnection. Connects in the constructor
	and disconnects in the destructor.
*/
class kdriveRPC_baos_API ScopedBaosConnection : public BaosConnection
{
public:
	/*!
		Creates a ScopedBaosConnection, and connects to a remote baos
		device with the specified name. The device
		can be obtained with a BaosEnumerator.

		If decodeProtocol is true, the BAOS protocol will be decoded and logged
		This is used typically for Debug purposes.
	*/
	ScopedBaosConnection(const std::string& name, bool decodeProtocol = false);

	/*!
		Creates a ScopedBaosConnection, and connects to a remote baos
		device with the specified ip address (remoteHost).
		If version is 0 an enumeration will be performed to determine the version.

		If decodeProtocol is true, the BAOS protocol will be decoded and logged
		This is used typically for Debug purposes.
	*/
	ScopedBaosConnection(const std::string ipAddress, unsigned char version, bool decodeProtocol = false);

	/*!
		Creates a ScopedBaosConnection, and connects to a remote baos
		device with the specified ip address (remoteHost). The device
		can be obtained with a BaosEnumerator.

		If decodeProtocol is true, the BAOS protocol will be decoded and logged
		This is used typically for Debug purposes.
	*/
	ScopedBaosConnection(const BaosDevice& baosDevice, bool decodeProtocol = false);

	/*!
		Destroys the ScopedBaosConnection and closes the connection
	*/
	virtual ~ScopedBaosConnection();
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_STREAM_CONNECTION_H__
