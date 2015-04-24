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
#include "kdrive/connector/Packet.h"
#include "kdrive/utility/PropertyCollection.h"
#include <Poco/Exception.h>
#include <cstring>

using namespace kdrive::connector;
using Poco::Exception;

/**************************************
** Anonymous namespace
***************************************/

namespace
{

void initProperties(Packet::PropertyCollection& collection)
{
	collection.setProperty(Packet::Timestamp, Poco::Timestamp());
	collection.setProperty(Packet::Protocol, "");
	collection.setProperty(Packet::ConnectorDescription, "");
}

} // end anonymous namespace

/************************************
** Packet
*************************************/

const std::string Packet::Timestamp = "frame.timestamp";
const std::string Packet::Protocol = "frame.protocol";
const std::string Packet::ConnectorDescription = "frame.connector_description";
bool Packet::useProperties_ = false;

Packet::Packet()
{
	if (useProperties_)
	{
		initProperties(propertyCollection_);
	}
}

Packet::Packet(std::size_t size)

	: buffer_(size, 0x00)
{
	if (useProperties_)
	{
		initProperties(propertyCollection_);
	}
}

Packet::Packet(const Buffer& buffer)

	: buffer_(buffer)
{
	if (useProperties_)
	{
		initProperties(propertyCollection_);
	}
}

Packet::~Packet()
{
}

const Poco::Timestamp& Packet::getTimestamp() const
{
	return propertyCollection_.extract<Poco::Timestamp>(Packet::Timestamp);
}

void Packet::setProtocol(const std::string& protocol)
{
	if (useProperties_)
	{
		propertyCollection_.setProperty(Packet::Protocol, protocol);
	}
}

const std::string& Packet::getProtocol() const
{
	return propertyCollection_.extract<std::string>(Packet::Protocol);
}

void Packet::setConnectorDescription(const std::string& connectorDescription)
{
	if (useProperties_)
	{
		propertyCollection_.setProperty(Packet::ConnectorDescription, connectorDescription);
	}
}

const std::string& Packet::getConnectorDescription() const
{
	return propertyCollection_.extract<std::string>(Packet::ConnectorDescription);
}

void Packet::setBuffer(const Buffer& buffer)
{
	buffer_ = buffer;
}

Packet::Buffer& Packet::getBuffer()
{
	return buffer_;
}

const Packet::Buffer& Packet::getBuffer() const
{
	const std::size_t bufferSize = size();
	if (bufferSize && (buffer_.size() != bufferSize))
	{
		// we implement some other form of data storage
		// so we simply write to our internal buffer
		buffer_.resize(bufferSize);
		writeToBufferImpl(&buffer_.at(0), bufferSize);
	}
	return buffer_;
}

std::size_t Packet::size() const
{
	return sizeImpl();
}

std::size_t Packet::readFromBuffer(const unsigned char* buffer, std::size_t bufferSize)
{
	return buffer && bufferSize ? readFromBufferImpl(buffer, bufferSize) : 0;
}

std::size_t Packet::writeToBuffer(unsigned char* buffer, std::size_t bufferSize) const
{
	std::size_t size = 0;

	if (buffer && bufferSize)
	{
		std::memset(buffer, 0x00, bufferSize);
		size = writeToBufferImpl(buffer, bufferSize);
	}

	return size;
}

Packet::PropertyCollection& Packet::getPropertyCollection()
{
	return propertyCollection_;
}

const Packet::PropertyCollection& Packet::getPropertyCollection() const
{
	return propertyCollection_;
}

Packet::PropertyCollection Packet::decode() const
{
	PropertyCollection propertyCollection = propertyCollection_;
	decodeImpl(propertyCollection);
	return propertyCollection;
}

void Packet::enableProperties(bool enable)
{
	useProperties_ = enable;
}

bool Packet::arePropertiesEnabled()
{
	return useProperties_;
}

void Packet::decodeImpl(Packet::PropertyCollection& propertyCollection) const
{
	const Buffer& buffer = getBuffer();
	propertyCollection.setProperty("frame.data", buffer);
	propertyCollection.setProperty("frame.size", buffer.size());
}

void Packet::setTimestamp()
{
	if (useProperties_)
	{
		propertyCollection_.setProperty(Packet::Timestamp, Poco::Timestamp());
	}
}

std::size_t Packet::sizeImpl() const
{
	return buffer_.size();
}

std::size_t Packet::readFromBufferImpl(const unsigned char* buffer, std::size_t bufferSize)
{
	buffer_.resize(bufferSize);
	std::copy(buffer, buffer + bufferSize, buffer_.begin());
	return bufferSize;
}

std::size_t Packet::writeToBufferImpl(unsigned char* buffer, std::size_t bufferSize) const
{
	const std::size_t size = buffer_.size();

	if (bufferSize < size)
	{
		throw Exception("Invalid Buffer");
	}

	std::copy(buffer_.begin(), buffer_.end(), buffer);

	return size;
}

void Packet::raiseException(const std::string& message)
{
	throw Poco::Exception(message);
}
