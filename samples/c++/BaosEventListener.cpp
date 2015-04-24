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
#include <kdrive/utility/Logger.h>
#include <kdrive/utility/LoggerFormatter.h>
#include <Poco/Exception.h>
#include <Poco/Format.h>
#include <Poco/Logger.h>
#include <vector>
#include <cstdio>

using namespace kdrive::connector;
using namespace kdrive::baos;
using namespace kdrive::utility;
using Poco::Exception;
using Poco::format;

CLASS_LOGGER("BaosEventListener")

/*!
	This sample shows how to connect to the BaosEvent class
	for event notifications. These include: datapoint indications
	(including the responses to the GetDatapointValue services)
	whether the KNX bus is connected or not (only for protocol version 2.0)
	and when the stream connector is disconnected (i.e. the TCP/IP connection)
*/

/*!
	Binds the datapoint indication event to a member function
*/
#define BIND_DATAPOINT_EVENT() \
	std::bind(&onDatapointEvent, std::placeholders::_1)

/*!
	Binds the datapoint knx bus connected event to a member function
*/
#define BIND_BUS_CONNECTED_EVENT() \
	std::bind(&onBusConnectedEvent, std::placeholders::_1)

/*!
	Binds the connector closed event to a member function
*/
#define BIND_CONNECTOR_CLOSED_EVENT() \
	std::bind(&onConnectorClosedEvent)

/***********************************
** Anonymous namespace
************************************/

namespace
{

void readValues(BaosConnector::Ptr connector)
{
	// this should trigger the onDatapointEvent event
	// as the response to getData is also treated as an indication
	BaosDatapoint baosDatapoint(connector, 1);
	baosDatapoint.getData();
}

/*!
	Called when a DatapointValue indication is received
*/
void onDatapointEvent(BaosDatapoint& baosDatapoint)
{
	const std::vector<unsigned char>& data = baosDatapoint.getData();
	poco_information(LOGGER(), format("Received datapoint value for id %d %s",
	                                  static_cast<int>(baosDatapoint.getId()), LoggerFormatter::toHex(data)));
}

/*!
	Called when the KNX bus is connected or disconnected
	to test this, temporarily disconnect the KNX bus connection
	from the baos device
*/
void onBusConnectedEvent(bool busConnected)
{
	poco_information(LOGGER(),
	                 format("KNX bus connection state event: %s",
	                        std::string(busConnected ? "connected" : "disconnected")));
}

/*!
	Called when the TCP/IP connection is broken.
	To test this, simply remove the IP cable from the baos device.
	Note: it can take some time for the stream connection to indicate
	the the connection has been shutdown
*/
void onConnectorClosedEvent()
{
	poco_information(LOGGER(), "BAOS Connector disconnected");
}

} // end anonymous namespace

/***********************************
** main
************************************/

int main(int argc, char* argv[])
{
	// configure the logging channel
	INIT_ROOT_CONSOLE_LOGGER();

	try
	{
		// connect to the baos events
		// we declare it before the ScopedStreamConnection
		// to ensure we get the connector disconnect event.
		// If we declare it afterwards the BaosEvent destructor
		// will be run before the disconnected event is called
		BaosEvent baosEvent;
		baosEvent.setDatapointEvent(BIND_DATAPOINT_EVENT());
		baosEvent.setBusConnectedEvent(BIND_BUS_CONNECTED_EVENT());
		baosEvent.setConnectorClosedEvent(BIND_CONNECTOR_CLOSED_EVENT());

		// create a TPC/IP connection with the remote BAOS device
		ScopedBaosConnection connection("Baos-Sample", true);
		BaosConnector::Ptr connector = connection.getConnector();
		baosEvent.setConnector(connector);

		// read datapoint values
		// (should trigger the datapoint event handler)
		readValues(connector);

		// wait for an Enter, all indications will be shown
		// in the same datapoint event handler
		poco_information(LOGGER(), "Press [Enter] to exit the application ...");
		std::getchar();

		connection.disconnect();
	}
	catch (Exception& exception)
	{
		LOGGER().log(exception);
	}

	return EXIT_SUCCESS;
}

