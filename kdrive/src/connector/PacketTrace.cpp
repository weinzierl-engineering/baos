//
// Copyright (c) 2002-2015 WEINZIERL ENGINEERING GmbH
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
#include "kdrive/connector/PacketTrace.h"
#include "kdrive/connector/Connector.h"
#include "kdrive/connector/Packet.h"
#include "kdrive/utility/Logger.h"
#include <Poco/Exception.h>

using namespace kdrive::connector;
using Poco::Exception;

CLASS_LOGGER("kdrive.connector.PacketTrace")

/****************************************
** PacketTrace
*****************************************/

PacketTrace::PacketTrace()
{
}

PacketTrace::PacketTrace(Connector& connector)
{
	connect(connector);
}

PacketTrace::~PacketTrace()
{
	disconnect();
}

void PacketTrace::connect(Connector& connector)
{
	Connector::PacketSignal& s = connector.getPacketSignal();
	connection_ = s.connect(
	                  [this](Packet::Ptr packet, int direction)
	{
		std::size_t size = packet->size();
		if (!size)
		{
			poco_warning(LOGGER(), "PacketTrace Decoder, received empty packet");
			return;
		}
		std::vector<unsigned char> buffer(size, 0x00);
		packet->writeToBuffer(&buffer.at(0), buffer.size());

		if (decoders_.empty())
		{
			const std::string str = direction == Connector::Rx ? "Rx : " : "Tx : ";
			poco_check_ptr(packet);
			LOGGER().dump(str, &buffer.at(0), buffer.size(), Poco::Message::PRIO_INFORMATION);
		}
		for (Decoder decoder : decoders_)
		{
			try
			{
				decoder(&buffer.at(0), buffer.size(), direction);
			}
			catch (Exception& exception)
			{
				poco_warning_f1(LOGGER(), "PacketTrace Decoder error %s", exception.displayText());
			}
		}
	}
	              );
}

void PacketTrace::disconnect()
{
	connection_.disconnect();
}

void PacketTrace::addDecoder(Decoder decoder)
{
	decoders_.push_back(decoder);
}

/****************************************
** EventTrace
*****************************************/

EventTrace::EventTrace()
{
}

EventTrace::EventTrace(Connector& connector)
{
	connect(connector);
}

EventTrace::~EventTrace()
{
	disconnect();
}

void EventTrace::connect(Connector& connector)
{
	Connector::EventSignal& s = connector.getEventSignal();
	connection_ = s.connect(
	                  [this](int e)
	{
		if (decoders_.empty())
		{
			poco_information_f1(LOGGER(), "Event %d", e);
		}
		for (Decoder decoder : decoders_)
		{
			try
			{
				decoder(e);
			}
			catch (Exception& exception)
			{
				poco_warning_f1(LOGGER(), "EventTrace Decoder error %s", exception.displayText());
			}
		}
	}
	              );
}

void EventTrace::disconnect()
{
	connection_.disconnect();
}

void EventTrace::addDecoder(Decoder decoder)
{
	decoders_.push_back(decoder);
}
