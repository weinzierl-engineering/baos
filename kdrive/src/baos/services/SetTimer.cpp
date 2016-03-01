//
// Copyright (c) 2002-2016 WEINZIERL ENGINEERING GmbH
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
#include "kdrive/baos/services/SetTimer.h"
#include "kdrive/baos/core/ServerFunction.h"
#include "kdrive/baos/protocols/Protocol.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/Exception.h"

using namespace kdrive::connector;
using namespace kdrive::baos;

SetTimer::SetTimer(std::shared_ptr<BaosConnector> connector)

	: ServiceRunner(connector)
{
}

SetTimer::~SetTimer()
{
}

void SetTimer::rpc(unsigned short offset, const Timer& timer, unsigned long timeout)
{
	const std::vector<Timer> timers = { timer };
	rpc(offset, timers, timeout);
}

void SetTimer::rpc(unsigned short offset, const std::vector<Timer>& timers, unsigned long timeout)
{
	const unsigned short count = static_cast<unsigned short>(timers.size());

	DataRequest::Ptr dataRequest =
	    DataRequestFactory::create(getConnector(), RequestFunctions::SetTimer, offset, count);

	ProtocolFormatter::encodeSetTimer_Req(dataRequest, timers);

	ServerFunction serverFunction(getConnector());
	DataResponse::Ptr dataResponse = serverFunction.rpc(dataRequest, timeout);
	setDataResponse(dataResponse);
}

