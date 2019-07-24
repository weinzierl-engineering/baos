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

#ifndef __KDRIVE_CONNECTOR_PACKET_FACTORY_H__
#define __KDRIVE_CONNECTOR_PACKET_FACTORY_H__

#include "kdrive/connector/Config.h"
#include <memory>

namespace kdrive
{
namespace connector
{

class Packet;

/*!
	\class PacketFactory
	A Packet Factory is used by the Connector to convert
	a raw buffer into a Packet
	This implementation (the default implementation) simply
	creates an unknown Packet (Packet). If your application implements its
	own Packet types it could/should also define a Packet Factory
*/
class kdriveConnector_API PacketFactory
{
public:
	typedef std::shared_ptr<PacketFactory> Ptr;

	/*!
		Creates a PacketFactory
	*/
	PacketFactory() = default;

	/*!
		Copy constructor is deleted
	*/
	PacketFactory(const PacketFactory&) = delete;

	/*!
		Destroys the ActiveFunction
	*/
	virtual ~PacketFactory();

	/*!
		Assignment Operator is deleted
	*/
	PacketFactory& operator=(const PacketFactory&) = delete;

	/*!
		Create a packet from the buffer
	*/
	virtual std::shared_ptr<Packet> create(const unsigned char* buffer, std::size_t bufferLength);
};

}
} // end namespace kdrive::connector

#endif // __KDRIVE_CONNECTOR_PACKET_FACTORY_H__
