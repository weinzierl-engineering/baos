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

#ifndef __KDRIVE_KNX_TELEGRAMS_FT12_VARIABLE_LENGTH_FRAME_H__
#define __KDRIVE_KNX_TELEGRAMS_FT12_VARIABLE_LENGTH_FRAME_H__

#include "kdrive/knx/Config.h"
#include "kdrive/knx/telegrams/formatters/Formatter.h"
#include <vector>

namespace kdrive
{
namespace knx
{
namespace ft12
{

/*!
	\class VariableLengthFrame
	\brief Frame with variable length

	Frames with user data shall consist of a start character,
	two equal characters that shall specify the number L of user data octets,
	a second start character, the user data, a frame checksum
	character and an end character.

	\verbatim

	|--------------------------------------|
	|            Start 68h                 |
	|--------------------------------------|
	|             Length L                 |
	|--------------------------------------|
	|             Length L                 |
	|--------------------------------------|
	|            Start 68h                 |
	|--------------------------------------|
	|           Control Field              |
	|--------------------------------------|
	|          Link User Data              |
	|--------------------------------------|
	|            Checksum                  |
	|--------------------------------------|
	|             End 16h                  |
	|--------------------------------------|
	\endverbatim

	Length shall specify the number of user data octets
	including the control field (range from 2 to 23).
*/

class kdriveKnx_API VariableLengthFrame : public Formatter
{
public:
	enum Attributes
	{
	    StartByte1 = 0,
	    Length1,
	    Length2,
	    StartByte2,
	    ControlField,
	    LinkUserDataBytes,
	    Checksum,
	    EndByte
	};

	enum Lengths
	{
	    HeaderLength = EndByte - 1  /*!< HeaderLength is end byte - 1, i.e. control field is not part of head length */
	};

	/*!
		Creates a default VariableLengthFrame formatter
	*/
	VariableLengthFrame();

	/*!
		Destroys the VariableLengthFrame
	*/
	virtual ~VariableLengthFrame();

	/*!
		\return the length of the VariableLengthFrame
	*/
	std::size_t size() const override;

	/*!
		The VariableLengthFrame is valid if the following checks pass

			* the specified start character at the beginning
			  and at the end of the frame header
			* the identity of the two length specifications L
			* that the number of received characters is equal to L + 6
			* the frame checksum
			* the end character

		\return true if the VariableLengthFrame is valid
	*/
	bool isValid() const override;

	/*!
		Sets the default to the valid start and end bytes,
		with control and checksum to 0x00
	*/
	void setDefaults() override;

	/*!
		\return the start byte 1
	*/
	unsigned char getStartByte1() const;

	/*!
		\return the length 1
	*/
	unsigned char getLength1() const;

	/*!
		\return the length 1
	*/
	unsigned char getLength2() const;

	/*!
		\return the start byte 2
	*/
	unsigned char getStartByte2() const;

	/*!
		sets the control field. this will also set the
		checksum if autoSetChecksum is true
	*/
	void setControlField(unsigned char controlField);

	/*!
		\return the control field
	*/
	unsigned char getControlField() const;

	/*!
		Copies the user data into the local user data buffer
	*/
	void setUserData(const unsigned char* buffer, std::size_t bufferSize);

	/*!
		\return the user data
	*/
	const std::vector<unsigned char>& getUserData() const;

	/*!
		sets the checksum
	*/
	void setChecksum(unsigned char checksum);

	/*!
		\return the checksum
	*/
	unsigned char getChecksum() const;

	/*!
		\return the end byte
	*/
	unsigned char getEndByte() const;

	/*!
		sets the variable attributes
		checksum and length1 and length2 fields
		based on the user data and control field
	*/
	void setVariableAttributes();

private:
	std::size_t readImpl(const Buffer& buffer) override;
	std::size_t writeImpl(Buffer& buffer) override;
	unsigned char calculateChecksum() const;
	int getChecksumOffset() const;

private:
	ByteFormatter startByte1_;
	ByteFormatter length1_;
	ByteFormatter length2_;
	ByteFormatter startByte2_;
	ByteFormatter controlField_;
	std::vector<unsigned char> userData_;
	ByteFormatter checksum_;
	ByteFormatter endByte_;
};

}
}
} // end namespace kdrive::knx::ft12

#endif // __KDRIVE_KNX_TELEGRAMS_FT12_VARIABLE_LENGTH_FRAME_H__
