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

#ifndef __KDRIVE_BAOS_SERVICES_SET_TIMER_H__
#define __KDRIVE_BAOS_SERVICES_SET_TIMER_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/ServiceRunner.h"
#include "kdrive/baos/core/Forwards.h"
#include "kdrive/baos/core/Timer.h"
#include <memory>
#include <vector>

namespace kdrive
{
namespace baos
{

class kdriveRPC_baos_API SetTimer : public ServiceRunner
{
public:
	/*!
		Creates a SetTimer service bound to a connection
	*/
	SetTimer(std::shared_ptr<BaosConnector> connector);

	/*!
		Destroys the SetTimer service
	*/
	virtual ~SetTimer();

	/*!
		sends a SetTimer.Req
		and waits for a SetTimer.Res
		for a single Timer
	*/
	void rpc(unsigned short offset, const Timer& timer,
	         unsigned long timeout = ServiceRunner::Timeout);

	/*!
		sends a SetTimer.Req
		and waits for a SetTimer.Res
		for multiple timers
	*/
	void rpc(unsigned short offset, const std::vector<Timer>& timers,
	         unsigned long timeout = ServiceRunner::Timeout);
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_SERVICES_SET_TIMER_H__
