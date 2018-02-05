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

#ifndef __KDRIVE_BAOS_CORE_ERROR_CODES_H__
#define __KDRIVE_BAOS_CORE_ERROR_CODES_H__

#include "kdrive/baos/Config.h"
#include <string>

namespace kdrive
{
namespace baos
{

/*!
	Error codes from the kdriveRPC_baos lib
	The range for the baos error codes begins with 0x00010000 and ends with 0x00011FFF.
	The other codes are reserved for other kdrive components.
*/
struct kdriveRPC_baos_API BaosErrorCodes
{
	/*
		Removing and reordering is not allowed.
		Add new codes on the end and mark nor more used codes with deprecated.
	*/
	enum Codes
	{
	    None = 0,

	    BaosError = 0x10000, // 65536
	    ClientError = 0x10001, // 65537

	    /*! 0x10002 to 0x10FFF are reserved for future client error codes */

	    ServerError = 0x11000, // 69632
	    Internal = 0x11001, // 69633
	    NoItemFound = 0x11002, // 69634
	    BufferTooSmall = 0x11003, // 69635
	    ItemNotWriteable = 0x11004, // 69636
	    ServiceNotSupported = 0x11005, // 69637
	    BadServiceParameter = 0x11006, // 69638
	    WrongDpId = 0x11007, // 69639
	    BadDpCmd = 0x11008, // 69640
	    BadDpValueLength = 0x11009, // 69641
	    MessageInconsistent = 0x1100A, // 69642
	    ObjectServerIsBusy = 0x1100B, // 69643
	};

	/*!
		given an error code will return the corresponding short string
	*/
	static std::string toString(unsigned int errorCode);
};

/*!
    given a std::exception will try to extract the error code
    embedded in Poco::Exception otherwise will return exception.what()
    use this if you are not compiling against the poco library
*/
kdriveRPC_baos_API std::string lookupErrorCode(std::exception& exception);

/*!
    given a std::exception will try to extract the error code
    embedded in Poco::Exception otherwise will return defaultCode
*/
kdriveRPC_baos_API unsigned int lookupErrorCodeValue(std::exception& exception, unsigned int defaultCode = 0);

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_CORE_ERROR_CODES_H__
