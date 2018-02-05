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

#ifndef __KDRIVE_CONNECTOR_PACKET_H__
#define __KDRIVE_CONNECTOR_PACKET_H__

#include "kdrive/connector/Config.h"
#include "kdrive/utility/Forwards.h"
#include "kdrive/utility/PropertyCollection.h"
#include <Poco/Timestamp.h>
#include <memory>
#include <string>
#include <vector>
#include <cstddef>

namespace kdrive
{
namespace connector
{

/*!
	\class Packet

	A packet is a wrapper around some form of buffer or structure
	At a minimum a packet must define operations for converting
	its internal packet structure into a byte stream (writeToBuffer)
	and creating its internal packet structure from a byte stream (readFromBuffer)
	and its size

	A packet has core properties e.g. Timestamp or ConnectorDescription this properties are
	stored in propertyCollection_ and can get and set with get/setPropertyCollection.

	A packet could also have additional properties for the buffer info which are
	handled by the drived classes. The function decode returns a copy of the
	core properties and calls decodeImpl from the drived classes.
	The could append additional properties (e.g. frame.protocol) to the copy.

	Because the buffer could be changed and the additional properties could
	be invalid we return in decode a copy and do not append it to our property collection.

	The Packet is the fundamental transfer type of the connector library.
*/
class kdriveConnector_API Packet
{
public:
	using Ptr = std::shared_ptr<Packet>;
	using Buffer = std::vector<unsigned char>;
	using PropertyCollection = utility::PropertyCollection;

	/*!
		Creates a default Packet
	*/
	Packet();

	/*!
		Creates an Packet with a buffer set to
		size elements
	*/
	Packet(std::size_t size);

	/*!
		Creates an Packet with a buffer
	*/
	explicit Packet(const Buffer& buffer);

	/*!
		Copy constructor is deleted
	*/
	Packet(const Packet&) = delete;

	/*!
		Destroys the Packet
	*/
	virtual ~Packet();

	/*!
		Assingment Operator is deleted
	*/
	Packet& operator=(const Packet&) = delete;

	/*!
		Each packet has a timestamp which relects its creation time
	*/
	const Poco::Timestamp& getTimestamp() const;

	/*!
		Sets the optional protocol string e.g. "knx".
		This is typical set in the connector route mechanism
		and used by decode functions
	*/
	void setProtocol(const std::string& protocol);

	/*!
		Gets the optional protocol string e.g. "knx".
		\sa setProtocol
	*/
	const std::string& getProtocol() const;

	/*!
		Each packet gets a copy of the connectors description
		once it goes through the connector route mechanism
	*/
	void setConnectorDescription(const std::string& connectorDescription);

	/*!
		Each packet gets a copy of the connectors description
		once it goes through the connector route mechanism
	*/
	const std::string& getConnectorDescription() const;

	/*!
		Sets the buffer
	*/
	void setBuffer(const Buffer& buffer);

	/*!
		Gets the buffer
		Can be modified, not thread safe
	*/
	Buffer& getBuffer();

	/*!
		Returns the buffer
	*/
	const Buffer& getBuffer() const;

	/*!
		Simply calls sizeImpl to determine the size of the packet
		\return the size of the packet
	*/
	std::size_t size() const;

	/*!
		checks that the buffer and buffer size are not zero
		and calls readFromBufferImpl
		creates an internal representation from a byte stream
	*/
	std::size_t readFromBuffer(const unsigned char* buffer, std::size_t bufferSize);

	/*!
		converts our internal packet representation into a byte stream
		returns the number of bytes copied into buffer, which may be less than bufferSize
		checks that buffer and bufferSize are not zero
		and resets the buffer to 0x00 before calling writeToBufferImpl
	*/
	std::size_t writeToBuffer(unsigned char* buffer, std::size_t bufferSize) const;

	/*!
		Gets the property collection with the core properties.
		\note It do not return buffer specific properties.
		When you need it use decode().
	*/
	PropertyCollection& getPropertyCollection();

	/*!
		Gets the property collection with the core properties.
		\note It do not return buffer specific properties.
		When you need it use decode().
	*/
	const PropertyCollection& getPropertyCollection() const;

	/*!
		Gets a copy of the property collection and additional properties.
		It calls decodeImpl.
	*/
	PropertyCollection decode() const;

	/*!
		converts an abstract packet type into a Packet type
		if validate is true an exeption is thrown if the conversion fails
	*/
	template <class T>
	static std::shared_ptr<T> convert(Packet::Ptr packet, bool validate)
	{
		std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(packet);
		if (validate && !ptr)
		{
			raiseException("Packet conversion failed");
		}
		return ptr;
	}

	static void enableProperties(bool enable);

	static bool arePropertiesEnabled();

public:
	static const std::string Timestamp;	/*!< Property key for timestamp */
	static const std::string Protocol;	/*!< Property key for protocol */
	static const std::string ConnectorDescription;	/*!< Property key for connector description */

protected:
	/*!
		We grant access to the Connector so it can set the timestamp
		on either routeTx or routeRx
	*/
	friend class Connector;

	/*
		Called on call decode
		It updates the content of the propertyCollection copy
		but do not propertyCollection_.
		Override it in the drived class when has buffer specific properties.
	*/
	virtual void decodeImpl(PropertyCollection& propertyCollection) const;

	/*!
		Updates the timestamp to now
	*/
	void setTimestamp();

private:
	/*!
		Derived classes can implement this function to return the size of the packet.
		The packet size can be fixed at compile time or dynamically determined at
		runtime.
	*/
	virtual std::size_t sizeImpl() const;

	/*!
		Derived classes can implement this function to decode the buffer into some
		form of internal storage.
	*/
	virtual std::size_t readFromBufferImpl(const unsigned char* buffer, std::size_t bufferSize);

	/*!
		Derived classes can implement this function to encode the buffer from some
		form of internal storage.
	*/
	virtual std::size_t writeToBufferImpl(unsigned char* buffer, std::size_t bufferSize) const;

	/*!
		Raise an Poco::Exception
	*/
	static void raiseException(const std::string& message);

private:
	mutable Buffer buffer_;
	PropertyCollection propertyCollection_;
	static bool useProperties_;
};

}
} // end namespace kdrive::connector

#endif // __KDRIVE_CONNECTOR_PACKET_H__
