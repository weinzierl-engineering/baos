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

#ifndef __KDRIVE_BAOS_STREAM_CONNECTION_H__
#define __KDRIVE_BAOS_STREAM_CONNECTION_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/BaosConnection.h"

namespace kdrive
{
namespace baos
{

/*!
	\class StreamConnection
	\brief The StreamConnection is responsible for creating
	a TCP/IP stream connection with the baos server

	The StreamConnection is responsible for creating a TCP/IP socket connection
	to the remote BAOS device. It requires the IP Address of the device. The
	StreamConnection is a wrapper around the Connector which is used throughout
	the baos rpc library.

	It implements a connect and a disconnect signal. These signals are invoked
	when the stream connection is connector and disconnected respectively.
	Note: a stream connection can be auto-disconnected if the tcp/ip connection
	is terminated by the remote peer (baos device). This may occur if a connection
	timeout occurs (i.e. no socket activity for a couple of minutes).
	\sa BaosHeartbeat

	\deprecated Use ScopedBaosConnection instead.
	This class calls only the functions from BaosConnection.
*/
class kdriveRPC_baos_API StreamConnection : public BaosConnection
{
public:
	/*!
		Creates a default (disconnected) StreamConnection
	*/
	StreamConnection();

	StreamConnection(const StreamConnection&) = delete;
	StreamConnection& operator=(const StreamConnection&) = delete;

	/*!
		Destroys the StreamConnection.
		If no other hold an reference to the Connector (the normal case),
		the destructor of Connector will called which closed the TCP/IP socket connection.
	*/
	virtual ~StreamConnection();

	/*!
		Connects to a remote IP BAOS device
	*/
	void connect(const std::string remoteHost, unsigned char version, bool decodeProtocol = false);

	/*!
		Connects to a remote IP BAOS device
	*/
	void connect(const BaosDevice& baosDevice, bool decodeProtocol = false);

	/*!
		Connects to a remote IP BAOS device
		It gets the IP address and protocol version via a KNXnet/IP Search Request/Response
	*/
	void connectByName(const std::string& name, bool decodeProtocol = false);

	/*!
		Connects to a remote IP BAOS device
		It gets the protocol version via a KNXnet/IP Search Request/Response
	*/
	void connectByAddress(const std::string& ipAddress, bool decodeProtocol = false);

	/*!
		Connects to a remote IP BAOS device with NAT
	*/
	void connectNat(const std::string& ipAddress, unsigned short port, unsigned char version, bool decodeProtocol = false);

private:
	using BaosConnection::connectSerial;
};

/*!
	\class ScopedStreamConnection
	\brief Auto-connect and disconnect of the StreamConnection

	RAII for StreamConnections. Connects in the constructor
	and disconnects in the destructor.

	\deprecated Use ScopedBaosConnection instead
*/
typedef ScopedBaosConnection ScopedStreamConnection;
}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_STREAM_CONNECTION_H__
