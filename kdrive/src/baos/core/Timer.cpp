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

#include "pch/kdrive_pch.h"
#include "kdrive/baos/core/Timer.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/utility/LoggerFormatter.h"
#include <sstream>

using namespace kdrive::baos;
using kdrive::utility::LoggerFormatter;

Timer::Timer()

	: id(0),
	  triggerType(0),
	  dateTime(0),
	  startDateTime(0),
	  endDateTime(0),
	  weeks(0),
	  days(0),
	  hours(0),
	  minutes(0),
	  seconds(0),
	  jobType(0)
{
}

std::string Timer::toString() const
{
	std::ostringstream stream;
	stream << "Timer [" << id << "]" << std::endl;
	stream << "Description: " << description << std::endl;

	switch (triggerType)
	{
		case BaosTimerTypes::TriggerDate:
			stream << "Trigger: Date" << std::endl;
			stream << "Date/Time: " << dateTime << std::endl;
			break;

		case BaosTimerTypes::TriggerInterval:
			stream << "Trigger: Interval" << std::endl;
			stream << "Start Date/Time: " << startDateTime << std::endl;
			stream << "End Date/Time: " << endDateTime << std::endl;
			stream << "Weeks: " << weeks << std::endl;
			stream << "Days: " << days << std::endl;
			stream << "Hours: " << hours << std::endl;
			stream << "Minutes: " << minutes << std::endl;
			stream << "Seconds: " << seconds << std::endl;
			break;

		default:
			stream << "Trigger: ??? Unknown" << std::endl;
			break;
	}

	switch (jobType)
	{
		case BaosTimerTypes::JobSetDatapointValue:
			stream << "Job: SetDatapointValue" << std::endl;
			stream << "Datapoint id: " << static_cast<int>(datapointValue.id) << std::endl;
			stream << "Command: " << static_cast<int>(datapointValue.serviceData) << std::endl;
			stream << "Data: " << LoggerFormatter::toHex(datapointValue.data) << std::endl;
			break;

		default:
			stream << "Job: ??? Unknown" << std::endl;
			break;
	}

	return stream.str();
}
