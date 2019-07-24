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
#include "kdrive/io/usbhid/UsbDriver.h"
#include "kdrive/io/usbhid/UsbVendors.h"
#include "kdrive/utility/Logger.h"
#include "kdrive/utility/LoggerFormatter.h"
#include <Poco/SingletonHolder.h>
#include <Poco/Exception.h>
#include <Poco/NumberFormatter.h>
#include <Poco/Platform.h>
#include <Poco/Format.h>
#include <Poco/Message.h>
#include <Poco/String.h>

#if defined(POCO_OS_FAMILY_WINDOWS)
#include "platform/UsbDriver_WIN32.cpp"
#elif defined(POCO_OS_FAMILY_UNIX)
#include "platform/UsbDriver_UNIX.cpp"
#else
#error "USB Platform not supported"
#endif

using namespace kdrive::io::usb;
using namespace kdrive::utility;
using Poco::Exception;
using Poco::FastMutex;
using Poco::NumberFormatter;
using Poco::ScopedLock;
using Poco::SingletonHolder;
using Poco::format;
using Poco::toUpperInPlace;
using Poco::Message;

/***********************************
** UsbDriver
************************************/

UsbDriver::UsbDriver()

	: driverImpl_(std::make_shared<UsbDriverImpl>())
{
}

UsbDriver::UsbDriver(unsigned int port)

	: driverImpl_(std::make_shared<UsbDriverImpl>(port))
{
}

UsbDriver::~UsbDriver()
{
	try
	{
		close();
	}
	catch (...)
	{
	}
}

void UsbDriver::open(unsigned int port)
{
	if (!driverImpl_->isOpen())
	{
		driverImpl_->open(port);
	}
}

void UsbDriver::close()
{
	if (driverImpl_->isOpen())
	{
		driverImpl_->close();
	}
}

bool UsbDriver::isOpen() const
{
	return driverImpl_->isOpen();
}

void UsbDriver::send(const unsigned char* buffer, std::size_t bufferSize)
{
	if (isOpen())
	{
		if (LOGGER().debug())
		{
			LOGGER().dump(format("usb tx: %z byte(s)", bufferSize), buffer, bufferSize, Poco::Message::PRIO_DEBUG);
		}

		driverImpl_->send(buffer, bufferSize);
	}
	else
	{
		throw Exception("Port not open");
	}
}

std::size_t UsbDriver::receive(unsigned char* buffer, std::size_t bufferSize)
{
	const std::size_t size = isOpen() ? driverImpl_->receive(buffer, bufferSize) : 0;

	if ((size > 0) && (LOGGER().getLevel() >= Message::PRIO_DEBUG))
	{
		LOGGER().dump(format("usb rx: %z byte(s)", size), buffer, size, Poco::Message::PRIO_DEBUG);
	}

	return size;
}

void UsbDriver::setRxTimeout(unsigned int timeout)
{
	return driverImpl_->setRxTimeout(timeout);
}

unsigned int UsbDriver::getRxTimeout() const
{
	return driverImpl_->getRxTimeout();
}

unsigned int UsbDriver::getVendorId() const
{
	return driverImpl_->getVendorId();
}

unsigned int UsbDriver::getProductId() const
{
	return driverImpl_->getProductId();
}

std::string UsbDriver::getUsbManufacturerString() const
{
	return driverImpl_->getUsbManufacturerString();
}

std::string UsbDriver::getUsbProductString() const
{
	return driverImpl_->getUsbProductString();
}

std::string UsbDriver::getUsbSerialNumberString() const
{
	return driverImpl_->getUsbSerialNumberString();
}

/***********************************
** UsbDriverEnumerator
************************************/

UsbDriverEnumerator::UsbDriverEnumerator()
{
	enumerate();
}

UsbDriverEnumerator::~UsbDriverEnumerator()
{
}

UsbDriverEnumerator& UsbDriverEnumerator::instance()
{
	static SingletonHolder<UsbDriverEnumerator> singletonHolder;
	return *singletonHolder.get();
}

const UsbDriverEnumerator::DeviceInfos& UsbDriverEnumerator::getDeviceInfos() const
{
	return deviceInfos_;
}

bool UsbDriverEnumerator::match(unsigned int vendor, unsigned int product)
{
	UsbVendors& vendors = UsbVendors::instance();
	return vendors.find(vendor, product);
}

/**************************************
** UsbDeviceInfo
***************************************/

UsbDeviceInfo::UsbDeviceInfo()

	: vendorId_(0),
	  productId_(0)
{
}

UsbDeviceInfo::UsbDeviceInfo(const std::string& path, unsigned int vendorId, unsigned int productId)

	: path_(path),
	  vendorId_(vendorId),
	  productId_(productId)
{
}

UsbDeviceInfo::~UsbDeviceInfo()
{
}

const std::string& UsbDeviceInfo::getPath() const
{
	return path_;
}

unsigned int UsbDeviceInfo::getVendorId() const
{
	return vendorId_;
}

unsigned int UsbDeviceInfo::getProductId() const
{
	return productId_;
}

void UsbDeviceInfo::setManufacturer(const std::string& manufacturer)
{
	manufacturer_ = manufacturer;
}

const std::string& UsbDeviceInfo::getManufacturer() const
{
	return manufacturer_;
}

void UsbDeviceInfo::setProduct(const std::string& product)
{
	product_ = product;
}

const std::string& UsbDeviceInfo::getProduct() const
{
	return product_;
}

void UsbDeviceInfo::setSerialNumber(const std::string& serialNumber)
{
	serialNumber_ = serialNumber;
}

const std::string& UsbDeviceInfo::getSerialNumber() const
{
	return serialNumber_;
}
