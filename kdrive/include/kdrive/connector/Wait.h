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

#ifndef __KDRIVE_CONNECTOR_WAIT_PACKET_H__
#define __KDRIVE_CONNECTOR_WAIT_PACKET_H__

#include "kdrive/connector/Config.h"
#include "kdrive/connector/Connector.h"
#include "kdrive/connector/Packet.h"
#include <Poco/Exception.h>
#include <Poco/Timestamp.h>
#include <tuple>
#include <memory>

namespace kdrive
{
namespace connector
{

/******************************
** TimeoutWatcher
*******************************/

/*!
	\class TimeoutWatcher
	Keeps track of the elapsed time and
	indicates when a timeout period has elapsed
*/
struct kdriveConnector_API TimeoutWatcher
{
	TimeoutWatcher(unsigned long timeout);
	bool elapsed();
	unsigned long timeout_;
	const Poco::Timestamp timestamp_;
	const Poco::Timestamp::TimeDiff timeoutMicroSeconds_;
};

/******************************
** BasicWaitPacketPolicy
*******************************/

/*!
	\class BasicWaitPacketPolicy
	The most basic wait policy, simply waits for any packet to arrive
	within the specified timeout period
*/
struct kdriveConnector_API BasicWaitPacketPolicy
{
	BasicWaitPacketPolicy(Connector& connector);
	Packet::Ptr operator()(unsigned long timeout);
	Connector& connector_;
};

/******************************
** wait Packet with Policy
*******************************/

template <typename T, typename WaitPolicy>
std::shared_ptr<T> waitPacketWithPolicy(WaitPolicy& waitPolicy, unsigned long timeout)
{
	std::shared_ptr<T> packet;
	TimeoutWatcher timeoutWatcher(timeout);

	while (!timeoutWatcher.elapsed())
	{
		packet = Packet::convert<T>(waitPolicy(timeoutWatcher.timeout_), false);

		if (packet)
		{
			break;
		}
	}

	if (!packet)
	{
		throw Poco::TimeoutException();
	}

	return packet;
}

/******************************
** wait packet : blocking
*******************************/

/*!
	wait packet will block until a specific packet type <Packet> is received
	all received packets that are not of type Packet will be discarded
*/
template <typename T>
std::shared_ptr<T> waitPacket(Connector& connector)
{
	BasicWaitPacketPolicy policy(connector);
	std::shared_ptr<T> packet;
	while (!packet)
	{
		packet = waitPacketWithPolicy<T>(policy, 1000);
	}
	return packet;
}

/******************************
** wait packet : timeout
*******************************/

/*!
	wait packet will wait for a specific packet type <Packet> for a specified time period
	all received packets that are not of type Packet will be discarded
	if the packet is not found within the specified time period an exception is thrown
*/
template <class T>
std::shared_ptr<T> waitPacket(Connector& connector, unsigned long timeout)
{
	BasicWaitPacketPolicy policy(connector);
	return waitPacketWithPolicy<T>(policy, timeout);
}

}
} // end namespace kdrive::connector

#endif // __KDRIVE_CONNECTOR_WAIT_PACKET_H__
