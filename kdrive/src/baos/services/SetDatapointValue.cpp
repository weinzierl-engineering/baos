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
#include "kdrive/baos/services/SetDatapointValue.h"
#include "kdrive/baos/protocols/Protocol.h"
#include "kdrive/baos/core/ServerFunction.h"
#include "kdrive/baos/core/API.h"

using namespace kdrive::connector;
using namespace kdrive::baos;

SetDatapointValue::SetDatapointValue(BaosConnector::Ptr connector)

	: ServiceRunner(connector)
{
}

SetDatapointValue::~SetDatapointValue()
{
}

void SetDatapointValue::rpc(unsigned short offset, const Value& value, unsigned long timeout)
{
	Values values;
	values.push_back(value);
	rpc(offset, values, timeout);
}

void SetDatapointValue::rpc(unsigned short offset, const Values& values, unsigned long timeout)
{
	unsigned short count = static_cast<unsigned short>(values.size());

	DataRequest::Ptr dataRequest =
	    DataRequestFactory::create(getConnector(), RequestFunctions::SetDatapointValue, offset, count);

	ProtocolFormatter::encodeSetDatapointValue_Req(dataRequest, values);

	ServerFunction serverFunction(getConnector());
	DataResponse::Ptr dataResponse = serverFunction.rpc(dataRequest, timeout);
	setDataResponse(dataResponse);
}
