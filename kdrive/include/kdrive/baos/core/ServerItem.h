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

#ifndef __KDRIVE_BAOS_CORE_SERVER_ITEM_H__
#define __KDRIVE_BAOS_CORE_SERVER_ITEM_H__

#include "kdrive/baos/Config.h"
#include <vector>

namespace kdrive
{
namespace baos
{

struct kdriveRPC_baos_API ServerItem
{
	ServerItem();

	unsigned short id;					/*!< the datapoint value id */
	unsigned char serviceData;			/*!< the state / command, depends on the service */
	unsigned char length;				/*!< the length of the data */
	std::vector<unsigned char> data;	/*!< the data */
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_CORE_SERVER_ITEM_H__
