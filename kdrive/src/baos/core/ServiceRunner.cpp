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
#include "kdrive/baos/core/ServiceRunner.h"
#include "kdrive/baos/core/ServerFunction.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/baos/protocols/Protocol.h"

using namespace kdrive::baos;
using namespace kdrive::connector;

ServiceRunner::~ServiceRunner()
{
}

unsigned short ServiceRunner::getOffset() const
{
	return dataResponse_ ? dataResponse_->getOffset() : 0;
}

unsigned short ServiceRunner::getCount() const
{
	return dataResponse_ ? dataResponse_->getCount() : 0;
}

const ServiceRunner::Buffer& ServiceRunner::getBuffer() const
{
	DataResponse::Ptr dataResponse = getDataResponse(true);
	return dataResponse->getBuffer();
}

ServiceRunner::ServiceRunner(BaosConnector::Ptr connector)

	: connector_(connector)
{
}

BaosConnector::Ptr ServiceRunner::getConnector(bool validate) const
{
	if (validate && !connector_)
	{
		throw ClientException("Invalid Connector");
	}

	return connector_;
}

void ServiceRunner::rpc(unsigned char subService,
                        unsigned short offset,
                        unsigned short count,
                        unsigned long timeout)
{

	DataRequest::Ptr dataRequest =
	    DataRequestFactory::create(getConnector(), subService, offset, count);

	ServerFunction serverFunction(getConnector());
	DataResponse::Ptr dataResponse = serverFunction.rpc(dataRequest, timeout);
	setDataResponse(dataResponse);
}

void ServiceRunner::setDataResponse(DataResponse::Ptr dataResponse)
{
	dataResponse_ = dataResponse;
}

DataResponse::Ptr ServiceRunner::getDataResponse(bool validate) const
{
	if (validate && !dataResponse_)
	{
		throw ClientException("Invalid Data Response");
	}

	return dataResponse_;
}
