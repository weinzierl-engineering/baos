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

#include "pch/kdrive_pch.h"
#include "kdrive/baos/BaosTimers.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/BaosConnector.h"
#include "kdrive/baos/services/GetTimer.h"
#include "kdrive/baos/services/SetTimer.h"
#include <boost/assert.hpp>

using namespace kdrive::connector;
using namespace kdrive::baos;

BaosTimers::BaosTimers(BaosConnector::Ptr connector)

	: connector_(connector)
{
	BOOST_ASSERT(connector && "Invalid Pointer");
}

BaosTimers::~BaosTimers()
{
}

Timer BaosTimers::getTimer(unsigned int id)
{
	GetTimer getTimer(connector_);
	getTimer.rpc(id, 1);
	return getTimer.find(id);
}

BaosTimers::Timers BaosTimers::getTimers()
{
	GetTimer getTimer(connector_);

	// we set a high timer count as we hard-coded the start id and count
	// this should ensure we always return all timers, unless of course
	// there are more than 100 timers, in which case you should use
	// GetTimer directly
	getTimer.rpc(1, 100);

	return getTimer.getTimers();
}

void BaosTimers::setTimer(const Timer& timer)
{
	SetTimer setTimer(connector_);
	setTimer.rpc(timer.id, timer);
}

void BaosTimers::setTimers(const Timers& timers)
{
	if (!timers.empty())
	{
		SetTimer setTimer(connector_);
		setTimer.rpc(timers.at(0).id, timers);
	}
}

void BaosTimers::deleteTimer(unsigned short id)
{
	Timer timer;
	timer.id = id;
	setTimer(timer);
}

void BaosTimers::deleteTimers(const Timers& timers)
{
	Timers deleteTimers;

	for (const auto& timer : timers)
	{
		Timer deleteTimer;
		deleteTimer.id = timer.id;
		deleteTimers.push_back(deleteTimer);
	}

	setTimers(deleteTimers);
}
