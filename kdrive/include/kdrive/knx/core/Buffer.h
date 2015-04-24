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

#ifndef __KDRIVE_KNX_TELEGRAMS_BUFFER_H__
#define __KDRIVE_KNX_TELEGRAMS_BUFFER_H__

#include "kdrive/knx/Config.h"
#include <boost/noncopyable.hpp>
#include <vector>

namespace kdrive
{
namespace knx
{

/*!
	Buffer is the base class used to format telegrams.
	It implements a user-owned buffer policy and does not have
	a buffer itself. You should take care to ensure that the buffer
	has adequate storage (length) and is available during the life of the
	telegram class (or at least until reset() or setBuffer is called)

	This class is not thread safe.
	This class is noncopyable
*/

/*********************************
** Buffer
**********************************/

// Note: This class is noncopyable to allow using with const user buffers:
// Use this only if you really need it!
// const unsigned char* bufferPtr = buffer;
// const Buffer b(const_cast<unsigned char*>(bufferPtr), bufferLength);
class kdriveKnx_API Buffer : private boost::noncopyable
{
public:
	/*!
		Default Constructor
		Creates a Buffer with an empty buffer
	*/
	Buffer();

	/*!
		Constructor
		sets the internal buffer to the specified buffer
		we simply take a copy of the buffer
		precondition: if bufferSize is > 0 buffer is not null
	*/
	Buffer(unsigned char* buffer, std::size_t bufferSize);

	/*!
		Destructor
		Destroys the Buffer
		\note The holded buffer will not destroyed.
	*/
	virtual ~Buffer();

	/*!
		Set buffer
		Sets the internal buffer to the specified buffer
		we simply take a copy of the buffer
		precondition: if bufferSize is > 0 buffer is not null
	*/
	void setBuffer(unsigned char* buffer, std::size_t bufferSize);

	/*!
		Set buffer
		Sets the internal buffer to the specified buffer
		we simply take a copy of the vectors' buffer
		precondition
	*/
	void setBuffer(std::vector<unsigned char>& buffer);

	/*!
		get buffer
		returns the buffer pointer
	*/
	const unsigned char* getBuffer() const;

	/*!
		get buffer
		returns the buffer pointer
	*/
	unsigned char* getBuffer();

	/*!
		get buffer length
	*/
	std::size_t getBufferSize() const;

	/*!
		A buffer is considered empty if buffer is 0 or bufferLength is 0
	*/
	bool isBufferEmpty() const;

	/*!
		Resets the buffer to empty
	*/
	void reset();

	/*!
		Writes data in all bytes from the buffer
	*/
	void assign(unsigned char data);

	/*!
		Writes a byte to the buffer
		If offset is out of range an exception is thrown
	*/
	void writeByte(unsigned int offset, unsigned char data);

	/*!
		Writes a word (two bytes) to the buffer
		If offset is out of range an exception is thrown
	*/
	void writeWord(unsigned int offset, unsigned short data);

	/*!
		Copies a buffer into our buffer
		If offset is out of range an exception is thrown
	*/
	void writeBuffer(unsigned int offset, const unsigned char* buffer, std::size_t bufferSize);

	/*!
		Reads a byte from the buffer
		If offset is out of range an exception is thrown
	*/
	unsigned char readByte(unsigned int offset) const;

	/*!
		Read a word (two bytes) from the buffer
		If offset is out of range an exception is thrown
	*/
	unsigned short readWord(unsigned int offset) const;

	/*!
		Returns a pointer to the buffer and validates that the requested buffer is
		a complete subset of our buffer
	*/
	unsigned char* readBuffer(unsigned int offset, std::size_t bufferSize);

	/*!
		Returns a const pointer to the buffer and validates that the requested buffer is
		a complete subset of our buffer
	*/
	const unsigned char* readBuffer(unsigned int offset, std::size_t bufferSize) const;

private:
	/*!
		Validate that the given offset is in range.
		If the buffer is null or if the offset (0 .. buffer size - 1)
		we fail with an exception

		\exception Poco::Exception If buffer length is not valid
	*/
	void validateInRange(unsigned int offset) const;

private:
	unsigned char* buffer_;
	std::size_t bufferLength_;
};

/*********************************
** BufferDecorator
**********************************/

template <class T>
struct BufferDecorator : public T
{
	BufferDecorator(unsigned char* buffer, std::size_t bufferSize)
	{
		T::setBuffer(buffer, bufferSize);
	}

	BufferDecorator(std::vector<unsigned char>& buffer)
	{
		T::setBuffer(buffer);
	}
};


}
} // end namespace kdrive::knx

#endif // __KDRIVE_KNX_TELEGRAMS_BUFFER_H__
