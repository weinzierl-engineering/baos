//
// Copyright (c) 2002-2009 WEINZIERL ENGINEERING GmbH
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
#include "kdrive/utility/LoggerFormatter.h"
#include <Poco/NumberFormatter.h>
#include <Poco/Exception.h>
#include <Poco/Timestamp.h>
#include <Poco/Timespan.h>
#include <Poco/Format.h>
#include <Poco/Logger.h>
#include <Poco/Glob.h>
#include <asm/types.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/hiddev.h>
#include <set>
#include <string>
#include <tuple>

using namespace kdrive::io::usb;
using kdrive::utility::LoggerFormatter;
using Poco::NumberFormatter;
using Poco::Exception;
using Poco::Timestamp;
using Poco::Timespan;
using Poco::IOException;
using Poco::Message;
using Poco::format;
using Poco::Glob;

/*!
  using linux device driver: hiddev
  see http://www.kernel.org/doc/Documentation/usb/hiddev.txt
*/

CLASS_LOGGER("kdrive.io.usb.UsbDriverImpl_UNIX")

/************************************
** Anonymous namespace
*************************************/

namespace
{

/************************************
** Private Functions
*************************************/

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

} // end anonymous namespace

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
		  fd_(invalidFileDescriptor_),
		  usageCode_(0),
		  vendorId_(0),
		  productId_(0)
	{
	}

	UsbDriverImpl(unsigned int port)

		: port_(port),
		  rxTimeout_(200),
		  fd_(invalidFileDescriptor_),
		  usageCode_(0),
		  vendorId_(0),
		  productId_(0)
	{
		open(port_);
	}

	~UsbDriverImpl()
	{
		if (isOpen())
		{
			close();
		}
	}

	void open(unsigned int port)
	{
		const std::string devicePath = getDevicePath(port);

		if (devicePath.empty())
		{
			throw IOException("Failed to open port", port);
		}

		open(devicePath);
		port_ = port;

		const UsbDeviceInfo& deviceInfo = getDeviceInfo(port);
		vendorId_ = deviceInfo.getVendorId();
		productId_ = deviceInfo.getProductId();
	}

	/*!
		\note the port_ is unknown!
	*/
	void open(const std::string& devicePath)
	{
		openImpl(devicePath);

		hiddev_devinfo device_info;
		readDeviceInfo(device_info);
		vendorId_ = device_info.vendor;
		productId_ = device_info.product;
	}

	void close()
	{
		::close(fd_);
		fd_ = invalidFileDescriptor_;
		port_ = 0;
	}

	bool isOpen() const
	{
		return fd_ > 0 ? true : false;
	}

	/*!
		We set the report id, followed by the 63 data bytes
		and then the report info
	 */
	void send(const unsigned char* buffer, std::size_t bufferSize)
	{
		const void* pV = static_cast<const void*>(buffer);
		const signed char* ptr = static_cast<const signed char*>(pV);

		struct hiddev_usage_ref_multi uref;
		uref.uref.report_type = HID_REPORT_TYPE_OUTPUT;
		uref.uref.report_id = *ptr++;
		uref.uref.field_index = 0;
		uref.uref.usage_index = 0;
		uref.uref.usage_code = usageCode_;
		uref.num_values = bufferSize - 1;

		const int size = static_cast<int>(bufferSize - 1);
		for (int index = 0; index < size; index++)
		{
			uref.values[index] = (__s32) *ptr++;
		}

		if (ioctl(fd_, HIDIOCSUSAGES, &uref) != 0)
		{
			poco_error(LOGGER(), "Send failed: HIDIOCSUSAGES");
			throw IOException("IO Error, unable to set USB Report data");
		}

		struct hiddev_report_info rinfo;
		rinfo.report_type = HID_REPORT_TYPE_OUTPUT;
		rinfo.report_id = 0x01;
		rinfo.num_fields = 1;
		if (ioctl( fd_, HIDIOCSREPORT, &rinfo ) != 0)
		{
			poco_error(LOGGER(), "Send failed: HIDIOCSREPORT");
			throw IOException("IO Error, unable to set USB Report");
		}
	}

	std::size_t receive(unsigned char* buffer, std::size_t bufferSize)
	{
		if (bufferSize < MaxEvents)
		{
			poco_error_f1(LOGGER(), "USB buffer size must be at least 64 bytes, received %d", static_cast<int>(bufferSize));
			throw IOException("Receive buffer too small for USB report");
		}

		int expected = MaxEvents - 1;
		int iter = 0;
		int rc = 0;
		buffer[iter++] = 0x01; // auto-set the report id. we could/should read this from the driver

		while (expected > 0)
		{
			rc = poll();

			if (!rc)
			{
				return 0;
			}
			else if (rc < 0)
			{
				poco_error_f1(LOGGER(), "Poll (select) failed with errno %d", errno);
				throw IOException("Receive Error");
			}

			const int readLength = ::read(fd_, eventBuffer_, sizeof(struct hiddev_event) * expected);

			if (readLength > 0)
			{
				const int events = readLength / sizeof(struct hiddev_event);

				for (int index = 0; index < events; ++index)
				{
					struct hiddev_event* e = &eventBuffer_[index];
					buffer[iter++] = e->value;
					--expected;
				}
			}
			else if (readLength < 0)
			{
				poco_error_f1(LOGGER(), "Read failed with errno %d", errno);
				poco_error_f3(LOGGER(), "Read length %d, iter %d, expected %d", readLength, iter, expected);
				throw IOException("Can not read from device", errno);
			}
		}

		return MaxEvents;
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
		// not implemented
		return "";
	}

	std::string getUsbProductString() const
	{
		// not implemented
		return "";
	}

	std::string getUsbSerialNumberString() const
	{
		// not implemented
		return "";
	}

private:
	void openImpl(const std::string& devicePath)
	{
		fd_ = ::open(devicePath.c_str(), O_RDWR | O_NONBLOCK);

		if (fd_ > 0)
		{
			usageCode_ = getUsageCode();
		}
		else
		{
			fd_ = invalidFileDescriptor_;
			throw IOException("Unable to open device");
		}
	}

	void readDeviceInfo(hiddev_devinfo& device_info)
	{
		if (ioctl(fd_, HIDIOCGDEVINFO, &device_info) < 0)
		{
			throw IOException("Unable to get device information");
		}
	}

	int getUsageCode()
	{
		struct hiddev_usage_ref uref;
		int rc;

		uref.report_type = HID_REPORT_TYPE_OUTPUT;
		uref.report_id = 0x01;
		uref.field_index = 0;
		uref.usage_index = 0;
		rc = ioctl( fd_, HIDIOCGUCODE, &uref );
		return rc < 0 ? 0 : uref.usage_code;
	}

	int poll()
	{
		fd_set fdRead;
		FD_ZERO(&fdRead);
		FD_SET(fd_, &fdRead);

		Timespan remainingTime(rxTimeout_ * 1000);
		int rc = 0;
		do
		{
			struct timeval tv;
			tv.tv_sec  = (long) remainingTime.totalSeconds();
			tv.tv_usec = (long) remainingTime.useconds();
			Timestamp start;
			rc = ::select(fd_ + 1, &fdRead, NULL, NULL, &tv);

			if (rc < 0 && errno == EINTR)
			{
				Timestamp end;
				Timespan waited = end - start;
				if (waited < remainingTime)
				{
					remainingTime -= waited;
				}
				else
				{
					remainingTime = 0;
				}
			}
		}
		while (rc < 0 && errno == EINTR);
		return rc;
	}

private:
	static const int invalidFileDescriptor_ = -1;
	static const unsigned int MaxEvents = 64;
	struct hiddev_event eventBuffer_[MaxEvents];
	unsigned int port_;
	unsigned int rxTimeout_;
	int fd_;
	int usageCode_;
	unsigned int vendorId_;
	unsigned int productId_;
};

/**************************************
** UsbDriverEnumerator
***************************************/

void UsbDriverEnumerator::enumerate()
{
	deviceInfos_.clear();

	std::set<std::string> files;
	Glob::glob("/dev/usb/hiddev*", files);

	for (const std::string& devicePath : files)
	{
		try
		{
			UsbDriverImpl d;
			d.open(devicePath);
			const unsigned int vendor = d.getVendorId();
			const unsigned int product = d.getProductId();
			if (match(vendor, product))
			{
				UsbDeviceInfo device(devicePath, vendor, product);
				deviceInfos_.push_back(device);
			}
			d.close();
		}
		catch (...)
		{
		}
	}
}

}
}
} // end namespace kdrive::io::usb
