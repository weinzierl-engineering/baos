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
#include "kdrive/baos/protocols/Protocol12.h"
#include "kdrive/baos/core/DataPacket.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/baos/core/ServerItem.h"
#include "kdrive/baos/core/String.h"
#include "kdrive/utility/Logger.h"

using namespace kdrive::baos;
using namespace kdrive::connector;
using Poco::Exception;

CLASS_LOGGER("kdrive.baos.PacketFactory12")

/**********************************
** HeaderPolicy12
***********************************/

std::size_t HeaderPolicy12::size(const DataPacket& /* dataPacket */)
{
	return Protocol12::HeaderSize;
}

std::size_t HeaderPolicy12::read(DataPacket& dataPacket, const unsigned char* buffer, std::size_t bufferSize)
{
	if (bufferSize < Protocol12::HeaderSize)
	{
		throw ClientException("Buffer Underrun");
	}

	dataPacket.setMainService(buffer[Protocol12::MainService]);
	dataPacket.setSubService(buffer[Protocol12::SubService]);
	dataPacket.setOffset(buffer[Protocol12::StartItem]);
	dataPacket.setCount(buffer[Protocol12::NumberOfItems]);

	return Protocol12::HeaderSize;
}

std::size_t HeaderPolicy12::write(const DataPacket& dataPacket, unsigned char* buffer, std::size_t bufferSize) const
{
	if (bufferSize < Protocol12::HeaderSize)
	{
		throw ClientException("Buffer Underrun");
	}

	buffer[Protocol12::MainService] = dataPacket.getMainService();
	buffer[Protocol12::SubService] = dataPacket.getSubService();
	buffer[Protocol12::StartItem] = static_cast<unsigned char>(dataPacket.getOffset());
	buffer[Protocol12::NumberOfItems] = static_cast<unsigned char>(dataPacket.getCount());

	return Protocol12::HeaderSize;
}

/**********************************
** PacketFactory12
***********************************/

PacketFactory12::PacketFactory12()
{
}

PacketFactory12::~PacketFactory12()
{
}

/*!
    To determine if a packet is an error response we check the length
    If the packet has a length of 5 bytes it is a potential error response
    However there are several valid responses that also have a length of 5 bytes
    So we additionally check the error code. If it is non-zero and number of items is 0
	we set it as a error response packet otherwise it gets processed as normal
*/
Packet::Ptr PacketFactory12::create(const unsigned char* buffer, std::size_t bufferLength)
{
	Packet::Ptr packet;

	if (bufferLength >= Protocol12::HeaderSize)
	{
		unsigned char mainService = buffer[Protocol12::MainService];
		unsigned char subService = buffer[Protocol12::SubService];
		unsigned char errorCode = 0x00;

		// if the response length is the header length + 1 and number of items is 0
		// it is an error response, we look up the error code and handle it below
		if (bufferLength == Protocol12::HeaderSize + 1 && !buffer[Protocol12::NumberOfItems])
		{
			errorCode = buffer[Protocol12::ErrorCode];
		}

		if (mainService == ProtocolConstants::MainService)
		{
			DataPacket::Ptr dataPacket = createFromSubService(subService, errorCode);

			if (dataPacket)
			{
				std::shared_ptr<HeaderPolicy> headerPolicy = std::make_shared<HeaderPolicy12>();
				dataPacket->setHeaderPolicy(headerPolicy);
				dataPacket->setVersion(ProtocolVersions::V12);
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

DataRequest::Ptr PacketFactory12::createDataRequest()
{
	return dataPacketFactory<DataRequest, HeaderPolicy12>(ProtocolVersions::V12);
}

/**********************************
** DatapointDescriptionDecoder12
***********************************/

void ProtocolFormatter12::decodeGetServerItem_Res(DataPacket::Ptr dataPacket,
        ProtocolFormatter::ServerItems& serverItems)
{
	BOOST_ASSERT(dataPacket && "Invalid Data Response");

	const DataPacket::Buffer& buffer = dataPacket->getBuffer();
	const unsigned char* begin = &buffer.at(0);
	const unsigned char* ptr = begin;
	const std::size_t bufferSize = buffer.size();

	const int count = dataPacket->getCount();
	for (int i = 0; i < count; ++i)
	{
		// we should have at least two more bytes in the buffer
		// one for id and one for length

		if (static_cast<std::size_t>((ptr + 2) - begin) > bufferSize)
		{
			throw ClientException("Buffer overrun while decoding Server Item (id)");
		}

		ServerItem value;
		value.id = *ptr++;
		value.serviceData = 0;
		value.length = *ptr++;

		if (static_cast<std::size_t>((ptr + value.length) - begin) > bufferSize)
		{
			throw ClientException("Buffer overrun while decoding Server Item (buffer)");
		}

		value.data = std::vector<unsigned char>(ptr, ptr + value.length);
		ptr += value.length;

		serverItems.push_back(value);
	}
}

void ProtocolFormatter12::encodeSetServerItem_Req(DataPacket::Ptr dataPacket,
        const ProtocolFormatter::ServerItems& serverItems)
{
	BOOST_ASSERT(dataPacket && "Invalid Data Response");

	DataPacket::Buffer& buffer = dataPacket->getBuffer();
	buffer.clear();

	for (const auto& serverItem : serverItems)
	{
		buffer.push_back(static_cast<unsigned char>(serverItem.id));
		buffer.push_back(serverItem.length);
		std::copy(serverItem.data.begin(), serverItem.data.end(), std::back_inserter(buffer));
	}
}

void ProtocolFormatter12::decodeServerItem_Ind(DataPacket::Ptr dataPacket,
        ProtocolFormatter::ServerItems& serverItems)
{
	decodeGetServerItem_Res(dataPacket, serverItems);
}

void ProtocolFormatter12::decodeGetDatapointDescription_Res(DataPacket::Ptr dataPacket,
        ProtocolFormatter::Descriptors& descriptors)
{
	BOOST_ASSERT(dataPacket && "Invalid Data Response");

	const DataPacket::Buffer& buffer = dataPacket->getBuffer();
	const unsigned char* begin = &buffer.at(0);
	const unsigned char* ptr = begin;
	const std::size_t bufferSize = buffer.size();

	const int count = dataPacket->getCount();
	unsigned short offset = dataPacket->getOffset();

	if (static_cast<std::size_t>(count * 2) > bufferSize)
	{
		throw ClientException("Buffer overrun while decoding Datapoint Description");
	}

	for (int i = 0; i < count; ++i)
	{
		const unsigned char valueType = *ptr++;
		const unsigned char configFlags = *ptr++;
		descriptors.push_back(std::make_tuple(offset++, valueType, configFlags, 0x00));
	}
}

void ProtocolFormatter12::decodeGetDescriptionString_Res(DataPacket::Ptr dataPacket,
        ProtocolFormatter::Strings& strings)
{
	const int count = dataPacket->getCount();

	if (count)
	{
		const DataPacket::Buffer& buffer = dataPacket->getBuffer();
		const unsigned char* begin = &buffer.at(0);
		const unsigned char* ptr = begin;
		const std::size_t bufferSize = buffer.size();

		if (static_cast<std::size_t>(count * Protocol12::DescriptionStringLength) > bufferSize)
		{
			throw ClientException("Buffer overrun while decoding String Description");
		}

		for (int i = 0; i < count; ++i)
		{
			const std::string s = extract(ptr, Protocol12::DescriptionStringLength);
			strings.push_back(s);
			ptr += Protocol12::DescriptionStringLength;
		}
	}
}

void ProtocolFormatter12::encodeGetDatapointValue_Req(DataPacket::Ptr /* dataPacket */,
        unsigned char /* filter */)
{
	// nothing to do, filter not supported
}

void ProtocolFormatter12::decodeGetDatapointValue_Res(DataPacket::Ptr dataPacket,
        ProtocolFormatter::ServerItems& serverItems)
{
	BOOST_ASSERT(dataPacket && "Invalid Data Response");

	const DataPacket::Buffer& buffer = dataPacket->getBuffer();
	const unsigned char* begin = &buffer.at(0);
	const unsigned char* ptr = begin;
	const std::size_t bufferSize = buffer.size();

	const int count = dataPacket->getCount();
	for (int i = 0; i < count; ++i)
	{
		// we should have at least two more bytes in the buffer
		// one for id and one for state/length

		if (static_cast<std::size_t>((ptr + 2) - begin) > bufferSize)
		{
			throw ClientException("Buffer overrun while decoding Datapoint Value (id)");
		}

		ServerItem value;
		value.id = *ptr++;
		const unsigned char stateLength = *ptr++;
		value.serviceData = (stateLength << 4) & 0xF0;
		value.length = stateLength & 0x0F;

		if (static_cast<std::size_t>((ptr + value.length) - begin) > bufferSize)
		{
			throw ClientException("Buffer overrun while decoding Datapoint Value (buffer)");
		}

		value.data = std::vector<unsigned char>(ptr, ptr + value.length);
		ptr += value.length;

		serverItems.push_back(value);
	}
}

void ProtocolFormatter12::decodeDatapointValue_Ind(DataPacket::Ptr dataPacket,
        ProtocolFormatter::ServerItems& serverItems)
{
	decodeGetDatapointValue_Res(dataPacket, serverItems);
}

void ProtocolFormatter12::encodeSetDatapointValue_Req(DataPacket::Ptr dataPacket,
        const ProtocolFormatter::ServerItems& serverItems)
{
	BOOST_ASSERT(dataPacket && "Invalid Data Response");

	DataPacket::Buffer& buffer = dataPacket->getBuffer();
	buffer.clear();

	for (const auto& serverItem : serverItems)
	{
		const unsigned char commandLength = ((serverItem.serviceData << 4) & 0xF0) |
		                                    (serverItem.length & 0x0F);

		buffer.push_back(serverItem.id & 0xFF);
		buffer.push_back(commandLength);
		std::copy(serverItem.data.begin(), serverItem.data.end(), std::back_inserter(buffer));
	}
}
