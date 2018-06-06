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
#include "kdrive/io/usbhid/UsbVendors.h"
#include <Poco/SingletonHolder.h>
#include <Poco/Exception.h>

using namespace kdrive::io::usb;
using Poco::Exception;
using Poco::SingletonHolder;

/********************************
** UsbVendors::Device
*********************************/

UsbVendors::Device::Device()

	: vendorId_(0),
	  productId_(0)
{
}

UsbVendors::Device::Device(unsigned int vendorId, unsigned int productId)

	: vendorId_(vendorId),
	  productId_(productId)
{
}

/********************************
** UsbVendors
*********************************/

UsbVendors::UsbVendors()
{
}

UsbVendors::~UsbVendors()
{
}

UsbVendors& UsbVendors::instance()
{
	static SingletonHolder<UsbVendors> singletonHolder;
	return *singletonHolder.get();
}

void UsbVendors::clear()
{
	devices_.clear();
}

const std::vector<UsbVendors::Device>& UsbVendors::getDevices() const
{
	return devices_;
}

void UsbVendors::appendDevices(const std::vector<Device>& devices)
{
	devices_.reserve(devices_.size() + devices.size());
	devices_.insert(devices_.end(), devices.begin(), devices.end());
}

bool UsbVendors::find(unsigned int vendorId, unsigned int productId) const
{
	for (const UsbVendors::Device& device : devices_)
	{
		if ((device.vendorId_ == vendorId) && (device.productId_ == productId))
		{
			return true;
		}
	}

	return false;
}
