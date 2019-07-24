//
// Copyright (c) 2002-2019 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//

#ifndef __KDRIVE_BAOS_PARAMETER_H__
#define __KDRIVE_BAOS_PARAMETER_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/Forwards.h"
#include <memory>
#include <vector>

namespace kdrive
{
namespace baos
{

/*!
	Reads a parameter byte from the BAOS device.
	This parameter byte should be configured with the ETS application
*/
kdriveRPC_baos_API unsigned char readParameter(std::shared_ptr<BaosConnector> connector, unsigned short offset);

/*!
	Reads multiple contiguous parameter bytes from the BAOS device.
	This parameter byte should be configured with the ETS application
*/
kdriveRPC_baos_API void readParameters(std::shared_ptr<BaosConnector> connector,
                                       std::vector<unsigned char>& data,
                                       unsigned short offset,
                                       unsigned short count);

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_PARAMETER_H__

