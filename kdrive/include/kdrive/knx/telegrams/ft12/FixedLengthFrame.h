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

#ifndef __KDRIVE_KNX_TELEGRAMS_FT12_FIXED_LENGTH_FRAME_H__
#define __KDRIVE_KNX_TELEGRAMS_FT12_FIXED_LENGTH_FRAME_H__

#include "kdrive/knx/Config.h"
#include "kdrive/knx/telegrams/formatters/Formatter.h"

namespace kdrive
{
namespace knx
{
namespace ft12
{

/*!
	\class FixedLengthFrame
	\brief Frame with fixed length

	Frames with fixed length shall consist of a start character,
	one Control field, a frame checksum character and an end
	character. In frames with fixed length the checksum shall
	be equal to the Control field.

	\verbatim

	|--------------------------------------|
	|            Start 10h                 |
	|--------------------------------------|
	|           Control Field              |
	|--------------------------------------|
	|            Checksum                  |
	|--------------------------------------|
	|             End 16h                  |
	|--------------------------------------|
	\endverbatim

	It is possible to configure the FixedLengthFrame formatter to
	auto-set the checksum whenever the control field is changed.
	This is the default behaviour. To disable this, construct the
	FixedLengthFrame with autoSetChecksum to false.

	A FixedLengthFrame is valid when:
		Start is 10h, End is 16h and control field and checksum are equal
*/
class kdriveKnx_API FixedLengthFrame : public Formatter
{
public:
	enum Attributes
	{
	    StartByte_ = 0,
	    ControlField,
	    Checksum,
	    EndByte,
	    Length /*!< The constant length of the fixed length frame */
	};

	/*
		Creates a FixedLengthFrame
		\param autoSetChecksum auto-sets the checksum to the control field when control field is set
	*/
	FixedLengthFrame(bool autoSetChecksum = true);

	/*!
		Destroys the FixedLengthFrame
	*/
	virtual ~FixedLengthFrame();

	/*!
		\return true if Start is 10h, End is 16h
		and the control field and checksum are equal
	*/
	bool isValid() const override;

	/*!
		Sets the default to the valid start and end bytes,
		with control and checksum to 0x00
	*/
	void setDefaults() override;

	/*!
		\return the start byte
	*/
	unsigned char getStartByte() const;

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
		sets the checksum
	*/
	void setChecksum(unsigned char checksum);

	/*!
		\return the checksum
	*/
	unsigned char getChecksum() const;

	/*!
		\return true if the checksum and the control field are equal
	*/
	bool isValidChecksum() const;

	/*!
		\return the end byte
	*/
	unsigned char getEndByte() const;

private:
	const bool autoSetChecksum_;
	ByteFormatter startByte_;
	ByteFormatter controlField_;
	ByteFormatter checksum_;
	ByteFormatter endByte_;
};

}
}
} // end namespace kdrive::knx::ft12

#endif // __KDRIVE_KNX_TELEGRAMS_FT12_FIXED_LENGTH_FRAME_H__
