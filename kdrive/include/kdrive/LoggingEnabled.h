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

#ifndef __KDRIVE_LOGGING_ENABLED_H__
#define __KDRIVE_LOGGING_ENABLED_H__

#include <Poco/Logger.h>

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_fatal)
#undef poco_fatal
#define poco_fatal(logger, msg)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_fatal_f1)
#undef poco_fatal_f1
#define poco_fatal_f1(logger, fmt, arg1)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_fatal_f2)
#undef poco_fatal_f2
#define poco_fatal_f2(logger, fmt, arg1, arg2)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_fatal_f3)
#undef poco_fatal_f3
#define poco_fatal_f3(logger, fmt, arg1, arg2, arg3)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_fatal_f4)
#undef poco_fatal_f4
#define poco_fatal_f4(logger, fmt, arg1, arg2, arg3, arg4)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_critical)
#undef poco_critical
#define poco_critical(logger, msg)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_critical_f1)
#undef poco_critical_f1
#define poco_critical_f1(logger, fmt, arg1)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_critical_f2)
#undef poco_critical_f2
#define poco_critical_f2(logger, fmt, arg1, arg2)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_critical_f3)
#undef poco_critical_f3
#define poco_critical_f3(logger, fmt, arg1, arg2, arg3)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_critical_f4)
#undef poco_critical_f4
#define poco_critical_f4(logger, fmt, arg1, arg2, arg3, arg4)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_error)
#undef poco_error
#define poco_error(logger, msg)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_error_f1)
#undef poco_error_f1
#define poco_error_f1(logger, fmt, arg1)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_error_f2)
#undef poco_error_f2
#define poco_error_f2(logger, fmt, arg1, arg2)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_error_f3)
#undef poco_error_f3
#define poco_error_f3(logger, fmt, arg1, arg2, arg3)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_error_f4)
#undef poco_error_f4
#define poco_error_f4(logger, fmt, arg1, arg2, arg3, arg4)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_warning)
#undef poco_warning
#define poco_warning(logger, msg)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_warning_f1)
#undef poco_warning_f1
#define poco_warning_f1(logger, fmt, arg1)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_warning_f2)
#undef poco_warning_f2
#define poco_warning_f2(logger, fmt, arg1, arg2)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_warning_f3)
#undef poco_warning_f3
#define poco_warning_f3(logger, fmt, arg1, arg2, arg3)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_warning_f4)
#undef poco_warning_f4
#define poco_warning_f4(logger, fmt, arg1, arg2, arg3, arg4)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_notice)
#undef poco_notice
#define poco_notice(logger, msg)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_notice_f1)
#undef poco_notice_f1
#define poco_notice_f1(logger, fmt, arg1)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_notice_f2)
#undef poco_notice_f2
#define poco_notice_f2(logger, fmt, arg1, arg2)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_notice_f3)
#undef poco_notice_f3
#define poco_notice_f3(logger, fmt, arg1, arg2, arg3)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_notice_f4)
#undef poco_notice_f4
#define poco_notice_f4(logger, fmt, arg1, arg2, arg3, arg4)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_information)
#undef poco_information
#define poco_information(logger, msg)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_information_f1)
#undef poco_information_f1
#define poco_information_f1(logger, fmt, arg1)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_information_f2)
#undef poco_information_f2
#define poco_information_f2(logger, fmt, arg1, arg2)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_information_f3)
#undef poco_information_f3
#define poco_information_f3(logger, fmt, arg1, arg2, arg3)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_information_f4)
#undef poco_information_f4
#define poco_information_f4(logger, fmt, arg1, arg2, arg3, arg4)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_debug)
#undef poco_debug
#define poco_debug(logger, msg)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_debug_f1)
#undef poco_debug_f1
#define poco_debug_f1(logger, fmt, arg1)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_debug_f2)
#undef poco_debug_f2
#define poco_debug_f2(logger, fmt, arg1, arg2)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_debug_f3)
#undef poco_debug_f3
#define poco_debug_f3(logger, fmt, arg1, arg2, arg3)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_debug_f4)
#undef poco_debug_f4
#define poco_debug_f4(logger, fmt, arg1, arg2, arg3, arg4)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_trace)
#undef poco_trace
#define poco_trace(logger, msg)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_trace_f1)
#undef poco_trace_f1
#define poco_trace_f1(logger, fmt, arg1)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_trace_f2)
#undef poco_trace_f2
#define poco_trace_f2(logger, fmt, arg1, arg2)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_trace_f3)
#undef poco_trace_f3
#define poco_trace_f3(logger, fmt, arg1, arg2, arg3)
#endif

#if defined(KDRIVE_DISABLE_LOGGING) && defined(poco_trace_f4)
#undef poco_trace_f4
#define poco_trace_f4(logger, fmt, arg1, arg2, arg3, arg4)
#endif

#endif // __KDRIVE_LOGGING_ENABLED_H__
