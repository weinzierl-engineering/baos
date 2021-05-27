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

#ifndef __KDRIVE_FT12_FT12_PACKETIZER_H__
#define __KDRIVE_FT12_FT12_PACKETIZER_H__

#include "kdrive/ft12/Config.h"
#include <Poco/Semaphore.h>
#include <cstddef>

namespace kdrive
{
namespace io
{
namespace serial
{

class SerialPort;

}
}
} // end namespace kdrive::io::serial

namespace kdrive
{
namespace ft12
{

/*!
	\class FT12_Packetizer
	\brief FT1.2 Frame Packetizer for rx frames
	\sa FT12

	The FT12_Packetizer reads bytes from the serial port
	and tries to receive a complete frame. There are 3 frame types:
	ack, fixed and variable.

	The get function reads a single byte and if it matches the start
	byte of any of the three frames it attempts to read a packet.
	If it doesn't match the start byte it returns false.
	The get function should be called continuously from an rx thread
	to try to receive frames. If a frame is recognised the get function
	will return the number of bytes read (the number of bytes in the frame)
	otherwise it will return 0.

	The FT12_Packetizer can be configured to auto-ack the received frame,
	which is the default implementation.
*/
class kdriveFt12_API FT12_Packetizer
{
public:
	/*!
		Creates a ft1.2 packetizer with a serial port and timeout value
		used within the get function.
	*/
	FT12_Packetizer(kdrive::io::serial::SerialPort& serialPort, long timeout);

	/*!
		Destroys the packetizer
	*/
	~FT12_Packetizer();

	/*!
		Copy constructor has been disabled
	*/
	FT12_Packetizer(const FT12_Packetizer&) = delete;

	/*!
		Assignment operator has been disabled
	*/
	FT12_Packetizer& operator=(const FT12_Packetizer&) = delete;

	/*!
		Reads from the serial port and attempts to return a complete
		FT1.2 frame. Note the frame may or may not be valid, that is,
		the checksums are not checked, end bytes are not checked, etc
		For a variable length frame the two length bytes however are
		checked to ensure they are equal.
		This function uses the serial port poll function with the timeout
		specified in the constructor.
		\return the length of the frame if one has been received, 0 otherwise
	*/
	std::size_t get(unsigned char* buffer, std::size_t bufferSize);

	/*!
		Sends a buffer out on the serial port.
		This is used by the FT1.2 protocol to send both local device management
		and user telegrams. They get wrapped in a variable length FT1.2 frame.
	*/
	void sendBuffer(const unsigned char* buffer, std::size_t bufferSize);

	/*!
		Enables the auto-acknowledgment mechanism.
		If enabled the packetizer will send an ack as soon as it recognises
		a fixed or variable length frame.
	 */
	void enableAutoAck(bool enabled);

private:
	/*!
		Attempts to read bytesToRead bytes from the serial port into the buffer.
		The caller must ensure that the buffer is big enough for bytesToRead bytes
		the timeout is an internal timeout and specifies the inter-character
		timeout we expect between bytes of a frame. This is not the timeout
		value specified in the constructor, which is the inter-frame timeout.
	*/
	std::size_t readBytes(char* buffer, std::size_t bytesToRead, long timeout);

	/*!
		Attempts to read any of the three FT1.2 frame types
		\return the frame size if a frame is received, 0 otherwise
	*/
	std::size_t readFrame(unsigned char* buffer, std::size_t bufferSize);

	/*!
		Attempts to read a fixed frame given that we have already received
		a fixed frame start byte
	*/
	std::size_t readFixedFrame(unsigned char* buffer, std::size_t bufferSize);

	/*!
		Attempts to read a variable frame given that we have already received
		a variable frame start byte
	*/
	std::size_t readVariableFrame(unsigned char* buffer, std::size_t bufferSize);

	/*!
		If auto-ack is enabled sendAck will send an acknowledge frame
	 */
	void sendAck();

private:
	kdrive::io::serial::SerialPort& serialPort_; /*!< the serial port reference */
	Poco::Semaphore semaphore_;
	const long timeout_; /*!< the inter-frame timeout specified in the constructor */
	bool autoAck_;
};

}
} // end namespace kdrive::ft12

#endif // __KDRIVE_FT12_FT12_PACKETIZER_H__
