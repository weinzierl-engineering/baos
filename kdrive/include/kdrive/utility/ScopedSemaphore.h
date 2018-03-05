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

#ifndef __KDRIVE_UTILITY_SCOPED_SEMAPHORE_H__
#define __KDRIVE_UTILITY_SCOPED_SEMAPHORE_H__

#include "kdrive/utility/Config.h"
#include <string>

namespace Poco
{

class Logger;
class Semaphore;

} // end namespace Poco


namespace kdrive
{
namespace utility
{

/*******************************
** ScopedSemaphore
********************************/

/*!
	ScopedSemaphore waits in the constructor for the semaphore to become signalled.
	The destructor increments the semaphore's value.
*/
class wzfUtility_API ScopedSemaphore
{
public:
	/*!
		Waits for the semaphore to become signalled.
	*/
	ScopedSemaphore(Poco::Semaphore& semaphore);

	/*!
		Copy constructor is deleted
	*/
	ScopedSemaphore(const ScopedSemaphore&) = delete;

	/*!
		Increments the semaphore's value.
	*/
	~ScopedSemaphore();

	/*!
		Assignment Operator is deleted
	*/
	ScopedSemaphore& operator=(const ScopedSemaphore&) = delete;

private:
	Poco::Semaphore& semaphore_;
};

/*******************************
** ScopedSemaphoreWithTraces
********************************/

/*!
	ScopedSemaphore waits in the constructor for the semaphore to become signalled.
	The destructor increments the semaphore's value.
*/
class wzfUtility_API ScopedSemaphoreWithTraces
{
public:
	/*!
		Waits for the semaphore to become signalled.
		It trace log "wait for semaphore".
	*/
	ScopedSemaphoreWithTraces(Poco::Semaphore& semaphore, Poco::Logger& logger,
	                          const std::string& name = "Unknown");

	/*!
		Copy constructor is deleted
	*/
	ScopedSemaphoreWithTraces(const ScopedSemaphoreWithTraces&) = delete;

	/*!
		Increments the semaphore's value.
		It trace "release semaphore".
	*/
	~ScopedSemaphoreWithTraces();

	/*!
		Assignment Operator is deleted
	*/
	ScopedSemaphoreWithTraces& operator=(const ScopedSemaphoreWithTraces&) = delete;

	/*!
		Sets the semaphore name.
	*/
	void setName(const std::string& name);

	/*!
		Gets the semaphore name.
	*/
	const std::string& getName() const;

private:
	Poco::Semaphore& semaphore_;
	Poco::Logger& logger_;
	std::string name_;
};

}
} // end namespace kdrive::utility

#endif // __KDRIVE_UTILITY_SCOPED_SEMAPHORE_H__
