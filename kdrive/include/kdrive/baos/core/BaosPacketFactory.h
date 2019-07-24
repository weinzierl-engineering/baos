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

#ifndef __KDRIVE_BAOS_CORE_BAOS_PACKET_FACTORY_H__
#define __KDRIVE_BAOS_CORE_BAOS_PACKET_FACTORY_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/Forwards.h"
#include "kdrive/connector/Forwards.h"
#include "kdrive/connector/PacketFactory.h"
#include <memory>

namespace kdrive
{
namespace baos
{

/*!
	\class BaosPacketFactory
	A connector has a PacketFactory which converts a raw byte stream
	into a known packet type. There are several baos packet types
	defined in this library, such as the DataRequest, DataResponse,
	DatapointValueIndication and ServerItemIndication
	This class is responsible for decoding the byte stream and
	creating the corresponding packet container
*/
class kdriveRPC_baos_API BaosPacketFactory : public connector::PacketFactory
{
public:
	BaosPacketFactory();
	virtual ~BaosPacketFactory();

	/*!
		Creates the packet type from a corresponding byte stream
		Actually, this simply returns an UnknownPacket
		and should be overridden by the specific protocol packet factory
	*/
	std::shared_ptr<connector::Packet> create(const unsigned char* buffer, std::size_t bufferLength) override;

protected:
	/*!
		Creates a packet based on the subService command
		If errorCode represents an error, a ErrorResponse will be created
	*/
	std::shared_ptr<DataPacket> createFromSubService(unsigned char subService, unsigned char errorCode);
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_CORE_BAOS_PACKET_FACTORY_H__
