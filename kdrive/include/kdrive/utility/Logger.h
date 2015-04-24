//
// Copyright (c) 2002-2015 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//

#ifndef __WZF_UTILITY_LOGGER_LOGGER_H__
#define __WZF_UTILITY_LOGGER_LOGGER_H__

#include "kdrive/utility/Config.h"
#include "kdrive/utility/LoggerFormatter.h"
#include <Poco/Logger.h>

namespace kdrive
{
namespace utility
{

template <const char* const Name>
struct NamedLogger
{
	static Poco::Logger& get()
	{
		return Poco::Logger::get(Name);
	}
};

}
} // end namespace kdrive::utility


/*!
	Allocates a class logger. This logger can be used
	once for each file module. To get the logger associated with
	the name, simply use the LOGGER() macro
*/
#define CLASS_LOGGER(Name) \
	namespace { extern const char wzfClassLogger[] = Name; }

/*!
	Returns the logger associated with the Name allocated
	with CLASS_LOGGER
*/
#define LOGGER() \
	kdrive::utility::NamedLogger<wzfClassLogger>::get()

#endif // __WZF_UTILITY_LOGGER_LOGGER_H__
