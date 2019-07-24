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

#include "pch/kdrive_pch.h"
#include "kdrive/baos/core/ErrorCodes.h"
#include <Poco/Exception.h>

using Poco::Exception;

std::string kdrive::baos::BaosErrorCodes::toString(unsigned int errorCode)
{
	switch (errorCode)
	{
		case BaosErrorCodes::None:
			return "No Error";
		case BaosErrorCodes::BaosError:
			return "kdriveBAOS Error";
		case BaosErrorCodes::ClientError:
			return "BAOS Client Error";
		case BaosErrorCodes::ServerError:
			return "BAOS Server Error";
		case BaosErrorCodes::Internal:
			return "Internal Error";
		case BaosErrorCodes::NoItemFound:
			return "No Item Found";
		case BaosErrorCodes::BufferTooSmall:
			return "Buffer is too small";
		case BaosErrorCodes::ItemNotWriteable:
			return "Item is not writable";
		case BaosErrorCodes::ServiceNotSupported:
			return "Service is not supported";
		case BaosErrorCodes::BadServiceParameter:
			return "Bad service parameter";
		case BaosErrorCodes::WrongDpId:
			return "Wrong datapoint ID";
		case BaosErrorCodes::BadDpCmd:
			return "Bad datapoint command";
		case BaosErrorCodes::BadDpValueLength:
			return "Bad length of datapoint value";
		case BaosErrorCodes::MessageInconsistent:
			return "Message inconsistent";
		case BaosErrorCodes::ObjectServerIsBusy:
			return "Object server is busy";
		default:
			return "Unknown Error Code";
	}
}

std::string kdrive::baos::lookupErrorCode(std::exception& exception)
{
	Exception* e = dynamic_cast<Exception*>(&exception);
	return e ? e->displayText() : exception.what();
}

unsigned int kdrive::baos::lookupErrorCodeValue(std::exception& exception, unsigned int defaultCode)
{
	Exception* e = dynamic_cast<Exception*>(&exception);
	return e ? e->code() : defaultCode;
}
