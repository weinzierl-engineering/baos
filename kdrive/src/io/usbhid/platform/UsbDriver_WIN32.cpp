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

#include "pch/kdrive_pch.h"
#include "kdrive/utility/Logger.h"
#include "kdrive/io/usbhid/hidapi.h"
#include <Poco/Format.h>
#include <Poco/Exception.h>
#include <Poco/SingletonHolder.h>
#include <Poco/UnicodeConverter.h>

using namespace kdrive::io::usb;
using Poco::SingletonHolder;
using Poco::UnicodeConverter;
using Poco::IOException;

CLASS_LOGGER("kdrive.io.usb.UsbDriverImpl_WIN32")

/************************************
** Anonymous namespace
*************************************/

namespace
{

struct UsbHidRAII
{
	UsbHidRAII()
	{
		hid_init();
	}

	~UsbHidRAII()
	{
		hid_exit();
	}

	static UsbHidRAII& instance()
	{
		static SingletonHolder<UsbHidRAII> instance;
		return *instance.get();
	}
};

const UsbDeviceInfo& getDeviceInfo(unsigned int port)
{
	UsbDriverEnumerator& driverEnumerator = UsbDriverEnumerator::instance();
	const UsbDriverEnumerator::DeviceInfos& deviceInfos = driverEnumerator.getDeviceInfos();
	return deviceInfos.at(port);
}

std::string getDevicePath(unsigned int port)
{
	UsbDriverEnumerator& driverEnumerator = UsbDriverEnumerator::instance();
	const UsbDriverEnumerator::DeviceInfos& deviceInfos = driverEnumerator.getDeviceInfos();
	return port < deviceInfos.size() ? deviceInfos.at(port).getPath() : "";
}

}

/************************************
** UsbDriverImpl
*************************************/

namespace kdrive
{
namespace io
{
namespace usb
{

class UsbDriverImpl
{
public:
	UsbDriverImpl()

		: port_(0),
		  rxTimeout_(200),
		  handle_(0),
		  vendorId_(0),
		  productId_(0)
	{
		UsbHidRAII::instance();
	}

	UsbDriverImpl(unsigned int port)

		: port_(port),
		  rxTimeout_(200),
		  handle_(0),
		  vendorId_(0),
		  productId_(0)
	{
		UsbHidRAII::instance();
		open(port_);
	}

	~UsbDriverImpl()
	{
	}

	void open(unsigned int port)
	{
		const std::string devicePath = getDevicePath(port);

		if (devicePath.empty())
		{
			throw IOException(Poco::format("Failed to open usb port (index: %u).\n"
			                                       "USB Interface not exist or already opened", port));
		}

		handle_ = hid_open_path(devicePath.c_str());
		if (!handle_)
		{
			throw IOException(Poco::format("Failed to open usb port (index: %u).\n"
			                                       "USB Interface not exist or already opened", port));
		}

		port_ = port;

		const UsbDeviceInfo& deviceInfo = getDeviceInfo(port);
		vendorId_ = deviceInfo.getVendorId();
		productId_ = deviceInfo.getProductId();
		manufacturer_ = deviceInfo.getManufacturer();
		product_ = deviceInfo.getProduct();
		serialNumber_ = deviceInfo.getSerialNumber();
	}

	void close()
	{
		if (handle_)
		{
			hid_close(handle_);
			handle_ = 0;
		}
	}

	bool isOpen() const
	{
		return handle_ ? true : false;
	}

	void send(const unsigned char* buffer, std::size_t bufferSize)
	{
		const int size = hid_write(handle_, buffer, bufferSize);
		if (size < 0)
		{
			if (size == -1)
			{
				const int errorCode = hid_last_error_code(handle_);
				if (errorCode == ERROR_DEVICE_NOT_CONNECTED)
				{
					throw IOException("Interface not connected");
				}
				else
				{
					throw IOException(Poco::format("USB driver: Send Error (WriteFile error %d)", errorCode));
				}
			}
			else if (size == -2)
			{
				throw IOException("USB driver: Send Error (WaitForSingleObject Timeout)");
			}
			else if (size == -3)
			{
				const int errorCode = hid_last_error_code(handle_);
				throw IOException(Poco::format("USB driver: Send Error (GetOverlappedResult error %d)", errorCode));
			}

			throw IOException("USB driver: Send Error");
		}
	}

	std::size_t receive(unsigned char* buffer, std::size_t bufferSize)
	{
		const int size = hid_read_timeout(handle_, buffer, bufferSize, rxTimeout_);
		if (size < 0)
		{
			const int errorCode = hid_last_error_code(handle_);
			if (errorCode == ERROR_DEVICE_NOT_CONNECTED)
			{
				throw IOException("Interface not connected");
			}
			else
			{
				throw IOException(("USB driver: Receive Error (error %d)", errorCode));
			}
		}
		return size;
	}

	void setRxTimeout(unsigned int timeout)
	{
		rxTimeout_ = timeout;
	}

	unsigned int getRxTimeout() const
	{
		return rxTimeout_;
	}

	unsigned int getVendorId() const
	{
		return vendorId_;
	}

	unsigned int getProductId() const
	{
		return productId_;
	}

	std::string getUsbManufacturerString() const
	{
		return manufacturer_;
	}

	std::string getUsbProductString() const
	{
		return product_;
	}

	std::string getUsbSerialNumberString() const
	{
		return serialNumber_;
	}

private:
	unsigned int port_;
	unsigned int rxTimeout_;
	hid_device* handle_;
	unsigned int vendorId_;
	unsigned int productId_;
	std::string manufacturer_;
	std::string product_;
	std::string serialNumber_;
};

/**************************************
** UsbDriverEnumerator
***************************************/

/*!
	Workaround for some usb interfaces (e.g. 310 or rf)
	which has not impl. a usb serial number but returns a very short string (0x0409):
	We ignore very short strings

	NOTE: We check the string ptr before because UnicodeConverter::convert not worked
	with "null ptr" / string with length 0!
*/
void UsbDriverEnumerator::enumerate()
{
	UsbHidRAII::instance();

	deviceInfos_.clear();

	struct hid_device_info* devs = hid_enumerate(0x0, 0x0);
	struct hid_device_info* iter = devs;

	while (iter)
	{
		const unsigned int vendor = iter->vendor_id;
		const unsigned int product = iter->product_id;

		if (match(vendor, product))
		{
			UsbDeviceInfo device(iter->path, vendor, product);
			if (iter->manufacturer_string)
			{
				std::string manufacturer;
				UnicodeConverter::convert(iter->manufacturer_string, manufacturer);
				device.setManufacturer(manufacturer);
			}
			if (iter->product_string)
			{
				std::string product;
				UnicodeConverter::convert(iter->product_string, product);
				device.setProduct(product);
			}
			if (iter->serial_number)
			{
				std::string serialNumber;
				UnicodeConverter::convert(iter->serial_number, serialNumber);
				if (serialNumber.size() > 3)
				{
					device.setSerialNumber(serialNumber);
				}
			}
			deviceInfos_.push_back(device);
		}
		iter = iter->next;
	}
	hid_free_enumeration(devs);
}

}
}
} // end namespace kdrive::io::usb
