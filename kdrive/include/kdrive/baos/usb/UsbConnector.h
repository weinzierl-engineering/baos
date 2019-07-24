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

#ifndef __KDRIVE_BAOS_USB_USB_CONNECTOR_H__
#define __KDRIVE_BAOS_USB_USB_CONNECTOR_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/BaosConnector.h"
#include "kdrive/baos/core/API.h"
#include <vector>

namespace kdrive
{
namespace baos
{

class KnxUsbPort;

/*********************************
** UsbConnector
**********************************/

/*!
	\class UsbConnector
	\brief The UsbConnector is responsible for creating
	a SUB connection with the baos server

	This class supports BAOS protocol 2.x (via USB).
	(It exist not usd device with protocol version 1.x)
*/
class kdriveRPC_baos_API UsbConnector : public BaosConnector
{
public:
	typedef std::shared_ptr<UsbConnector> Ptr;

	/*!
		Creates a default (disconnected) USB baos connector
	*/
	UsbConnector();

	/*!
		Closes the connections and destroys the connector
	*/
	virtual ~UsbConnector();

	/*!
		Opens a connection with the local device
		using the UsbIndex property as the index
	*/
	using BaosConnector::open;

	/*!
		Opens a connection with the local device
		\param index is the last enumeration index 
	*/
	void open(int index);

	/*!
		Returns a formatted port description.
		Format: "USB"<UsbIndex+1>
		e.g. USB1
	*/
	std::string getDescription() override;

	bool isConnected() const override;

	/*!
		Returns the usb index.
		Ports are enumerated with the hid driver, and are
		numbered in the order that the hid driver enumerates
		the devices.
	*/
	unsigned int getUsbIndex() const;

	/*!
		Returns the USB device vendor ID
	*/
	unsigned int getUsbVendorId();

	/*!
		Returns the USB device product ID
	*/
	unsigned int getUsbProductId();

	/*!
		Returns the USB manufacturer string
	*/
	std::string getUsbManufacturerString();

	/*!
		Returns the USB product string
	*/
	std::string getUsbProductString();

	/*!
		Returns the USB serial number string
	*/
	std::string getUsbSerialNumberString();

private:
	/*!
		Request to open the port from the base class.
		Opens the usb port, starts the receive thread
		and initialises the KNX protocol
		precondition: the port is not already open
	*/
	void openImpl() override;

	/*!
		Closes the serial port
		precondition: the usb port is open
	*/
	void closeImpl() override;

	/*!
		\return true if the usb port is open, false otherwise
	*/
	bool isOpenImpl() const override;

	/*!
		Calls resetPropertiesImpl from BaosConnector and
		resetPropertiesImpl from internal knxUsbPort
	*/
	void resetPropertiesImpl() override;

	/*!
		Called from the connector system when a packet for transmission is ready.
		We pack it into a USB HID frame, send it on the bus via the usb connection
		and wait for an confirm.
		If we don't receive a L_DATA_CON, than an LDataConfirmTimeoutException will throw.
	*/
	void txImpl(std::shared_ptr<connector::Packet> packet) override;

	/*!
		Receive thread callback function called from the base class
	*/
	void rxImpl() override;

	void onPacket(std::shared_ptr<kdrive::connector::Packet> packet, int direction);

	void onEvent(unsigned int eventType);

public:
	static const std::string ConnectorTypeLabel;

private:
	boost::signals2::scoped_connection signalConnectionPacket_;
	boost::signals2::scoped_connection signalConnectionEvent_;
	std::unique_ptr<KnxUsbPort> knxUsbPort_;
};

/********************************
** Enumeration
*********************************/

/*!
	\internal
	Use BaosUsbEnumerator instead
*/
void kdriveRPC_baos_API enumerateBaosUsbDevices(std::vector<kdrive::utility::PropertyCollection>& devices);

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_USB_USB_CONNECTOR_H__
