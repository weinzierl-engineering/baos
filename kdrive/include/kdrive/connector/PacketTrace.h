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

#ifndef __KDRIVE_CONNECTOR_PACKET_TRACE_H__
#define __KDRIVE_CONNECTOR_PACKET_TRACE_H__

#include "kdrive/connector/Config.h"
#include "kdrive/connector/Forwards.h"
#include <boost/signals2/connection.hpp>
#include <vector>
#include <functional>

namespace kdrive
{
namespace connector
{

/*!
	\class PacketTrace
	A utility class to log rx and tx packets
	it connects to the packet router notifications
	and logs the packets as they are sent and received

	Decoders can be added to provide additional debugging.
	We always run through all decoders, which means it is possible
	to show multiple interpretations. The decoder should
	typically write to the LOGGER
*/
class kdriveConnector_API PacketTrace
{
public:
	PacketTrace();
	explicit PacketTrace(Connector& connector);
	~PacketTrace();

	void connect(Connector& connector);
	void disconnect();

	typedef std::function<void (const unsigned char*, std::size_t, int direction)> Decoder;
	void addDecoder(Decoder decoder);

private:
	boost::signals2::scoped_connection connection_;
	std::vector<Decoder> decoders_;
};

/*!
	\class EventTrace
	A utility class to log event notifications
	it connects to the event notifications
	and logs the event ids as they are received

	Decoders can be added to provide additional debugging.
	We always run through all decoders, which means it is possible
	to show multiple interpretations. The decoder should
	typically write to the LOGGER
*/
class kdriveConnector_API EventTrace
{
public:
	EventTrace();
	explicit EventTrace(Connector& connector);
	~EventTrace();

	void connect(Connector& connector);
	void disconnect();

	typedef std::function<void (int)> Decoder;
	void addDecoder(Decoder decoder);

private:
	boost::signals2::scoped_connection connection_;
	std::vector<Decoder> decoders_;
};

}
} // end namespace kdrive::connector

#endif // __KDRIVE_CONNECTOR_PACKET_TRACE_H__
