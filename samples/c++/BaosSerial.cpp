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

#include <kdrive/baos/Baos.h>
#include <kdrive/connector/CallbackThread.h>
#include <kdrive/utility/Logger.h>
#include <kdrive/utility/LoggerFormatter.h>
#include <Poco/Exception.h>
#include <Poco/Format.h>
#include <iostream>

using namespace kdrive::baos;
using namespace kdrive::connector;
using namespace kdrive::utility;
using Poco::Exception;
using Poco::format;

CLASS_LOGGER("BaosSerial")

int main(int argc, char* argv[])
{
	// configure the logging channel
	INIT_ROOT_CONSOLE_LOGGER();

	try
	{
		// connects the BAOS FT 1.2 Module
		FT12Connector::Ptr connector = std::make_shared<FT12Connector>();
		connector->open("COM8");

		// get the Serial Number
		BaosServerItems baosServerItems(connector);
		poco_information(LOGGER(), format("Serial Number: %s", LoggerFormatter::toHex(baosServerItems.getSerialNumber())));

		// Reads the data point descriptions
		BaosDatapointDescriptions baosDatapointDescriptions(connector);

		baosDatapointDescriptions.readFromDevice();
		const BaosDatapointDescriptions::Descriptions descriptions = baosDatapointDescriptions.getDescriptions();

		const unsigned int count = descriptions.size();
		poco_information(LOGGER(), format("%u items found", count));

		for (const auto& item : descriptions)
		{
			const BaosDatapointDescription& d = item.second;
			const int id = d.getId();
			const int dpt = d.getDatapointType();
			const int bits = d.getValueTypeSizeBits();
			const int bytes = d.getValueTypeSizeBytes();
			const std::string size = d.isBitType() ? format("%d Bits", bits) : format("%d Bytes", bytes);
			poco_information(LOGGER(), format("Id: %d, Datapoint type %d, Size: %s", id, dpt, size));
		}
	}
	catch (Exception& exception)
	{
		LOGGER().log(exception);
	}

	return EXIT_SUCCESS;
}
