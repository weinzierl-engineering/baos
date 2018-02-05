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
#include <Poco/Thread.h>
#include <Poco/Exception.h>
#include <Poco/Logger.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/Format.h>

using namespace kdrive::baos;
using namespace kdrive::connector;
using Poco::Thread;
using Poco::Exception;
using Poco::format;

CLASS_LOGGER("LightSwitcher")

/*!
	Light Switcher

	This demo shows how to:

		create a connection with the BAOS device
		get/set Datapoint values
		read parameters

	It assumes an application with a single boolean bit (i.e. a light switch)
	which it turns on and off. A parameter is also used to specify the wait period
	before turning the light off.

	You will have to change the IP Address or device name to match your device.
	You can find the device name and ip address by running the Enumerator sample.
*/

/***********************************
** Anonymous namespace
************************************/

namespace
{

struct BaosApp
{
	enum CommunicationObjects { Ch1Request = 1 };
	enum Parameters { Ch1Timeout = 1 };
};

/*!
	sets the datapoint value to 1 or 0

	we read the value first to determine if it needs to be set.
	This is not normally required and you can simply set the value
	without reading it first. Implemented only to show how to
	read the datapoint value
*/
void switchLight(BaosConnector::Ptr connector, bool enabled)
{
	BaosDatapoint datapoint(connector, BaosApp::Ch1Request);

	if (datapoint.getBoolean() != enabled)
	{
		const std::string status = enabled ? "on" : "off";
		poco_information(LOGGER(), format("Switching DP number %d : %s", static_cast<int>(BaosApp::Ch1Request), status));

		datapoint.setBoolean(enabled);
	}
}

/*!
	Wait (sleep) a specified period of time
	The timeout period is set as a baos parameter byte, in ms
*/
void waitTimeout(BaosConnector::Ptr connector)
{
	const int timeout = readParameter(connector, BaosApp::Ch1Timeout);
	poco_information(LOGGER(), format("Timeout is %d ms", timeout));
	Thread::sleep(timeout);
}

} // end anonymous namespace

int main(int argc, char* argv[])
{
	try
	{
		// configure the logging channel
		INIT_ROOT_CONSOLE_LOGGER();
		LOGGER().setLevel("debug");

		// create a TPC/IP connection with the remote BAOS device
		// and attach to the connect and disconnect signals
		// set decodeProtocol to true to see the protocol information
		ScopedSerialBaosConnection connection("/dev/ttyAMA0", true);
		BaosConnector::Ptr connector = connection.getConnector();
		switchLight(connector, true);
		waitTimeout(connector);
		switchLight(connector, false);
	}
	catch (Exception& exception)
	{
		LOGGER().log(exception);
	}

	return EXIT_SUCCESS;
}

