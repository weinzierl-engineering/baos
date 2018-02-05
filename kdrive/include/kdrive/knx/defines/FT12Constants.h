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

#ifndef __KDRIVE_KNX_DEFINES_FT12_CONSTANTS_H__
#define __KDRIVE_KNX_DEFINES_FT12_CONSTANTS_H__

#include "kdrive/knx/Config.h"

namespace kdrive
{
namespace knx
{
namespace ft12
{

struct kdriveKnx_API FT12Constants
{
	/*!
		Single char frames
		This frames are only one byte long.
	*/
	enum SingleCharFrames
	{
	    AckFrame = 0xE5 /*!< Positive acknowledge frame. */
	};

	/*!
		Control Bytes
		Special bytes for start and end frames.
	*/
	enum ControlBytes
	{
	    StartFixedLengthFrame = 0x10, /*!< Start byte for frames with fixed length. */
	    StartVarLengthFrame = 0x68, /*!< Start byte for frames with variable length. */
	    EndFrame = 0x16, /*!< The end character. */
	};

	/*!
		Physical transmission direction. (DIR)
		Used with a bitwise OR in the "Control field" from FT1.2 frames.
	*/
	enum Directions
	{
	    ExternalToBauDirection = 0x00, /*!< Direction from External device to BAU */
	    BauToExternalDirection = 0x80 /*!< Direction from BAU device to External device */
	};

	/*!
		Primary message. (PRM)
		Comes the message from a primary or from a secondary station.
		Used with a bitwise OR in the "Control field" from FT1.2 frames.
	*/
	enum PrimarySecondaryMessage
	{
	    SecondaryMessage = 0x00, /*!< Message from secondary station. */
	    PrimaryMessage = 0x40 /*!< Message from primary station. */
	};

	/*!
		Frame count bit valid. (FCV)
		Used with a bitwise OR in the "Control field" from FT1.2 frames.
	*/
	enum FrameCountBitValid
	{
	    InvalidFCB = 0x00, /*!< The frame count bit is invalid */
	    ValidFCB = 0x10 /*!< The frame count bit is valid */
	};

	/*!
		Frame count bit values. (FCB)
		Used with a bitwise OR in the "Control field" from FT1.2 frames.
	*/
	enum FrameCountBitValue
	{
	    FCB_SET = 0x20 /*!< The frame count bit is set */
	};

	/*!
		Function Codes
		Used with a bitwise OR in the "Control field" from FT1.2 frames.
	*/
	enum FunctionCodes
	{
	    SendReset = 0x00, /*!< Reset of link. (Send with fixed length frame.) */
	    SendUdat = 0x03, /*!< Send unser data. (Send with variable length frame.) */
	    ReqStatus = 0x09, /*!< Request status of link. (Send with fixed length frame.) */
	    RespondStatus = 0x0B /*!< Response status of link. (Send with fixed length frame.) */
	};

	/*!
		Buffer Constants
		Indicates the expected max buffer size associated with FT1.2 in bytes
	*/
	enum BufferConstants
	{
	    MaxBufferSize = 256
	};
};

}
}
} // end namespace kdrive::knx::ft12

#endif // __KDRIVE_KNX_DEFINES_FT12_CONSTANTS_H__
