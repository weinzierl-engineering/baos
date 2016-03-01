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

#pragma once

#include "kdriveManagedConfig.h"
#include <kdrive/baos/stream/StreamConnection.h>
#include <kdrive/baos/core/BaosConnector.h>
#include <boost/assert.hpp>
#include <memory>

namespace unmanaged
{
typedef std::shared_ptr<kdrive::baos::BaosConnector> ConnectorPtr;
typedef kdrive::baos::StreamConnection StreamConnection;
}

namespace kdrive
{
namespace baos
{
namespace bindings
{

/// <summary>
/// The StreamConnection is responsible for creating
///	a TCP/IP stream connection with the baos server
/// </summary>
/// <remarks>
///	The StreamConnection is responsible for creating a TCP/IP socket connection
///	to the remote BAOS device. It requires the IP Address of the device. The
///	StreamConnection is a wrapper around the Connector which is used throughout
///	the baos rpc library.
/// <para>
///	It implements a connect and a disconnect signal. These signals are invoked
///	when the stream connection is connector and disconnected respectively.
///	Note: a stream connection can be auto-disconnected if the tcp/ip connection
///	is terminated by the remote peer (baos device).
/// </para>
/// <para>
///	\note It's recommended that you release the connection with disconnect or Dispose if you do not more need it.
///
/// <code>
///		// C# sample
///		StreamConnection streamConnection = null;
///
///		try
///		{
///			StreamConnection streamConnection = new StreamConnection();
///			streamConnection.connectByName("Baos-Sample");
///			
///			// ...
///
///			streamConnection.disconnect();
///		}
///		catch (kdrive.KdriveException exception)
///		{
///			Console.WriteLine(exception.Message);
///		}
///		finally
///		{
///			if (streamConnection != null)
///			{
///				streamConnection.Dispose();
///			}
///		}
/// </code>
/// </para>
/// </remarks>
public ref class StreamConnection
{
public:
	/// <summary>
	///	Constructor. There are no parameters.
	/// </summary>
	StreamConnection()

		: connection_(0)
	{
	}

	/// <summary>
	///	Destructor cleans up unmanaged and managed resources.
	/// </summary>
	~StreamConnection()
	{
		// call finalizer to release unmanaged resources
		this->!StreamConnection();
	}

	/// <summary>
	/// Connects to the remote device.
	/// </summary>
	/// <param name="remoteHost">The remote is the IP Address of the device.</param>
	/// <param name="protocol">The protocol is the BAOS protocol version:
	/// - for BAOS 770 this is 0x01 (ProtocolVersions::V12)
	/// - for BAOS 771/772 this is 0x20 (ProtocolVersions::V20)
	/// </param>
	/// <param name="decodeProtocol">
	/// Indicates whether the packet trace is enabled,
	///	if true use in conjunction with the logger
	/// </param>
	/// <remarks>
	/// \note This function does perform enumeration, if the protocol version is unknown,
	///	to determine the protocol version
	/// </remarks>
	void connect(System::String^ remoteHost, unsigned char protocol, bool decodeProtocol)
	{
		try
		{
			if (!connection_)
			{
				std::string s = interop::StringConvA(remoteHost);
				connection_ = new unmanaged::StreamConnection;
				connection_->connect(s, protocol, decodeProtocol);
			}
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Connects to the remote device.
	/// </summary>
	/// <param name="remoteHost">
	/// Remote Host is the IP Address of the device.
	///	Tip: you can find this address with the NetnNode Client Application
	///	when you select Open Port - Knx via Ip Tunnelling.
	/// </param>
	/// <remarks>
	///	\note This function performs device enumeration to
	///	determine the protocol version
	/// </remarks>
	void connect(System::String^ remoteHost)
	{
		connect(remoteHost, false);
	}

	/// <summary>
	///	Connects to the remote device.
	/// </summary>
	/// <param name="remoteHost">The remote is the IP Address of the device.</param>
	/// <param name="decodeProtocol">
	/// Indicates whether the packet trace is enabled,
	///	if true use in conjunction with the logger
	/// </param>
	/// <remarks>
	///	\note This function does perform enumeration, if the protocol version is unknown,
	///	to determine the protocol version
	/// </remarks>
	void connect(System::String^ remoteHost, bool decodeProtocol)
	{
		try
		{
			if (!connection_)
			{
				std::string s = interop::StringConvA(remoteHost);
				connection_ = new unmanaged::StreamConnection;
				connection_->connectByAddress(s, decodeProtocol);
			}
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Enumerates the network and finds all available BAOS devices.
	///	Selects the device that matches the specified name
	///	and opens a connection to it.
	/// </summary>
	/// <param name="name"> The device friendly name. (Which you can set with the ETS)</param>
	/// <remarks>
	///	This auto-select the BAOS protocol.
	/// </remarks>
	void connectByName(System::String^ name)
	{
		connectByName(name, false);
	}

	/// <summary>
	///	Enumerates the network and finds all available BAOS devices.
	///	Selects the device that matches the specified name
	///	and opens a connection to it.
	/// </summary>
	/// <param name="name"> The device friendly name. (Which you can set with the ETS)</param>
	/// <param name="decodeProtocol">
	/// Indicates whether the packet trace is enabled,
	///	if true use in conjunction with the logger
	/// </param>
	/// <remarks>
	///	This auto-select the BAOS protocol.
	/// </remarks>
	void connectByName(System::String^ name, bool decodeProtocol)
	{
		try
		{
			std::string s = interop::StringConvA(name);
			connection_ = new unmanaged::StreamConnection;
			connection_->connectByName(s, decodeProtocol);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Connects to a remote IP BAOS device with NAT
	/// </summary>
	/// <param name="remoteHost">
	/// Remote Host is the IP Address of the device.
	///	Tip: you can find this address with the NetnNode Client Application
	///	when you select Open Port - Knx via Ip Tunnelling.
	/// </param>
	/// <param name="port">
	/// The port associated with the connection.
	/// The default port of the BAOS TCP protocol is 12004
	/// </param>
	/// <param name="protocol">The protocol is the BAOS protocol version:
	/// - for BAOS 770 this is 0x01 (ProtocolVersions::V12)
	/// - for BAOS 771/772 this is 0x20 (ProtocolVersions::V20)
	/// </param>
	/// <param name="decodeProtocol">
	/// Indicates whether the packet trace is enabled,
	///	if true use in conjunction with the logger
	/// </param>
	/// <remarks>
	///	This function does perform enumeration, if the protocol version is unknown,
	///	to determine the protocol version
	/// </remarks>
	void connectNat(System::String^ remoteHost, unsigned short port, unsigned char protocol, bool decodeProtocol)
	{
		try
		{
			std::string s = interop::StringConvA(remoteHost);
			connection_ = new unmanaged::StreamConnection;
			connection_->connectNat(s, port, protocol, decodeProtocol);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Disconnects the connection
	/// </summary>
	void disconnect()
	{
		try
		{
			if (connection_)
			{
				connection_->disconnect();
				delete connection_;
				connection_ = 0;
			}
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Returns true if the connection is available
	///	false otherwise
	/// </summary>
	bool isConnected()
	{
		return connection_ ? true : false;
	}

	/// <summary>
	///	Returns the unmanaged (shared) connector pointer.
	///	Used by the managed C++ implementation
	/// </summary>
	unmanaged::ConnectorPtr getConnector()
	{
		BOOST_ASSERT(connection_ && "Invalid Connector");
		return connection_->getConnector();
	}

protected:
	/// <summary>
	///	Finalizer (non-deterministic destructor) 
	///	cleans up unmanaged resources.
	/// </summary>
	!StreamConnection()
	{
		try
		{
			disconnect();
		}
		catch (...)
		{
		}
	}

private:
	unmanaged::StreamConnection* connection_;
};

}
}
} // end namespace kdrive::baos::bindings

