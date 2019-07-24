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

#include "pch/kdrive_pch.h"
#include "kdrive/baos/BaosHeartbeat.h"
#include "kdrive/baos/BaosServerItems.h"
#include "kdrive/baos/core/BaosConnector.h"
#include "kdrive/connector/Events.h"
#include <Poco/Exception.h>
#include <boost/assert.hpp>

using Poco::Exception;
using namespace kdrive::connector;
using namespace kdrive::baos;

/******************************
** BaosHeartbeat
*******************************/

BaosHeartbeat::BaosHeartbeat(BaosConnector::Ptr connector, unsigned int interval)

	: connector_(connector),
	  activeFunction_(std::bind(&BaosHeartbeat::sendHeartbeat, this), interval, "BaosHeartbeat"),
	  alive_(true),
	  autoTerminate_(false),
	  autoTerminateFailCount_(0),
	  timeSinceReset_(0)
{
	BOOST_ASSERT(connector && "Invalid Pointer");
}

BaosHeartbeat::~BaosHeartbeat()
{
	try
	{
		stop();
	}
	catch (...)
	{
	}
}

void BaosHeartbeat::start()
{
	activeFunction_.start();
}

void BaosHeartbeat::stop()
{
	activeFunction_.stop();
}

bool BaosHeartbeat::isAlive() const
{
	return alive_;
}

unsigned long BaosHeartbeat::getTimeSinceReset() const
{
	return timeSinceReset_;
}

void BaosHeartbeat::setAutoTerminate(bool autoTerminate, int failCount)
{
	autoTerminate_ = autoTerminate;
	autoTerminateFailCount_ = failCount;
	autoTerminateFailCounter_ = failCount;
}

void BaosHeartbeat::sendHeartbeat()
{
	try
	{
		BaosServerItems serverItems(connector_);
		timeSinceReset_ = serverItems.getTimeSinceReset();
		alive_ = true;
		autoTerminateFailCounter_ = autoTerminateFailCount_;
	}
	catch (Exception& /* exception */)
	{
		alive_ = false;
	}

	if (autoTerminate_ && !alive_)
	{
		if (autoTerminateFailCounter_ > 0)
		{
			--autoTerminateFailCounter_;
		}
		else
		{
			connector_->routeEvent(ConnectorEvents::Terminated);
			connector_->close();
			activeFunction_.stopFromWithinCallback();
		}
	}
}

/******************************
** ScopedBaosHeartbeat
*******************************/

ScopedBaosHeartbeat::ScopedBaosHeartbeat(BaosConnector::Ptr connector, unsigned int interval)

	: BaosHeartbeat(connector, interval)
{
	start();
}

ScopedBaosHeartbeat::~ScopedBaosHeartbeat()
{
	try
	{
		stop();
	}
	catch (...)
	{
	}
}

