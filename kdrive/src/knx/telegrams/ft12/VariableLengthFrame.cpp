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
#include "kdrive/knx/telegrams/ft12/VariableLengthFrame.h"
#include "kdrive/knx/defines/FT12Constants.h"
#include <algorithm>
#include <numeric>

using namespace kdrive::knx::ft12;
using kdrive::knx::Buffer;

VariableLengthFrame::VariableLengthFrame()
{
}

VariableLengthFrame::~VariableLengthFrame()
{
}

/*
	The frame size is the header length + the two user attributes
	control field (1 byte) + user data buffer length
*/
std::size_t VariableLengthFrame::size() const
{
	return HeaderLength + userData_.size() + 1;
}

/*
	Note: length is control field + link user data
*/
bool VariableLengthFrame::isValid() const
{
	return ((startByte1_.get() == FT12Constants::StartVarLengthFrame) &&
	        (endByte_.get() == FT12Constants::EndFrame) &&
	        (length1_.get() == length2_.get()) &&
	        (length1_.get() == (userData_.size() + 1)) &&
	        (checksum_.get() == calculateChecksum()));
}

void VariableLengthFrame::setDefaults()
{
	startByte1_.set(FT12Constants::StartVarLengthFrame);
	length1_.set(1);
	length2_.set(1);
	startByte2_.set(FT12Constants::StartVarLengthFrame);
	controlField_.set(0x00);
	checksum_.set(0x00);
	endByte_.set(FT12Constants::EndFrame);
}

unsigned char VariableLengthFrame::getStartByte1() const
{
	return startByte1_.get();
}

unsigned char VariableLengthFrame::getLength1() const
{
	return length1_.get();
}

unsigned char VariableLengthFrame::getLength2() const
{
	return length2_.get();
}

unsigned char VariableLengthFrame::getStartByte2() const
{
	return startByte2_.get();
}

void VariableLengthFrame::setControlField(unsigned char controlField)
{
	controlField_.set(controlField);
}

unsigned char VariableLengthFrame::getControlField() const
{
	return controlField_.get();
}

void VariableLengthFrame::setUserData(const unsigned char* buffer, std::size_t bufferSize)
{
	if (buffer && bufferSize)
	{
		userData_.resize(bufferSize);
		std::copy(buffer, buffer + bufferSize, userData_.begin());
	}
	else
	{
		userData_.clear();
	}
}

const std::vector<unsigned char>& VariableLengthFrame::getUserData() const
{
	return userData_;
}

void VariableLengthFrame::setChecksum(unsigned char checksum)
{
	checksum_.set(checksum);
}

unsigned char VariableLengthFrame::getChecksum() const
{
	return checksum_.get();
}

unsigned char VariableLengthFrame::getEndByte() const
{
	return endByte_.get();
}

/*
	Note: length is control field + link user data
*/
void VariableLengthFrame::setVariableAttributes()
{
	const unsigned char length = static_cast<unsigned char>(userData_.size()) + 1;
	const unsigned char checkSum = calculateChecksum();

	length1_.set(length);
	length2_.set(length);
	checksum_.set(checkSum);
}

std::size_t VariableLengthFrame::readImpl(const Buffer& buffer)
{
	startByte1_.set(buffer.readByte(StartByte1));
	length1_.set(buffer.readByte(Length1));
	length2_.set(buffer.readByte(Length2));
	startByte2_.set(buffer.readByte(StartByte2));
	controlField_.set(buffer.readByte(ControlField));

	// offset for control field, which is part of user data
	const int userDataLength = length1_.get() - 1;
	const unsigned char* ptr = buffer.readBuffer(LinkUserDataBytes, userDataLength);
	setUserData(ptr, userDataLength);

	const int checksumOffset = getChecksumOffset();
	checksum_.set(buffer.readByte(checksumOffset));
	endByte_.set(buffer.readByte(checksumOffset + 1));

	return size();
}

std::size_t VariableLengthFrame::writeImpl(Buffer& buffer)
{
	buffer.writeByte(StartByte1, startByte1_.get());
	buffer.writeByte(Length1, length1_.get());
	buffer.writeByte(Length2, length2_.get());
	buffer.writeByte(StartByte2, startByte2_.get());
	buffer.writeByte(ControlField, controlField_.get());

	if (!userData_.empty())
	{
		buffer.writeBuffer(LinkUserDataBytes, &userData_.at(0), userData_.size());
	}

	const int checksumOffset = getChecksumOffset();
	buffer.writeByte(checksumOffset, checksum_.get());
	buffer.writeByte(checksumOffset + 1, endByte_.get());

	return size();
}

/*
	The sequence of user data characters shall be terminated by an 8 bit checksum.
	The checksum shall be the arithmetic sum disregarding overflows
	(sum modulo 256) over all user data octets. User data octets is the control field
	and the user data.
*/
unsigned char VariableLengthFrame::calculateChecksum() const
{
	return std::accumulate(userData_.begin(), userData_.end(), controlField_.get());
}

/*
	We can't use the Checksum and EndByte offsets because the user data is
	variable length. This function calculates the real offset of the
	end of user data (i.e. Checksum field).
	We have to do user data size - 1 because we already allocate 1 byte
	for LinkUserDataBytes in the attributes enum
*/
int VariableLengthFrame::getChecksumOffset() const
{
	return Checksum + (userData_.size() - 1);
}
