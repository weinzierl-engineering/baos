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

unsigned char BaosServerItems::getRestServiceProtocolVersion() const
{
	return getItemByte(ServerItemProperties::RestServiceProtocolVersion);
}

unsigned short BaosServerItems::getIndividualAddress() const
{
	return getItemShort(ServerItemProperties::IndividualAddress);
}

std::vector<unsigned char> BaosServerItems::getMacAddress() const
{
	return getItemData(ServerItemProperties::MacAddress);
}

bool BaosServerItems::isTunnellingEnabled() const
{
	return getItemByte(ServerItemProperties::TunnellingEnabled) ? true : false;
}

bool BaosServerItems::isBaosBinaryEnabled() const
{
	return getItemByte(ServerItemProperties::BaosBinaryEnabled) ? true : false;
}

bool BaosServerItems::isBaosWebEnabled() const
{
	return getItemByte(ServerItemProperties::BaosWebEnabled) ? true : false;
}

bool BaosServerItems::isBaosRestEnabled() const
{
	return getItemByte(ServerItemProperties::BaosRestEnabled) ? true : false;
}

bool BaosServerItems::isHttpFileEnabled() const
{
	return getItemByte(ServerItemProperties::HttpFileEnabled) ? true : false;
}

bool BaosServerItems::isSearchRequestEnabled() const
{
	return getItemByte(ServerItemProperties::SearchRequestEnabled) ? true : false;
}

bool BaosServerItems::isIsStructured() const
{
	return getItemByte(ServerItemProperties::IsStructured) ? true : false;
}

unsigned char BaosServerItems::getMaxManagementClients() const
{
	return getItemByte(ServerItemProperties::MaxManagementClients);
}

unsigned char BaosServerItems::getConnectedManagementClients() const
{
	return getItemByte(ServerItemProperties::ConnectedManagementClients);
}

unsigned char BaosServerItems::getMaxTunnellingClients() const
{
	return getItemByte(ServerItemProperties::MaxTunnellingClients);
}

unsigned char BaosServerItems::getConnectedTunnellingClients() const
{
	return getItemByte(ServerItemProperties::ConnectedTunnellingClients);
}

unsigned char BaosServerItems::getMaxBaosUdpClients() const
{
	return getItemByte(ServerItemProperties::MaxBaosUdpClients);
}

unsigned char BaosServerItems::getConnectedBaosUdpClients() const
{
	return getItemByte(ServerItemProperties::ConnectedBaosUdpClients);
}

unsigned char BaosServerItems::getMaxBaosTcpClients() const
{
	return getItemByte(ServerItemProperties::MaxBaosTcpClients);
}

unsigned char BaosServerItems::getConnectedBaosTcpClients() const
{
	return getItemByte(ServerItemProperties::ConnectedBaosTcpClients);
}

std::string BaosServerItems::getDeviceFriendlyName() const
{
	const std::vector<unsigned char> data = getItemData(ServerItemProperties::DeviceFriendlyName);
	const std::string deviceName = std::string(data.begin(), data.end());
	return deviceName;
}

unsigned short BaosServerItems::getMaxDatapoints() const
{
	return getItemShort(ServerItemProperties::MaxDatapoints);
}

unsigned short BaosServerItems::getConfiguredDatapoints() const
{
	return getItemShort(ServerItemProperties::ConfiguredDatapoints);
}

unsigned short BaosServerItems::getMaxParameterBytes() const
{
	return getItemShort(ServerItemProperties::MaxParameterBytes);
}

unsigned short BaosServerItems::getDownloadCounter() const
{
	return getItemShort(ServerItemProperties::DownloadCounter);
}

unsigned char BaosServerItems::getIpAssignment() const
{
	return getItemByte(ServerItemProperties::IPAssignment);
}

unsigned int BaosServerItems::getIpAddress() const
{
	return getItemLong(ServerItemProperties::IPAddress);
}

unsigned int BaosServerItems::getSubnetMask() const
{
	return getItemLong(ServerItemProperties::SubnetMask);
}

unsigned int BaosServerItems::getDefaultGateway() const
{
	return getItemLong(ServerItemProperties::DefaultGateway);
}

unsigned char BaosServerItems::getTimeSinceResetUnit() const
{
	return getItemByte(ServerItemProperties::TimeSinceResetUnit);
}

std::vector<unsigned char> BaosServerItems::getSystemTime() const
{
	return getItemData(ServerItemProperties::SystemTime);
}

unsigned char BaosServerItems::getSystemTimezoneOffset() const
{
	return getItemByte(ServerItemProperties::SystemTimezoneOffset);
}

bool BaosServerItems::isMenuEnabled() const
{
	return getItemByte(ServerItemProperties::MenuEnabled) ? true : false;
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
unsigned short BaosServerItems::getItemShort(unsigned short id) const
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
	if (getServerItem.getCount() != 1)
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
