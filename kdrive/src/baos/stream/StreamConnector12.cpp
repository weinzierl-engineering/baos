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
#include "kdrive/baos/stream/StreamConnector12.h"
#include "kdrive/baos/protocols/Protocol12.h"
#include "kdrive/baos/core/DataPacket.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/baos/core/ServerItem.h"
#include "kdrive/baos/core/String.h"
#include "kdrive/connector/Events.h"
#include "kdrive/utility/Logger.h"

using namespace kdrive::baos;
using namespace kdrive::connector;
using Poco::Exception;

CLASS_LOGGER("kdrive.baos.PacketFactory12")

/**********************************
** StreamConnector12
***********************************/

StreamConnector12::StreamConnector12()

	: StreamConnector(ProtocolVersions::V12)
{
	PacketFactory12::Ptr packetFactory(new PacketFactory12);
	setPacketFactory(packetFactory);
}

StreamConnector12::StreamConnector12(const std::string& remoteHost, unsigned short port)

	: StreamConnector(ProtocolVersions::V12, remoteHost, port)
{
	PacketFactory12::Ptr packetFactory(new PacketFactory12);
	setPacketFactory(packetFactory);
}

StreamConnector12::~StreamConnector12()
{
}

void StreamConnector12::rxImpl()
{
	poco_information(LOGGER(), "rxImpl");

	try
	{
		rxBuffer_.fill(0);
		unsigned char* buffer = &rxBuffer_.at(0);
		const int dataLength = packetize(buffer, BufferSize);

		if (dataLength)
		{
			Packet::Ptr packet = create(buffer, dataLength);
			routeRx(packet);
		}
	}
	catch (Exception& exception)
	{
		poco_error_f1(LOGGER(), "Error in rxImpl, %s", exception.displayText());
		routeEvent(ConnectorEvents::Terminated);
		raiseError(exception);
	}
}

/*!
	No additioanl encapsulation is need
*/
std::size_t StreamConnector12::encapsulate(const Packet::Ptr packet, unsigned char* buffer, std::size_t bufferSize)
{
	const std::size_t size = packet->writeToBuffer(buffer, bufferSize);
	return size;
}

int StreamConnector12::packetize(unsigned char* buffer, std::size_t bufferSize)
{
	int dataLength = readFromSocket(buffer, bufferSize, Protocol12::HeaderSize, false);

	if (dataLength == Protocol12::HeaderSize)
	{
		// check the main service
		if (buffer[0] != ProtocolConstants::MainService)
		{
			throw ClientException("Invalid Service");
		}

		if (!buffer[Protocol12::NumberOfItems])
		{
			// this is an error response, receive 1 byte
			return rx(buffer, bufferSize, Protocol12::HeaderSize, 1);
		}

		switch (buffer[Protocol12::SubService])
		{
			case ResponseFunctions::GetServerItem:
				return receiveGetServerItemRes(buffer, bufferSize);

			case ResponseFunctions::SetServerItem:
				return receiveSetServerItemRes(buffer, bufferSize);

			case ResponseFunctions::GetDatapointDescription:
				return receiveGetDatapointDescriptionRes(buffer, bufferSize);

			case ResponseFunctions::GetDescriptionString:
				return receiveGetDescriptionStringRes(buffer, bufferSize);

			case ResponseFunctions::GetDatapointValue:
				return receiveGetDatapointValueRes(buffer, bufferSize);

			case ResponseFunctions::SetDatapointValue:
				return receiveSetDatapointValueRes(buffer, bufferSize);

			case ResponseFunctions::GetParameterByte:
				return receiveGetParameterByteRes(buffer, bufferSize);

			case IndicationFunctions::DatapointValueIndication:
				return receiveDatapointValueInd(buffer, bufferSize);
		}
	}
	else
	{
		dataLength = 0;
	}

	return dataLength;
}

int StreamConnector12::receiveGetServerItemRes(unsigned char* buffer, std::size_t bufferSize)
{
	int bufferIterator = Protocol12::HeaderSize;
	const int numberOfItems = buffer[Protocol12::NumberOfItems];

	if (numberOfItems)
	{
		for (int index = 0; index < numberOfItems; ++index)
		{
			// we need to read 2 bytes before we can work out the length
			// then we can read the length and then receive n bytes
			bufferIterator = rx(buffer, bufferSize, bufferIterator, 2);
			bufferIterator = rx(buffer, bufferSize, bufferIterator, buffer[bufferIterator - 1]);
		}
	}
	else
	{
		bufferIterator = rx(buffer, bufferSize, bufferIterator, 1);
	}

	return bufferIterator;
}

int StreamConnector12::receiveSetServerItemRes(unsigned char* buffer, std::size_t bufferSize)
{
	return rx(buffer, bufferSize, Protocol12::HeaderSize, 1);
}

int StreamConnector12::receiveGetDatapointDescriptionRes(unsigned char* buffer, std::size_t bufferSize)
{
	// if number of items is not 0x00 we expect 2 bytes for each item
	// i.e. value type, config flags
	// if 0x00 it's an error packet and we expect 1 more byte

	int numberOfItems = buffer[Protocol12::NumberOfItems];
	numberOfItems = numberOfItems ? numberOfItems * 2 : 1;

	return rx(buffer, bufferSize, Protocol12::HeaderSize, numberOfItems);
}

int StreamConnector12::receiveGetDescriptionStringRes(unsigned char* buffer, std::size_t bufferSize)
{
	// each string has a hard-coded length of 32 bytes

	int numberOfStrings = buffer[Protocol12::NumberOfItems];
	numberOfStrings = numberOfStrings * Protocol12::DescriptionStringLength;

	return rx(buffer, bufferSize, Protocol12::HeaderSize, numberOfStrings);
}

int StreamConnector12::receiveGetDatapointValueRes(unsigned char* buffer, std::size_t bufferSize)
{
	int bufferIterator = Protocol12::HeaderSize;
	const int numberOfItems = buffer[Protocol12::NumberOfItems];

	if (numberOfItems)
	{
		for (int index = 0; index < numberOfItems; ++index)
		{
			// we need to read 2 bytes before we can work out the length
			// then we can read the length and then receive n bytes
			bufferIterator = rx(buffer, bufferSize, bufferIterator, 2);
			bufferIterator = rx(buffer, bufferSize, bufferIterator, buffer[bufferIterator - 1] & 0x0F);
		}
	}
	else
	{
		bufferIterator = rx(buffer, bufferSize, bufferIterator, 1);
	}

	return bufferIterator;
}

int StreamConnector12::receiveSetDatapointValueRes(unsigned char* buffer, std::size_t bufferSize)
{
	return rx(buffer, bufferSize, Protocol12::HeaderSize, 1);
}

int StreamConnector12::receiveGetParameterByteRes(unsigned char* buffer, std::size_t bufferSize)
{
	// if number of items is not 0x00 we expect 1 bytes for each item
	// if 0x00 it's an error packet and we expect 1 more byte

	int numberOfItems = buffer[Protocol12::NumberOfItems];
	if (!numberOfItems)
	{
		numberOfItems = 1;
	}

	return rx(buffer, bufferSize, Protocol12::HeaderSize, numberOfItems);
}

int StreamConnector12::receiveDatapointValueInd(unsigned char* buffer, std::size_t bufferSize)
{
	int bufferIterator = Protocol12::HeaderSize;
	const int numberOfItems = buffer[Protocol12::NumberOfItems];

	if (!numberOfItems)
	{
		throw ClientException("Expected number of items");
	}

	for (int index = 0; index < numberOfItems; ++index)
	{
		// we need to read 2 bytes before we can work out the length
		// then we can read the length and then receive n bytes
		bufferIterator = rx(buffer, bufferSize, bufferIterator, 2);
		bufferIterator = rx(buffer, bufferSize, bufferIterator, buffer[bufferIterator - 1] & 0x07);
	}

	return bufferIterator;
}

int StreamConnector12::rx(unsigned char* buffer, std::size_t bufferSize, int pos, int length)
{
	return length ? pos + readFromSocket(buffer + pos, bufferSize - pos, length, true) : pos;
}
