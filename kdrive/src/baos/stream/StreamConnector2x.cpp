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
#include "kdrive/baos/stream/StreamConnector2x.h"
#include "kdrive/baos/protocols/Protocol2x.h"
#include "kdrive/baos/core/DataPacket.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/baos/core/ServerItem.h"
#include "kdrive/baos/core/String.h"
#include "kdrive/connector/Events.h"
#include "kdrive/utility/Logger.h"
#include <Poco/Logger.h>

using namespace kdrive::baos;
using namespace kdrive::connector;
using Poco::Exception;

CLASS_LOGGER("kdrive.baos.StreamConnector2x")

/**********************************
** Anonymous namespace
***********************************/

namespace
{

/*!
	Header for encapsulating of the ObjectServer protocol 2
	in a KNXnet/IP protocol
*/
enum TransportHeader
{
    // KNXnet/IP header
    KnxNetIpHeaderSize = 0,
    Version,
    ObjectServerRequestHigh,
    ObjectServerRequestLow,
    FrameSizeHigh,
    FrameSizeLow,

    // Connection header
    StructureLength, /*< The value is in baos protocol 2 always 4 */
    Reserved1,
    Reserved2,
    Reserved3,

    HeaderSize, /*< Note: This is not a field. It's only a helper */
};

enum Defaults
{
    KnxNetIpHeaderSizeValue = 0x06,			/*!< Size of the KNXNet/IP Header */
    StructureLengthValue = 0x04,			/*!< Size of the Connection Header */
    ObjectServerMessageSizeValue = 0x06,	/*!< Size of Object Server Message Header */
    ObjectServerRequestValue = 0xF080,		/*!< Object Server Request ID */
};

enum class ValidationCode
{
    Valid = 0,
    IncompletePacket,
    InvalidHeaderSize,
    InvalidVersion,
    InvalidService
};

/*
	precondition: buffer holds at least TransportHeader::HeaderSize bytes
*/
unsigned int getFrameSize(const unsigned char* buffer)
{
	const int frameSize = buffer[TransportHeader::FrameSizeHigh] << 8 |
	                      buffer[TransportHeader::FrameSizeLow];
	return frameSize;
}

/*
	Attempts to read the transport packet header (KNXnet/IP)
	If this is not a valid KNXnet/IP packet header an exception
	will be thrown.
*/
ValidationCode isValid(unsigned char version, unsigned char* buffer, std::size_t bufferSize)
{
	if (bufferSize < TransportHeader::HeaderSize)
	{
		return ValidationCode::IncompletePacket;
	}

	if (buffer[TransportHeader::KnxNetIpHeaderSize] != KnxNetIpHeaderSizeValue)
	{
		return ValidationCode::InvalidHeaderSize;
	}

	if (buffer[TransportHeader::Version] != version)
	{
		return ValidationCode::InvalidVersion;
	}

	const unsigned int objectServerRequest = buffer[TransportHeader::ObjectServerRequestHigh] << 8 |
	        buffer[TransportHeader::ObjectServerRequestLow];

	if (objectServerRequest != ObjectServerRequestValue)
	{
		return ValidationCode::InvalidService;
	}

	if (bufferSize < getFrameSize(buffer))
	{
		return ValidationCode::IncompletePacket;
	}

	return ValidationCode::Valid;
}

void initProperties(kdrive::utility::PropertyCollection& collection)
{
	collection.setProperty(StreamConnector2x::PortType, StreamConnector2x::ConnectorTypeLabel);
}

} // end anonymous namespace

/**********************************
** StreamConnector2x
***********************************/

const std::string StreamConnector2x::ConnectorTypeLabel = "baos.tcp.2x";

StreamConnector2x::StreamConnector2x()

	: StreamConnector(ProtocolVersions::V20)
{
	initProperties(*this);
	setPacketFactory(std::make_shared<PacketFactory2x>());
}

StreamConnector2x::StreamConnector2x(const std::string& remoteHost, unsigned short port)

	: StreamConnector(ProtocolVersions::V20, remoteHost, port)
{
	initProperties(*this);
	setPacketFactory(std::make_shared<PacketFactory2x>());
}

StreamConnector2x::~StreamConnector2x()
{
}

void StreamConnector2x::resetPropertiesImpl()
{
	StreamConnector::resetPropertiesImpl();
	initProperties(*this);
}

void StreamConnector2x::openImpl()
{
	std::shared_ptr<PacketFactory2x> packetFactory =
	    std::dynamic_pointer_cast<PacketFactory2x>(getPacketFactory());

	if (!packetFactory)
	{
		throw ClientException("Unable to get PacketFactory2x");
	}

	packetFactory->setProtocolVersion(getVersion());

	StreamConnector::openImpl();
}

void StreamConnector2x::rxImpl()
{
	int length = 0;

	try
	{
		length = readFromSocket(&rxBuffer_.at(0), rxBuffer_.size());
	}
	catch (Exception& exception)
	{
		poco_error_f1(LOGGER(), "Error in rxImpl, %s", exception.displayText());
		routeEvent(ConnectorEvents::Terminated);
		raiseError(exception);
	}

	if (length > 0)
	{
		onReceive(&rxBuffer_.at(0), length);
	}
}

/*!
	Encapsulate it in a KNXnet/IP Packet
*/
std::size_t StreamConnector2x::encapsulate(const Packet::Ptr packet, unsigned char* buffer, std::size_t bufferSize)
{
	const unsigned int frameSize = packet->size() + TransportHeader::HeaderSize;
	if (bufferSize < frameSize)
	{
		throw Exception("Invalid Buffer");
	}

	buffer[TransportHeader::KnxNetIpHeaderSize] = KnxNetIpHeaderSizeValue;
	buffer[TransportHeader::Version] = getVersion();
	buffer[TransportHeader::ObjectServerRequestHigh] = (ObjectServerRequestValue >> 8) & 0xFF;
	buffer[TransportHeader::ObjectServerRequestLow] = ObjectServerRequestValue & 0xFF;
	buffer[TransportHeader::FrameSizeHigh] = (frameSize >> 8) & 0xFF;
	buffer[TransportHeader::FrameSizeLow] = frameSize & 0xFF;
	buffer[TransportHeader::StructureLength] = StructureLengthValue;
	buffer[TransportHeader::Reserved1] = 0x00;
	buffer[TransportHeader::Reserved2] = 0x00;
	buffer[TransportHeader::Reserved3] = 0x00;

	packet->writeToBuffer(buffer + TransportHeader::HeaderSize, bufferSize - TransportHeader::HeaderSize);
	return frameSize;
}

void StreamConnector2x::onReceive(const unsigned char* buffer, std::size_t length)
{
	frameBuffer_.insert(frameBuffer_.end(), buffer, buffer + length);

	int bufferOffset = 0;
	while (packetize(bufferOffset))
	{
		// get the buffer length from the frame
		// and route to the user
		const unsigned char* transportFrame = &frameBuffer_.at(bufferOffset);
		const unsigned int frameSize = getFrameSize(transportFrame);
		onReceiveFrame(transportFrame, frameSize);

		// remove this response frame from the frameBuffer_
		// including whatever came before it (if it isn't at the start of the frame buffer)
		// note, we can have data in the buffer following this packet
		// so we don't clear the buffer, we just erase our response
		frameBuffer_.erase(frameBuffer_.begin(), frameBuffer_.begin() + bufferOffset + frameSize);
	}
}

bool StreamConnector2x::packetize(int& bufferOffset)
{
	bool isValidPacket = false;
	const int size = static_cast<int>(frameBuffer_.size());
	bool eraseData = false;
	for (int index = 0; index < size; ++index)
	{
		switch (isValid(getVersion(), &frameBuffer_.at(index), frameBuffer_.size() - index))
		{
			case ValidationCode::Valid:
				// we have a valid frame
				// set the location for the response in the frame buffer
				// and exit the loop
				isValidPacket = true;
				bufferOffset = index;
				eraseData = false;
				index = size; // ensure we leave the loop
				break;

			case ValidationCode::IncompletePacket:
				// leave the loop, we need more data, but erase up
				// till the start of our packet
				if (index > 0)
				{
					frameBuffer_.erase(frameBuffer_.begin(), frameBuffer_.begin() + index);
				}
				eraseData = false;
				index = size;
				break;

			case ValidationCode::InvalidHeaderSize:
			case ValidationCode::InvalidVersion:
			case ValidationCode::InvalidService:
			default:
				// try the next position
				// we are out of sync or we get an invalid / not supported frame
				eraseData = true;
				break;
		}
	}

	if (eraseData)
	{
		frameBuffer_.clear();
	}

	return isValidPacket;
}

void StreamConnector2x::onReceiveFrame(const unsigned char* transportFrame, std::size_t length)
{
	Packet::Ptr packet = create(transportFrame + TransportHeader::HeaderSize, length - TransportHeader::HeaderSize);
	routeRx(packet);
}
