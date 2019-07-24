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
#include <Poco/Logger.h>
#include <cstdio>

using namespace kdrive::baos;
using namespace kdrive::connector;
using Poco::Exception;
using Poco::format;

/*!
	This sample shows how a single application can implement multiple
	connections to a single BAOS device. In practice however you
	should only really need a single connection.

	This sample creates 10 threads and connects to the indication event.
	It counts the number of indications received for each thread.

	It waits for a ENTER to end the threads
*/

CLASS_LOGGER("MultiConnector")

/*!
	We use the active function callback thread mechanism, and pass it a
	baos device from the enumeration mechanism
	i.e. this shows how to pass additional parameters to the thread callback function
	using std::bind
*/
#define BIND_THREAD_FUNCTION(fn, baosDevice) \
	std::bind(fn, std::placeholders::_1, std::cref(baosDevice))

/*!
	This function is called when a datapoint indication is received.
	It simply increments the counter. We pass the counter as a reference.
*/
#define BIND_DATAPOINT_EVENT(id, counter) \
	std::bind(onDatapointEvent, std::placeholders::_1, id, std::ref(counter))

/******************************************
** Anonymous namespace
*******************************************/

namespace
{

/*!
	Waits (and consumes) a rx packet notification
	This uses the connector queue mechanism
	waitReceive will throw a Poco::TimeoutException is a
	packet is not received within timeout milliseconds,
	and we simply ignore the exception
	waitReceive also returns an AbstractPacket, which
	we also ignore. This is simply to provide a blocking
	function in the thread loop.
	Of course, we could have simply used Thread::sleep...
*/
void wait(BaosConnector::Ptr connector, unsigned int timeout)
{
	try
	{
		connector->waitReceive(timeout);
	}
	catch (...)
	{
	}
}

/*!
	The datapoint indication handler.
	We simply increment the indication counter
*/
void onDatapointEvent(BaosDatapoint& datapoint, int threadId, int& counter)
{
	++counter;

	const int id = datapoint.getId();
	poco_information(LOGGER(), format("Indication: baos id %d thread %d counter %d", id, threadId, counter));
}

/*!
	eventHandler is the thread loop callback function.
	We implement our own loop and block on the rx queue of the connector.
	The loop will end when the caller invokes thread.stop
	If an exception is raised, we stop the thread ourselves with stopFromWithinCallback
*/
void eventHandler(ActiveFunction& activeFunction, const BaosDevice& baosDevice)
{
	CallbackThread& callbackThread = activeFunction.getCallbackThread();
	const int id = callbackThread.getId();
	int counter = 0;

	try
	{
		// create a TPC/IP connection with the remote BAOS device
		// set decodeProtocol to false to suppress the protocol information
		ScopedBaosConnection connection(baosDevice, false);
		BaosConnector::Ptr connector = connection.getConnector();

		// connect to the baos events
		BaosEvent baosEvent(connector);
		baosEvent.setDatapointEvent(BIND_DATAPOINT_EVENT(id, counter));

		// we enable the rx queue so we can block while idle,
		// i.e. not receiving packets
		connector->enableRxQueue();

		while (callbackThread.canLoop())
		{
			wait(connector, 50);
		}
	}
	catch (Exception& exception)
	{
		LOGGER().log(exception);
		activeFunction.stopFromWithinCallback();
	}

	// and write out the number of indications received:
	poco_information(LOGGER(), format("Received Indications: thread %d counter %d", id, counter));
}

} // end anonymous namespace

/******************************************
** MultiConnector
*******************************************/

int main(int argc, char* argv[])
{
	INIT_ROOT_CONSOLE_LOGGER();

	try
	{
		// find the baos device using baos enumeration
		BaosEnumerator baosEnumerator;
		const BaosEnumerator::Device& device = baosEnumerator.find("Baos-Sample");

		// increase the thread pool capacity, the default will not
		// handle 10 baos connections (each with a receive and notification thread)
		// plus 10 additional callback threads
		static const int maxThreads = 10;
		CallbackThreadManager::getThreadPool().addCapacity(maxThreads * 2);

		// create some threads
		std::shared_ptr<ActiveFunction> thread;
		std::vector<std::shared_ptr<ActiveFunction> > threads;
		for (int index = 0; index < maxThreads; ++index)
		{
			thread.reset(new ActiveFunction(BIND_THREAD_FUNCTION(eventHandler, device)));
			threads.push_back(thread);
			thread->start();
		}

		// wait for an Enter, all indications will be shown
		// in the same datapoint event handler
		poco_information(LOGGER(), "Press [Enter] to exit the application ...");
		std::getchar();

		for (std::shared_ptr<ActiveFunction> thread : threads)
		{
			thread->stop();
		}

		threads.clear();
	}
	catch (Exception& exception)
	{
		poco_error(LOGGER(), exception.displayText());
	}

	return EXIT_SUCCESS;
}

