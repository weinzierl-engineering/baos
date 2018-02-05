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
#include "kdrive/baos/core/ServerFunction.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/baos/core/ErrorCodes.h"
#include "kdrive/connector/Semaphore.h"
#include <Poco/Timestamp.h>
#include <boost/assert.hpp>

using namespace kdrive::connector;
using namespace kdrive::baos;
using Poco::Timestamp;
using Poco::TimeoutException;

/*****************************
** ServerServerFunction
******************************/

ServerFunction::ServerFunction(BaosConnector::Ptr connector)

	: errorCode_(0),
	  connector_(connector)
{
	BOOST_ASSERT(connector_ && "Invalid Connector");
}

ServerFunction::~ServerFunction()
{
}

DataResponse::Ptr ServerFunction::rpc(DataRequest::Ptr request, unsigned long timeout)
{
	DataResponse::Ptr response;
	connector_->waitSem(timeout);

	try
	{
		ScopedQueueConnectorRxQueue queue(*connector_);
		send(request);
		response = receive(queue, timeout);
	}
	catch (...)
	{
		connector_->setSem();
		throw;
	}

	connector_->setSem();
	return response;
}

void ServerFunction::send(DataRequest::Ptr request)
{
	if (!connector_)
	{
		throw ClientException("Invalid Connector");
	}
	else if (!connector_->isConnected())
	{
		throw ClientException("Connection not available");
	}

	errorCode_ = 0;
	request_ = request;
	response_.reset();

	connector_->clearRx();
	connector_->send(request);
}

DataResponse::Ptr ServerFunction::receive(Connector& connector, unsigned long timeout)
{
	waitResponse(connector, timeout);
	validateResponse();
	return response_;
}

void ServerFunction::waitResponse(Connector& connector, unsigned long timeout)
{
	Packet::Ptr packet;
	Timestamp timestamp;
	Timestamp::TimeDiff timeoutMicroSeconds = timeout * 1000;
	bool elapsed = false;
	while (!elapsed)
	{
		Timestamp startTime;
		packet = connector.waitReceive(timeout);

		DataResponse::Ptr dataResponse =
		    std::dynamic_pointer_cast<DataResponse>(packet);

		if (dataResponse)
		{
			response_ = dataResponse;
			elapsed = true;
		}

		ErrorResponse::Ptr errorResponse =
		    std::dynamic_pointer_cast<ErrorResponse>(packet);

		if (errorResponse)
		{
			errorCode_ = errorResponse->getErrorCode();
			elapsed = true;
		}

		// ensure that the request matches the response.
		if (response_ && (response_->getSubService() != (request_->getSubService() | 0x80)))
		{
			elapsed = false;
		}

		if (!elapsed)
		{
			elapsed = timestamp.isElapsed(timeoutMicroSeconds);
		}

		if (!elapsed)
		{
			const unsigned long msElapsed = static_cast<unsigned long>(timestamp.elapsed()) / 1000;
			if (timeout < msElapsed)
			{
				elapsed = true;
			}
			else
			{
				timeout -= msElapsed;
			}
		}
	}
}

void ServerFunction::validateResponse()
{
	if (errorCode_)
	{
		throwBaosServerException(errorCode_);
	}
	else if (!response_)
	{
		throw TimeoutException();
	}
}
