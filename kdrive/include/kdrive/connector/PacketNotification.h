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

#ifndef __KDRIVE_CONNECTOR_PACKET_NOTIFICATION_H__
#define __KDRIVE_CONNECTOR_PACKET_NOTIFICATION_H__

#include "kdrive/connector/Config.h"
#include "kdrive/connector/Forwards.h"
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

namespace kdrive
{
namespace connector
{

/*!
	PacketNotification
	Used by the Connector signal mechanism to indicate
	either a packet or event notification

	We sequeze both notification types into a single notification class
	as this mechansim is not scalable. i.e. we do not intend on adding
	new types of notifications in the future for the connector
*/
class kdriveConnector_API PacketNotification
{
public:
	using Ptr = std::shared_ptr<PacketNotification>;

	PacketNotification(unsigned long e);
	PacketNotification(std::shared_ptr<Packet> packet, int direction);
	~PacketNotification();

	bool isEventNotification() const;

	std::shared_ptr<Packet> getPacket() const;
	int getDirection() const;
	unsigned long getEvent() const;

private:
	const bool eventNotification_;
	const unsigned long e_;
	const int direction_;
	std::shared_ptr<Packet> packet_;
};

/*!
	PacketNotificationQueue
*/
class kdriveConnector_API PacketNotificationQueue
{
public:
	using Queue = std::queue<std::shared_ptr<PacketNotification>>;

	PacketNotificationQueue();
	~PacketNotificationQueue();

	bool empty() const;
	Queue::size_type size() const;
	void clear();
	PacketNotification::Ptr front();
	void pop();
	void push(PacketNotification::Ptr notification);
	PacketNotification::Ptr wait(long milliseconds);
	void wakeUpAll();

private:
	Queue queue_;
	mutable std::mutex lock_;
	std::condition_variable condition_;
};

}
} // end namespace kdrive::connector

#endif // __KDRIVE_CONNECTOR_PACKET_NOTIFICATION_H__
