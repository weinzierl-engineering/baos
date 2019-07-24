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
#include "kdrive/connector/PacketNotification.h"
#include "kdrive/connector/Packet.h"

using namespace kdrive::connector;

/******************************
** PacketNotification
*******************************/

PacketNotification::PacketNotification(unsigned long e)

	: eventNotification_(true),
	  e_(e),
	  direction_(0)
{
}

PacketNotification::PacketNotification(Packet::Ptr packet, int direction)

	: eventNotification_(false),
	  e_(0),
	  direction_(direction),
	  packet_(packet)
{
}

PacketNotification::~PacketNotification()
{
}

bool PacketNotification::isEventNotification() const
{
	return eventNotification_;
}

Packet::Ptr PacketNotification::getPacket() const
{
	return packet_;
}

int PacketNotification::getDirection() const
{
	return direction_;
}

unsigned long PacketNotification::getEvent() const
{
	return e_;
}

/******************************
** PacketNotificationQueue
*******************************/

PacketNotificationQueue::PacketNotificationQueue()
{
}

PacketNotificationQueue::~PacketNotificationQueue()
{
}

bool PacketNotificationQueue::empty() const
{
	std::unique_lock<std::mutex> locker(lock_);
	return queue_.empty();
}

PacketNotificationQueue::Queue::size_type PacketNotificationQueue::size() const
{
	std::unique_lock<std::mutex> locker(lock_);
	return queue_.size();
}

void PacketNotificationQueue::clear()
{
	std::unique_lock<std::mutex> locker(lock_);
	Queue empty;
	std::swap(queue_, empty);
}

PacketNotification::Ptr PacketNotificationQueue::front()
{
	std::unique_lock<std::mutex> locker(lock_);
	return queue_.front();
}

void PacketNotificationQueue::pop()
{
	std::unique_lock<std::mutex> locker(lock_);
	queue_.pop();
}

void PacketNotificationQueue::push(PacketNotification::Ptr notification)
{
	std::unique_lock<std::mutex> locker(lock_);
	queue_.push(notification);
	condition_.notify_one();
}

PacketNotification::Ptr PacketNotificationQueue::wait(long milliseconds)
{
	PacketNotification::Ptr notification;

	{
		std::unique_lock<std::mutex> locker(lock_);

		if (queue_.empty())
		{
			condition_.wait_for(locker, std::chrono::milliseconds(milliseconds));
		}

		if (!queue_.empty())
		{
			notification = queue_.front();
			queue_.pop();
		}
	}

	return notification;
}

void PacketNotificationQueue::wakeUpAll()
{
	std::unique_lock<std::mutex> locker(lock_);
	condition_.notify_all();
}
