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
#include "kdrive/baos/protocols/Protocol.h"
#include "kdrive/baos/protocols/Protocol12.h"
#include "kdrive/baos/protocols/Protocol2x.h"
#include "kdrive/baos/stream/StreamConnector12.h"
#include "kdrive/baos/stream/StreamConnector2x.h"
#include "kdrive/baos/core/DataPacket.h"
#include "kdrive/baos/core/BaosConnector.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/Exception.h"
#include <Poco/Format.h>

using namespace kdrive::baos;
using namespace kdrive::connector;

/******************************
** DataRequestFactory
*******************************/

DataRequest::Ptr DataRequestFactory::create(BaosConnector::Ptr connector,
        unsigned char subService,
        unsigned short offset,
        unsigned short count)
{
	const unsigned char version = connector->getVersion();
	return DataRequestFactory::create(version, subService, offset, count);
}

DataRequest::Ptr DataRequestFactory::create(unsigned char version,
        unsigned char subService,
        unsigned short offset,
        unsigned short count)
{
	DataRequest::Ptr dataRequest;

	if (ProtocolVersions::is1x(version))
	{
		dataRequest = PacketFactory12::createDataRequest();
	}
	else if (ProtocolVersions::is2x(version))
	{
		dataRequest = PacketFactory2x::createDataRequest(version);
	}

	if (!dataRequest)
	{
		throw ClientException("Protocol Version Not Supported");
	}

	dataRequest->setMainService(ProtocolConstants::MainService);
	dataRequest->setSubService(subService);
	dataRequest->setOffset(offset);
	dataRequest->setCount(count);
	dataRequest->setVersion(version);

	return dataRequest;
}

/******************************
** ProtocolFormatter
*******************************/

#define PROTOCOL_FORMATTER_IMPL(Fn, dataPacket, arg1) \
	BOOST_ASSERT(dataPacket && "Invalid Data Response"); \
	ProtocolVersions::is1x(dataPacket->getVersion()) ? \
		ProtocolFormatter12::Fn(dataPacket, arg1) : ProtocolFormatter2x::Fn(dataPacket, arg1)

#define PROTOCOL_FORMATTER_IMPL_2X(Fn, dataPacket, arg1) \
	BOOST_ASSERT(dataPacket && "Invalid Data Response"); \
	if (ProtocolVersions::is1x(dataPacket->getVersion())) { throw ClientException("Service not support for 1.x protocols"); } \
	ProtocolFormatter2x::Fn(dataPacket, arg1);

void ProtocolFormatter::decodeGetServerItem_Res(DataPacket::Ptr dataPacket, ServerItems& serverItems)
{
	PROTOCOL_FORMATTER_IMPL(decodeGetServerItem_Res, dataPacket, serverItems);
}

void ProtocolFormatter::encodeSetServerItem_Req(DataPacket::Ptr dataPacket, const ServerItems& serverItems)
{
	PROTOCOL_FORMATTER_IMPL(encodeSetServerItem_Req, dataPacket, serverItems);
}

void ProtocolFormatter::decodeServerItem_Ind(DataPacket::Ptr dataPacket, ServerItems& serverItems)
{
	PROTOCOL_FORMATTER_IMPL(decodeServerItem_Ind, dataPacket, serverItems);
}

void ProtocolFormatter::decodeGetDatapointDescription_Res(DataPacket::Ptr dataPacket, Descriptors& descriptors)
{
	PROTOCOL_FORMATTER_IMPL(decodeGetDatapointDescription_Res, dataPacket, descriptors);
}

void ProtocolFormatter::decodeGetDescriptionString_Res(DataPacket::Ptr dataPacket, Strings& strings)
{
	PROTOCOL_FORMATTER_IMPL(decodeGetDescriptionString_Res, dataPacket, strings);
}

void ProtocolFormatter::encodeGetDatapointValue_Req(DataPacket::Ptr dataPacket, unsigned char filter)
{
	PROTOCOL_FORMATTER_IMPL(encodeGetDatapointValue_Req, dataPacket, filter);
}

void ProtocolFormatter::decodeGetDatapointValue_Res(DataPacket::Ptr dataPacket, ServerItems& serverItems)
{
	PROTOCOL_FORMATTER_IMPL(decodeGetDatapointValue_Res, dataPacket, serverItems);
}

void ProtocolFormatter::decodeDatapointValue_Ind(DataPacket::Ptr dataPacket, ServerItems& serverItems)
{
	PROTOCOL_FORMATTER_IMPL(decodeDatapointValue_Ind, dataPacket, serverItems);
}

void ProtocolFormatter::encodeSetDatapointValue_Req(DataPacket::Ptr dataPacket, const ServerItems& serverItems)
{
	PROTOCOL_FORMATTER_IMPL(encodeSetDatapointValue_Req, dataPacket, serverItems);
}

void ProtocolFormatter::decodeGetParameterByte_Res(DataPacket::Ptr dataPacket, ParameterBytes& parameterBytes)
{
	BOOST_ASSERT(dataPacket && "Invalid Data Response");
	parameterBytes = dataPacket->getBuffer();
}

void ProtocolFormatter::encodeSetDatapointHistoryCommand_Req(std::shared_ptr<DataPacket> dataPacket, unsigned char command)
{
	PROTOCOL_FORMATTER_IMPL_2X(encodeSetDatapointHistoryCommand_Req, dataPacket, command);
}

void ProtocolFormatter::decodeGetTimer_Res(std::shared_ptr<DataPacket> dataPacket, Timers& timers)
{
	PROTOCOL_FORMATTER_IMPL_2X(decodeGetTimer_Res, dataPacket, timers);
}

void ProtocolFormatter::encodeSetTimer_Req(std::shared_ptr<DataPacket> dataPacket, const Timers& timers)
{
	PROTOCOL_FORMATTER_IMPL_2X(encodeSetTimer_Req, dataPacket, timers);
}
