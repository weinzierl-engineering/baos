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
#include "Connector.h"
#include <kdrive/baos/BaosHeartbeat.h>
#include <memory>

namespace unmanaged
{
typedef std::shared_ptr<kdrive::baos::BaosConnector> ConnectorPtr;
typedef kdrive::baos::BaosHeartbeat BaosHeartbeat;
}

namespace kdrive
{
namespace baos
{
namespace bindings
{

/// <summary>
///	BaosHeartbeat sends periodically a heartbeat.
/// </summary>
/// <remarks>
/// DEPRECATED
/// In a previous version did the StreamConnector no heartbeat.
/// Now th StreamConnector implemented internally the heartbeat.
/// So this class is no more needed. Its exists only for backward compatibility.
/// </remarks>
public ref class BaosHeartbeat
{
public:
	/// <summary>
	///	Creates a BaosHearbeat class. It keeps a reference to the
	///	connector internally so it can periodically send a request
	///	to the server. Nothing will happen however until you call start
	/// </summary>
	BaosHeartbeat(Connector^ connector)

		: heartbeat_(0)
	{
		try
		{
			heartbeat_ = new unmanaged::BaosHeartbeat(connector->getUnmanaged());
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Destroys the BaosHeartbeat
	///	Destructor cleans up unmanaged and managed resources.
	/// </summary>
	~BaosHeartbeat()
	{
		// call finalizer to release unmanaged resources
		this->!BaosHeartbeat();
	}

	/// <summary>
	///	Starts the heartbeat service.
	///	This will periodically send a data request until stopped.
	/// </summary>
	void start()
	{
		heartbeat_->start();
	}

	/// <summary>
	///	Stops the hearbeat service.
	/// </summary>
	void stop()
	{
		heartbeat_->stop();
	}

protected:
	/// <summary>
	///	Finalizer (non-deterministic destructor) 
	///	cleans up unmanaged resources.
	/// </summary>
	!BaosHeartbeat()
	{
		try
		{
			if (heartbeat_)
			{
				delete heartbeat_;
				heartbeat_ = 0;
			}
		}
		catch (...)
		{
		}
	}

private:
	unmanaged::BaosHeartbeat* heartbeat_;
};

}
}
} // end namespace kdrive::baos::bindings

