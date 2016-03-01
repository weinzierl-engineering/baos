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

#ifndef __KDRIVE_BAOS_SERVICES_SET_DATAPOINT_HISTORY_COMMAND_H__
#define __KDRIVE_BAOS_SERVICES_SET_DATAPOINT_HISTORY_COMMAND_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/ServiceRunner.h"
#include "kdrive/baos/core/Forwards.h"
#include <memory>

namespace kdrive
{
namespace baos
{

class kdriveRPC_baos_API SetDatapointHistoryCommand : public ServiceRunner
{
public:
	SetDatapointHistoryCommand(std::shared_ptr<BaosConnector> connector);
	virtual ~SetDatapointHistoryCommand();

	enum Commands
	{
	    Clear = 0x01,
	    Start = 0x02,
	    StartClear = 0x03,
	    Stop = 0x04,
	    StopClear = 0x05
	};

	void rpc(unsigned short offset, unsigned short count, unsigned char command,
	         unsigned long timeout = ServiceRunner::Timeout);
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_SERVICES_SET_DATAPOINT_HISTORY_COMMAND_H__
