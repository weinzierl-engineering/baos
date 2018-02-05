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

#include "pch/kdrive_pch.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/baos/core/API.h"
#include <Poco/Format.h>
#include <typeinfo>

using Poco::format;

namespace kdrive
{
namespace baos
{

POCO_IMPLEMENT_EXCEPTION(BaosException, Poco::Exception, "kdriveBAOS exception")

POCO_IMPLEMENT_EXCEPTION(ClientException, BaosException, "BAOS Client exception")

POCO_IMPLEMENT_EXCEPTION(ServerException, BaosException, "BAOS Server exception")
POCO_IMPLEMENT_EXCEPTION(InternalServerException, ServerException, "Internal error")
POCO_IMPLEMENT_EXCEPTION(NoItemFoundServerException, ServerException, "No item found")
POCO_IMPLEMENT_EXCEPTION(BufferTooSmallServerException, ServerException, "Buffer is too small")
POCO_IMPLEMENT_EXCEPTION(ItemNotWriteableServerException, ServerException, "Item is not writable")
POCO_IMPLEMENT_EXCEPTION(ServiceNotSupportedServerException, ServerException, "Service is not supported")
POCO_IMPLEMENT_EXCEPTION(BadServiceParameterServerException, ServerException, "Bad service parameter")
POCO_IMPLEMENT_EXCEPTION(WrongDpIdServerException, ServerException, "Wrong datapoint ID")
POCO_IMPLEMENT_EXCEPTION(BadDpCmdServerException, ServerException, "Bad datapoint command")
POCO_IMPLEMENT_EXCEPTION(BadDpValueLengthServerException, ServerException, "Bad length of datapoint value")
POCO_IMPLEMENT_EXCEPTION(MessageInconsistentServerException, ServerException, "Message inconsistent")
POCO_IMPLEMENT_EXCEPTION(ObjectServerIsBusyServerException, ServerException, "Object server is busy")

void throwBaosServerException(unsigned int baosServerErrorCode)
{
	switch (baosServerErrorCode)
	{
		case BaosServerErrorCodes::None:
			// No error; Nothing to do.
			break;
		case BaosServerErrorCodes::Internal:
			throw InternalServerException();
		case BaosServerErrorCodes::NoItemFound:
			throw NoItemFoundServerException();
		case BaosServerErrorCodes::BufferTooSmall:
			throw BufferTooSmallServerException();
		case BaosServerErrorCodes::ItemNotWriteable:
			throw ItemNotWriteableServerException();
		case BaosServerErrorCodes::ServiceNotSupported:
			throw ServiceNotSupportedServerException();
		case BaosServerErrorCodes::BadServiceParameter:
			throw BadServiceParameterServerException();
		case BaosServerErrorCodes::WrongDpId:
			throw WrongDpIdServerException();
		case BaosServerErrorCodes::BadDpCmd:
			throw BadDpCmdServerException();
		case BaosServerErrorCodes::BadDpValueLength:
			throw BadDpValueLengthServerException();
		case BaosServerErrorCodes::MessageInconsistent:
			throw MessageInconsistentServerException();
		case BaosServerErrorCodes::ObjectServerIsBusy:
			throw ObjectServerIsBusyServerException();
		default:
			throw ServerException(format("Unknown Error Code (%u)", baosServerErrorCode));
	}
}

}
} // end namespace kdrive::baos
