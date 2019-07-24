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
#include "kdrive/baos/services/GetDatapointValue.h"
#include "kdrive/baos/core/ServerFunction.h"
#include "kdrive/baos/protocols/Protocol.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/Exception.h"

using namespace kdrive::connector;
using namespace kdrive::baos;

GetDatapointValue::GetDatapointValue(BaosConnector::Ptr connector)

	: ServiceRunner(connector),
	  filter_(GetAll)
{
}

GetDatapointValue::~GetDatapointValue()
{
}

void GetDatapointValue::setFilter(unsigned char filter)
{
	filter_ = filter;
}

unsigned char GetDatapointValue::getFilter()
{
	return filter_;
}

void GetDatapointValue::rpc(unsigned short offset, unsigned short count, unsigned long timeout)
{
	values_.clear();

	DataRequest::Ptr dataRequest =
	    DataRequestFactory::create(getConnector(), RequestFunctions::GetDatapointValue, offset, count);

	ProtocolFormatter::encodeGetDatapointValue_Req(dataRequest, filter_);

	ServerFunction serverFunction(getConnector());
	DataResponse::Ptr dataResponse = serverFunction.rpc(dataRequest, timeout);
	setDataResponse(dataResponse);

	ProtocolFormatter::decodeGetDatapointValue_Res(dataResponse, values_);
}

const GetDatapointValue::Value& GetDatapointValue::at(int index) const
{
	return values_.at(index);
}

const GetDatapointValue::Value& GetDatapointValue::find(unsigned short id) const
{
	for (const auto& value : values_)
	{
		if (value.id == id)
		{
			return value;
		}
	}

	throw ClientException("Datapoint value not found");
}

const GetDatapointValue::Values& GetDatapointValue::getValues() const
{
	return values_;
}
