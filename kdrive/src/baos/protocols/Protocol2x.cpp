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

#include "pch/kdrive_pch.h"
#include "kdrive/baos/Config.h"
#include "kdrive/baos/protocols/Protocol2x.h"
#include "kdrive/baos/core/DataPacket.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/baos/core/ServerItem.h"
#include "kdrive/baos/core/Timer.h"
#include "kdrive/baos/core/String.h"
#include "kdrive/utility/Logger.h"
#include <Poco/Exception.h>
#include <Poco/Format.h>

using namespace kdrive::baos;
using namespace kdrive::connector;
using Poco::Exception;
using Poco::format;

CLASS_LOGGER("kdrive.baos.PacketFactory2x")

/**********************************
** anonymous namespace
***********************************/

namespace
{

bool isRemaining(const unsigned char* begin,
                 const unsigned char* ptr,
                 std::size_t bufferSize,
                 std::size_t remaining)
{
	return static_cast<std::size_t>((ptr + remaining) - begin) <= bufferSize;
}


} // end anonymous namespace

/**********************************
** HeaderPolicy2x
***********************************/

std::size_t HeaderPolicy2x::size(const DataPacket& /* dataPacket */)
{
	return Protocol2x::HeaderSize;
}

std::size_t HeaderPolicy2x::read(DataPacket& dataPacket, const unsigned char* buffer, std::size_t bufferSize)
{
	if (bufferSize < Protocol2x::HeaderSize)
	{
		throw ClientException("Buffer Underrun");
	}

	dataPacket.setMainService(buffer[Protocol2x::MainService]);
	dataPacket.setSubService(buffer[Protocol2x::SubService]);
	dataPacket.setOffset(buffer[Protocol2x::StartItemHigh] << 8 | buffer[Protocol2x::StartItemLow]);
	dataPacket.setCount(buffer[Protocol2x::NumberOfItemsHigh] << 8 | buffer[Protocol2x::NumberOfItemsLow]);

	return Protocol2x::HeaderSize;
}

/*
	frame size is the total number of byte in the packet, including the header
*/
std::size_t HeaderPolicy2x::write(const DataPacket& dataPacket, unsigned char* buffer, std::size_t bufferSize_) const
{
	if (bufferSize_ < Protocol2x::HeaderSize)
	{
		throw ClientException("Buffer Underrun");
	}

	const unsigned short startItem = dataPacket.getOffset();
	const unsigned short numberOfItems = dataPacket.getCount();

	buffer[Protocol2x::MainService] = dataPacket.getMainService();
	buffer[Protocol2x::SubService] = dataPacket.getSubService();
	buffer[Protocol2x::StartItemHigh] = (startItem >> 8) & 0xFF;
	buffer[Protocol2x::StartItemLow] = startItem & 0xFF;
	buffer[Protocol2x::NumberOfItemsHigh] = (numberOfItems >> 8) & 0xFF;
	buffer[Protocol2x::NumberOfItemsLow] = numberOfItems & 0xFF;

	return Protocol2x::HeaderSize;
}

/**********************************
** PacketFactory2x
***********************************/

PacketFactory2x::PacketFactory2x()

	: version_(ProtocolVersions::V20)
{
}

PacketFactory2x::~PacketFactory2x()
{
}

void PacketFactory2x::setProtocolVersion(unsigned char version)
{
	if (!ProtocolVersions::is2x(version))
	{
		throw ClientException("PacketFactory2x only supports V2x protocols");
	}
	version_ = version;
}

/*!
    To determine if a packet is an error response we check:
		that the packet has a length of packet header bytes + 1
		and the number of items is 0 and the error code non-zero
*/
Packet::Ptr PacketFactory2x::create(const unsigned char* buffer, std::size_t bufferLength)
{
	Packet::Ptr packet;

	if (bufferLength >= Protocol2x::HeaderSize)
	{
		unsigned char errorCode = 0x00;
		const unsigned char mainService = buffer[Protocol2x::MainService];
		const unsigned char subService = buffer[Protocol2x::SubService];
		const unsigned short numberOfItems = (buffer[Protocol2x::NumberOfItemsHigh] << 8) |
		                                     buffer[Protocol2x::NumberOfItemsLow];

		// if the response length is the header length + 1 and number of items is 0
		// and the last byte is not 0x00 it is an error response
		// we look up the error code and handle it below
		if ((bufferLength == (Protocol2x::HeaderSize + 1)) &&
		    !numberOfItems &&
		    buffer[Protocol2x::ErrorCode])
		{
			errorCode = buffer[Protocol2x::ErrorCode];
		}

		if (mainService == ProtocolConstants::MainService)
		{
			DataPacket::Ptr dataPacket = createFromSubService(subService, errorCode);

			if (dataPacket)
			{
				std::shared_ptr<HeaderPolicy> headerPolicy = std::make_shared<HeaderPolicy2x>();
				dataPacket->setHeaderPolicy(headerPolicy);
				dataPacket->setVersion(version_);
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

DataRequest::Ptr PacketFactory2x::createDataRequest(unsigned char version)
{
	return dataPacketFactory<DataRequest, HeaderPolicy2x>(version);
}

/**********************************
** ProtocolFormatter2x
***********************************/

void ProtocolFormatter2x::decodeGetServerItem_Res(DataPacket::Ptr dataPacket,
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

		if (!isRemaining(begin, ptr, bufferSize, 3))
		{
			throw ClientException("Buffer overrun while decoding Server Item");
		}

		ServerItem value;
		value.id = ((*ptr) << 8) | *(ptr + 1);
		ptr += 2;

		value.serviceData = 0x00;
		value.length = *ptr++;

		if (!isRemaining(begin, ptr, bufferSize, value.length))
		{
			throw ClientException("Buffer overrun while decoding Server Item");
		}

		value.data = std::vector<unsigned char>(ptr, ptr + value.length);
		ptr += value.length;

		serverItems.push_back(value);
	}
}

void ProtocolFormatter2x::encodeSetServerItem_Req(DataPacket::Ptr dataPacket,
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

void ProtocolFormatter2x::decodeServerItem_Ind(DataPacket::Ptr dataPacket,
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
void ProtocolFormatter2x::decodeGetDatapointDescription_Res(DataPacket::Ptr dataPacket,
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

void ProtocolFormatter2x::decodeGetDescriptionString_Res(DataPacket::Ptr dataPacket,
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

			if (!isRemaining(begin, ptr, bufferSize, 2))
			{
				throw ClientException("Buffer overrun while decoding description string length");
			}

			const short length = ptr[0] << 8 | ptr[1];
			ptr += 2;

			// ensure we don't have a buffer overrun
			if (!isRemaining(begin, ptr, bufferSize, length))
			{
				throw ClientException("Buffer overrun while decoding description string");
			}

			const std::string s = extract(ptr, length);
			strings.push_back(s);
			ptr += length;
		}
	}
}

void ProtocolFormatter2x::encodeGetDatapointValue_Req(DataPacket::Ptr dataPacket,
        unsigned char filter)
{
	DataPacket::Buffer& buffer = dataPacket->getBuffer();
	buffer.clear();
	buffer.push_back(filter);
}

void ProtocolFormatter2x::decodeGetDatapointValue_Res(DataPacket::Ptr dataPacket,
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

		if (!isRemaining(begin, ptr, bufferSize, 4))
		{
			throw ClientException("Buffer overrun while decoding Datapoint Value (id)");
		}

		ServerItem value;
		value.id = ((*ptr) << 8) | *(ptr + 1);
		ptr += 2;

		value.serviceData = *ptr++;
		value.length = *ptr++;

		if (!isRemaining(begin, ptr, bufferSize, value.length))
		{
			throw ClientException("Buffer overrun while decoding Datapoint Value (buffer)");
		}

		value.data = std::vector<unsigned char>(ptr, ptr + value.length);
		ptr += value.length;

		serverItems.push_back(value);
	}
}

void ProtocolFormatter2x::decodeDatapointValue_Ind(DataPacket::Ptr dataPacket,
        ProtocolFormatter::ServerItems& serverItems)
{
	decodeGetDatapointValue_Res(dataPacket, serverItems);
}

void ProtocolFormatter2x::encodeSetDatapointValue_Req(DataPacket::Ptr dataPacket,
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

void ProtocolFormatter2x::encodeSetDatapointHistoryCommand_Req(DataPacket::Ptr dataPacket, unsigned char command)
{
	DataPacket::Buffer& buffer = dataPacket->getBuffer();
	buffer.clear();
	buffer.push_back(command);
}

void ProtocolFormatter2x::decodeGetTimer_Res(std::shared_ptr<DataPacket> dataPacket, ProtocolFormatter::Timers& timers)
{
	BOOST_ASSERT(dataPacket && "Invalid Data Response");

	const DataResponse::Buffer& buffer = dataPacket->getBuffer();
	const unsigned char* begin = &buffer.at(0);
	const unsigned char* ptr = begin;
	const std::size_t bufferSize = buffer.size();

	const int count = dataPacket->getCount();
	for (int i = 0; i < count; ++i)
	{
		/********************************
		** timer id
		*********************************/

		// 2 byte timer id
		if (!isRemaining(begin, ptr, bufferSize, 2))
		{
			throw ClientException("Buffer overrun while decoding Timer (id)");
		}

		Timer timer;
		timer.id = ((*ptr) << 8) | *(ptr + 1);
		ptr += 2;

		/********************************
		** timer trigger parameters
		*********************************/

		// Timer trigger parameters
		// 1 byte trigger id + 1 byte trigger block length
		if (!isRemaining(begin, ptr, bufferSize, 2))
		{
			throw ClientException("Buffer overrun while decoding Timer (trigger header)");
		}

		timer.triggerType = *ptr++;
		int triggerParamLength = *ptr++;

		if (timer.triggerType == BaosTimerTypes::TriggerDate)
		{
			if (triggerParamLength != 4)
			{
				throw ClientException(format("Trigger date parameter block size mismatch: %d", triggerParamLength));
			}
			timer.dateTime = (ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ptr[3];
		}
		else if (timer.triggerType == BaosTimerTypes::TriggerInterval)
		{
			if (triggerParamLength != 14)
			{
				throw ClientException(format("Trigger interval parameter block size mismatch: %d", triggerParamLength));
			}
			timer.startDateTime = (ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ptr[3];
			timer.endDateTime = (ptr[4] << 24) | (ptr[5] << 16) | (ptr[6] << 8) | ptr[7];
			timer.weeks = (ptr[8] << 8) | ptr[9];
			timer.days = ptr[10];
			timer.hours = ptr[11];
			timer.minutes = ptr[12];
			timer.seconds = ptr[13];
		}
		else
		{
			throw ClientException("Unknown timer trigger type");
		}

		ptr += triggerParamLength;

		/********************************
		** timer job parameters
		*********************************/

		// Timer job parameters
		// 1 byte job id + 1 byte job block length
		if (!isRemaining(begin, ptr, bufferSize, 2))
		{
			throw ClientException("Buffer overrun while decoding Timer (job header)");
		}

		timer.jobType = *ptr++;
		int jobParamLength = *ptr++;

		if (timer.jobType == BaosTimerTypes::JobSetDatapointValue)
		{
			if (!isRemaining(begin, ptr, bufferSize, jobParamLength))
			{
				throw ClientException("Buffer overrun while decoding Datapoint Value (block)");
			}

			timer.datapointValue.id = ((*ptr) << 8) | *(ptr + 1);
			ptr += 2;

			timer.datapointValue.serviceData = *ptr++;
			timer.datapointValue.length = *ptr++;

			if ((jobParamLength < timer.datapointValue.length) ||
			    (jobParamLength - timer.datapointValue.length) != 4)
			{
				throw ClientException("Buffer overrun while decoding Datapoint Value (value)");
			}

			timer.datapointValue.data = std::vector<unsigned char>(ptr, ptr + timer.datapointValue.length);
			ptr += timer.datapointValue.length;
		}
		else
		{
			throw ClientException("Unknown timer job type");
		}

		/********************************
		** timer description string
		*********************************/

		// we should have at least two bytes in the buffer
		// to indicate the length of the description string

		if (!isRemaining(begin, ptr, bufferSize, 2))
		{
			throw ClientException("Buffer overrun while decoding description string length");
		}

		int descriptionLength = ptr[0] << 8 | ptr[1];
		ptr += 2;

		if (descriptionLength)
		{
			// ensure we don't have a buffer overrun
			if (!isRemaining(begin, ptr, bufferSize, descriptionLength))
			{
				throw ClientException("Buffer overrun while decoding description string");
			}

			timer.description = extract(ptr, descriptionLength);
			ptr += descriptionLength;
		}

		timers.push_back(timer);
	}
}

void ProtocolFormatter2x::encodeSetTimer_Req(std::shared_ptr<DataPacket> dataPacket, const ProtocolFormatter::Timers& timers)
{
	BOOST_ASSERT(dataPacket && "Invalid Data Response");

	DataPacket::Buffer& buffer = dataPacket->getBuffer();
	buffer.clear();

	for (const auto& timer : timers)
	{
		// 2 byte timer id
		buffer.push_back((timer.id >> 8) & 0xFF);
		buffer.push_back(timer.id & 0xFF);

		/********************************
		** timer trigger parameters
		*********************************/

		buffer.push_back(timer.triggerType);

		if (!timer.triggerType)
		{
			// if the trigger type is 0 it is a delete timer request
			// so we skip to the next timer
			continue;
		}
		else if (timer.triggerType == BaosTimerTypes::TriggerDate)
		{
			buffer.push_back(0x04); // parameter block length of 4
			buffer.push_back((timer.dateTime >> 24) & 0xFF);
			buffer.push_back((timer.dateTime >> 16) & 0xFF);
			buffer.push_back((timer.dateTime >> 8) & 0xFF);
			buffer.push_back(timer.dateTime & 0xFF);
		}
		else if (timer.triggerType == BaosTimerTypes::TriggerInterval)
		{
			buffer.push_back(0x0E); // parameter block length of 14
			buffer.push_back((timer.startDateTime >> 24) & 0xFF);
			buffer.push_back((timer.startDateTime >> 16) & 0xFF);
			buffer.push_back((timer.startDateTime >> 8) & 0xFF);
			buffer.push_back(timer.startDateTime & 0xFF);
			buffer.push_back((timer.endDateTime >> 24) & 0xFF);
			buffer.push_back((timer.endDateTime >> 16) & 0xFF);
			buffer.push_back((timer.endDateTime >> 8) & 0xFF);
			buffer.push_back(timer.endDateTime & 0xFF);
			buffer.push_back((timer.weeks >> 8) & 0xFF);
			buffer.push_back(timer.weeks & 0xFF);
			buffer.push_back(timer.days & 0xFF);
			buffer.push_back(timer.hours & 0xFF);
			buffer.push_back(timer.minutes & 0xFF);
			buffer.push_back(timer.seconds & 0xFF);
		}
		else
		{
			// not sure what this one is, set no parameter data and hope for the best
			buffer.push_back(0x00); // parameter block length of 0
		}

		/********************************
		** timer job parameters
		*********************************/

		buffer.push_back(timer.jobType);

		if (timer.jobType == BaosTimerTypes::JobSetDatapointValue)
		{
			buffer.push_back(0x04 + timer.datapointValue.data.size()); // parameter block length of 4 + data
			buffer.push_back((timer.datapointValue.id >> 8) & 0xFF);
			buffer.push_back(timer.datapointValue.id & 0xFF);
			buffer.push_back(timer.datapointValue.serviceData);
			buffer.push_back(static_cast<unsigned char>(timer.datapointValue.data.size()));
			std::copy(timer.datapointValue.data.begin(), timer.datapointValue.data.end(), std::back_inserter(buffer));
		}
		else
		{
			// not sure what this one is, set no parameter data and hope for the best
			buffer.push_back(0x00); // parameter block length of 0
		}

		/********************************
		** timer description string
		*********************************/

		unsigned short descriptionLength = timer.description.size();
		buffer.push_back((descriptionLength >> 8) & 0xFF);
		buffer.push_back(descriptionLength & 0xFF);
		std::copy(timer.description.begin(), timer.description.end(), std::back_inserter(buffer));
	}
}
