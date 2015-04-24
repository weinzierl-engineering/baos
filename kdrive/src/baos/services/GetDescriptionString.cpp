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
#include "kdrive/baos/services/GetDescriptionString.h"
#include "kdrive/baos/protocols/Protocol.h"
#include "kdrive/baos/core/API.h"

using namespace kdrive::connector;
using namespace kdrive::baos;

GetDescriptionString::GetDescriptionString(BaosConnector::Ptr connector)

	: ServiceRunner(connector)
{
}

GetDescriptionString::~GetDescriptionString()
{
}

void GetDescriptionString::rpc(unsigned short offset, unsigned short count, unsigned long timeout)
{
	strings_.clear();

	ServiceRunner::rpc(RequestFunctions::GetDescriptionString, offset, count, timeout);

	ProtocolFormatter::decodeGetDescriptionString_Res(getDataResponse(), strings_);
}

/*!
    returns a single item
*/
const std::string& GetDescriptionString::at(int index) const
{
	return strings_.at(index);
}

/*!
    returns all items
*/
const GetDescriptionString::Strings& GetDescriptionString::getStrings() const
{
	return strings_;
}

