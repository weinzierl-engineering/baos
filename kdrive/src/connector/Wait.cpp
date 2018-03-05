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
#include "kdrive/connector/Wait.h"

using namespace kdrive::connector;
using Poco::Timestamp;

/******************************
** TimeoutWatcher
*******************************/

/*!
	\class TimeoutWatcher
	Keeps track of the elapsed time and
	indicates when a timeout period has elapsed
*/
TimeoutWatcher::TimeoutWatcher(unsigned long timeout)

	: timeout_(timeout),
	  timeoutMicroSeconds_(timeout * 1000)
{
}

bool TimeoutWatcher::elapsed()
{
	const Timestamp::TimeDiff elapsed = timestamp_.elapsed();
	return (timeoutMicroSeconds_ < elapsed) ? true : false;
}

/******************************
** BasicWaitPacketPolicy
*******************************/

BasicWaitPacketPolicy::BasicWaitPacketPolicy(Connector& connector)

	: connector_(connector)
{
}

Packet::Ptr BasicWaitPacketPolicy::operator()(unsigned long timeout)
{
	Packet::Ptr packet;
	try
	{
		packet = connector_.waitReceive(timeout);
	}
	catch (...)
	{
	}
	return packet;
}

/******************************
** waitPacket
*******************************/

std::shared_ptr<Packet> kdrive::connector::waitPacket(Connector& connector, unsigned long timeout,
        std::function<bool (std::shared_ptr<Packet>)> waitPolicy)
{
	TimeoutWatcher timeoutWatcher(timeout);

	while (!timeoutWatcher.elapsed())
	{
		try
		{
			std::shared_ptr<Packet> packet = connector.waitReceive(timeout);
			if (waitPolicy(packet))
			{
				return packet;
			}
		}
		catch (...)
		{
		}
	}

	throw Poco::TimeoutException();
}
