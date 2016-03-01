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

#ifndef __KDRIVE_BAOS_CORE_TIMER_H__
#define __KDRIVE_BAOS_CORE_TIMER_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/ServerItem.h"
#include <string>

namespace kdrive
{
namespace baos
{

struct kdriveRPC_baos_API Timer
{
	Timer();

	/*!
		This function is intended mostly for debug purposes
		It will generate the timer configuration string
		depending on the trigger and job types
	*/
	std::string toString() const;

	unsigned short id;					/*!< the datapoint value id */

	int triggerType;					/*!< the trigger type, either date or interval */
	unsigned int dateTime;				/*!< trigger date: date/time seconds since epoch */
	unsigned int startDateTime;			/*!< trigger interval: start date/time seconds since epoch */
	unsigned int endDateTime;			/*!< trigger interval: end date/time seconds since epoch */
	int weeks;							/*!< trigger interval: every n weeks */
	int days;							/*!< trigger interval: every n days */
	int hours;							/*!< trigger interval: every n hours */
	int minutes;						/*!< trigger interval: every n minutes */
	int seconds;						/*!< trigger interval: every n seconds */

	int jobType;						/*!< the job type, currently only set datapoint value */
	ServerItem datapointValue;			/*!< job set datapoint value */

	std::string description;			/*!< timer description string */
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_CORE_TIMER_H__
