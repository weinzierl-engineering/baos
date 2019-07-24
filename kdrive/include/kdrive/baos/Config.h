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

#ifndef __BAOS_CONFIG_H__
#define __BAOS_CONFIG_H__

#include "kdrive/Config.h"

#define kdriveRPC_baos_API kdrive_API

// The baos sdk has several extensions which can be
// enabled if compiling with the kdriveAccess library
// The kdriveAccess is part of the kdrive C++ source SDK
// from Weinzierl Engineering and is not available as
// part of the open source BAOS SDK
// The open source BAOS SDK will not compile if this is
// set to 1
#define KDRIVE_BAOS_ACCESS_ENABLED (0)

#endif // __BAOS_CONFIG_H__
