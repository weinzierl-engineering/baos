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
#include <kdrive/utility/LoggerFormatter.h>
#include <Poco/Exception.h>
#include <Poco/Format.h>
#include <iostream>

using namespace kdrive::baos;
using namespace kdrive::connector;
using namespace kdrive::utility;
using Poco::Exception;
using Poco::format;

/*!
	ServerItem

	This demo shows how to:

	Read the users input(IP-Adress) and
	create a connection with the BAOS device with this IP-Adress and
	read the ServerItem - Serial Number and show it to the user
*/

CLASS_LOGGER("ServerItem")

int main(int argc, char* argv[])
{
	// configure the logging channel
	INIT_ROOT_CONSOLE_LOGGER();

	std::string ipAdress;

	if (argc > 1)
	{
		ipAdress = argv[1];
	}

	// Here we create the help text when the IP-Adress is missing or the user typed in '/?' for help
	if (argc < 2 || ipAdress == "/?")
	{
		std::cout << argv[0] << std::endl << std::endl << "Please type in the IP-Adress after the .exe" << std::endl <<
		          "to find out the Serial Number of the Baos device." << std::endl << "Use '/?' for help!" << std::endl;

		return EXIT_FAILURE;
	}
	std::cout << argv[1] << std::endl;

	try
	{
		// create a TPC/IP connection with the remote BAOS device
		StreamConnector2x::Ptr connector = std::make_shared<StreamConnector2x>();
		connector->open(ipAdress);

		// create baosServerItems value with the information of the baos device
		BaosServerItems baosServerItems(connector);

		// Get the Serial Number and show it to the user
		poco_information(LOGGER(), format("Serial Number: %s", LoggerFormatter::toHex(baosServerItems.getSerialNumber())));
	}
	catch (Exception& exception)
	{
		LOGGER().log(exception);
	}

	return EXIT_SUCCESS;
}
