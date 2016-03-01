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
#include "kdrive/knx/core/ByteStream.h"

using namespace kdrive::knx;
using Poco::Exception;


/*!
	This functon do nothing, because a byte haven't flip.
*/
template <>
void kdrive::knx::flipData<unsigned char>(ByteStreamUnion<unsigned char>& u)
{
	// Nothing to do
}

/*!
	This functon do nothing, because a char haven't flip.
*/
template <>
void kdrive::knx::flipData<char>(ByteStreamUnion<char>& u)
{
	// Nothing to do
}

template <>
void kdrive::knx::flipData<float>(ByteStreamUnion<float>& u)
{
	flipBytes(u);
}

template <>
unsigned char kdrive::knx::fromByteStream<unsigned char, 1>(const unsigned char* buffer, std::size_t bufferLength,std::size_t index)
{
	if (bufferLength < 1+index)
	{
		throw Exception("Buffer Overrun");
	}

	return *(buffer+index);
};

template <>
char kdrive::knx::fromByteStream<char, 1>(const unsigned char* buffer, std::size_t bufferLength,std::size_t index)
{
	if (bufferLength < 1+index)
	{
		throw Exception("Buffer Overrun");
	}

	return static_cast<char>(*(buffer+index));
};

