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
#include "kdrive/baos/services/GetDatapointDescription.h"
#include "kdrive/baos/protocols/Protocol.h"
#include "kdrive/baos/core/API.h"

using namespace kdrive::connector;
using namespace kdrive::baos;

GetDatapointDescription::GetDatapointDescription(BaosConnector::Ptr connector)

	: ServiceRunner(connector)
{
}

GetDatapointDescription::~GetDatapointDescription()
{
}

void GetDatapointDescription::rpc(unsigned short offset, unsigned short count, unsigned long timeout)
{
	descriptors_.clear();

	ServiceRunner::rpc(RequestFunctions::GetDatapointDescription, offset, count, timeout);

	ProtocolFormatter::decodeGetDatapointDescription_Res(getDataResponse(), descriptors_);
}

const GetDatapointDescription::Descriptor& GetDatapointDescription::at(int index) const
{
	return descriptors_.at(index);
}

const GetDatapointDescription::Descriptors& GetDatapointDescription::getDescriptors() const
{
	return descriptors_;
}

