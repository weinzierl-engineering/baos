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

#ifndef __KDRIVE_KNX_TELEGRAMS_FT12_ACK_FRAME_H__
#define __KDRIVE_KNX_TELEGRAMS_FT12_ACK_FRAME_H__

#include "kdrive/knx/Config.h"
#include "kdrive/knx/telegrams/formatters/Formatter.h"

namespace kdrive
{
namespace knx
{
namespace ft12
{

/*!
	\class AckFrame
	\brief Acknowledgment Frame format (single character)
	One single character is specified: Ack E5h
	The single character shall be used for a positive acknowledgment.
*/
class kdriveKnx_API AckFrame : public ByteFormatter
{
public:
	enum Attributes
	{
	    Length = 1	/*!< The constant length of the ack frame */
	};

	/*!
		Creates a default AckFrame
		calls setDefaults: the frame is constructed with
		the correct value
		\sa setDefaults
	*/
	AckFrame();

	/*!
		Destroys the AckFrame
	*/
	virtual ~AckFrame();

	/*!
		\return true if an ack frame
	*/
	bool isValid() const override;

	/*!
		sets the default to the ack frame value
	*/
	void setDefaults() override;
};

}
}
} // end namespace kdrive::knx::ft12

#endif // __KDRIVE_KNX_TELEGRAMS_FT12_ACK_FRAME_H__
