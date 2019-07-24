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

#ifndef __KDRIVE_FT12_FT12_H__
#define __KDRIVE_FT12_FT12_H__

#include "kdrive/ft12/Config.h"
#include <Poco/Event.h>
#include <atomic>
#include <vector>
#include <functional>

namespace kdrive
{
namespace ft12
{
/*!
	\class FT12
	\brief FT1.2 Protocol Handler
	\sa FT12_Packetizer

	<b>System Specifications:</b>
	\li 03_06_02 03_06_02 Physical External Interface v1.1 AS<br />
		6.4 The default Protocol at PEI-type 10: FT1.2 page 22

	\note: We don't send the ack. We let the packetizer handle this.
	Precondition: when we receive a frame it is valid.
*/
class kdriveFt12_API FT12 final
{
public:
	FT12();
	~FT12() = default;

	/*!
		Protocol Initialisation
		Sends a Reset to the interface and waits for an ack
		This function is synchronous and returns once the ack
		has been received. If the ack fails then it returns false.
	*/
	bool init();

	/*!
		Returns true if the FT1.2 connection is established otherwise false
	*/
	bool isConnectionEstablished() const;

	/*!
		Sends the buffer to the serial port
		The sender function is responsible for its error checking
		On an error it should throw an exception. If the function returns
		it is assumed the send was successful
	*/
	typedef std::function<void (const unsigned char*, std::size_t)> Sender;

	/*!
		Sets the serial port send (tx) function
		This function called internally from the FT12 class
		will send the buffer to the serial port
	*/
	void setSender(Sender sender);

	/*!
		Callback function for the received link user data telegrams
	*/
	typedef std::function<void (const std::vector<unsigned char>&)> UserDataCallback;

	/*!
		Sets the user data callback function
		This is called when a variable length frame with SEND_UDAT is received
		The callback function will contain the user data buffer taken from the ft1.2 frame
		and not the frame itself
		Note: this callback can be called within the Rx Thread context, so the callback
		handler should queue the data and handle it later...
	*/
	void setUserDataCallback(UserDataCallback userDataCallback);

	enum class ResetReason
	{
		ResetInd = 0,
		ServerItemBusStatus
	};

	/*!
		Callback function for the received reset telegrams
	*/
	typedef std::function<void(ResetReason resetReason)> ReceivedResetCallback;

	/*!
		Sets the FT1.2 connection reset callback function
		This is called when a fixed length frame with RESET is received
		Note: this callback can be called within the Rx Thread context, so the callback
		handler should queue the data and handle it later...
	*/
	void setReceivedResetCallback(ReceivedResetCallback receivedResetCallback);

	/*!
		Called from the serial port rx task or handler
		when data is is received on the serial port
		precondition: the ft1.2 frame is a valid frame.
		precondition: the buffer is not null
		precondition: the bufferSize it not 0
	*/
	void onReceive(const unsigned char* buffer, std::size_t bufferSize);

	/*!
		Send a fixed length frame
		uses send(buffer, bufferLength)
	*/
	bool sendFixedLengthFrame(unsigned char functionCode);

	/*!
		Send a variable length frame
		Uses the sender function Sender to send the buffer
		If the sender function is not set an exception is thrown
		If the send function returns anything other than the buffer length
		an exception is thrown.	If a buffer is successfully sent, we wait for the ack
		This function is synchronous and implements the send state
		(i.e. with 3x retry and wait on ack)
		\return true if the frame is send and the ack is received, false if the ack is not received
	*/
	bool sendVariableLengthFrame(const unsigned char* buffer, std::size_t bufferLength);

	/*!
		This sets the exchange timeout period and is defined as
		the time-out for end of exchange in case of SEND/CONFIRM or REQUEST/RESPOND
		ca. 510 bits. Note the baud rate isn't really the gross bit rate and there
		is a function to work it out, but for now, we'll simply assume the baud rate is
		the bit rate. We calculate the timeout in milliseconds by the following:
		timeout = 510 * 1000 / bitsPerSecond (timeout in milliseconds)
		\param bitsPerSecond the expected number of bits per second, i.e. 19200 bps for 19200 baud
	*/
	void setBitsPerSecond(long bitsPerSecond);

private:
	/*!
		\return true if the buffer is a ack character
	*/
	bool isAck(const unsigned char* buffer, std::size_t bufferLength) const;

	/*!
		\return true if the buffer is fixed length frame
	*/
	bool isFixedFrame(const unsigned char* buffer, std::size_t bufferLength) const;

	/*!
		\return true if the buffer is variable length frame
	*/
	bool isVariableFrame(const unsigned char* buffer, std::size_t bufferLength) const;

	/*!
		handling function when a ack character is received from the interface
		we set the ack event to indicate an acknowledgment has been received
		any sending thread blocking on an ack will receive the event and continue
	*/
	void onAckRx();

	/*!
		handling function for fixed length frames
		checks the control field for the function code
		we only handle the reset function code where we reset the fcbs
	*/
	void onFixedFrameRx(const unsigned char* buffer, std::size_t bufferLength);

	/*!
		handling function for variable length frames for user data
		when user data is received the user data callback function is called
		to pass the data on
	*/
	void onVariableFrameRx(const unsigned char* buffer, std::size_t bufferLength);

	/*!
		Waits for an ack frame. This is a blocking wait, and waits for
		at least 150 bits.
		\return true if an ack is received within the timeout period
	*/
	bool waitAck();

	/*!
		Sets both the rx and tx fcb to 0
	*/
	void resetFCBs();

	/*!
		Toggles the Rx fcb
	*/
	void toggleRxFCB();

	/*!
		Toggles the Tx fcb
	*/
	void toggleTxFCB();

	/*!
		Sends a buffer on the serial port
		We use the Sender to actually send the data however
		this function handles send and wait for ack.
		It implements a retry mechanism, limited by repeatLimit_
		\return true if the ack was received
	*/
	bool send(const unsigned char* buffer, std::size_t bufferLength);

private:
	std::atomic<bool> isConnectionEstablished_; /*!< The FT1.2 connection is established*/
	Sender sender_;
	UserDataCallback userDataCallback_;
	ReceivedResetCallback receivedResetCallback_;
	Poco::Event ackEvent_;
	long exchangeTimeout_;
	unsigned char fcbRx_;
	unsigned char fcbTx_;
	static const long exchangeTimeoutBps_;
	static const int repeatLimit_;
};

}
} // end namespace kdrive::ft12

#endif // __KDRIVE_FT12_FT12_H__
