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

#ifndef __KDRIVE_IO_USBHID_USB_DRIVER_H__
#define __KDRIVE_IO_USBHID_USB_DRIVER_H__

#include "kdrive/io/usbhid/Config.h"
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace kdrive
{
namespace io
{
namespace usb
{

/**************************************
** UsbDriverEnumerator
***************************************/

class UsbDriverImpl;
class UsbDeviceInfo;

class wzfIOUsbHid_API UsbDriver
{
public:
	/*!
		Creates a Usb UsbDriver without a open connection
		Open must be called manually
	*/
	UsbDriver();

	/*!
		Creates a USB connection for a specified port
		Port can be 0, 1, 2 etc
		The connection will be opened at this point
		If it can't be opened an exception will be thrown
	*/
	UsbDriver(unsigned int port);

	/*!
		Closes the connection and destroys the UsbDriver
	*/
	~UsbDriver();

	void open(unsigned int port);
	void close();
	bool isOpen() const;

	/*!
		sends data on the connection
	*/
	void send(const unsigned char* buffer, std::size_t bufferSize);

	/*!
		receives data from the connection
		returns 0 if no data was received
	*/
	std::size_t receive(unsigned char* buffer, std::size_t bufferSize);

	void setRxTimeout(unsigned int timeout);
	unsigned int getRxTimeout() const;

	unsigned int getVendorId() const;
	unsigned int getProductId() const;
	std::string getUsbManufacturerString() const;
	std::string getUsbProductString() const;
	std::string getUsbSerialNumberString() const;

private:
	std::shared_ptr<UsbDriverImpl> driverImpl_;
};

/**************************************
** UsbDriverEnumerator
***************************************/

class wzfIOUsbHid_API UsbDriverEnumerator
{
public:
	UsbDriverEnumerator();
	~UsbDriverEnumerator();
	static UsbDriverEnumerator& instance();

	typedef std::vector<UsbDeviceInfo> DeviceInfos;
	const DeviceInfos& getDeviceInfos() const;

	void enumerate();

private:
	bool match(unsigned int vendor, unsigned int product);

private:
	DeviceInfos deviceInfos_;
};

/**************************************
** UsbDeviceInfo
***************************************/

class wzfIOUsbHid_API UsbDeviceInfo
{
public:
	UsbDeviceInfo();
	UsbDeviceInfo(const std::string& path, unsigned int vendorId, unsigned int productId);
	~UsbDeviceInfo();

	const std::string& getPath() const;
	unsigned int getVendorId() const;
	unsigned int getProductId() const;

	void setManufacturer(const std::string& manufacturer);
	const std::string& getManufacturer() const;

	void setProduct(const std::string& product);
	const std::string& getProduct() const;

	void setSerialNumber(const std::string& serialNumber);
	const std::string& getSerialNumber() const;

private:
	std::string path_;
	unsigned int vendorId_;
	unsigned int productId_;
	std::string manufacturer_; /*!< optional, only for windows implemented */
	std::string product_; /*!< optional, only for windows implemented */
	std::string serialNumber_; /*!< optional, only for windows implemented */
};

}
}
} // end namespace kdrive::io::usb

#endif // __KDRIVE_IO_USBHID_USB_DRIVER_H__
