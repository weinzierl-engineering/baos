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
#include "kdrive/baos/services/GetTimer.h"
#include "kdrive/baos/core/ServerFunction.h"
#include "kdrive/baos/protocols/Protocol.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/Exception.h"

using namespace kdrive::connector;
using namespace kdrive::baos;

GetTimer::GetTimer(BaosConnector::Ptr connector)

	: ServiceRunner(connector)
{
}

GetTimer::~GetTimer()
{
}

void GetTimer::rpc(unsigned short offset, unsigned short count, unsigned long timeout)
{
	timers_.clear();

	ServiceRunner::rpc(RequestFunctions::GetTimer, offset, count, timeout);

	ProtocolFormatter::decodeGetTimer_Res(getDataResponse(), timers_);
}

const Timer& GetTimer::at(int index) const
{
	return timers_.at(index);
}

const Timer& GetTimer::find(unsigned short id) const
{
	for (const auto& value : timers_)
	{
		if (value.id == id)
		{
			return value;
		}
	}

	throw ClientException("Timer not found");
}

const GetTimer::Timers& GetTimer::getTimers() const
{
	return timers_;
}
