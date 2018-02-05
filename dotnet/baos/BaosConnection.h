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

#pragma once

#include "kdriveManagedConfig.h"
#include <kdrive/baos/BaosConnection.h>
#include <kdrive/baos/core/API.h>
#include <kdrive/baos/core/BaosConnector.h>
#include <boost/assert.hpp>
#include <memory>

namespace unmanaged
{
typedef std::shared_ptr<kdrive::baos::BaosConnector> ConnectorPtr;
typedef kdrive::baos::BaosConnection BaosConnection;

typedef kdrive::baos::ProtocolVersions ProtocolVersions;

}

namespace kdrive
{
namespace baos
{
namespace bindings
{

/// <summary>
/// BAOS protocol versions
/// </summary>
public enum class ProtocolVersions
{
	Unknown = unmanaged::ProtocolVersions::Unknown, /*!< The protocol version is unknown*/

	V12 = unmanaged::ProtocolVersions::V12, /*!<Protocol Version 1.2 (e.g. for BAOS 770) */
	V20 = unmanaged::ProtocolVersions::V20 /*!<Protocol Version 2.0 (e.g. for BAOS 771 and BAOS 772) */
};

/// <summary>
/// The BaosConnection is responsible for creating a TCP/IP stream
/// or a FT 1.2 connection with the baos server
/// </summary>
/// <remarks>
///	The BaosConnection is responsible for creating a TCP/IP socket connection or
///	FT 1.2 connection to the remote BAOS device.
///	For IP it requires the IP Address of the device and for FT 1.2 Serial the
///	name of the serial port.
///	The BaosConnection is a wrapper around the Connector which is used throughout
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
///		BaosConnection baosConnection = null;
///
///		try
///		{
///			BaosConnection baosConnection = new StreamConnection();
///			baosConnection.connectIpByName("Baos-Sample");
///			
///			// ...
///
///			baosConnection.disconnect();
///		}
///		catch (kdrive.KdriveException exception)
///		{
///			Console.WriteLine(exception.Message);
///		}
///		finally
///		{
///			if (baosConnection != null)
///			{
///				baosConnection.Dispose();
///			}
///		}
/// </code>
/// </para>
/// <para>
/// DEPRECATED! Use ScopedBaosConnection instead.
/// This class calls only the functions from BaosConnection.
/// </para>
/// </remarks>
public ref class BaosConnection
{
public:
	/// <summary>
	///	Constructor. There are no parameters.
	/// </summary>
	BaosConnection()

		: connection_(0)
	{
	}

	/// <summary>
	///	Destructor cleans up unmanaged and managed resources.
	/// </summary>
	~BaosConnection()
	{
		// call finalizer to release unmanaged resources
		this->!BaosConnection();
	}

	/// <summary>
	/// Connects to the remote IP BAOS device.
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
	void connectIp(System::String^ remoteHost, unsigned char protocol, bool decodeProtocol)
	{
		try
		{
			if (!connection_)
			{
				std::string s = interop::StringConvA(remoteHost);
				connection_ = new unmanaged::BaosConnection;
				connection_->connectIp(s, protocol, decodeProtocol);
			}
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Connects to the remote IP BAOS device.
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
	void connectIp(System::String^ remoteHost)
	{
		connectIp(remoteHost, false);
	}

	/// <summary>
	///	Connects to the remote IP BAOS device.
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
	void connectIp(System::String^ remoteHost, bool decodeProtocol)
	{
		try
		{
			if (!connection_)
			{
				std::string s = interop::StringConvA(remoteHost);
				connection_ = new unmanaged::BaosConnection;
				connection_->connectIpByAddress(s, decodeProtocol);
			}
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Enumerates the network and finds all available IP BAOS devices.
	///	Selects the device that matches the specified name
	///	and opens a connection to it.
	/// </summary>
	/// <param name="name"> The device friendly name. (Which you can set with the ETS)</param>
	/// <remarks>
	///	This auto-select the BAOS protocol.
	/// </remarks>
	void connectIpByName(System::String^ name)
	{
		connectIpByName(name, false);
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
	void connectIpByName(System::String^ name, bool decodeProtocol)
	{
		try
		{
			std::string s = interop::StringConvA(name);
			connection_ = new unmanaged::BaosConnection;
			connection_->connectIpByName(s, decodeProtocol);
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
	void connectIpNat(System::String^ remoteHost, unsigned short port, unsigned char protocol, bool decodeProtocol)
	{
		try
		{
			std::string s = interop::StringConvA(remoteHost);
			connection_ = new unmanaged::BaosConnection;
			connection_->connectIpNat(s, port, protocol, decodeProtocol);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Connects to a Serial FT1.2 BAOS device
	/// </summary>
	/// <param name="serialDeviceName">
	/// SerialDeviceName is the platform specific device name, e.g. COM1 or /dev/ttyS0
	/// </param>
	/// <param name="decodeProtocol">
	/// Indicates whether the packet trace is enabled,
	///	if true use in conjunction with the logger
	/// </param>
	void connectSerial(System::String^ serialDeviceName, bool decodeProtocol)
	{
		try
		{
			std::string s = interop::StringConvA(serialDeviceName);
			connection_ = new unmanaged::BaosConnection;
			connection_->connectSerial(s, decodeProtocol);
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
	!BaosConnection()
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
	unmanaged::BaosConnection* connection_;
};

}
}
} // end namespace kdrive::baos::bindings

