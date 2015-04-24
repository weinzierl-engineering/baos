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
#include "kdrive/baos/Config.h"
#include "kdrive/baos/protocols/Protocol20.h"
#include "kdrive/baos/core/DataPacket.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/baos/core/ServerItem.h"
#include "kdrive/baos/core/String.h"
#include "kdrive/utility/Logger.h"

using namespace kdrive::baos;
using namespace kdrive::connector;
using Poco::Exception;

CLASS_LOGGER("kdrive.baos.PacketFactory20")

/**********************************
** Anonymous namespace
***********************************/

namespace
{

} // end anonymous namespace

/**********************************
** HeaderPolicy20
***********************************/

std::size_t HeaderPolicy20::size(const DataPacket& /* dataPacket */)
{
	return Protocol20::HeaderSize;
}

std::size_t HeaderPolicy20::read(DataPacket& dataPacket, const unsigned char* buffer, std::size_t bufferSize)
{
	if (bufferSize < Protocol20::HeaderSize)
	{
		throw ClientException("Buffer Underrun");
	}

	dataPacket.setMainService(buffer[Protocol20::MainService]);
	dataPacket.setSubService(buffer[Protocol20::SubService]);
	dataPacket.setOffset(buffer[Protocol20::StartItemHigh] << 8 | buffer[Protocol20::StartItemLow]);
	dataPacket.setCount(buffer[Protocol20::NumberOfItemsHigh] << 8 | buffer[Protocol20::NumberOfItemsLow]);

	return Protocol20::HeaderSize;
}

/*
	frame size is the total number of byte in the packet, including the header
*/
std::size_t HeaderPolicy20::write(const DataPacket& dataPacket, unsigned char* buffer, std::size_t bufferSize_) const
{
	if (bufferSize_ < Protocol20::HeaderSize)
	{
		throw ClientException("Buffer Underrun");
	}

	const unsigned short startItem = dataPacket.getOffset();
	const unsigned short numberOfItems = dataPacket.getCount();

	buffer[Protocol20::MainService] = dataPacket.getMainService();
	buffer[Protocol20::SubService] = dataPacket.getSubService();
	buffer[Protocol20::StartItemHigh] = (startItem >> 8) & 0xFF;
	buffer[Protocol20::StartItemLow] = startItem & 0xFF;
	buffer[Protocol20::NumberOfItemsHigh] = (numberOfItems >> 8) & 0xFF;
	buffer[Protocol20::NumberOfItemsLow] = numberOfItems & 0xFF;

	return Protocol20::HeaderSize;
}

/**********************************
** PacketFactory20
***********************************/

PacketFactory20::PacketFactory20()
{
}

PacketFactory20::~PacketFactory20()
{
}

/*!
    To determine if a packet is an error response we check:
		that the packet has a length of packet header bytes + 1
		and the number of items is 0 and the error code non-zero
*/
Packet::Ptr PacketFactory20::create(const unsigned char* buffer, std::size_t bufferLength)
{
	Packet::Ptr packet;

	if (bufferLength >= Protocol20::HeaderSize)
	{
		unsigned char errorCode = 0x00;
		const unsigned char mainService = buffer[Protocol20::MainService];
		const unsigned char subService = buffer[Protocol20::SubService];
		const unsigned short numberOfItems = (buffer[Protocol20::NumberOfItemsHigh] << 8) |
		                                     buffer[Protocol20::NumberOfItemsLow];

		// if the response length is the header length + 1 and number of items is 0
		// it is an error response, we look up the error code and handle it below
		if ((bufferLength == (Protocol20::HeaderSize + 1)) && !numberOfItems)
		{
			errorCode = buffer[Protocol20::ErrorCode];
		}

		if (mainService == ProtocolConstants::MainService)
		{
			DataPacket::Ptr dataPacket = createFromSubService(subService, errorCode);

			if (dataPacket)
			{
				std::shared_ptr<HeaderPolicy> headerPolicy = std::make_shared<HeaderPolicy20>();
				dataPacket->setHeaderPolicy(headerPolicy);
				dataPacket->setVersion(ProtocolVersions::V20);
				packet = dataPacket;
			}
		}
	}

	if (!packet)
	{
		packet = BaosPacketFactory::create(buffer, bufferLength);
	}

	try
	{
		packet->readFromBuffer(buffer, bufferLength);
	}
	catch (Exception& exception)
	{
		poco_warning(LOGGER(), exception.displayText());
	}

	return packet;
}

DataRequest::Ptr PacketFactory20::createDataRequest()
{
	return dataPacketFactory<DataRequest, HeaderPolicy20>(ProtocolVersions::V20);
}

/**********************************
** ProtocolFormatter20
***********************************/

void ProtocolFormatter20::decodeGetServerItem_Res(DataPacket::Ptr dataPacket,
        ProtocolFormatter::ServerItems& serverItems)
{
	BOOST_ASSERT(dataPacket && "Invalid Data Response");

	const DataResponse::Buffer& buffer = dataPacket->getBuffer();
	const unsigned char* begin = &buffer.at(0);
	const unsigned char* ptr = begin;
	const std::size_t bufferSize = buffer.size();

	const int count = dataPacket->getCount();
	for (int i = 0; i < count; ++i)
	{
		// we should have at least three more bytes in the buffer
		// two for id and one for length

		if (static_cast<std::size_t>((ptr + 3) - begin) > bufferSize)
		{
			throw ClientException("Buffer overrun while decoding Server Item");
		}

		ServerItem value;
		value.id = ((*ptr) << 8) | *(ptr + 1);
		ptr += 2;

		value.serviceData = 0x00;
		value.length = *ptr++;

		if (static_cast<std::size_t>((ptr + value.length) - begin) > bufferSize)
		{
			throw ClientException("Buffer overrun while decoding Server Item");
		}

		value.data = std::vector<unsigned char>(ptr, ptr + value.length);
		ptr += value.length;

		serverItems.push_back(value);
	}
}

void ProtocolFormatter20::encodeSetServerItem_Req(DataPacket::Ptr dataPacket,
        const ProtocolFormatter::ServerItems& serverItems)
{
	BOOST_ASSERT(dataPacket && "Invalid Data Response");

	DataPacket::Buffer& buffer = dataPacket->getBuffer();
	buffer.clear();

	for (const auto& serverItem : serverItems)
	{
		buffer.push_back((serverItem.id >> 8) & 0xFF);
		buffer.push_back(serverItem.id & 0xFF);
		buffer.push_back(serverItem.length);
		std::copy(serverItem.data.begin(), serverItem.data.end(), std::back_inserter(buffer));
	}
}

void ProtocolFormatter20::decodeServerItem_Ind(DataPacket::Ptr dataPacket,
        ProtocolFormatter::ServerItems& serverItems)
{
	decodeGetServerItem_Res(dataPacket, serverItems);
}

/*
	Each item is encoded as:

		Id				2 Bytes
		Value Type		1 Byte
		Config Flags	1 Byte
		Datapoint Type	1 Byte
						--------
						5 Bytes
						========
*/
void ProtocolFormatter20::decodeGetDatapointDescription_Res(DataPacket::Ptr dataPacket,
        ProtocolFormatter::Descriptors& descriptors)
{
	static const int itemLength = 5;

	BOOST_ASSERT(dataPacket && "Invalid Data Response");

	const DataResponse::Buffer& buffer = dataPacket->getBuffer();
	const unsigned char* begin = &buffer.at(0);
	const unsigned char* ptr = begin;
	const std::size_t bufferSize = buffer.size();

	const int count = dataPacket->getCount();

	if (static_cast<std::size_t>(count * itemLength) > bufferSize)
	{
		throw ClientException("Buffer overrun while decoding Datapoint Description");
	}

	for (int i = 0; i < count; ++i)
	{
		const unsigned short id = (ptr[0] << 8) | ptr[1];
		const unsigned char valueType = ptr[2];
		const unsigned char configFlags = ptr[3];
		const unsigned char datapointType = ptr[4];
		ptr += itemLength;
		descriptors.push_back(std::make_tuple(id, valueType, configFlags, datapointType));
	}
}

void ProtocolFormatter20::decodeGetDescriptionString_Res(DataPacket::Ptr dataPacket,
        ProtocolFormatter::Strings& strings)
{
	const int count = dataPacket->getCount();

	if (count)
	{
		const DataResponse::Buffer& buffer = dataPacket->getBuffer();
		const unsigned char* begin = &buffer.at(0);
		const unsigned char* ptr = begin;
		const std::size_t bufferSize = buffer.size();

		for (int i = 0; i < count; ++i)
		{
			// we should have at least two bytes in the buffer
			// to indicate the length of the next string

			if (static_cast<std::size_t>((ptr + 2) - begin) > bufferSize)
			{
				throw ClientException("Buffer overrun while decoding description string length");
			}

			const short length = ptr[0] << 8 | ptr[1];
			ptr += 2;

			// ensure we don't have a buffer overrun

			if (static_cast<std::size_t>((ptr + length) - begin) > bufferSize)
			{
				throw ClientException("Buffer overrun while decoding description string");
			}

			const std::string s = extract(ptr, length);
			strings.push_back(s);
			ptr += length;
		}
	}
}

void ProtocolFormatter20::encodeGetDatapointValue_Req(DataPacket::Ptr dataPacket,
        unsigned char filter)
{
	DataPacket::Buffer& buffer = dataPacket->getBuffer();
	buffer.clear();
	buffer.push_back(filter);
}

void ProtocolFormatter20::decodeGetDatapointValue_Res(DataPacket::Ptr dataPacket,
        ProtocolFormatter::ServerItems& serverItems)
{
	BOOST_ASSERT(dataPacket && "Invalid Data Response");

	const DataResponse::Buffer& buffer = dataPacket->getBuffer();
	const unsigned char* begin = &buffer.at(0);
	const unsigned char* ptr = begin;
	const std::size_t bufferSize = buffer.size();

	const int count = dataPacket->getCount();
	for (int i = 0; i < count; ++i)
	{
		// we should have at least four more bytes in the buffer
		// two for id, one for state and one for length

		if (static_cast<std::size_t>((ptr + 4) - begin) > bufferSize)
		{
			throw ClientException("Buffer overrun while decoding Datapoint Value (id)");
		}

		ServerItem value;
		value.id = ((*ptr) << 8) | *(ptr + 1);
		ptr += 2;

		value.serviceData = *ptr++;
		value.length = *ptr++;

		if (static_cast<std::size_t>((ptr + value.length) - begin) > bufferSize)
		{
			throw ClientException("Buffer overrun while decoding Datapoint Value (buffer)");
		}

		value.data = std::vector<unsigned char>(ptr, ptr + value.length);
		ptr += value.length;

		serverItems.push_back(value);
	}
}

void ProtocolFormatter20::decodeDatapointValue_Ind(DataPacket::Ptr dataPacket,
        ProtocolFormatter::ServerItems& serverItems)
{
	decodeGetDatapointValue_Res(dataPacket, serverItems);
}

void ProtocolFormatter20::encodeSetDatapointValue_Req(DataPacket::Ptr dataPacket,
        const ProtocolFormatter::ServerItems& serverItems)
{
	BOOST_ASSERT(dataPacket && "Invalid Data Response");

	DataPacket::Buffer& buffer = dataPacket->getBuffer();
	buffer.clear();

	for (const auto& serverItem : serverItems)
	{
		buffer.push_back((serverItem.id >> 8) & 0xFF);
		buffer.push_back(serverItem.id & 0xFF);
		buffer.push_back(serverItem.serviceData);
		buffer.push_back(serverItem.length);
		std::copy(serverItem.data.begin(), serverItem.data.end(), std::back_inserter(buffer));
	}
}
