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

#include <kdrive/baos/Baos.h>
#include <kdrive/connector/CallbackThread.h>
#include <kdrive/utility/Logger.h>
#include <Poco/Exception.h>
#include <Poco/Format.h>

using namespace kdrive::baos;
using namespace kdrive::connector;
using Poco::Exception;
using Poco::format;

/*!
	Datapoint Description

	This demo shows how to:

		create a connection with the BAOS device
		reads the datapoint descriptions

	You will have to change the IP Address or device name to match your device.
	You can find the device name and ip address by running the Enumerator sample.
*/

CLASS_LOGGER("DatapointDescription")

int main(int argc, char* argv[])
{
	// configure the logging channel
	INIT_ROOT_CONSOLE_LOGGER();

	try
	{
		// Find all available baos devices
		// and search for the "Baos-Sample" device
		BaosEnumerator baosEnumerator;
		const BaosEnumerator::Device device = baosEnumerator.find("Baos-Sample");

		// create a TPC/IP connection with the remote BAOS device
		ScopedBaosConnection connection(device);
		BaosConnector::Ptr connector = connection.getConnector();

		// reads all configured (enabled) datapoint descriptions from the device
		BaosDatapointDescriptions baosDatapointDescriptions(connector);
		baosDatapointDescriptions.readFromDevice();

		// trace the descriptions
		const BaosDatapointDescriptions::Descriptions descriptions = baosDatapointDescriptions.getDescriptions();

		const unsigned int count = descriptions.size();
		poco_information(LOGGER(), format("%u datapoints found", count));

		for (const auto& item : descriptions)
		{
			poco_information(LOGGER(), "");
			const BaosDatapointDescription& desc = item.second;
			poco_information(LOGGER(), format("Datapoint id: %d", static_cast<int>(desc.getId())));
			poco_information(LOGGER(), format("Datapoint type: %d", static_cast<int>(desc.getDatapointType())));

			// reads the datapoint string
			BaosDatapoint datapoint(connector, desc.getId());
			poco_information(LOGGER(), format("Description string: %s", datapoint.getDescriptionString()));
		}
	}
	catch (Exception& exception)
	{
		LOGGER().log(exception);
	}

	return EXIT_SUCCESS;
}
