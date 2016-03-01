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
#include <kdrive/utility/Logger.h>
#include <kdrive/utility/LoggerFormatter.h>
#include <Poco/Exception.h>

using namespace kdrive::baos;
using namespace kdrive::connector;
using namespace kdrive::utility;
using Poco::Exception;

/*!
	Timer

	This demo shows how to:

	get the list of timers
	delete timers
	add / update timers

	NOTE: this will only work with BAOS devices that support timers.
	i.e. BAOS 777
*/

CLASS_LOGGER("Timer")

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
		// and attach to the connect and disconnect signals
		// set decodeProtocol to true to see the protocol information
		ScopedBaosConnection connection(device, true);
		BaosConnector::Ptr connector = connection.getConnector();

		// we use the BaosTimers class to get/set the timers
		BaosTimers baosTimers(connector);

		// get the timers
		auto timers = baosTimers.getTimers();
		for (const auto& timer : timers)
		{
			poco_information(LOGGER(), timer.toString());
		}

		// delete them and add them back again
		baosTimers.deleteTimers(timers);
		baosTimers.setTimers(timers);

		// now we do the same thing, but with individual timers
		// that is, first we delete them and then we add them back

		// delete them
		for (const auto& timer : timers)
		{
			baosTimers.deleteTimer(timer.id);
		}

		// add them
		for (const auto& timer : timers)
		{
			baosTimers.setTimer(timer);
		}

		// now we modify the first timer (description) and update it
		if (!timers.empty())
		{
			auto& timer = timers.at(0);
			timer.description = "Modified by BaosTimer sample";
			baosTimers.setTimer(timer);
		}
	}
	catch (Exception& exception)
	{
		LOGGER().log(exception);
	}

	return EXIT_SUCCESS;
}
