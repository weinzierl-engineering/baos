//
// Copyright (c) 2002-2016 WEINZIERL ENGINEERING GmbH
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
#include "kdrive/knx/core/Buffer.h"
#include <Poco/Exception.h>
#include <boost/assert.hpp>
#include <cstring>

using namespace kdrive::knx;
using Poco::Exception;

Buffer::Buffer()

	: buffer_(0),
	  bufferLength_(0)
{
}

Buffer::Buffer(unsigned char* buffer, std::size_t bufferSize)

	: buffer_(buffer),
	  bufferLength_(bufferSize)
{
	if (bufferSize)
	{
		BOOST_ASSERT(buffer && "Invalid Pointer");
	}
}

Buffer::~Buffer()
{
}

void Buffer::setBuffer(unsigned char* buffer, std::size_t bufferSize)
{
	if (bufferSize)
	{
		BOOST_ASSERT(buffer && "Invalid Pointer");
	}

	buffer_ = buffer;
	bufferLength_ = bufferSize;
}

void Buffer::setBuffer(std::vector<unsigned char>& buffer)
{
	if (!buffer.empty())
	{
		buffer_ = &buffer.at(0);
		bufferLength_ = buffer.size();
	}
	else
	{
		reset();
	}
}

const unsigned char* Buffer::getBuffer() const
{
	return buffer_;
}

unsigned char* Buffer::getBuffer()
{
	return buffer_;
}

std::size_t Buffer::getBufferSize() const
{
	return bufferLength_;
}

bool Buffer::isBufferEmpty() const
{
	return (!buffer_ || !bufferLength_);
}

void Buffer::reset()
{
	buffer_ = 0;
	bufferLength_ = 0;
}

void Buffer::assign(unsigned char data)
{
	if (!isBufferEmpty())
	{
		std::memset(buffer_, data, bufferLength_);
	}
}

void Buffer::writeByte(unsigned int offset, unsigned char data)
{
	validateInRange(offset);
	buffer_[offset] = data;
}

void Buffer::writeWord(unsigned int offset, unsigned short data)
{
	validateInRange(offset + 1);

	buffer_[offset] = (data >> 8) & 0xFF;
	buffer_[offset + 1] = data & 0xFF;
}

void Buffer::writeBuffer(unsigned int offset, const unsigned char* buffer, std::size_t bufferSize)
{
	if (buffer && bufferSize)
	{
		validateInRange((offset + bufferSize) - 1);
		unsigned char* ptr = buffer_ + offset;
		std::memcpy(ptr, buffer, bufferSize);
	}
}

unsigned char Buffer::readByte(unsigned int offset) const
{
	validateInRange(offset);
	return buffer_[offset];
}

unsigned short Buffer::readWord(unsigned int offset) const
{
	validateInRange(offset + 1);

	unsigned short data = buffer_[offset] << 8;
	data |= buffer_[offset + 1];
	return data;
}

unsigned char* Buffer::readBuffer(unsigned int offset, std::size_t bufferSize)
{
	validateInRange((offset + bufferSize) - 1);
	return buffer_ + offset;
}

const unsigned char* Buffer::readBuffer(unsigned int offset, std::size_t bufferSize) const
{
	validateInRange((offset + bufferSize) - 1);
	return buffer_ + offset;
}

void Buffer::validateInRange(unsigned int offset) const
{
	if (!buffer_ || (offset >= bufferLength_))
	{
		throw Exception("Invalid Buffer");
	}
}
