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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <kdrive/baos/Headers.h>
#include <kdrive/utility/Logger.h>
#include <Poco/Exception.h>
#include <Poco/Format.h>
#include <Poco/Logger.h>
#include <QMessageBox>

using namespace kdrive::baos;
using namespace kdrive::utility;
using Poco::Exception;
using Poco::format;

CLASS_LOGGER("PushButtonDemo")

/***********************************
** Anonymous namespace
************************************/

namespace
{

template <typename T> bool readDatapointValue(BaosConnector::Ptr connector, int id)
{
	return false;
}

template <> bool readDatapointValue<bool>(BaosConnector::Ptr connector, int id)
{
	bool success = false;

	try
	{
		BaosDatapoint baosDatapoint(connector, id);
		baosDatapoint.getBoolean();
		success = true;
	}
	catch (Exception& exception)
	{
		const std::string a = exception.displayText();
		poco_error(LOGGER(), exception.displayText());
	}

	return success;
}

template <> bool readDatapointValue<float>(BaosConnector::Ptr connector, int id)
{
	bool success = false;

	try
	{
		BaosDatapoint baosDatapoint(connector, id);
		baosDatapoint.get2OctetFloat();
		success = true;
	}
	catch (Exception& exception)
	{
		poco_error(LOGGER(), exception.displayText());
	}

	return success;
}

} // end anonymous namespace

/***********************************
** MainWindow
************************************/

/*!
    Creates a Main Window, standard Qt window constructor

	Initializes the timers used for auto-off. These are started when
	a light is turned on and the auto-off parameter is not zero (see switchLight)

	Connects to the indication signal, this is emitted when a datapoint value indication is received
	We use a single to do this as the indication is received in a separate thread, and we need to update
	the GUI, i.e. to set the pixmap and start the timer

	Starts a single shot time to initiate the connection sequence. This is because we show a QMessageBox
	on exception and need a constructed Main Window (i.e. doesn't work if within the constructor)
*/
MainWindow::MainWindow(QWidget* parent)

	: QMainWindow(parent),
	  ui_(new Ui::MainWindow)
{
	ui_->setupUi(this);

	ch1Timer_.setSingleShot(true);
	connect(&ch1Timer_, SIGNAL(timeout()), this, SLOT(on_channel1Off_clicked()));

	ch2Timer_.setSingleShot(true);
	connect(&ch2Timer_, SIGNAL(timeout()), this, SLOT(on_channel2Off_clicked()));

	connect(this, SIGNAL(receivedBoolean(int, bool)), this, SLOT(onReceivedBoolean(int, bool)));
	connect(this, SIGNAL(receivedFloat(int, float)), this, SLOT(onReceivedFloat(int, float)));
	connect(this, SIGNAL(disconnected()), this, SLOT(on_disconnect_clicked()));

	QTimer::singleShot(25, this, SLOT(on_scan_clicked()));

	enableGui();
}

/*!
	Destroys the main window
*/
MainWindow::~MainWindow()
{
	delete ui_;
}

/*!
	Enumerates and display the names in the combo box
*/
void MainWindow::on_scan_clicked()
{
	poco_information(LOGGER(), "Scan Requested");

	try
	{
		ui_->deviceNames->clear();
		BaosEnumerator baosEnumerator;
		devices_ = baosEnumerator.getDevices();
		for (const BaosEnumerator::Device& device : devices_)
		{
			const std::string& name = std::get<BaosDeviceAttr::Name>(device);
			const std::string& ip = std::get<BaosDeviceAttr::Address>(device);
			const std::string label = format("%s %s", name, ip);
			const QString userData(name.c_str());
			ui_->deviceNames->addItem(label.c_str(), userData);
		}
	}
	catch (Exception& exception)
	{
		poco_error(LOGGER(), exception.displayText());
		QMessageBox::information(this, "Exception", exception.displayText().c_str());
	}

	enableGui();
}

/*!
	Connects to the baos device. We create a connection and then
	read the parameters
*/
void MainWindow::on_connect_clicked()
{
	poco_information(LOGGER(), "Connect Requested");

	try
	{
		createConnection();
		readStatus();
		readParameters();
	}
	catch (Exception& exception)
	{
		poco_error(LOGGER(), exception.displayText());
		QMessageBox::information(this, "Exception", exception.displayText().c_str());
	}

	enableGui();
}

void MainWindow::on_disconnect_clicked()
{
	poco_information(LOGGER(), "Disconnect Requested");

	try
	{
		destroyConnection();
	}
	catch (Exception& exception)
	{
		poco_error(LOGGER(), exception.displayText());
		QMessageBox::information(this, "Exception", exception.displayText().c_str());
	}

	enableGui();
}

/*!
	Slot to turn channel 1 light on
	Called when the button is pressed
*/
void MainWindow::on_channel1On_clicked()
{
	poco_information(LOGGER(), "Channel 1 On");
	send(Ch1Request, true);
}

/*!
	Slot to turn channel 1 light off
	Called when the button is pressed
	Or the channel 1 timer expires
*/
void MainWindow::on_channel1Off_clicked()
{
	poco_information(LOGGER(), "Channel 1 Off");
	send(Ch1Request, false);
}

/*!
	Slot to read the value of the KNX 2 Byte float
	The response will also be handled as an indication
	by the BaosEvent class, so we let it display the
	result as though a standard indication was received.
	i.e. we don't have to handle the response here
*/
void MainWindow::on_floatRead_clicked()
{
	poco_information(LOGGER(), "Read KNX 2 Byte Float");

	if (!readDatapointValue<float>(baosConnection_->getConnector(), TwoByteFloat))
	{
		QMessageBox::information(this, "Exception", "Unable to read value from Baos");
	}
}

/*!
	Slot to turn channel 2 light on
	Called when the button is pressed
*/
void MainWindow::on_channel2On_clicked()
{
	poco_information(LOGGER(), "Channel 2 On");
	send(Ch2Request, true);
}

/*!
	Slot to turn channel 2 light off
	Called when the button is pressed
	Or the channel 2 timer expires
*/
void MainWindow::on_channel2Off_clicked()
{
	poco_information(LOGGER(), "Channel 2 Off");
	send(Ch2Request, false);
}

/*!
	Slot called when a datapoint value indication is received
	for one of the boolean values.
	We check to see if it is a datapoint we are interested in
	and then switch the light on or off, depending on enabled
	1 for on, 0 for off.
*/
void MainWindow::onReceivedBoolean(int id, bool enabled)
{
	if (id == Ch1Status || id == Ch2Status)
	{
		switchLight(id, enabled);
	}
}

/*!
	Slot called when a datapoint value indication is received
	for one of the float values (there is currently only one)
	We display the value
*/
void MainWindow::onReceivedFloat(int id, float value)
{
	if (id == TwoByteFloat)
	{
		QString str;
		str.sprintf("%f", value);
		ui_->floatEdit->setText(str);
	}
}

/*!
	Switches the GUI light on or off
	Precondition: coNo is either Ch1Status or Ch2Status
	If enabled we set the image to on, otherwise off
	If enabled we update the timer, which will start the timer
	if the corresponding parameter is not 0. When the timer elapses
	it will turn the light off
	Note, this function is called not when we send the request but when
	we receive the status response
*/
void MainWindow::switchLight(int coNo, bool enabled)
{
	if (isChannel1(coNo) || isChannel2(coNo))
	{
		QLabel* label = isChannel1(coNo) ? ui_->lightBulb1 : ui_->lightBulb2;
		QString image = enabled ? ":/images/lightbulb.png" : ":/images/lightbulb-off.png";
		label->setPixmap(QPixmap(image));

		if (enabled)
		{
			updateTimer(coNo);
		}
	}
}

/*!
	Sends a set datapoint value request.
	It uses the default BAOS command SetNewValueAndSendOnBus
*/
void MainWindow::send(unsigned int coNo, bool enabled)
{
	try
	{
		BaosDatapoint baosDatapoint(baosConnection_->getConnector(), coNo);
		baosDatapoint.setBoolean(enabled);
	}
	catch (Exception& exception)
	{
		poco_error(LOGGER(), exception.displayText());
		QMessageBox::information(this, "Exception", exception.displayText().c_str());
	}
}

/*!
	Creates a connection with the BAOS device
	This connection is a stream (TCP/IP) connection.

	We get the device details from the enumerated device list

	We also set up the notification listener. This notification listener is a callback function
	that is invoked when a Datapoint Value Indication is received. The receive
	thread is a separate thread (to the main GUI thread) and the callback function
	will be in the context of the receive thread (i.e. you shouldn't update the GUI
	in onIndicationPacket).
*/
void MainWindow::createConnection()
{
	// get the address and version
	const int index = ui_->deviceNames->currentIndex();
	const BaosEnumerator::Device& device = devices_.at(index);
	const std::string& ip = std::get<BaosDeviceAttr::Address>(device);
	const unsigned char version = std::get<BaosDeviceAttr::Version>(device);

	// create the connection
	baosConnection_.reset(new ScopedBaosConnection(ip, version, true));

	// connect the signals
	baosEvent_.setDatapointEvent(std::bind(&MainWindow::onIndication, this, std::placeholders::_1));
	baosEvent_.setConnectorClosedEvent(std::bind(&MainWindow::onDisconnected, this));
	baosEvent_.setConnector(baosConnection_->getConnector());

	poco_information_f2(LOGGER(), "Created connection to %s version: %d", ip, static_cast<int>(version));
}

/*!
	Closes the connection
	We first disconnect the baos event notifications
	Then stop the heartbeat
	and finally kill the connection
	(i.e. reverse order of create connection)
	Finally, we turn the lights off (gui only)
*/
void MainWindow::destroyConnection()
{
	BaosConnector::Ptr nullConnector;
	baosEvent_.setConnector(nullConnector, false);

	baosConnection_.reset();

	switchLight(Ch1Status, false);
	switchLight(Ch2Status, false);

	poco_information(LOGGER(), "Closed connection");
}

/*!
	We read the value of the status datapoints to update the light images
	and the float value.

	i.e. on startup we have to read to ensure we show the correct
	status of the bus. otherwise we could show that the light is off when it
	is on. Note: the response is handled by the baos event, so we don't have
	to do anything here...

	This function also handles checking that the Baos has been property configured
	for this application.
*/
void MainWindow::readStatus()
{
	bool success = true;

	BaosConnector::Ptr connector = baosConnection_->getConnector();

	success = readDatapointValue<bool>(connector, Ch1Request);
	success = readDatapointValue<bool>(connector, Ch1Status) && success;
	success = readDatapointValue<bool>(connector, Ch2Request) && success;
	success = readDatapointValue<bool>(connector, Ch2Status) && success;
	success = readDatapointValue<float>(connector, TwoByteFloat) && success;

	if (!success)
	{
		QMessageBox::information(this, "Warning", "Unable to read all datapoints.\n"
		                         "This app may not function correctly!\n"
		                         "Please check the Baos ETS configuration");
	}
}

/*!
	Reads the application parameters from the BAOS device.
	We expect two parameters, each 1 byte, indicating a timeout value
	If the timeout is not zero we use it to auto-switch off the light when it is enabled
	The timeout is in seconds, and the timer requires milliseconds
*/
void MainWindow::readParameters()
{
	BaosConnector::Ptr connector = baosConnection_->getConnector();

	ch1Timer_.setInterval(readParameter(connector, 1) * 1000);
	ch2Timer_.setInterval(readParameter(connector, 2) * 1000);
}

/*!
	Callback notification function invoked when a BaosDatapoint event is received
	This callback is in the context of the receive thread so we can't update the GUI directly
	Instead we emit a signal to indicate a datapoint indication. This function handles
	both the response from a BaosDatapoint read and the asynchronous datapoint value
	indication from the device. We filter out all datapoints except for the status
	datapoints, i.e. to update the light image.
*/
void MainWindow::onIndication(BaosDatapoint& baosDatapoint)
{
	const int id = baosDatapoint.getId();

	const std::string s = LoggerFormatter::toHex(baosDatapoint.getData());
	poco_information_f2(LOGGER(), "Indication for id: %d data: %s", id, s);

	switch (id)
	{
		case Ch1Status:
		case Ch2Status:
			emit receivedBoolean(id, baosDatapoint.getBoolean());
			break;

		case TwoByteFloat:
			emit receivedFloat(id, baosDatapoint.get2OctetFloat());
			break;
	}
}

/*!
	Callback notification function invoked when a disconnect event is received
	This callback is in the context of a thread so we can't update the GUI directly
	Instead we emit a signal to indicate a disconnect signal.
*/
void MainWindow::onDisconnected()
{
	emit disconnected();
}

/*!
	Starts the auto-off timer if the timer interval is set.
*/
void MainWindow::updateTimer(int coNo)
{
	QTimer& timer = isChannel1(coNo) ? ch1Timer_ : ch2Timer_;

	if (timer.interval())
	{
		timer.start();
	}
}

/*!
	Returns true if the communication object number (status response)
	refers to channel 1
*/
bool MainWindow::isChannel1(int coNo) const
{
	return coNo == Ch1Status ? true : false;
}

/*!
	Returns true if the communication object number (status response)
	refers to channel 2
*/
bool MainWindow::isChannel2(int coNo) const
{
	return coNo == Ch2Status ? true : false;
}

/*!
	Enable the buttons
*/
void MainWindow::enableGui()
{
	const bool connected = (baosConnection_ && baosConnection_->getConnector()) ? true : false;
	ui_->channel1Off->setEnabled(connected);
	ui_->channel1On->setEnabled(connected);
	ui_->channel2Off->setEnabled(connected);
	ui_->channel2On->setEnabled(connected);
	ui_->disconnect->setEnabled(connected);
	ui_->scan->setEnabled(!connected);
	ui_->deviceNames->setEnabled(!connected);
	ui_->floatRead->setEnabled(connected);
	ui_->floatEdit->setEnabled(connected);

	const int devices = ui_->deviceNames->count();
	ui_->connect->setEnabled(!connected && (devices != 0));
}
