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
#include "kdrive/baos/services/GetServerItem.h"
#include "kdrive/baos/protocols/Protocol.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/Exception.h"

using namespace kdrive::connector;
using namespace kdrive::baos;

GetServerItem::GetServerItem(BaosConnector::Ptr connector)

	: ServiceRunner(connector)
{
}

GetServerItem::~GetServerItem()
{
}

void GetServerItem::rpc(unsigned short offset, unsigned short count, unsigned long timeout)
{
	items_.clear();

	ServiceRunner::rpc(RequestFunctions::GetServerItem, offset, count, timeout);

	ProtocolFormatter::decodeGetServerItem_Res(getDataResponse(), items_);
}

/*!
    returns a single item
*/
const GetServerItem::Item& GetServerItem::at(int index) const
{
	return items_.at(index);
}

/*!
    returns a single item, matching item id
    throws an exception if not found
*/
const GetServerItem::Item& GetServerItem::find(unsigned short id) const
{
	for (const auto& item : items_)
	{
		if (item.id == id)
		{
			return item;
		}
	}

	throw ClientException("Item not found");
}

/*!
    returns all items
*/
const GetServerItem::Items& GetServerItem::getItems() const
{
	return items_;
}
