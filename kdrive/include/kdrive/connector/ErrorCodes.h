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

#ifndef __KDRIVE_CONNECTOR_ERROR_CODES_H__
#define __KDRIVE_CONNECTOR_ERROR_CODES_H__

#include "kdrive/connector/Config.h"

namespace kdrive
{
namespace connector
{

/*!
	Error codes from the kdriveConnector lib
	The connector error codes begins with 0x0001.
*/
struct kdriveConnector_API ConnectorErrorCodes
{
	/*
		Removing and reordering is not allowed.
		Add new codes on the and mark nor more used codes with deprecated.
	*/
	enum
	{
	    None = 0, /*!< No error */
	    ConnectorError = 0x0001, /*!< kdriveConnector error */
	};
};

}
} // end namespace kdrive::access

#endif // __KDRIVE_CONNECTOR_ERROR_CODES_H__
