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
#include "kdrive/baos/services/SetDatapointHistoryCommand.h"
#include "kdrive/baos/protocols/Protocol.h"
#include "kdrive/baos/core/ServerFunction.h"
#include "kdrive/baos/core/API.h"

using namespace kdrive::connector;
using namespace kdrive::baos;

SetDatapointHistoryCommand::SetDatapointHistoryCommand(BaosConnector::Ptr connector)

	: ServiceRunner(connector)
{
}

SetDatapointHistoryCommand::~SetDatapointHistoryCommand()
{
}

void SetDatapointHistoryCommand::rpc(unsigned short offset, unsigned short count, unsigned char command, unsigned long timeout)
{
	DataRequest::Ptr dataRequest =
	    DataRequestFactory::create(getConnector(), RequestFunctions::GetDatapointHistoryCommand, offset, count);

	ProtocolFormatter::encodeSetDatapointHistoryCommand_Req(dataRequest, command);

	ServerFunction serverFunction(getConnector());
	DataResponse::Ptr dataResponse = serverFunction.rpc(dataRequest, timeout);
	setDataResponse(dataResponse);
}
