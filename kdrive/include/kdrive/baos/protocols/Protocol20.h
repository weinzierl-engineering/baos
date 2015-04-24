
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

#ifndef __KDRIVE_BAOS_PROTOCOLS_PROTOCOL20_H__
#define __KDRIVE_BAOS_PROTOCOLS_PROTOCOL20_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/protocols/Protocol.h"
#include "kdrive/baos/core/BaosPacketFactory.h"
#include "kdrive/baos/core/Forwards.h"
#include <string>
#include <memory>

namespace kdrive
{
namespace baos
{

struct Protocol20
{
	enum
	{
	    MainService,
	    SubService,
	    StartItemHigh,
	    StartItemLow,
	    NumberOfItemsHigh,
	    NumberOfItemsLow,
	    HeaderSize
	};

	enum
	{
	    ErrorCode = HeaderSize
	};
};

/*!
	HeaderPolicy20
*/

struct kdriveRPC_baos_API HeaderPolicy20 : public HeaderPolicy
{
	virtual std::size_t size(const DataPacket& dataPacket);
	virtual std::size_t read(DataPacket& dataPacket, const unsigned char* buffer, std::size_t bufferSize);
	virtual std::size_t write(const DataPacket& dataPacket, unsigned char* buffer, std::size_t bufferSize) const;
};

/*!
	PacketFactory20
*/

class kdriveRPC_baos_API PacketFactory20 : public BaosPacketFactory
{
public:
	typedef std::shared_ptr<DataRequest> DataRequestPtr;

	PacketFactory20();
	virtual ~PacketFactory20();

	virtual connector::Packet::Ptr create(const unsigned char* buffer, std::size_t bufferLength);
	static DataRequestPtr createDataRequest();
};

/*!
	ProtocolFormatter20
*/
struct kdriveRPC_baos_API ProtocolFormatter20
{
	static void decodeGetServerItem_Res(std::shared_ptr<DataPacket> dataPacket, ProtocolFormatter::ServerItems& serverItems);
	static void encodeSetServerItem_Req(std::shared_ptr<DataPacket> dataPacket, const ProtocolFormatter::ServerItems& serverItems);
	static void decodeServerItem_Ind(std::shared_ptr<DataPacket> dataPacket, ProtocolFormatter::ServerItems& serverItems);
	static void decodeGetDatapointDescription_Res(std::shared_ptr<DataPacket> dataPacket, ProtocolFormatter::Descriptors& descriptors);
	static void decodeGetDescriptionString_Res(std::shared_ptr<DataPacket> dataPacket, ProtocolFormatter::Strings& strings);
	static void encodeGetDatapointValue_Req(std::shared_ptr<DataPacket> dataPacket, unsigned char filter);
	static void decodeGetDatapointValue_Res(std::shared_ptr<DataPacket> dataPacket, ProtocolFormatter::ServerItems& serverItems);
	static void decodeDatapointValue_Ind(std::shared_ptr<DataPacket> dataPacket, ProtocolFormatter::ServerItems& serverItems);
	static void encodeSetDatapointValue_Req(std::shared_ptr<DataPacket> dataPacket, const ProtocolFormatter::ServerItems& serverItems);
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_PROTOCOLS_PROTOCOL20_H__
