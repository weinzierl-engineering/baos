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

#include <kdrive/baos/Baos.h>
#include <kdrive/utility/Logger.h>
#include <Poco/Exception.h>
#include <Poco/Format.h>

using namespace kdrive::baos;
using Poco::Exception;
using Poco::format;

CLASS_LOGGER("BaosUsbEnumerator")

/*!
	Enumerator

	This demo shows how to find all available USB BAOS devices
*/
int main(int argc, char* argv[])
{
	INIT_ROOT_CONSOLE_LOGGER();

	try
	{
		BaosUsbEnumerator enumerator;
		const BaosUsbEnumerator::Devices& devices = enumerator.getDevices();

		for (const auto& device : devices)
		{
			poco_information(LOGGER(), "============");
			poco_information(LOGGER(), "Found Device");
			poco_information(LOGGER(), "============");
			poco_information(LOGGER(), format("USB vendor id: %u", enumerator.getUsbVendorId(device)));
			poco_information(LOGGER(), format("USB product id: %u", enumerator.getUsbProductId(device)));
			poco_information(LOGGER(), format("USB manufacturer: %s", enumerator.getUsbManufacturerString(device)));
			poco_information(LOGGER(), format("USB product: %s", enumerator.getUsbProductString(device)));
			poco_information(LOGGER(), format("USB serial number: %s", enumerator.getUsbSerialNumberString(device)));
			poco_information(LOGGER(), "");
		}
	}
	catch (Exception& exception)
	{
		LOGGER().log(exception);
	}

	return EXIT_SUCCESS;
}
