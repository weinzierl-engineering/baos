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

#ifndef __KDRIVE_BAOS_SERVER_ITEMS_H__
#define __KDRIVE_BAOS_SERVER_ITEMS_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/Forwards.h"
#include <memory>
#include <vector>

namespace kdrive
{
namespace baos
{

/*!
	\class BaosServerItems

	BaosServerItems is used to get/set the server item parameters
	from/on the remote device. It wraps the GetServerItem and SetServerItem services,
	which are byte based and provides the appropriate interpretation to
	convert the parameters to their corresponding values.
*/
class kdriveRPC_baos_API BaosServerItems
{
public:
	/*!
		Creates a BaosServerItems object with a specified connector.
		precondition: connector is not null
	*/
	BaosServerItems(std::shared_ptr<BaosConnector> connector);

	/*!
		Destroys the BaosServerItems
	*/
	~BaosServerItems();

	/*!
		Gets the hardware type.
		Can be used to identify the hardware type. Coding is manufacturer specific.
		It is mapped to property PID_HARDWARE_TYPE in the device object.
		Server item: hardware type, id 1
	*/
	std::vector<unsigned char> getHardwareType() const;

	/*!
		Gets the version of the ObjectServer hardware
		Coding Ex.: 0x10 = Version 1.0
		Server item: hardware version, id 2
	*/
	unsigned char getHardwareVersion() const;

	/*!
		Gets the version of ObjectServer firmware.
		Version of the ObjectServer firmware
		Coding Ex.: 0x10 = Version 1.0
		Server item: firmware version, id 3
	*/
	unsigned char getFirmwareVersion() const;

	/*!
		Gets the KNX manufacturer code of the device.
		Not modified by ETS.
		It is mapped to property PID_MANUFACTURER_ID in the device object.
		Server item: KNX manufacture code DEV, id 4
	*/
	unsigned int getManufactureCodeDevice() const;

	/*!
		Gets the KNX manufacturer code loaded by ETS.
		It is mapped to bytes 0 and 1 of property
		PID_APPLICATION_VER in the application object.
		Server item: KNX manufacture code APP, id 5
	*/
	unsigned int getManufactureCodeApp() const;

	/*!
		Gets the id of application loaded by ETS.
		It is mapped to bytes 2 and 3 of property
		PID_APPLICATION_VER in the application object.
		Server item: application id (ETS), id 6
	*/
	unsigned int getApplicationId() const;

	/*!
		Gets the version of application loaded by ETS.
		It is mapped to byte 4 of property PID_APPLICATION_VER
		in application object.
		Server item: application version (ETS), id 7
	*/
	unsigned char getApplicationVersion() const;

	/*!
		Gets KNX serial number of device.
		It is mapped to property PID_SERIAL_NUMBER in thie device object.
		Server item: serial number, id 8
	*/
	std::vector<unsigned char> getSerialNumber() const;

	/*!
		Gets the time since reset in ms.
		Server item: time since reset, id 9
	*/
	unsigned long getTimeSinceReset() const;

	/*!
		Returns true if the KNX bus is connected, otherwise false.
		Server item: bus connection state, id 10
	*/
	bool isBusConnected() const;

	/*!
		Gets the maximal buffer size.
		Server item: Maximal buffer size, id 11
	*/
	unsigned int getMaxBufferSize() const;

	/*!
		Gets the length of the description string.
		Server item: Length of description string, id 12
	*/
	unsigned int getLengthOfDescriptionString() const;

	/*!
		Possible values for server item Baudrate, id 13
	*/
	enum Baudrate
	{
	    Unknown = 0,
	    B19200,
	    B115200
	};

	/*!
		Sets the Baudrate
		Values: BaosServerItems::Unknown,
		BaosServerItems::BB19200, BaosServerItems::B115200
	*/
	void setBaudrate(unsigned char baudrate);

	/*!
		Gets the baudrate.
		Server item: Baudrate, id 13
		\see Baudrate
	*/
	unsigned char getBaudrate() const;

	/*!
		Sets the current buffer size.
		Server item: Current buffer size, id 14
	*/
	void setBufferSize(unsigned int bufferSize);

	/*!
		Gets the current buffer size.
		Server item: Current buffer size, id 14
		\see Baudrate
	*/
	unsigned int getBufferSize() const;

	/*!
		Possible values for server item ProgrammingMode, id 15
	*/
	enum ProgrammingMode
	{
	    NotActive = 0,
	    Active
	};

	/*!
		Sets the programming mode
		Values: ProgrammingMode::NotActive ProgrammingMode::Active
		Server item: Programming mode, id 15
	*/
	void setProgrammingMode(unsigned char programmingMode);

	/*!
		Gets the programming mode.
		Server item: Programming mode, id 15
		\see ProgrammingMode
	*/
	unsigned char getProgrammingMode() const;

	/*!
		Gets the version of the ObjectServer binary protocol
		\deprecated use getBinaryProtocolVersion instead
	*/
	unsigned char getProtocolVersion() const;

	/*!
		Gets the version of the ObjectServer binary protocol
		Server item: Protocol Version (Binary), id 16
	*/
	unsigned char getBinaryProtocolVersion() const;

	/*!
		Possible values for server item Indication Sending, id 17
	*/
	enum IndicationSetting
	{
	    IndicationSetting_NotActive = 0,
	    IndicationSetting_Active
	};

	/*!
		Sets the indication setting
		Values: IndicationSetting::IndicationSetting_NotActive IndicationSetting::IndicationSetting_Active
		Server item: Indication Sending, id 17
	*/
	void setIndicationSetting(unsigned char indicationSetting);

	/*!
		Gets the indication setting
		Server item: Indication Sending, id 17
	*/
	unsigned char getIndicationSetting() const;

	/*!
		Gets the version of the ObjectServer web services protocol
		Server item: Protocol Version (WebService), id 18
	*/
	unsigned char getWebServicesProtocolVersion() const;

	/*!
		Gets the version of the ObjectServer web services protocol
		Server item: Protocol Version (WebService), id 19
	*/
	unsigned char getRestServiceProtocolVersion() const;

	/*!
		Gets the KNX individual address
	*/
	unsigned short getIndividualAddress() const;

	/*!
		Gets the MAC address
	*/
	std::vector<unsigned char> getMacAddress() const;

	/*!
		Returns true if the KNXnet/IP Tunneling service is enabled, otherwise false
	*/
	bool isTunnellingEnabled() const;

	/*!
		Returns true if the BAOS Binay service is enabled, otherwise false
	*/
	bool isBaosBinaryEnabled() const;

	/*!
		Returns true if the BAOS Web service is enabled, otherwise false
	*/
	bool isBaosWebEnabled() const;

	/*!
		Returns true if the BAOS Rest service is enabled, otherwise false
	*/
	bool isBaosRestEnabled() const;

	/*!
		Returns true if the HTTP file service is enabled, otherwise false
	*/
	bool isHttpFileEnabled() const;

	/*!
		Returns true if the KNXnet/IP Search service is enabled, otherwise false
	*/
	bool isSearchRequestEnabled() const;

	/*!
		Returns true if the loaded application is a structed database, otherwise false
	*/
	bool isIsStructured() const;

	/*!
		Gets the maximum supported management clients
	*/
	unsigned char getMaxManagementClients() const;

	/*!
		Gets the current connected management clients
	*/
	unsigned char getConnectedManagementClients() const;

	/*!
		Gets the maximum supported tunneling clients
	*/
	unsigned char getMaxTunnellingClients() const;

	/*!
		Gets the current connected tunneling clients
	*/
	unsigned char getConnectedTunnellingClients() const;

	/*!
		Gets the maximum supported BAOS UDP clients
	*/
	unsigned char getMaxBaosUdpClients() const;

	/*!
		Gets the current connected  BAOS UDP clients
	*/
	unsigned char getConnectedBaosUdpClients() const;

	/*!
		Gets the maximum supported BAOS TCP clients
	*/
	unsigned char getMaxBaosTcpClients() const;

	/*!
		Gets the current connected  BAOS TCP clients
	*/
	unsigned char getConnectedBaosTcpClients() const;

	/*!
		Gets the device friendly name
	*/
	std::string getDeviceFriendlyName() const;

	/*!
		Gets the maximum supported datapoints
	*/
	unsigned short getMaxDatapoints() const;

	/*!
		Gets the current configured datapoints
	*/
	unsigned short getConfiguredDatapoints() const;

	/*!
		Gets the maximum supported parameter bytes
	*/
	unsigned short getMaxParameterBytes() const;

	/*!
		Gets the download counter
	*/
	unsigned short getDownloadCounter() const;

	/*!
		Gets the IP assigment methode
	*/
	unsigned char getIpAssignment() const;

	/*!
		Gets the IP address
	*/
	unsigned int getIpAddress() const;

	/*!
		Gets the subnet mask
	*/
	unsigned int getSubnetMask() const;

	/*!
		Gets the IP address of the default gateway
	*/
	unsigned int getDefaultGateway() const;

	/*!
		Gets the time since reset
	*/
	unsigned char getTimeSinceResetUnit() const;

	/*!
		Gets the system time
	*/
	std::vector<unsigned char> getSystemTime() const;

	/*!
		Gets the system timezone offset
	*/
	unsigned char getSystemTimezoneOffset() const;

	/*!
		Returns true if Menu is enabled, otherwise false
	*/
	bool isMenuEnabled() const;

private:
	std::vector<unsigned char> getItemData(unsigned short id) const;
	unsigned char getItemByte(unsigned short id) const;
	unsigned short getItemShort(unsigned short id) const;
	unsigned long getItemLong(unsigned short id) const;
	ServerItem getServerItem(unsigned short id) const;
	void setServerItem(unsigned short id, const std::vector<unsigned char>& data);

private:
	std::shared_ptr<BaosConnector> connector_;
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_SERVER_ITEMS_H__
