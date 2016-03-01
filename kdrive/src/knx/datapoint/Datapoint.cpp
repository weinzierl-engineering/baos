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
#include "kdrive/knx/datapoint/Datapoint.h"
#include "kdrive/knx/datapoint/FloatConverter.h"
#include "kdrive/knx/core/ByteStream.h"
#include <Poco/Exception.h>
#include <Poco/DateTime.h>
#include <Poco/LocalDateTime.h>
#include <boost/assert.hpp>

using namespace kdrive::knx;
using Poco::Dynamic::Var;
using Poco::DataFormatException;
using Poco::DateTime;
using Poco::LocalDateTime;

/********************************
** Anonymous namespace for private functions
*********************************/

namespace
{

unsigned char getByte(const Datapoint& datapoint, std::size_t validateLength)
{
	BOOST_ASSERT(validateLength && "Precondition failed");

	const std::vector<unsigned char>& data = datapoint.getData();
	if (data.size() != validateLength)
	{
		throw DataFormatException("Invalid data length");
	}
	return data.at(0);
}

const std::vector<unsigned char>& getData(const Datapoint& datapoint, std::size_t validateLength)
{
	BOOST_ASSERT(validateLength && "Precondition failed");

	const std::vector<unsigned char>& data = datapoint.getData();
	if (data.size() != validateLength)
	{
		throw DataFormatException("Invalid data length");
	}
	return data;
}

void setData(Datapoint& datapoint, const std::vector<unsigned char>& data, std::size_t validateLength)
{
	BOOST_ASSERT(validateLength && "Precondition failed");

	if (data.size() != validateLength)
	{
		throw DataFormatException("Invalid data length");
	}
	datapoint.setData(data);
}

} // end anonymous namespace

/********************************
** Datapoint
*********************************/

const std::string Datapoint::Id = "Dpt.Id";
const std::string Datapoint::Number = "Dpt.Number";
const std::string Datapoint::Name = "Dpt.Name";
const std::string Datapoint::Text = "Dpt.Text";
const std::string Datapoint::SizeInBit = "Dpt.SizeInBit";
const std::string Datapoint::Data = "Dpt.Data";

Datapoint::Datapoint()
{
}

Datapoint::Datapoint(const std::string id,
                     const std::string& number,
                     const std::string& name,
                     const std::string& text,
                     const std::string& sizeInBit)
{
	setProperty(Id, id);
	setProperty(Number, number);
	setProperty(Name, name);
	setProperty(Text, text);
	setProperty(SizeInBit, sizeInBit);

	std::vector<unsigned char> data(getSizeInBytes(), 0x00);
	setProperty(Data, data);
}

Datapoint::Datapoint(const Datapoint& datapoint)

	: PropertyCollection(datapoint)
{
}

Datapoint::~Datapoint()
{
}

Datapoint& Datapoint::operator=(const Datapoint& datapoint)
{
	PropertyCollection::operator=(datapoint);
	return *this;
}

const std::string& Datapoint::getId() const
{
	return getStringRef(Id);
}

int Datapoint::getNumber() const
{
	return getProperty(Number);
}

const std::string& Datapoint::getName() const
{
	return getStringRef(Name);
}

const std::string& Datapoint::getText() const
{
	return getStringRef(Text);
}

int Datapoint::getSizeInBits() const
{
	return getProperty(SizeInBit);
}

int Datapoint::getSizeInBytes() const
{
	return getSizeInBytes(getSizeInBits());
}

const std::vector<unsigned char>& Datapoint::getData() const
{
	const Var& var = getProperty(Data);
	return var.extract<std::vector<unsigned char> >();
}

void Datapoint::setData(const std::vector<unsigned char>& data)
{
	setProperty(Data, data);
}

const std::string& Datapoint::getStringRef(const std::string& key) const
{
	const Var& var = getProperty(key);
	return var.extract<std::string>();
}

int Datapoint::getSizeInBytes(int sizeInBits) const
{
	return sizeInBits < 8 ? 1 : sizeInBits / 8;
}

/********************************
** Standard Datapoint value Getters and Setters
*********************************/

void kdrive::knx::encode_DPT1(Datapoint& datapoint, bool value)
{
	const std::vector<unsigned char> data(1, value);
	setData(datapoint, data, 1);
}

bool kdrive::knx::decode_DPT1(const Datapoint& datapoint)
{
	return getByte(datapoint, 1) ? 1 : 0;
}

void kdrive::knx::encode_DPT2(Datapoint& datapoint, bool control, bool value)
{
	unsigned char data = control ? 0x02 : 0x00;
	if (value)
	{
		data |= 0x01;
	}
	const std::vector<unsigned char> v(1, data);
	setData(datapoint, v, 1);
}

void kdrive::knx::decode_DPT2(const Datapoint& datapoint, bool& control, bool& value)
{
	const unsigned char data = getByte(datapoint, 1);
	control = (data & 0x02) ? true : false;
	value = (data & 0x01) ? true : false;
}

void kdrive::knx::encode_DPT3(Datapoint& datapoint, bool control, unsigned char value)
{
	const unsigned char data = (control ? 0x08 : 0x00) | (value & 0x07);
	const std::vector<unsigned char> v(1, data);
	setData(datapoint, v, 1);
}

void kdrive::knx::decode_DPT3(const Datapoint& datapoint, bool& control, unsigned char& value)
{
	const unsigned char data = getByte(datapoint, 1);
	control = (data & 0x08) ? true : false;
	value = data & 0x07;
}

void kdrive::knx::encode_DPT4(Datapoint& datapoint, unsigned char value)
{
	const std::vector<unsigned char> data(1, value);
	setData(datapoint, data, 1);
}

unsigned char kdrive::knx::decode_DPT4(const Datapoint& datapoint)
{
	return getByte(datapoint, 1);
}

void kdrive::knx::encode_DPT5(Datapoint& datapoint, unsigned char value)
{
	const std::vector<unsigned char> data(1, value);
	setData(datapoint, data, 1);
}

unsigned char kdrive::knx::decode_DPT5(const Datapoint& datapoint)
{
	return getByte(datapoint, 1);
}

void kdrive::knx::encode_DPT6(Datapoint& datapoint, char value)
{
	const std::vector<unsigned char> data(1, static_cast<unsigned char>(value));
	setData(datapoint, data, 1);
}

signed char kdrive::knx::decode_DPT6(const Datapoint& datapoint)
{
	return static_cast<signed char>(getByte(datapoint, 1));
}

void kdrive::knx::encode_DPT7(Datapoint& datapoint, unsigned short value)
{
	setData(datapoint, toByteStream<unsigned short, 2>(value), 2);
}

unsigned short kdrive::knx::decode_DPT7(const Datapoint& datapoint)
{
	const std::vector<unsigned char>& data = getData(datapoint, 2);
	return fromByteStream<unsigned short, 2>(&data.at(0), data.size());
}

void kdrive::knx::encode_DPT8(Datapoint& datapoint, short value)
{
	setData(datapoint, toByteStream<short, 2>(value), 2);
}

signed short kdrive::knx::decode_DPT8(const Datapoint& datapoint)
{
	const std::vector<unsigned char>& data = getData(datapoint, 2);
	return fromByteStream<signed short, 2>(&data.at(0), data.size());
}

void kdrive::knx::encode_DPT9_Raw(Datapoint& datapoint, unsigned char msb, unsigned char lsb)
{
	std::vector<unsigned char> data;
	data.push_back(msb);
	data.push_back(lsb);
	setData(datapoint, data, 2);
}

void kdrive::knx::encode_DPT9(Datapoint& datapoint, float f)
{
	std::tuple<unsigned char, unsigned char> t = FloatConverter::toFloat2FromFloat4(f);
	encode_DPT9_Raw(datapoint, std::get<0>(t), std::get<1>(t));
}

unsigned short kdrive::knx::decode_DPT9_Raw(const Datapoint& datapoint)
{
	const std::vector<unsigned char>& data = getData(datapoint, 2);
	return data.at(0) << 8 | data.at(1);
}

float kdrive::knx::decode_DPT9(const Datapoint& datapoint)
{
	const std::vector<unsigned char>& data = getData(datapoint, 2);
	return FloatConverter::toFloat4FromFloat2(data.at(0), data.at(1));
}

void kdrive::knx::encode_DPT10_Local(Datapoint& datapoint)
{
	LocalDateTime now;

	// poco day of week is 0 to 6 where 0 is sunday, 1 is monday etc
	// Datapoint Time expects 1 to 7 where 1 is monday and 7 is sunday
	int day = now.dayOfWeek();

	if (!day)
	{
		day = 7;
	}

	return encode_DPT10(datapoint, day, now.hour(), now.minute(), now.second());
}

void kdrive::knx::encode_DPT10_UTC(Datapoint& datapoint)
{
	DateTime now;

	// poco day of week is 0 to 6 where 0 is sunday, 1 is monday etc
	// Datapoint Time expects 1 to 7 where 1 is monday and 7 is sunday
	int day = now.dayOfWeek();
	if (!day)
	{
		day = 7;
	}

	return encode_DPT10(datapoint, day, now.hour(), now.minute(), now.second());
}

void kdrive::knx::encode_DPT10(Datapoint& datapoint, int day, int hour, int minute, int second)
{
	std::vector<unsigned char> data;

	data.push_back(((day & 0x07) << 5) | (hour & 0x1F));
	data.push_back(minute & 0x3F);
	data.push_back(second & 0x3F);

	setData(datapoint, data, 3);
}

void kdrive::knx::decode_DPT10(const Datapoint& datapoint, int& day, int& hour, int& minute, int& second)
{
	const std::vector<unsigned char>& data = getData(datapoint, 3);
	const unsigned char ch0 = data.at(0);
	const unsigned char ch1 = data.at(1);
	const unsigned char ch2 = data.at(2);

	day = ch0 >> 5;
	hour = ch0 & 0x1F;
	minute = ch1 & 0x3F;
	second = ch2 & 0x3F;
}

void kdrive::knx::encode_DPT11_Local(Datapoint& datapoint)
{
	LocalDateTime now;
	return encode_DPT11(datapoint, now.year(), now.month(), now.day());
}

void kdrive::knx::encode_DPT11_UTC(Datapoint& datapoint)
{
	DateTime now;
	return encode_DPT11(datapoint, now.year(), now.month(), now.day());
}

void kdrive::knx::encode_DPT11(Datapoint& datapoint, int year, int month, int day)
{
	// year is expected to be between 0..99
	// but is not validated.

	std::vector<unsigned char> data;
	data.push_back(day & 0x1F);
	data.push_back(month & 0x0F);
	data.push_back(year & 0x7F);

	setData(datapoint, data, 3);
}

void kdrive::knx::decode_DPT11(const Datapoint& datapoint, int& year, int& month, int& day)
{
	const std::vector<unsigned char>& data = getData(datapoint, 3);

	const unsigned char ch0 = data.at(0);
	const unsigned char ch1 = data.at(1);
	const unsigned char ch2 = data.at(2);

	day = ch0 & 0x1F;
	month = ch1 & 0x0F;
	year = ch2 & 0x7F;
}

void kdrive::knx::encode_DPT12(Datapoint& datapoint, unsigned int value)
{
	setData(datapoint, toByteStream<unsigned int, 4>(value), 4);
}

unsigned int kdrive::knx::decode_DPT12(const Datapoint& datapoint)
{
	const std::vector<unsigned char>& data = getData(datapoint, 4);
	return fromByteStream<unsigned int, 4>(&data.at(0), data.size());
}

void kdrive::knx::encode_DPT13(Datapoint& datapoint, int value)
{
	setData(datapoint, toByteStream<int, 4>(value), 4);
}

signed int kdrive::knx::decode_DPT13(const Datapoint& datapoint)
{
	const std::vector<unsigned char>& data = getData(datapoint, 4);
	return fromByteStream<signed int, 4>(&data.at(0), data.size());
}

void kdrive::knx::encode_DPT14(Datapoint& datapoint, float f)
{
	setData(datapoint, toByteStream<float, 4>(f), 4);
}

float kdrive::knx::decode_DPT14(const Datapoint& datapoint)
{
	const std::vector<unsigned char>& data = getData(datapoint, 4);
	return fromByteStream<float, 4>(&data.at(0), data.size());
}

void kdrive::knx::encode_DPT15(Datapoint& datapoint,
                               unsigned int accessCode,
                               bool error,
                               bool permission,
                               bool direction,
                               bool encrypted,
                               unsigned char index)
{
	std::vector<unsigned char> v;

	// access code, 24 bits
	v.push_back((accessCode >> 16) & 0xFF);
	v.push_back((accessCode >> 8) & 0xFF);
	v.push_back(accessCode & 0xFF);

	unsigned char data = 0x00;
	if (error)
	{
		data |= 0x80;
	}
	if (permission)
	{
		data |= 0x40;
	}
	if (direction)
	{
		data |= 0x20;
	}
	if (encrypted)
	{
		data |= 0x10;
	}
	data |= index & 0x0F;
	v.push_back(data);

	setData(datapoint, v, 4);
}

void kdrive::knx::decode_DPT15(const Datapoint& datapoint,
                               unsigned int& accessCode,
                               bool& error,
                               bool& permission,
                               bool& direction,
                               bool& encrypted,
                               unsigned char& index)
{
	const std::vector<unsigned char>& data = getData(datapoint, 4);

	const unsigned char ch0 = data.at(0);
	const unsigned char ch1 = data.at(1);
	const unsigned char ch2 = data.at(2);
	const unsigned char ch3 = data.at(3);

	accessCode = (ch0 << 16) | (ch1 << 8) | ch2;
	error = ch3 & 0x80 ? true : false;
	permission = ch3 & 0x40 ? true : false;
	direction = ch3 & 0x20 ? true : false;
	encrypted = ch3 & 0x10 ? true : false;
	index = ch3 & 0x0F;
}

void kdrive::knx::encode_DPT16(Datapoint& datapoint, const std::string& str)
{
	static const int stringSize = 14;
	std::vector<unsigned char> data;
	for (char ch : str)
	{
		data.push_back(static_cast<unsigned char>(ch));
	}

	// fill shorter strings with '0'
	if (data.size() < stringSize)
	{
		data.resize(stringSize, 0);
	}

	setData(datapoint, data, stringSize);
}

std::string kdrive::knx::decode_DPT16(const Datapoint& datapoint)
{
	std::string str;
	const std::vector<unsigned char>& data = getData(datapoint, 14);
	for (unsigned char ch : data)
	{
		if (!ch)
		{
			// we break as soon as we hit a 0
			break;
		}
		str += static_cast<char>(ch);
	}
	return str;
}

void kdrive::knx::encode_DPT17(Datapoint& datapoint, unsigned char sceneNumber)
{
	const std::vector<unsigned char> data(1, sceneNumber);
	setData(datapoint, data, 1);
}

unsigned char kdrive::knx::decode_DPT17(const Datapoint& datapoint)
{
	return getByte(datapoint, 1);
}

void kdrive::knx::encode_DPT18(Datapoint& datapoint, bool control, unsigned char sceneNumber)
{
	unsigned char data = control ? 0x80 : 0x00;
	data |= sceneNumber & 0x3F;
	const std::vector<unsigned char> v(1, data);
	setData(datapoint, v, 1);
}

void kdrive::knx::decode_DPT18(const Datapoint& datapoint, bool& control, unsigned char& sceneNumber)
{
	const unsigned char data = getByte(datapoint, 1);
	control = (data & 0x80) ? true : false;
	sceneNumber = data & 0x3F;
}

void kdrive::knx::encode_DPT232(Datapoint& datapoint, unsigned char r, unsigned char g, unsigned char b)
{
	const std::vector<unsigned char> v = { r, g, b };
	setData(datapoint, v, 3);
}

void kdrive::knx::decode_DPT232(const Datapoint& datapoint, unsigned char& r, unsigned char& g, unsigned char& b)
{
	const std::vector<unsigned char>& data = getData(datapoint, 3);
	r = data.at(0);
	g = data.at(1);
	b = data.at(2);
}

