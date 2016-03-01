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

#ifndef __KDRIVE_KNX_BYTE_STREAM_H__
#define __KDRIVE_KNX_BYTE_STREAM_H__

#include "kdrive/knx/Config.h"
#include <Poco/ByteOrder.h>
#include <Poco/Exception.h>
#include <vector>
#include <algorithm>
#include <cstddef>

namespace kdrive
{
namespace knx
{

/*!
	\class ByteStreamUnion
	This class is a utility class which can be used to
	turn an integral type (i.e. int, float, unsigned short etc)
	into a byte sequence to be transmitted on the KNX bus

	The byte encoding for the bus if Big Endian so if on a little
	endian machine the functions flipData / flipBytes should be used
	flipData is more efficient than flipBytes and should be used
	where possible. i.e. Your compiler should complain if
	Poco::ByteOrder::flipBytes(data) can't handle the given type
	and you should use flipBytes instead.

	This uses the union hack to perform the cast, where we define
	a union between a T and an unsigned char buffer array which is
	the same size as T. Note, often the size of the type and the
	encoded buffer sequence to be sent on the bus will be the same size
	i.e. a short will be 2 bytes etc. This may not be the cast on 64-bit
	machines, in which case you should use getTruncatedBuffer with the
	size of the bytes to be sent on the bus. (see the function
	getTruncatedBuffer below)
*/
template <typename T>
union ByteStreamUnion
{
	enum DataLength { Size = sizeof(T) };

	T data;
	unsigned char bytes[sizeof(T)];
};

/*!
	Flips the byte order, used to convert from/to
	Big and Little Endian
*/
template <typename T>
void flipData(ByteStreamUnion<T>& u)
{
	u.data = Poco::ByteOrder::flipBytes(u.data);
}

/*!
	Flips the byte order, used to convert from/to
	Big and Little Endian.
*/
template <>
kdriveKnx_API void flipData<unsigned char>(ByteStreamUnion<unsigned char>& u);

/*!
	Flips the byte order, used to convert from/to
	Big and Little Endian.
*/
template <>
kdriveKnx_API void flipData<char>(ByteStreamUnion<char>& u);

/*!
	Flips the byte order, used to convert from/to
	Big and Little Endian.
*/
template <>
kdriveKnx_API void flipData<float>(ByteStreamUnion<float>& u);

/*!
	Flips the byte order, used to convert from/to
	Big and Little Endian when flipData doesn't support
	the T type (not as efficient as flipData)
*/
template <typename T>
void flipBytes(ByteStreamUnion<T>& u)
{
	std::vector<unsigned char> v(u.bytes, u.bytes + ByteStreamUnion<T>::Size);
	std::reverse(v.begin(), v.end());
	std::copy(v.begin(), v.end(), u.bytes);
}


/*!
	fromByteStream : converts a byte sequence into a given type
	Auto-handles the conversion from little endian to big endian
	@param index the index where the conversion should start by aware that the index is used as offset = index*n and starts with 0
*/
template<typename T, int n>
T fromByteStream(const unsigned char* buffer, std::size_t bufferLength, std::size_t index = 0)
{
	if ((bufferLength < (index + 1) * n) || (n > ByteStreamUnion<T>::Size))
	{
		throw Poco::Exception("Buffer Overrun");
	}

	ByteStreamUnion<T> u;

	u.data = 0;
	std::copy(buffer + (index * n), buffer + (index + 1) * n, u.bytes);

#if defined(POCO_ARCH_LITTLE_ENDIAN)

	flipData(u);

#endif // POCO_ARCH_LITTLE_ENDIAN

	return u.data;
};

template<typename T, int n>
T fromByteStream(const std::vector<unsigned char>& buffer, std::size_t index = 0)
{
	if (buffer.empty())
	{
		throw Poco::Exception("Buffer Overrun");
	}

	return fromByteStream<T, n>(&buffer.at(0), buffer.size(), index);
}

/*!
converts a given bytestream in a vector with type T elements
@param index the index where the conversion should start by aware that the index is used as offset = index*n and starts with 0
@throw Poco::Exception("Buffer Overrun") , std::bad_alloc
*/
template<typename T, int n>
void fromByteStreamtoVector(const unsigned char* buffer, std::size_t bufferLength,
                            std::vector<T>& result, std::size_t index = 0)
{
	result.clear();
	if ((1 + index) * n > bufferLength)
	{
		throw Poco::Exception("Buffer Overrun");
	}
	for (std::size_t idx = index; idx < (unsigned int) bufferLength / n; ++idx)
	{
		result.push_back(fromByteStream<T, n>(buffer, bufferLength, idx));
	}

}

/*!
converts a given bytestream in a vector with type T elements
@param index the index where the conversion should start by aware that the index is used as offset = index*n and starts with 0
@throw Poco::Exception("Buffer Overrun") , std::bad_alloc
*/
template<typename T, int n>
void fromByteStreamtoVector(const std::vector<unsigned char>& buffer,
                            std::vector<T>& result, std::size_t index =0)
{
	if (buffer.empty())
	{
		throw Poco::Exception("Buffer Overrun");
	}

	fromByteStreamtoVector<T, n>(&buffer.at(0), buffer.size(), result, index);
}


/*!
	fromByteStream : specialization for unsigned char
	we simply return the first byte of the buffer
*/
template <>
kdriveKnx_API unsigned char fromByteStream<unsigned char, 1>(const unsigned char* buffer, std::size_t bufferLength,std::size_t index );

/*!
	fromByteStream : specialization for unsigned char
	we simply return the first byte of the buffer
	with a static_cast<char>
*/
template <>
kdriveKnx_API char fromByteStream<char, 1>(const unsigned char* buffer, std::size_t bufferLength,std::size_t index );

/*!
	getTruncatedBuffer gets the least significant bytes
	of the big endian encoded buffer. This function is
	used to ensure that in a 64-bit environment
	where the type T is larger than the buffer that the
	least significant (low) bytes are transmitted

	Precondition: the buffer is encoded as BIG ENDIAN
	Precondition: length is less than or equal to Size
*/
template <typename T, int length>
const unsigned char* getTruncatedBuffer(const ByteStreamUnion<T>& u)
{
	if (length > ByteStreamUnion<T>::Size)
	{
		throw Poco::Exception("Buffer Overrun");
	}

	if (sizeof(T) == length)
	{
		return u.bytes;
	}
	else
	{
		return u.bytes + (ByteStreamUnion<T>::Size - length);
	}
}

/*!
	toByteStream : converts a given type into a byte stream
	Auto-handles the conversion from little endian to big endian
*/
template <typename T, int n>
std::vector<unsigned char> toByteStream(T t)
{
	ByteStreamUnion<T> u;
	u.data = t;

#if defined(POCO_ARCH_LITTLE_ENDIAN)

	flipData(u);

#endif // POCO_ARCH_LITTLE_ENDIAN

	const unsigned char* ptr = getTruncatedBuffer<T, n>(u);
	return std::vector<unsigned char>(ptr, ptr + n);
}

/*!
 arrayToByteStream : converts a given vector consisting of type T values into a byte stream
 the index allows to start converting from a given point, in c tradition the index starts with 0
 Auto-handles the conversion from little endian to big endian
 @throw Poco::Exception("Buffer Overrun") , std::bad_alloc
 */
template<typename T, int n>
void arrayToByteStream(T* t, std::size_t bufferLength,
                       std::vector<unsigned char>& result, std::size_t index = 0)
{
	result.clear();
	std::vector<unsigned char> temp;
	if (t == NULL  || bufferLength < (index+1))
	{
		throw Poco::Exception("Buffer Overrun");
	}

	for (T* idx = (t+index); idx < (t+bufferLength); ++idx)
	{

		temp = toByteStream<T, n>(*idx);
		result.insert(result.end(), temp.begin(), temp.end());
	}
}

/*!
 vectorToByteStream : converts a given vector consisting of type T values into a byte stream
 the index allows to start converting from a given point, in c tradition the index starts with 0
 Auto-handles the conversion from little endian to big endian
 @throw Poco::Exception("Buffer Overrun") , std::bad_alloc
 */
template<typename T, int n>
void vectorToByteStream(std::vector<T>& t, std::vector<unsigned char>& result,
                        std::size_t index = 0)
{
	if (t.empty())
	{
		throw Poco::Exception("Buffer Overrun");
	}
	arrayToByteStream<T, n>(&t.at(0), t.size(), result, index);
}

}
} // end namespace kdrive::knx

#endif // __KDRIVE_KNX_BYTE_STREAM_H__
