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

#ifndef __KDRIVE_BAOS_SERVICES_GET_TIMER_H__
#define __KDRIVE_BAOS_SERVICES_GET_TIMER_H__

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

class kdriveRPC_baos_API GetTimer : public ServiceRunner
{
public:
	/*!
		Creates a GetTimer service bound to a connection
	*/
	GetTimer(std::shared_ptr<BaosConnector> connector);

	/*!
		Destroys the GetTimer service
	*/
	virtual ~GetTimer();

	/*!
		sends a GetTimer.Req
		and waits for a GetTimer.Res
	*/
	void rpc(unsigned short offset, unsigned short count,
	         unsigned long timeout = ServiceRunner::Timeout);

	/*!
		the list of timers received from the device
	*/
	using Timers = std::vector<Timer>;

	/*!
		Gets a Timer from the list
		Throws an exception if index is out of range
		\return Timer at index, index is the position in the list, not the id
		\sa find
	*/
	const Timer& at(int index) const;

	/*!
		Finds a Timer in the list based on the id
		\return the timer if found, otherwise an exception is thrown
	*/
	const Timer& find(unsigned short id) const;

	/*!
		\return the list of timers
	*/
	const Timers& getTimers() const;

private:
	Timers timers_;
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_SERVICES_GET_TIMER_H__
