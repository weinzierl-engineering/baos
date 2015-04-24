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
#include "kdrive/baos/BaosServerItems.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/BaosConnector.h"
#include "kdrive/baos/services/GetServerItem.h"
#include "kdrive/baos/services/SetServerItem.h"
#include <boost/assert.hpp>

using namespace kdrive::connector;
using namespace kdrive::baos;

BaosServerItems::BaosServerItems(BaosConnector::Ptr connector)

	: connector_(connector)
{
	BOOST_ASSERT(connector && "Invalid Pointer");
}

BaosServerItems::~BaosServerItems()
{
}

std::vector<unsigned char> BaosServerItems::getHardwareType() const
{
	return getItemData(ServerItemProperties::HardwareType);
}

unsigned char BaosServerItems::getHardwareVersion() const
{
	return getItemByte(ServerItemProperties::HardwareVersion);
}

unsigned char BaosServerItems::getFirmwareVersion() const
{
	return getItemByte(ServerItemProperties::FirmwareVersion);
}

unsigned int BaosServerItems::getManufactureCodeDevice() const
{
	return getItemShort(ServerItemProperties::ManufactureCodeDevice);
}

unsigned int BaosServerItems::getManufactureCodeApp() const
{
	return getItemShort(ServerItemProperties::ManufactureCodeApp);
}

unsigned int BaosServerItems::getApplicationId() const
{
	return getItemShort(ServerItemProperties::ApplicationId);
}

unsigned char BaosServerItems::getApplicationVersion() const
{
	return getItemByte(ServerItemProperties::ApplicationVersion);
}

std::vector<unsigned char> BaosServerItems::getSerialNumber() const
{
	return getItemData(ServerItemProperties::SerialNumber);
}

unsigned long BaosServerItems::getTimeSinceReset() const
{
	return getItemLong(ServerItemProperties::TimeSinceReset);
}

bool BaosServerItems::isBusConnected() const
{
	return getItemByte(ServerItemProperties::BusConnected) ? true : false;
}

unsigned int BaosServerItems::getMaxBufferSize() const
{
	return getItemShort(ServerItemProperties::MaxBufferSize);
}

unsigned int BaosServerItems::getLengthOfDescriptionString() const
{
	return getItemShort(ServerItemProperties::LengthOfDescriptionString);
}

void BaosServerItems::setBaudrate(unsigned char baudrate)
{
	const std::vector<unsigned char> v(1, baudrate);
	setServerItem(ServerItemProperties::BaudrateItem, v);
}

unsigned char BaosServerItems::getBaudrate() const
{
	return getItemByte(ServerItemProperties::BaudrateItem);
}

void BaosServerItems::setBufferSize(unsigned int bufferSize)
{
	std::vector<unsigned char> v;
	v.push_back(bufferSize >> 8);
	v.push_back(bufferSize & 0xFF);
	setServerItem(ServerItemProperties::CurrentBufferSize, v);
}

unsigned int BaosServerItems::getBufferSize() const
{
	return getItemShort(ServerItemProperties::CurrentBufferSize);
}

void BaosServerItems::setProgrammingMode(unsigned char programmingMode)
{
	const std::vector<unsigned char> v(1, programmingMode);
	setServerItem(ServerItemProperties::ProgrammingModeItem, v);
}

unsigned char BaosServerItems::getProgrammingMode() const
{
	return getItemByte(ServerItemProperties::ProgrammingModeItem);
}

unsigned char BaosServerItems::getProtocolVersion() const
{
	return getBinaryProtocolVersion();
}

unsigned char BaosServerItems::getBinaryProtocolVersion() const
{
	return getItemByte(ServerItemProperties::BinaryProtocolVersion);
}

void BaosServerItems::setIndicationSetting(unsigned char indicationSetting)
{
	const std::vector<unsigned char> v(1, indicationSetting);
	setServerItem(ServerItemProperties::IndicationSetting, v);
}

unsigned char BaosServerItems::getIndicationSetting() const
{
	return getItemByte(ServerItemProperties::IndicationSetting);
}

unsigned char BaosServerItems::getWebServicesProtocolVersion() const
{
	return getItemByte(ServerItemProperties::WebServicesProtocolVersion);
}

/*!
    Returns the server item data buffer
*/
std::vector<unsigned char> BaosServerItems::getItemData(unsigned short id) const
{
	const GetServerItem::Item& item = getServerItem(id);
	return item.data;
}

/*!
    Returns the first byte of the server item data buffer
*/
unsigned char BaosServerItems::getItemByte(unsigned short id) const
{
	const GetServerItem::Item& item = getServerItem(id);
	return item.data.at(0);
}

/*!
    Returns the first two bytes of the server item as an unsigned int
*/
unsigned int BaosServerItems::getItemShort(unsigned short id) const
{
	const GetServerItem::Item& item = getServerItem(id);
	return item.data.at(0) << 8 | item.data.at(1);
}

/*!
    Returns the first four bytes of the server item as an unsigned long
*/
unsigned long BaosServerItems::getItemLong(unsigned short id) const
{
	unsigned long value = 0;
	const GetServerItem::Item& item = getServerItem(id);
	value |= item.data.at(0) << 24;
	value |= item.data.at(1) << 16;
	value |= item.data.at(2) << 8;
	value |= item.data.at(3);
	return value;
}

/*!
    Sends a get request to the baos remote device
    And waits for the server item response
    Throws an exception on error
*/
ServerItem BaosServerItems::getServerItem(unsigned short id) const
{
	GetServerItem getServerItem(connector_);
	getServerItem.rpc(id, 1);
	if (!getServerItem.getCount() == 1)
	{
		throw ClientException("Failed for get server item");
	}
	return getServerItem.at(0);
}

/*!
    Sends a set request to the baos remote device
    And waits for the server item response
    Throws an exception on error
*/
void BaosServerItems::setServerItem(unsigned short id, const std::vector<unsigned char>& data)
{
	SetServerItem::Item item;
	item.id = id;
	item.length = static_cast<unsigned char>(data.size());
	item.data = data;

	SetServerItem setServerItem(connector_);
	setServerItem.rpc(id, item);
}
