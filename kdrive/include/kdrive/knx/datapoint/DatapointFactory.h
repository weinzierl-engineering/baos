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

#ifndef __KDRIVE_KNX_DATAPOINT_FACTORY_H__
#define __KDRIVE_KNX_DATAPOINT_FACTORY_H__

#include "kdrive/knx/Config.h"
#include "kdrive/knx/datapoint/Datapoint.h"

namespace kdrive
{
namespace knx
{

struct kdriveKnx_API DatapointFactory
{
	/*!
		Creates a datapoint from a datapoint type enum
		\sa DatapointTypes
	*/
	static Datapoint create(int datapointType);

	/*!
		Creates a datapoint from a datapoint id
		for example, DPST-1-1
		\sa DatapointTypes
	*/
	static Datapoint create(const std::string& datapointId);
};

}
} // end namespace kdrive::knx

#endif // __KDRIVE_KNX_DATAPOINT_FACTORY_H__
