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
#include "kdrive/knx/telegrams/formatters/Formatter.h"
#include "kdrive/knx/core/ByteStream.h"
#include <boost/assert.hpp>
#include <algorithm>

using namespace kdrive::knx;

/**************************************
** AbstractFormatter
***************************************/

AbstractFormatter::AbstractFormatter()
{
}

AbstractFormatter::~AbstractFormatter()
{
}

std::size_t AbstractFormatter::read(std::vector<unsigned char>& buffer)
{
	Buffer b;
	b.setBuffer(buffer);

	return read(b);
}

std::size_t AbstractFormatter::read(const Buffer& buffer)
{
	prepareRead();
	const std::size_t size = readImpl(buffer);
	postRead();
	return size;
}

std::size_t AbstractFormatter::write(std::vector<unsigned char>& buffer)
{
	buffer.resize(size());

	Buffer b;
	b.setBuffer(buffer);

	return write(b);
}

std::size_t AbstractFormatter::write(Buffer& buffer)
{
	prepareWrite();
	const std::size_t size = writeImpl(buffer);
	postWrite();
	return size;
}

void AbstractFormatter::setDefaults()
{
	// nothing to do
}

void AbstractFormatter::prepareRead()
{
	// nothing to do
}

void AbstractFormatter::postRead()
{
	// nothing to do
}

void AbstractFormatter::prepareWrite()
{
	// nothing to do
}

void AbstractFormatter::postWrite()
{
	// nothing to do
}

/**************************************
** Null Formatter
***************************************/

NullFormatter::NullFormatter()
{
}

NullFormatter::NullFormatter(unsigned char value)
{
}

NullFormatter::~NullFormatter()
{
}

std::size_t NullFormatter::size() const
{
	return 0;
}

bool NullFormatter::isValid() const
{
	return true;
}

void NullFormatter::set(unsigned char value)
{
}

unsigned char NullFormatter::get() const
{
	return 0;
}

std::size_t NullFormatter::readImpl(const Buffer& buffer)
{
	return size();
}

std::size_t NullFormatter::writeImpl(Buffer& buffer)
{
	return size();
}

/**************************************
** ByteFormatter
***************************************/

ByteFormatter::ByteFormatter()

	: value_(0)
{
}

ByteFormatter::ByteFormatter(unsigned char value)

	: value_(value)
{
}

ByteFormatter::~ByteFormatter()
{
}

std::size_t ByteFormatter::size() const
{
	return 1;
}

bool ByteFormatter::isValid() const
{
	return true;
}

void ByteFormatter::set(unsigned char value)
{
	value_ = value;
}

unsigned char ByteFormatter::get() const
{
	return value_;
}

std::size_t ByteFormatter::readImpl(const Buffer& buffer)
{
	set(buffer.readByte(0));
	return size();
}

std::size_t ByteFormatter::writeImpl(Buffer& buffer)
{
	buffer.writeByte(0, get());
	return size();
}

/**************************************
** WordFormatter
***************************************/

WordFormatter::WordFormatter()

	: value_(0)
{
}

WordFormatter::WordFormatter(unsigned short value)

	: value_(value)
{
}

WordFormatter::~WordFormatter()
{
}

std::size_t WordFormatter::size() const
{
	return 2;
}

bool WordFormatter::isValid() const
{
	return true;
}

void WordFormatter::set(unsigned short value)
{
	value_ = value;
}

unsigned short WordFormatter::get() const
{
	return value_;
}

std::size_t WordFormatter::readImpl(const Buffer& buffer)
{
	set(buffer.readWord(0));
	return size();
}

std::size_t WordFormatter::writeImpl(Buffer& buffer)
{
	buffer.writeWord(0, get());
	return size();
}

/**************************************
** UIntFormatter
***************************************/

UIntFormatter::UIntFormatter()

	: value_(0)
{
}

UIntFormatter::UIntFormatter(unsigned int value)

	: value_(value)
{
}

UIntFormatter::~UIntFormatter()
{
}

std::size_t UIntFormatter::size() const
{
	return 4;
}

bool UIntFormatter::isValid() const
{
	return true;
}

void UIntFormatter::set(unsigned int value)
{
	value_ = value;
}

unsigned int UIntFormatter::get() const
{
	return value_;
}

std::size_t UIntFormatter::readImpl(const Buffer& buffer)
{
	set(fromByteStream<unsigned int, 4>(buffer.getBuffer(), buffer.getBufferSize()));
	return 4;
}

std::size_t UIntFormatter::writeImpl(Buffer& buffer)
{
	const std::vector<unsigned char> data = toByteStream<unsigned int, 4>(value_);
	buffer.writeBuffer(0, &data.at(0), data.size());
	return 4;
}

/**************************************
** Formatter
***************************************/

Formatter::Formatter()
{
}

Formatter::~Formatter()
{
}

std::size_t Formatter::size() const
{
	std::size_t size = 0;

	for (AbstractFormatter* formatter : formatters_)
	{
		BOOST_ASSERT(formatter && "Invalid Formatter");
		size += formatter->size();
	}

	return size;
}

std::size_t Formatter::readFromBuffer(const Buffer& buffer)
{
	std::size_t size = 0;

	const unsigned char* bufferPtr = buffer.getBuffer();
	std::size_t bufferLength = buffer.getBufferSize();

	for (AbstractFormatter* formatter : formatters_)
	{
		BOOST_ASSERT(formatter && "Invalid Formatter");

		// Note: Here we need a const_cast, because the member buffer in the
		// class Buffer is not const. It is not possible to initialize non-const member (buffer_)
		// with a const variable (bufferPtr) although the object (Buffer) is const.
		// const_castis is normally dangerous but here it is ok:
		// We know that buffer will not change in the class Buffer because
		// the object is const and in the constructor of Buffer will buffer_ not modified.
		// And the class Buffer is noncopyable so nobody could copy Buffer and then modified the buffer_.
		const Buffer b(const_cast<unsigned char*>(bufferPtr), bufferLength);

		std::size_t length = formatter->read(b);

		size += length;
		bufferLength -= length;
		bufferPtr += length;
	}

	return size;
}

std::size_t Formatter::writeToBuffer(Buffer& buffer)
{
	std::size_t size = 0;

	unsigned char* bufferPtr = buffer.getBuffer();
	std::size_t bufferLength = buffer.getBufferSize();

	for (AbstractFormatter* formatter : formatters_)
	{
		BOOST_ASSERT(formatter && "Invalid Formatter");

		BufferDecorator<Buffer> b(bufferPtr, bufferLength);
		std::size_t length = formatter->write(b);

		size += length;
		bufferLength -= length;
		bufferPtr += length;
	}

	return size;
}

bool Formatter::isValid() const
{
	for (AbstractFormatter* formatter : formatters_)
	{
		BOOST_ASSERT(formatter && "Invalid Formatter");

		if (!formatter->isValid())
		{
			return false;
		}
	}

	return true;
}

void Formatter::addFormatter(AbstractFormatter* formatter)
{
	BOOST_ASSERT(formatter && "Invalid Formatter");
	formatters_.push_back(formatter);
}

void Formatter::insertFormatter(AbstractFormatter* formatter, int index)
{
	BOOST_ASSERT(formatter && "Invalid Formatter");
	formatters_.insert(formatters_.begin() + index, formatter);
}

void Formatter::removeFormatter(AbstractFormatter* formatter)
{
	BOOST_ASSERT(formatter && "Invalid Formatter");

	Formatters::iterator iter = std::find(formatters_.begin(), formatters_.end(), formatter);
	while (iter != formatters_.end())
	{
		formatters_.erase(iter);
		iter = std::find(formatters_.begin(), formatters_.end(), formatter);
	}
}

const Formatter::Formatters& Formatter::getFormatters() const
{
	return formatters_;
}

std::size_t Formatter::readImpl(const Buffer& buffer)
{
	return readFromBuffer(buffer);
}

std::size_t Formatter::writeImpl(Buffer& buffer)
{
	return writeToBuffer(buffer);
}

/**************************************
** GreedyFormatter
***************************************/

GreedyFormatter::GreedyFormatter()

	: limit_(-1)
{
}

GreedyFormatter::~GreedyFormatter()
{
}

std::size_t GreedyFormatter::size() const
{
	return buffer_.size();
}

bool GreedyFormatter::isValid() const
{
	return true;
}

void GreedyFormatter::setBuffer(const std::vector<unsigned char>& buffer)
{
	buffer_ = buffer;

	if (buffer_.size() > static_cast<std::size_t>(limit_))
	{
		buffer_.resize(limit_);
	}
}

const std::vector<unsigned char>& GreedyFormatter::getBuffer() const
{
	return buffer_;
}

std::vector<unsigned char>& GreedyFormatter::getBuffer()
{
	return buffer_;
}

void GreedyFormatter::setLimit(int limit)
{
	limit_ = limit;
}

int GreedyFormatter::getLimit() const
{
	return limit_;
}

bool GreedyFormatter::isLimited() const
{
	return (limit_ >= 0) ? true : false;
}

std::size_t GreedyFormatter::readImpl(const Buffer& buffer)
{
	const std::size_t availableLength = buffer.getBufferSize();
	const std::size_t limit = limit_;
	const std::size_t readLength = isLimited() ? std::min(availableLength, limit) : availableLength;

	if (readLength)
	{
		buffer_.resize(readLength);
		const unsigned char* bufferPtr = buffer.readBuffer(0, readLength);
		std::copy(bufferPtr, bufferPtr + readLength, buffer_.begin());
	}
	else
	{
		buffer_.clear();
	}

	return readLength;
}

std::size_t GreedyFormatter::writeImpl(Buffer& buffer)
{
	std::size_t size = buffer_.size();

	if (size)
	{
		buffer.writeBuffer(0, &buffer_.at(0), size);
	}

	return size;
}

/**************************************
** WordListFormatter
***************************************/

WordListFormatter::WordListFormatter()
{
}

WordListFormatter::~WordListFormatter()
{
}

std::size_t WordListFormatter::size() const
{
	return values_.size() * 2;
}

bool WordListFormatter::isValid() const
{
	return true;
}

void WordListFormatter::set(const std::vector<unsigned short>& values)
{
	values_ = values;
}

const std::vector<unsigned short>& WordListFormatter::get() const
{
	return values_;
}

std::size_t WordListFormatter::readImpl(const Buffer& buffer)
{
	values_.clear();

	const std::size_t size = buffer.getBufferSize();
	std::size_t offset = 0;
	while (offset < size)
	{
		values_.push_back(buffer.readWord(offset));
		offset += 2;
	}

	return size;
}

std::size_t WordListFormatter::writeImpl(Buffer& buffer)
{
	std::size_t offset = 0;
	for (unsigned short value : values_)
	{
		buffer.writeWord(offset, value);
		offset += 2;
	}

	return size();
}
