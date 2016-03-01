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

#ifndef __KDRIVE_KNX_TELEGRAMS_FT12_CONTROL_FIELD_H__
#define __KDRIVE_KNX_TELEGRAMS_FT12_CONTROL_FIELD_H__

#include "kdrive/knx/Config.h"
#include "kdrive/knx/telegrams/formatters/Formatter.h"

namespace kdrive
{
namespace knx
{
namespace ft12
{

/*!
	\class ControlField
	\brief FT1.2 Control Field

	The 1 byte control field has the following structure:
	\verbatim

	|-----------------------------------------------|
	|                    1 byte                     |
	|-----------------------------------------------|
	|               Control field                   |
	|-----------------------------------------------|
	|  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
	|-----|-----------------|-----------------------|
	| DIR | PRM | FCB | FCV | Function Code         |
	|-----|-----------------|-----------------------|

	DIR: Physical transmission direction
		0 = External device to BAU
		1 = BAU to external device

	PRM: Primary message
		0 = Message from secondary station.
		1 = Message from primary station.

	FCB: Frame count bit
		Alternation bit for successive SEND/CONFIRM

	FCV: Frame count bit valid
		1: The FCB is not valid.
		0: The FCB is valid
	\endverbatim

	Note: the control field class implements setters and getters
	for the bit fields, DIR, PRM, FCB etc. The setters require that
	their arguments are formatted correspondingly, i.e for DIR that
	it is either 0x80 or 0x00 and not 0x01 or 0x00. The setters return
	the corresponding bit value field, i.e. DIR is then either
	0x80 or 0x00 etc.
*/
class kdriveKnx_API ControlField : public ByteFormatter
{
public:
	/*!
		Creates a default control field
		with a default value of 0x00
	*/
	ControlField();

	/*!
		Creates a control field set to a specific value
		\param data the value that is assigned to the control field
	*/
	ControlField(unsigned char data);

	/*!
		Destroys the control field
	*/
	virtual ~ControlField();

	/*!
		Sets the message direction
		0x80 or 0x00
	*/
	void setDirection(unsigned char direction);

	/*!
		Returns the direction bit field
		0x80 or 0x00
	*/
	unsigned char getDirection() const;

	/*!
		Sets the primary message
		0x40 or 0x00
	*/
	void setPrimaryMessage(unsigned char primaryMessage);

	/*!
		Returns the primary message
		0x40 or 0x00
	*/
	unsigned char getPrimaryMessage() const;

	/*!
		Sets the value of the frame count bit
		0x20 or 0x00
	*/
	void setFrameCountBit(unsigned char frameCountBit);

	/*!
		Returns the value of the frame count bit
		0x20 or 0x00
	*/
	unsigned char getFrameCountBit() const;

	/*!
		Sets whether the FCB is valid
		0x10 or 0x00
	*/
	void setFrameCountBitValid(unsigned char frameCountBitValid);

	/*!
		Returns the value of the FCB valid bit
		0x10 or 0x00
	*/
	unsigned char getFrameCountBitValid() const;

	/*!
		Sets the function code
		All values between 0x00 and 0x0F are supported
	*/
	void setFunctionCode(unsigned char functionCode);

	/*!
		Returns the function code
		A value between 0x00 and 0x0F
	*/
	unsigned char getFunctionCode() const;

private:
	enum Masks
	{
	    DirectionMask = 0x80,
	    PrimaryMessageMask = 0x40,
	    FrameCountBitMask = 0x20,
	    FrameCountBitValidMask = 0x10,
	    FunctionCodeMask = 0x0F
	};

	enum Attributes
	{
	    Direction = 0,
	    PrimaryMessage,
	    FrameCountBit,
	    FrameCountBitValid,
	    FunctionCode
	};
};

}
}
} // end namespace kdrive::knx::ft12

#endif // __KDRIVE_KNX_TELEGRAMS_FT12_CONTROL_FIELD_H__
