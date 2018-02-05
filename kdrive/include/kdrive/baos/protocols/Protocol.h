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

#ifndef __KDRIVE_BAOS_PROTOCOLS_PROTOCOL_H__
#define __KDRIVE_BAOS_PROTOCOLS_PROTOCOL_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/BaosConnector.h"
#include "kdrive/baos/core/Forwards.h"
#include <Poco/Net/StreamSocket.h>
#include <vector>
#include <string>
#include <memory>
#include <tuple>

namespace kdrive
{
namespace baos
{

struct ServerItem;

/*!
	DataPacketHeaderPolicy
*/

struct kdriveRPC_baos_API HeaderPolicy
{
	virtual std::size_t size(const DataPacket& dataPacket) = 0;
	virtual std::size_t read(DataPacket& dataPacket, const unsigned char* buffer, std::size_t bufferSize) = 0;
	virtual std::size_t write(const DataPacket& dataPacket, unsigned char* buffer, std::size_t bufferSize) const = 0;
};

/*!
	DataRequestFactory
*/

struct DataRequestFactory
{
	static std::shared_ptr<DataRequest> create(std::shared_ptr<BaosConnector> connector,
	        unsigned char subService,
	        unsigned short offset,
	        unsigned short count);

	static std::shared_ptr<DataRequest> create(unsigned char version,
	        unsigned char subService,
	        unsigned short offset,
	        unsigned short count);
};

/*!
	DataPacketFactory
*/

template <class DataPacketType, class HeaderPolicyType>
typename DataPacketType::Ptr dataPacketFactory(unsigned char version)
{
	typename DataPacketType::Ptr dataPacketType(new DataPacketType);
	std::shared_ptr<HeaderPolicy> headerPolicy(new HeaderPolicyType);
	dataPacketType->setHeaderPolicy(headerPolicy);
	dataPacketType->setVersion(version);
	return dataPacketType;
}

/*!
	ProtocolFormatter
*/
struct ProtocolFormatter
{
	typedef std::tuple<unsigned short, unsigned char, unsigned char, unsigned char> Descriptor;
	typedef std::vector<Descriptor> Descriptors;
	typedef std::vector<ServerItem> ServerItems;
	typedef std::vector<Timer> Timers;
	typedef std::vector<std::string> Strings;
	typedef std::vector<unsigned char> ParameterBytes;

	static void decodeGetServerItem_Res(std::shared_ptr<DataPacket> dataPacket, ServerItems& serverItems);

	static void encodeSetServerItem_Req(std::shared_ptr<DataPacket> dataPacket, const ServerItems& serverItems);
	static void decodeServerItem_Ind(std::shared_ptr<DataPacket> dataPacket, ServerItems& serverItems);

	static void decodeGetDatapointDescription_Res(std::shared_ptr<DataPacket> dataPacket, Descriptors& descriptors);

	static void decodeGetDescriptionString_Res(std::shared_ptr<DataPacket> dataPacket, Strings& strings);

	static void encodeGetDatapointValue_Req(std::shared_ptr<DataPacket> dataPacket, unsigned char filter);
	static void decodeGetDatapointValue_Res(std::shared_ptr<DataPacket> dataPacket, ServerItems& serverItems);
	static void decodeDatapointValue_Ind(std::shared_ptr<DataPacket> dataPacket, ServerItems& serverItems);

	static void encodeSetDatapointValue_Req(std::shared_ptr<DataPacket> dataPacket, const ServerItems& serverItems);

	static void decodeGetParameterByte_Res(std::shared_ptr<DataPacket> dataPacket, ParameterBytes& parameterBytes);

	static void encodeSetDatapointHistoryCommand_Req(std::shared_ptr<DataPacket> dataPacket, unsigned char command);

	static void decodeGetTimer_Res(std::shared_ptr<DataPacket> dataPacket, Timers& timers);
	static void encodeSetTimer_Req(std::shared_ptr<DataPacket> dataPacket, const Timers& timers);
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_PROTOCOLS_PROTOCOL_H__
