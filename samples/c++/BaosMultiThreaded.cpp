//
// Copyright (c) 2002-2015 WEINZIERL ENGINEERING GmbH
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

using namespace kdrive::baos;
using namespace kdrive::connector;
using namespace kdrive::utility;
using Poco::Exception;
using Poco::format;

/*!
	MultiThreaded

	This demo shows how the baos device communication is across
	multiple threads. Synchronization is handled automatically
	by the rpc library in the ServerFunction class. So you don't
	need to use a semaphore or a mutex in your application when
	using the connector. If however you are sharing data across
	the threads (for example, a BaosDatapoint class, you will need
	to wrap it in a mutex).
*/

CLASS_LOGGER("MultiThreaded")

/*!
	Binds a thread function with a connector
*/
#define BIND_THREAD_FUNCTION(fn, connector)	\
	std::bind(fn, std::placeholders::_1, connector)

/*********************************
** Anonymous namespace
**********************************/

namespace
{

enum
{
    MinId = 1,
    MaxId = 250
};

/*!
	Sets the user event
	and stops the callback thread loop
*/
void stop(ActiveFunction& activeFunction)
{
	activeFunction.getCallbackThread().set();
	activeFunction.stopFromWithinCallback();
}

/*!
	Gets and displays datapoint descriptions
*/
void getDatapointDescriptions(ActiveFunction& activeFunction, BaosConnector::Ptr connector)
{
	try
	{
		BaosDatapointDescriptions baosDatapointDescriptions(connector);

		baosDatapointDescriptions.readFromDevice();
		const BaosDatapointDescriptions::Descriptions descriptions = baosDatapointDescriptions.getDescriptions();

		const unsigned int count = descriptions.size();
		poco_information(LOGGER(), format("(t1) %u items found", count));

		for (const auto& item : descriptions)
		{
			const BaosDatapointDescription& d = item.second;
			const int id = d.getId();
			const int dpt = d.getDatapointType();
			const int bits = d.getValueTypeSizeBits();
			const int bytes = d.getValueTypeSizeBytes();
			const std::string size = d.isBitType() ? format("%d Bits", bits) : format("%d Bytes", bytes);
			poco_information(LOGGER(), format("(t1) Id: %d, Datapoint type %d, Size: %s", id, dpt, size));
		}
	}
	catch (Exception& exception)
	{
		poco_error(LOGGER(), format("(t1) %s", exception.displayText()));
	}

	stop(activeFunction);
}

/*!
	Gets and displays datapoint string descriptions
*/
void getDatapointStringDescriptions(ActiveFunction& activeFunction, BaosConnector::Ptr connector)
{
	try
	{
		GetDescriptionString getDescriptionString(connector);

		for (int id = MinId; id <= MaxId; ++id)
		{
			getDescriptionString.rpc(id, 1);
			poco_information(LOGGER(), format("(t2) Id: %d Desc: %s", id, getDescriptionString.at(0)));
		}
	}
	catch (Exception& exception)
	{
		poco_error(LOGGER(), format("(t2) %s", exception.displayText()));
	}

	stop(activeFunction);
}

/*!
	Gets and displays datapoint values
*/
void getDatapointValues(ActiveFunction& activeFunction, BaosConnector::Ptr connector)
{
	try
	{
		GetDatapointValue getDatapointValue(connector);

		for (int id = MinId; id <= MaxId; ++id)
		{
			getDatapointValue.rpc(id, 1);
			const GetDatapointValue::Value& value = getDatapointValue.at(0);

			const int length = value.length;
			const std::string data = LoggerFormatter::toHex(value.data);
			poco_information(LOGGER(), format("(t3) Id: %d Length: %d Data:%s", id, length, data));
		}
	}
	catch (Exception& exception)
	{
		poco_error(LOGGER(), format("(t3) %s", exception.displayText()));
	}

	stop(activeFunction);
}

/*!
	Gets and displays server items
*/
void getServerItems(ActiveFunction& activeFunction, BaosConnector::Ptr connector)
{
	try
	{
		BaosServerItems baosServerItems(connector);

		poco_information(LOGGER(), format("(t4) Hardware Type: %s", LoggerFormatter::toHex(baosServerItems.getHardwareType())));
		poco_information(LOGGER(), format("(t4) Hardware Version: %d", (int) baosServerItems.getHardwareVersion()));
		poco_information(LOGGER(), format("(t4) Firmware Version: %d", (int) baosServerItems.getFirmwareVersion()));
		poco_information(LOGGER(), format("(t4) Manufacture Code Device: %u", baosServerItems.getManufactureCodeDevice()));
		poco_information(LOGGER(), format("(t4) Manufacture Code App: %u", baosServerItems.getManufactureCodeApp()));
		poco_information(LOGGER(), format("(t4) Application Id: %u", baosServerItems.getApplicationId()));
		poco_information(LOGGER(), format("(t4) Application Version: %d", (int) baosServerItems.getApplicationVersion()));
		poco_information(LOGGER(), format("(t4) Serial Number: %s", LoggerFormatter::toHex(baosServerItems.getSerialNumber())));
		poco_information(LOGGER(), format("(t4) Time Since Reset: %lu", baosServerItems.getTimeSinceReset()));
		poco_information(LOGGER(), format("(t4) Bus Connected: %b", baosServerItems.isBusConnected()));
		poco_information(LOGGER(), format("(t4) Max Buffer Size: %u", baosServerItems.getMaxBufferSize()));
		poco_information(LOGGER(), format("(t4) Buffer Size: %u", baosServerItems.getBufferSize()));
		poco_information(LOGGER(), format("(t4) Length of Description String: %u", baosServerItems.getLengthOfDescriptionString()));
		poco_information(LOGGER(), format("(t4) Programming Mode: %d", (int) baosServerItems.getProgrammingMode()));
	}
	catch (Exception& exception)
	{
		poco_error(LOGGER(), format("(t4) %s", exception.displayText()));
	}

	stop(activeFunction);
}

} // end anonymous namespace

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
		// set decodeProtocol to true to see the protocol information
		ScopedBaosConnection connection(device, false);
		BaosConnector::Ptr connector = connection.getConnector();

		// create some threads, they are auto-started
		ActiveFunction thread1(BIND_THREAD_FUNCTION(getDatapointDescriptions, connector));
		ActiveFunction thread2(BIND_THREAD_FUNCTION(getDatapointStringDescriptions, connector));
		ActiveFunction thread3(BIND_THREAD_FUNCTION(getDatapointValues, connector));
		ActiveFunction thread4(BIND_THREAD_FUNCTION(getServerItems, connector));

		// start the threads
		thread1.start();
		thread2.start();
		thread3.start();
		thread4.start();

		// and wait until they are done
		thread1.getCallbackThread().wait();
		thread2.getCallbackThread().wait();
		thread3.getCallbackThread().wait();
		thread4.getCallbackThread().wait();
	}
	catch (Exception& exception)
	{
		LOGGER().log(exception);
	}

	return EXIT_SUCCESS;
}
