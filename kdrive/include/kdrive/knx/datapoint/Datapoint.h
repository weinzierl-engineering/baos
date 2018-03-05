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

#ifndef __KDRIVE_KNX_DATAPOINT_DATAPOINT_H__
#define __KDRIVE_KNX_DATAPOINT_DATAPOINT_H__

#include "kdrive/knx/Config.h"
#include "kdrive/utility/PropertyCollection.h"
#include <vector>
#include <string>

namespace kdrive
{
namespace knx
{

/*!

	\verbatim

	|----------|----------|-----------------------------|-------------|---------------|
	|  Id      |  Number  |  Name                       |  SizeInBit  |  Implemented  |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-1    | 1        | 1 bit                       | 1           | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-2    | 2        | 1 bit controlled            | 2           | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-3    | 3        | 3 bit controlled            | 4           | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-4    | 4        | Character                   | 8           | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-5    | 5        | 8 bit unsigned value        | 8           | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-6    | 6        | 8 bit signed value          | 8           | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-7    | 7        | 2 byte unsigned value       | 16          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-8    | 8        | 2 byte signed value         | 16          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-9    | 9        | 2 byte float value          | 16          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-10   | 10       | Time                        | 24          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-11   | 11       | Date                        | 24          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-12   | 12       | 4 byte unsigned value       | 32          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-13   | 13       | 4 byte signed value         | 32          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-14   | 14       | 4 byte float value          | 32          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-15   | 15       | Entrance access             | 32          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-16   | 16       | Character string            | 112         | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-17   | 17       | Scene Number                | 8           | No            |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-18   | 18       | Scene Control               | 8           | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-19   | 19       | Date Time                   | 64          | No            |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-20   | 20       | 1 byte                      | 8           | use DPT-5/6   |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-217  | 217      | Version                     | 16          | No            |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-219  | 219      | Alarm Info                  | 48          | No            |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-222  | 222      | 3x 16-Float Value           | 48          | No            |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-232  | 232      | 3-byte colour RGB           | 24          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	\endverbatim
*/

/********************************
** Datapoint
*********************************/

/*!
	The Datapoint class. It is a PropertyCollection (map) and has the following
	attributes:

		id:			[std::string]			the datapoint id (DPT-1, DPST-1-1 etc)
		number:		[int]					the datapoint number
		name:		[std::string]			the datapoint name, DPT_Switch etc
		text:		[std::string]			the datapoint text, on/off etc
		sizeInBit:	[int]					the data size in bits
		data:		[vector<unsigned char>]	the data
*/
class kdriveKnx_API Datapoint : public kdrive::utility::PropertyCollection
{
public:
	/*!
		Creates an empty uninitialized Datapoint
	*/
	Datapoint();

	/*!
		Creates an initialised Datapoint with empty data
	*/
	Datapoint(const std::string id, const std::string& number, const std::string& name,
	          const std::string& text, const std::string& sizeInBit);

	/*!
		Copy constructor
	*/
	Datapoint(const Datapoint& datapoint);

	/*!
		Destroys the Datapoint
	*/
	virtual ~Datapoint();

	/*!
		Assignment Operator
	*/
	Datapoint& operator=(const Datapoint& datapoint);

	/*!
		Gets the Datapoint Id from the property map
	*/
	const std::string& getId() const;

	/*!
		Gets the Datapoint Number from the property map
	*/
	int getNumber() const;

	/*!
		Gets the Datapoint Name from the property map
	*/
	const std::string& getName() const;

	/*!
		Gets the Datapoint Text from the property map
	*/
	const std::string& getText() const;

	/*!
		Gets the SizeInBits from the property map
	*/
	int getSizeInBits() const;

	/*!
		Gets the SizeInBytes calculated from SizeInBit
		If sizeInBit < 8 returns 1
	*/
	int getSizeInBytes() const;

	/*!
		Gets the Data from the property map
	*/
	const std::vector<unsigned char>& getData() const;

	/*!
		Sets the Data
	*/
	void setData(const std::vector<unsigned char>& data);

public:
	static const std::string Id;
	static const std::string Number;
	static const std::string Name;
	static const std::string Text;
	static const std::string SizeInBit;
	static const std::string Data;

	enum SizeInBits
	{
		DPT1_Bits = 1,
		DPT2_Bits = 2,
		DPT3_Bits = 4,
		DPT4_Bits = 8,
		DPT5_Bits = 8,
		DPT6_Bits = 8,
		DPT7_Bits = 16,
		DPT8_Bits = 16,
		DPT9_Bits = 16,
		DPT10_Bits = 24,
		DPT11_Bits = 24,
		DPT12_Bits = 32,
		DPT13_Bits = 32,
		DPT14_Bits = 32,
		DPT15_Bits = 32,
		DPT16_Bits = 112,
		DPT232_Bits = 24
	};

private:
	/*!
		Extracts a string type as reference from the property map
	*/
	const std::string& getStringRef(const std::string& key) const;

	/*!
		Calculates the size in bytes from size in bits
	*/
	int getSizeInBytes(int sizeInBits) const;
};

/********************************
** Standard Datapoint value Getters and Setters
*********************************/

// DPT-1: 1 bit
kdriveKnx_API void encode_DPT1(Datapoint& datapoint, bool value);
kdriveKnx_API bool decode_DPT1(const Datapoint& datapoint);

// DPT-2: 1 bit controlled
kdriveKnx_API void encode_DPT2(Datapoint& datapoint, bool control, bool value);
kdriveKnx_API void decode_DPT2(const Datapoint& datapoint, bool& control, bool& value);

// DPT-3: 3 bit controlled
kdriveKnx_API void encode_DPT3(Datapoint& datapoint, bool control, unsigned char value);
kdriveKnx_API void decode_DPT3(const Datapoint& datapoint, bool& control, unsigned char& value);

// DPT-4: Character
kdriveKnx_API void encode_DPT4(Datapoint& datapoint, unsigned char value);
kdriveKnx_API unsigned char decode_DPT4(const Datapoint& datapoint);

// DPT-5: 8 bit unsigned value
kdriveKnx_API void encode_DPT5(Datapoint& datapoint, unsigned char value);
kdriveKnx_API unsigned char decode_DPT5(const Datapoint& datapoint);

// DPT-6: 8 bit signed value
kdriveKnx_API void encode_DPT6(Datapoint& datapoint, char value);
kdriveKnx_API signed char decode_DPT6(const Datapoint& datapoint);

// DPT-7: 2 byte unsigned value
kdriveKnx_API void encode_DPT7(Datapoint& datapoint, unsigned short value);
kdriveKnx_API unsigned short decode_DPT7(const Datapoint& datapoint);

// DPT-8: 2 byte signed value
kdriveKnx_API void encode_DPT8(Datapoint& datapoint, short value);
kdriveKnx_API signed short decode_DPT8(const Datapoint& datapoint);

// DPT-9: 2 byte float value, the float is a standard IEEE float. It gets converted into a KNX 2 byte float
kdriveKnx_API void encode_DPT9_Raw(Datapoint& datapoint, unsigned char msb, unsigned char lsb);
kdriveKnx_API void encode_DPT9(Datapoint& datapoint, float f);
kdriveKnx_API unsigned short decode_DPT9_Raw(const Datapoint& datapoint);
kdriveKnx_API float decode_DPT9(const Datapoint& datapoint);

// DPT-10: time
kdriveKnx_API void encode_DPT10_Local(Datapoint& datapoint);
kdriveKnx_API void encode_DPT10_UTC(Datapoint& datapoint);
kdriveKnx_API void encode_DPT10(Datapoint& datapoint, int day, int hour, int minute, int second);
kdriveKnx_API void decode_DPT10(const Datapoint& datapoint, int& day, int& hour, int& minute, int& second);

// DPT-11: date
kdriveKnx_API void encode_DPT11_Local(Datapoint& datapoint);
kdriveKnx_API void encode_DPT11_UTC(Datapoint& datapoint);
kdriveKnx_API void encode_DPT11(Datapoint& datapoint, int year, int month, int day);
kdriveKnx_API void encode_DPT11_knx(Datapoint& datapoint, int year, int month, int day);
kdriveKnx_API void encode_DPT11_yyyy(Datapoint& datapoint, int year, int month, int day);
kdriveKnx_API void decode_DPT11(const Datapoint& datapoint, int& year, int& month, int& day);
kdriveKnx_API void decode_DPT11_knx(const Datapoint& datapoint, int& year, int& month, int& day);
kdriveKnx_API void decode_DPT11_yyyy(const Datapoint& datapoint, int& year, int& month, int& day);

// DPT-12: 4 byte unsigned value
kdriveKnx_API void encode_DPT12(Datapoint& datapoint, unsigned int value);
kdriveKnx_API unsigned int decode_DPT12(const Datapoint& datapoint);

// DPT-13: 4 byte signed value
kdriveKnx_API void encode_DPT13(Datapoint& datapoint, int value);
kdriveKnx_API signed int decode_DPT13(const Datapoint& datapoint);

// DPT-14: 4 byte float value
kdriveKnx_API void encode_DPT14(Datapoint& datapoint, float f);
kdriveKnx_API float decode_DPT14(const Datapoint& datapoint);

// DPT-15: Entrance access
kdriveKnx_API void encode_DPT15(Datapoint& datapoint, unsigned int accessCode,
                                bool error, bool permission, bool direction,
                                bool encrypted, unsigned char index);

kdriveKnx_API void decode_DPT15(const Datapoint& datapoint, unsigned int& accessCode,
                                bool& error, bool& permission, bool& direction,
                                bool& encrypted, unsigned char& index);

// DPT-16: Character string
kdriveKnx_API void encode_DPT16(Datapoint& datapoint, const std::string& str);
kdriveKnx_API std::string decode_DPT16(const Datapoint& datapoint);

// DPT-17: Scene Number
kdriveKnx_API void encode_DPT17(Datapoint& datapoint, unsigned char sceneNumber);
kdriveKnx_API unsigned char decode_DPT17(const Datapoint& datapoint);

// DPT-18: Scene Control
kdriveKnx_API void encode_DPT18(Datapoint& datapoint, bool control, unsigned char sceneNumber);
kdriveKnx_API void decode_DPT18(const Datapoint& datapoint, bool& control, unsigned char& sceneNumber);

// DPT-19: Date Time

// DPT-20: 1 Byte, use DPT-5 or DPT-6

// DPT-217: version

// DPT-219: Alarm Info

// DPT-222: 3x 16-Float Value

// DPT-232: 3-byte colour RGB
kdriveKnx_API void encode_DPT232(Datapoint& datapoint, unsigned char r, unsigned char g, unsigned char b);
kdriveKnx_API void decode_DPT232(const Datapoint& datapoint, unsigned char& r, unsigned char& g, unsigned char& b);

}
} // end namespace kdrive::knx

#endif // __KDRIVE_KNX_DATAPOINT_DATAPOINT_H__
