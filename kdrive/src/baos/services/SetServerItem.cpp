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
#include "kdrive/baos/services/SetServerItem.h"
#include "kdrive/baos/protocols/Protocol.h"
#include "kdrive/baos/core/ServerFunction.h"
#include "kdrive/baos/core/API.h"

using namespace kdrive::connector;
using namespace kdrive::baos;

SetServerItem::SetServerItem(BaosConnector::Ptr connector)

	: ServiceRunner(connector)
{
}

SetServerItem::~SetServerItem()
{
}

void SetServerItem::rpc(unsigned short offset, const Item& item, unsigned long timeout)
{
	Items items;
	items.push_back(item);
	rpc(offset, items, timeout);
}

void SetServerItem::rpc(unsigned short offset, const Items& items, unsigned long timeout)
{
	const unsigned short count = static_cast<unsigned short>(items.size());

	DataRequest::Ptr dataRequest =
	    DataRequestFactory::create(getConnector(), RequestFunctions::SetServerItem, offset, count);

	ProtocolFormatter::encodeSetServerItem_Req(dataRequest, items);

	ServerFunction serverFunction(getConnector());
	DataResponse::Ptr dataResponse = serverFunction.rpc(dataRequest, timeout);
	setDataResponse(dataResponse);
}
