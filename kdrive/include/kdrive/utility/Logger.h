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

#ifndef __WZF_UTILITY_LOGGER_LOGGER_H__
#define __WZF_UTILITY_LOGGER_LOGGER_H__

#include "kdrive/utility/Config.h"
#include "kdrive/utility/LoggerFormatter.h"
#include <Poco/Logger.h>

/*!
	Adds a new logger for a module
	Note: only one logger per file
*/
#define CLASS_LOGGER(Name) \
	namespace { \
		extern const char wzfClassLoggerName[] = Name; \
		Poco::Logger* wzfClassLogger = nullptr; \
	}

/*!
	Returns the logger associated with the Name allocated
	with CLASS_LOGGER
*/
#define LOGGER() (*(!::wzfClassLogger ? ::wzfClassLogger = &Poco::Logger::get(::wzfClassLoggerName) : ::wzfClassLogger))

#endif // __WZF_UTILITY_LOGGER_LOGGER_H__
