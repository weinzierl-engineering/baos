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

#ifndef __KDRIVE_BAOS_FT12_FT12_CONNECTOR_H__
#define __KDRIVE_BAOS_FT12_FT12_CONNECTOR_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/BaosConnector.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/ft12/FT12.h"
#include "kdrive/ft12/FT12Packetizer.h"
#include "kdrive/io/serial/SerialPort.h"
#include <boost/signals2.hpp>
#include <vector>

namespace kdrive
{
namespace baos
{

/*!
	\class FT12Connector
	\brief The FT12Connector is responsible for creating
	a Serial FT 1.2 connection with the baos server

	This class supports BAOS protocol version 1.0 and 2.0.

	Devices with protocol version 1:
	- KNX BAOS Module 820
	- KNX BAOS Module 822
	- KNX Serial BAOS 870

	Devices with protocol version 2:
	- KNX BAOS Module 830
*/

class kdriveRPC_baos_API FT12Connector : public BaosConnector
{
public:
	typedef std::shared_ptr<FT12Connector> Ptr;

	/*!
		Creates a default (disconnected) FT 1.2 baos connector
	*/
	FT12Connector();

	/*!
		Closes the connections and destroys the connector
	*/
	virtual ~FT12Connector();

	/*!
		Opens a connection with the local device
		using the SerialDeviceName property as the device name
	*/
	using BaosConnector::open;

	/*!
		Opens a connection with the local device
		\param serialDeviceName is the platform specific device name, e.g. COM1 or /dev/ttyS0
	*/
	void open(const std::string& serialDeviceName);

	/*!
		Returns a formatted port description.
		Format: <SerialDeviceName>
		e.g. COM1
	*/
	std::string getDescription() override;

	/*!
		Returns the serial device name used to open the serial port
	*/
	std::string getSerialDeviceName() const;

	/*!
		Enable or disable allow of offline (unpowered) FT1.2 connection
	*/
	void setAllowOfflineConnection(bool enable);

	/*!
		Returns true, if offline (unpowered) FT1.2 connection is allowed. Otherwise false.
		Default: false
		\see setAllowDisconnectedFt12
	*/
	bool isAllowOfflineConnectionEnabled() const;

public:
	static const std::string ConnectorTypeLabel;
	static const std::string SerialDeviceName; /*!< Property key for the serial device name e.g. COM1 */
	static const std::string AllowOfflineConnection; /*!< Property Key for open connection also when ft12 connection not exist */

private:
	/*!
		Request to open the port from the base class.
		Opens the serial port, starts the receive thread
		and initialises the FT1.2 protocol
		precondition: the port is not already open
	*/
	void openImpl() override;

	/*!
		Closes the serial port
		precondition: the serial port is open
	*/
	void closeImpl() override;

	/*!
		\return true if the serial port is open, false otherwise
	*/
	bool isOpenImpl() const override;

	/*!
		Calls resetPropertiesImpl from BaosConnector and
		readded following properties with default values:
		- FT12Connector::PortType: FT12Connector::ConnectorTypeLabel
		- KnxSerialDeviceName: ""
	*/
	void resetPropertiesImpl() override;

	/*!
		Called from the connector system when a packet for transmission is ready.
		If the telegram is in cEMI format and our protocol is EMI1 or EMI2" we convert it.
		Once the conversion is done (if required) we pack it into a FT1.2 variable length frame,
		send it on the serial port and wait for an ack. The FT1.2 protocol
		is handled by ft12_, we just give it the raw buffer.
		note: we route the original packet (cEmi-Format) and not the converted format
	*/
	void txImpl(std::shared_ptr<connector::Packet> packet) override;

	/*!
		Receive thread callback function called from the base class
		We used the FT1.2 Packetizer to read from the serial port
		and obtain a frame. If a frame is received we pass it to the
		FT1.2 protocol handler.
	*/
	void rxImpl() override;

	/*!
		Called from the FT1.2 protocol when a user data variable length frame
		is received.
	*/
	void onTelegramInd(const std::vector<unsigned char>& buffer);

	/*!
		Called when a FT1.2 Reset (or BAOS ServerItem: Bus Connected) received
	*/
	void onResetReceived(kdrive::ft12::FT12::ResetReason resetReason);

	/*!
		Event Notification callback handler
		This function is called when we receive a event notification.
		When we receive a TransportReset event we simply try to read 
		the device properties
	*/
	void onEvent(unsigned long e);

private:
	kdrive::io::serial::SerialPort serialPort_;
	std::vector<unsigned char> txBuffer_;
	std::vector<unsigned char> rxBuffer_;
	kdrive::ft12::FT12 ft12_;
	kdrive::ft12::FT12_Packetizer packetizer_;
	boost::signals2::scoped_connection signalConnectionEvent_; /*!< Signal connection for event signal. */
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_FT12_FT12_CONNECTOR_H__
