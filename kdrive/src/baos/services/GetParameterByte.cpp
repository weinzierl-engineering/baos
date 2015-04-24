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

#include "pch/kdrive_pch.h"
#include "kdrive/baos/services/GetParameterByte.h"
#include "kdrive/baos/protocols/Protocol.h"
#include "kdrive/baos/core/API.h"
#include <Poco/Exception.h>

using namespace kdrive::connector;
using namespace kdrive::baos;
using Poco::Exception;

GetParameterByte::GetParameterByte(BaosConnector::Ptr connector)

	: ServiceRunner(connector)
{
}

GetParameterByte::~GetParameterByte()
{
}

void GetParameterByte::rpc(unsigned short offset, unsigned short count, unsigned long timeout)
{
	data_.clear();

	ServiceRunner::rpc(RequestFunctions::GetParameterByte, offset, count, timeout);

	ProtocolFormatter::decodeGetParameterByte_Res(getDataResponse(), data_);

	if (count != data_.size())
	{
		throw Exception("GetParameterByte Invalid Response size");
	}
}

/*!
    returns data
*/
const std::vector<unsigned char>& GetParameterByte::getData() const
{
	return data_;
}
