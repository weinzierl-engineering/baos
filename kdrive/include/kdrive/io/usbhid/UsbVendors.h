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

#ifndef __KDRIVE_IO_USBHID_USB_VENDORS_H__
#define __KDRIVE_IO_USBHID_USB_VENDORS_H__

#include "kdrive/io/usbhid/Config.h"
#include <cstddef>
#include <vector>
#include <string>

namespace kdrive
{
namespace io
{
namespace usb
{

/********************************
** UsbVendors
*********************************/

class wzfIOUsbHid_API UsbVendors
{
public:
	struct Device
	{
		Device();
		Device(unsigned int vendorId, unsigned int productId);

		unsigned int vendorId_;
		unsigned int productId_;
	};

	UsbVendors();
	~UsbVendors();

	/*!
		the single global usb vendor holder
	*/
	static UsbVendors& instance();

	/*!
		Clears all devices from list
	*/
	void clear();

	/*!
		returns the list of devices
	*/
	const std::vector<Device>& getDevices() const;

	/*!
		Append devices to the the list of devices
	*/
	void appendDevices(const std::vector<Device>& devices);

	/*!
		returns true if device is in the vendor list
	*/
	bool find(unsigned int vendorId, unsigned int productId) const;

private:
	std::vector<Device> devices_;
};

}
}
} // end namespace kdrive::io::usb

#endif // __KDRIVE_IO_USBHID_USB_VENDORS_H__
