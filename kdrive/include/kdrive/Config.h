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

#ifndef __KDRIVE_CONFIG_H__
#define __KDRIVE_CONFIG_H__

#include "kdrive/ConfigEnabled.h"
#include "kdrive/LoggingEnabled.h"

//
// Ensure that KDRIVE_DLL is default unless KDRIVE_STATIC is defined
//
#if defined(_WIN32) && defined(_DLL)
#if !defined(KDRIVE_DLL) && !defined(KDRIVE_STATIC)
#define KDRIVE_DLL
#endif
#endif

//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the kdrive_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// kdrive_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(KDRIVE_DLL)
#if defined(kdrive_EXPORTS)
#define kdrive_API __declspec(dllexport)
#else
#define kdrive_API __declspec(dllimport)
#endif
#endif

#if defined (__GNUC__) && (__GNUC__ >= 4) && defined(KDRIVE_DLL)
#define kdrive_API __attribute__ ((visibility ("default")))
#endif

#if !defined(kdrive_API)
#define kdrive_API
#endif

#if defined(_MSC_VER)
#pragma warning(disable:4251) // ... needs to have dll-interface warning
#pragma warning(disable:4275) // ... non dll-interface class
#endif // _MSC_VER

// undefine min and max macros for windows
#if defined(_MSC_VER)
#if !defined(NOMINMAX)

#define NOMINMAX

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#endif // NOMINMAX
#endif // _MSC_VER

#endif // __KDRIVE_CONFIG_H__
