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

#ifndef __KDRIVE_KNX_DATAPOINT_DATAPOINT_FLOAT_CONVERTER_H__
#define __KDRIVE_KNX_DATAPOINT_DATAPOINT_FLOAT_CONVERTER_H__

#include "kdrive/knx/Config.h"
#include <cstddef>
#include <tuple>

namespace kdrive
{
namespace knx
{

struct kdriveKnx_API FloatConverter
{
	/*!
		\deprecated
		Use toFloat4FromFloat2 instead.
	*/
	static float toFloat2(unsigned char msb, unsigned char lsb);

	/*!
		converts a 4-byte float to a 2-byte float
		This function converts a 4-byte float (IEEE-Float) to
		a 2-byte float (KNX-Float DPT 9.xxx/EIS5)
	*/
	static std::tuple<unsigned char, unsigned char> toFloat2FromFloat4(float f);

	/*!
		This function converts a 2-byte float (KNX-Float DPT 9.xxx/EIS5) to a 4-byte float (IEEE-Float)
		The format of the KNX-float is MEEEEMMM MMMMMMMM
	*/
	static float toFloat4FromFloat2(unsigned char msb, unsigned char lsb);
};

}
} // end namespace kdrive::knx

#endif // __KDRIVE_KNX_DATAPOINT_DATAPOINT_FLOAT_CONVERTER_H__
