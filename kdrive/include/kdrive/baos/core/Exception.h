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

#ifndef __KDRIVE_BAOS_CORE_EXCEPTION_H__
#define __KDRIVE_BAOS_CORE_EXCEPTION_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/ErrorCodes.h"
#include "kdrive/baos/core/FixPocoException.h"
#include <Poco/Exception.h>

namespace kdrive
{
namespace baos
{

#define DECLARE_BAOS_EXCEPTION(CLS, BASE, CODE) \
	POCO_DECLARE_EXCEPTION_CODE(kdriveRPC_baos_API, CLS, BASE, BaosErrorCodes::CODE)

DECLARE_BAOS_EXCEPTION(BaosException, Poco::Exception, BaosError)

DECLARE_BAOS_EXCEPTION(ClientException, BaosException, ClientError)

DECLARE_BAOS_EXCEPTION(ServerException, BaosException, ServerError)
DECLARE_BAOS_EXCEPTION(InternalServerException, ServerException, Internal)
DECLARE_BAOS_EXCEPTION(NoItemFoundServerException, ServerException, NoItemFound)
DECLARE_BAOS_EXCEPTION(BufferTooSmallServerException, ServerException, BufferTooSmall)
DECLARE_BAOS_EXCEPTION(ItemNotWriteableServerException, ServerException, ItemNotWriteable)
DECLARE_BAOS_EXCEPTION(ServiceNotSupportedServerException, ServerException, ServiceNotSupported)
DECLARE_BAOS_EXCEPTION(BadServiceParameterServerException, ServerException, BadServiceParameter)
DECLARE_BAOS_EXCEPTION(WrongDpIdServerException, ServerException, WrongDpId)
DECLARE_BAOS_EXCEPTION(BadDpCmdServerException, ServerException, BadDpCmd)
DECLARE_BAOS_EXCEPTION(BadDpValueLengthServerException, ServerException, BadDpValueLength)
DECLARE_BAOS_EXCEPTION(MessageInconsistentServerException, ServerException, MessageInconsistent)
DECLARE_BAOS_EXCEPTION(ObjectServerIsBusyServerException, ServerException, ObjectServerIsBusy)


#undef DECLARE_BAOS_EXCEPTION

/*!
	Throws the baos server exception in dependency from the BAOS server error code.
	\param baosServerErrorCode see BaosServerErrorCodes
	\note param baosServerErrorCode is not a BaosErrorCodes!
*/
kdriveRPC_baos_API void throwBaosServerException(unsigned int baosServerErrorCode);

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_CORE_EXCEPTION_H__
