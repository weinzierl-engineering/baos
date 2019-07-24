//
// Copyright (c) 2002-2019 WEINZIERL ENGINEERING GmbH
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
#include "StreamConnection.h"
#include "BaosConnection.h"
#include <kdrive/connector/Connector.h>
#include <memory>

namespace unmanaged
{
typedef std::shared_ptr<kdrive::baos::BaosConnector> ConnectorPtr;
}

namespace kdrive
{
namespace baos
{
namespace bindings
{

/// <summary>
/// The Connector is an abstraction around a physical medium.
/// </summary>
/// <remarks>
///	The kdrive BAOS library currently implements the TCP/IP
///	stream connection and Serial FT1.2 connection (other possibile connections is via UDP/IP).
///	There is nothing you really have to do with the connection except for
///	create it and pass it to the other classes in this library.
///	In the native C++ SDK there are additional things you can do with the connector,
///	such as attach to the notification events for Rx / Tx packets etc however
///	this functionality is not currently exposed via the managed C++ implementation.
/// </remarks>
public ref class Connector
{
public:
	/// <summary>
	/// Constructor. 
	/// The connector takes a StreamConnection
	/// </summary>
	Connector(StreamConnection^ streamConnection)
	{
		try
		{
			connector_ = new unmanaged::ConnectorPtr;
			*connector_ = streamConnection->getConnector();
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	/// Constructor. 
	/// The connector takes a BaosConnection
	/// </summary>
	Connector(BaosConnection^ baosConnection)
	{
		try
		{
			connector_ = new unmanaged::ConnectorPtr;
			*connector_ = baosConnection->getConnector();
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Destructor, releases the connector
	///	if it has not already been released
	/// </summary>
	~Connector()
	{
		// call finalizer to release unmanaged resources
		this->!Connector();
	}

	/// <summary>
	///	Gets the raw unmanaged connector.
	///	Used by the managed C++ implementation
	/// </summary>
	unmanaged::ConnectorPtr getUnmanaged()
	{
		return *connector_;
	}

	/// <summary>
	///	Releases the connector.
	/// </summary>
	void releaseConnector()
	{
		if (connector_)
		{
			delete connector_;
			connector_ = 0;
		}
	}

protected:
	/// <summary>
	///	Finalizer (non-deterministic destructor) 
	///	cleans up unmanaged resources.
	///	Releases the connector, if it has not already been released
	/// </summary>
	!Connector()
	{
		try
		{
			releaseConnector();
		}
		catch (...)
		{
		}
	}

private:
	unmanaged::ConnectorPtr* connector_;
};

}
}
} // end namespace kdrive::baos::bindings

