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
#include "kdrive/baos/core/DataPacket.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/baos/protocols/Protocol.h"
#include <boost/assert.hpp>

using namespace kdrive::baos;
using namespace kdrive::connector;

/*************************************
** Data Packet
**************************************/

DataPacket::~DataPacket()
{
}

void DataPacket::setMainService(unsigned char mainService)
{
	mainService_ = mainService;
}

unsigned char DataPacket::getMainService() const
{
	return mainService_;
}

void DataPacket::setSubService(unsigned char subService)
{
	subService_ = subService;
}

unsigned char DataPacket::getSubService() const
{
	return subService_;
}

void DataPacket::setOffset(unsigned short offset)
{
	offset_ = offset;
}

unsigned short DataPacket::getOffset() const
{
	return offset_;
}

void DataPacket::setCount(unsigned short count)
{
	count_ = count;
}

unsigned short DataPacket::getCount() const
{
	return count_;
}

void DataPacket::setBuffer(const Buffer& buffer)
{
	buffer_ = buffer;
}

DataPacket::Buffer& DataPacket::getBuffer()
{
	return buffer_;
}

const DataPacket::Buffer& DataPacket::getBuffer() const
{
	return buffer_;
}

void DataPacket::setHeaderPolicy(std::shared_ptr<HeaderPolicy> headerPolicy)
{
	headerPolicy_ = headerPolicy;
}

void DataPacket::setVersion(unsigned char version)
{
	version_ = version;
}

unsigned char DataPacket::getVersion() const
{
	return version_;
}

DataPacket::DataPacket()

	: version_(0),
	  mainService_(ProtocolConstants::MainService),
	  subService_(0),
	  offset_(0),
	  count_(0)
{
	setProtocol("baos");
}

std::size_t DataPacket::sizeImpl() const
{
	return sizeOfHeader() + sizeOfBody();
}

std::size_t DataPacket::readFromBufferImpl(const unsigned char* buffer, std::size_t bufferSize)
{
	std::size_t size = readHeader(buffer, bufferSize);
	size += readBody(buffer + size, bufferSize - size);
	return size;
}

std::size_t DataPacket::writeToBufferImpl(unsigned char* buffer, std::size_t bufferSize) const
{
	std::size_t size = writeHeader(buffer, bufferSize);
	size += writeBody(buffer + size, bufferSize - size);
	return size;
}

std::size_t DataPacket::sizeOfHeader() const
{
	BOOST_ASSERT(headerPolicy_.get() && "Invalid Data Packet Header Policy");
	return headerPolicy_->size(*this);
}

std::size_t DataPacket::readHeader(const unsigned char* buffer, std::size_t bufferSize)
{
	BOOST_ASSERT(headerPolicy_.get() && "Invalid Data Packet Header Policy");
	return headerPolicy_->read(*this, buffer, bufferSize);
}

std::size_t DataPacket::writeHeader(unsigned char* buffer, std::size_t bufferSize) const
{
	BOOST_ASSERT(headerPolicy_.get() && "Invalid Data Packet Header Policy");
	return headerPolicy_->write(*this, buffer, bufferSize);
}

std::size_t DataPacket::sizeOfBody() const
{
	return buffer_.size();
}

std::size_t DataPacket::readBody(const unsigned char* buffer, std::size_t bufferSize)
{
	if (bufferSize)
	{
		buffer_.resize(bufferSize);
		std::copy(buffer, buffer + bufferSize, buffer_.begin());
	}
	else
	{
		buffer_.clear();
	}
	return bufferSize;
}

std::size_t DataPacket::writeBody(unsigned char* buffer, std::size_t bufferSize) const
{
	std::size_t size = buffer_.size();

	if (size)
	{
		if (size > bufferSize)
		{
			throw ClientException("Buffer Overflow");
		}

		std::uninitialized_copy(buffer_.begin(), buffer_.end(), buffer);
	}

	return size;
}

/*************************************
** Error Response
**************************************/

unsigned char ErrorResponse::getErrorCode() const
{
	const Buffer& buffer = getBuffer();
	return buffer.at(0);
}
