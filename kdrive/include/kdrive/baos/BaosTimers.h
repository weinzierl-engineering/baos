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

#ifndef __KDRIVE_BAOS_TIMERS_H__
#define __KDRIVE_BAOS_TIMERS_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/Forwards.h"
#include "kdrive/baos/core/Timer.h"
#include <memory>
#include <vector>

namespace kdrive
{
namespace baos
{

/*!
	\class BaosTimers

	BaosTimers is used to get/set the timer parameters
	from/on the remote device. It wraps the GetTimer and SetTimer services,
*/
class kdriveRPC_baos_API BaosTimers
{
public:
	using Timers = std::vector<Timer>;

	/*!
		Creates a BaosTimers object with a specified connector.
		precondition: connector is not null
	*/
	BaosTimers(std::shared_ptr<BaosConnector> connector);

	/*!
		Destroys the BaosTimers
	*/
	~BaosTimers();

	/*!
		Gets the time with id
	*/
	Timer getTimer(unsigned int id);

	/*!
		Gets the timers from the baos device
		Does not locally cache them.
	*/
	Timers getTimers();

	/*!
		Sets a single timer
	*/
	void setTimer(const Timer& timer);

	/*!
		Sets multiple timers
	*/
	void setTimers(const Timers& timers);

	/*!
		Deletes a single timer
	*/
	void deleteTimer(unsigned short id);

	/*!
		Deletes multiple timers
	*/
	void deleteTimers(const Timers& timers);

private:
	std::shared_ptr<BaosConnector> connector_;
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_TIMERS_H__
