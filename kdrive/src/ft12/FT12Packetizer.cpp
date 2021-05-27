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
#include "kdrive/ft12/FT12Packetizer.h"
#include "kdrive/knx/telegrams/ft12/FT12.h"
#include "kdrive/io/serial/SerialPort.h"
#include "kdrive/utility/ScopedSemaphore.h"
#include "kdrive/utility/LoggerFormatter.h"
#include "kdrive/utility/Logger.h"
#include <Poco/Logger.h>
#include <Poco/Message.h>
#include <Poco/NumberFormatter.h>
#include <boost/assert.hpp>
#include <algorithm>
#include <numeric>

using namespace kdrive::ft12;
using namespace kdrive::knx;
using namespace kdrive::knx::ft12;
using namespace kdrive::utility;
using Poco::Logger;
using Poco::Message;
using Poco::NumberFormatter;

CLASS_LOGGER("kdrive.ft12.FT12_Packetizer")

// 50 milliseconds (in microseconds), the max inter-character timeout
static const long shortTimeout = 500 * 1000;

FT12_Packetizer::FT12_Packetizer(kdrive::io::serial::SerialPort& serialPort, long timeout)

	: serialPort_(serialPort),
	  semaphore_(1),
	  timeout_(timeout * 1000),
	  autoAck_(true)
{
}

FT12_Packetizer::~FT12_Packetizer()
{
}

std::size_t FT12_Packetizer::get(unsigned char* buffer, std::size_t bufferSize)
{
	BOOST_ASSERT(buffer && "Invalid Buffer Pointer");
	BOOST_ASSERT(bufferSize >= 1 && "Invalid Buffer Size");

	void* pV = static_cast<void*>(buffer);
	char* ptr = static_cast<char*>(pV);

	std::size_t length = 0;

	if (readBytes(ptr, 1, timeout_) == 1)
	{
		length = readFrame(buffer, bufferSize);
	}

	if (length && (LOGGER().getLevel() >= Message::PRIO_DEBUG))
	{
		poco_information_f1(LOGGER(), "ft1.2 rx: %s", LoggerFormatter::toHex(buffer, length));
	}

	return length;
}

void FT12_Packetizer::sendBuffer(const unsigned char* buffer, std::size_t bufferSize)
{
	BOOST_ASSERT(buffer && "Invalid Buffer");
	BOOST_ASSERT(bufferSize && "Invalid Buffer Size");

	ScopedSemaphore scopedSemaphore(semaphore_);
	const void* pV = static_cast<const void*>(buffer);
	const char* ptr = static_cast<const char*>(pV);
	serialPort_.write(ptr, bufferSize);

	if (LOGGER().getLevel() >= Message::PRIO_DEBUG)
	{
		poco_information_f1(LOGGER(), "ft1.2 tx: %s", LoggerFormatter::toHex(buffer, bufferSize));
	}
}

void FT12_Packetizer::enableAutoAck(bool enabled)
{
	autoAck_ = enabled;
}

std::size_t FT12_Packetizer::readBytes(char* buffer, std::size_t bytesToRead, long timeout)
{
	std::size_t length = 0;
	while ((length < bytesToRead) && serialPort_.poll(timeout))
	{
		const std::size_t n = serialPort_.read(buffer + length, bytesToRead - length);

		if (n > 0)
		{
			length += n;
		}
	}

	return length;
}

std::size_t FT12_Packetizer::readFrame(unsigned char* buffer, std::size_t bufferSize)
{
	std::size_t length = 0;

	if (*buffer == FT12Constants::AckFrame)
	{
		length = 1;
	}
	else if (*buffer == FT12Constants::StartFixedLengthFrame)
	{
		length = readFixedFrame(buffer, bufferSize);
	}
	else if (*buffer == FT12Constants::StartVarLengthFrame)
	{
		length = readVariableFrame(buffer, bufferSize);
	}

	return length;
}

std::size_t FT12_Packetizer::readFixedFrame(unsigned char* buffer, std::size_t bufferSize)
{
	BOOST_ASSERT(FixedLengthFrame::Length <= bufferSize && "Invalid Buffer Size");

	void* pV = static_cast<void*>(buffer);
	char* ptr = static_cast<char*>(pV);

	// we already have the start byte, so read the other three bytes,
	// and add one to the length to adjust for the start byte
	std::size_t length = readBytes(ptr + 1, FixedLengthFrame::Length - 1, shortTimeout) + 1;

	// we already know that the first byte, the start byte, matches, so no need to check
	const bool valid = (length == FixedLengthFrame::Length) &&
	                   (buffer[FixedLengthFrame::ControlField] == buffer[FixedLengthFrame::Checksum]) &&
	                   (buffer[FixedLengthFrame::EndByte] == FT12Constants::EndFrame);

	if (valid)
	{
		sendAck();
	}
	else
	{
		length = 0;
	}

	return length;
}

std::size_t FT12_Packetizer::readVariableFrame(unsigned char* buffer, std::size_t bufferSize)
{
	BOOST_ASSERT(bufferSize > VariableLengthFrame::EndByte && "Invalid Buffer Size");

	Logger& logger = Logger::get("FT12_Packetizer");

	void* pV = static_cast<void*>(buffer);
	char* ptr = static_cast<char*>(pV);

	// we have already read the start byte, so adjust the pointer
	++ptr;

	// try and read the two length bytes and the end of header (second start byte)
	if (readBytes(ptr, 3, shortTimeout) != 3)
	{
		poco_information(logger, "Unable to read variable frame length bytes");
		return 0;
	}

	ptr += 3;

	const unsigned char length1 = buffer[VariableLengthFrame::Length1];
	const unsigned char length2 = buffer[VariableLengthFrame::Length2];

	if (length1 != length2)
	{
		poco_information(logger, "Variable length frame length bytes do not match");
		return 0;
	}

	if (buffer[VariableLengthFrame::StartByte2] != FT12Constants::StartVarLengthFrame)
	{
		poco_information(logger, "Variable length frame second start byte does not match");
		return 0;
	}

	BOOST_ASSERT(bufferSize >= (VariableLengthFrame::HeaderLength + length1 + 2) && "Invalid Buffer Size");

	// try and read the user data bytes and final two characters, checksum and end byte
	if (readBytes(ptr, length1 + 2, shortTimeout) != length1 + 2)
	{
		poco_information(logger, "Unable to read variable length end of frame");
		return 0;
	}

	// calculate the checksum
	const unsigned char* userData = buffer + VariableLengthFrame::ControlField;
	const unsigned char checksum = std::accumulate(userData, userData + length1, 0);

	// calculate the checksum offset and check the checksum
	const int offset = VariableLengthFrame::ControlField + length1;
	if (buffer[offset] != checksum)
	{
		poco_information(logger, "Variable length frame checksum failed");
		return 0;
	}

	// finally check the end byte
	if (buffer[offset + 1] != FT12Constants::EndFrame)
	{
		poco_information(logger, "Variable length frame end byte does not match");
		return 0;
	}

	sendAck();

	return VariableLengthFrame::HeaderLength + length1;
}

void FT12_Packetizer::sendAck()
{
	if (autoAck_)
	{
		const unsigned char ack = FT12Constants::AckFrame;
		sendBuffer(&ack, 1);
	}
}
