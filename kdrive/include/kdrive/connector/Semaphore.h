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

#ifndef __KDRIVE_CONNECTOR_SEMAPHORE_H__
#define __KDRIVE_CONNECTOR_SEMAPHORE_H__

#include "kdrive/connector/Config.h"
#include <Poco/Semaphore.h>

namespace kdrive
{
namespace connector
{

/*!
	\class ScopedWait
	A class that simplifies semaphore synchronization
	The constructor accepts a semaphore and waits on it.
	The destructor sets the semaphore.
*/

template <class S>
class ScopedWait
{
public:
	inline ScopedWait(S& semaphore)

		: s_(semaphore),
		  set_(false)
	{
		s_.waitSem();
		set_ = true;
	}

	inline ScopedWait(S& semaphore, long milliseconds)

		: s_(semaphore),
		  set_(false)
	{
		s_.waitSem(milliseconds);
		set_ = true;
	}

	inline ~ScopedWait()
	{
		if (set_)
		{
			try
			{
				s_.setSem();
			}
			catch (...)
			{
			}
		}
	}

private:
	S& s_;
	bool set_;

	ScopedWait();
	ScopedWait(const ScopedWait&);
	ScopedWait& operator = (const ScopedWait&);
};

}
} // end namespace kdrive::connector

#endif // __KDRIVE_CONNECTOR_SEMAPHORE_H__
