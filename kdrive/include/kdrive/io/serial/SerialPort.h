//
// SerialPort.h
//
// $Id: //poco/1.4/IO/Serial/include/Poco/IO/Serial/SerialPort.h#2 $
//
// Library: IoT/Serial
// Package: Serial
// Module: SerialPort
//
// Definition of the SerialPort class.
//
// Copyright (c) 2009-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//

#ifndef __KDRIVE_IO_SERIAL_SERIALPORT_H__
#define __KDRIVE_IO_SERIAL_SERIALPORT_H__

#include "kdrive/io/serial/Config.h"
#include "Poco/Logger.h"
#include "Poco/Timespan.h"
#include "Poco/Buffer.h"
#include <cctype>

#if defined(_WIN32)
#include "SerialPort_WIN32.h"
#else
#include "SerialPort_POSIX.h"
#endif

namespace kdrive
{
namespace io
{
namespace serial
{

/*!
	This class provides an interface to a serial port.
*/
class wzfIOSerial_API SerialPort : private SerialPortImpl
{
public:
	enum FlowControl
	{
		FLOW_NONE,   /*!< No flow control */
		FLOW_RTSCTS  /*!< Hardware (RTS/CTS) flow control */
	};

	enum
	{
		DEFAULT_BUFFER_SIZE = 4096 /*!< Default size for the internal buffer. */
	};

	/*!
		Creates the SerialPort.
	*/
	SerialPort();

	/*!
		Creates the SerialPort, using the given buffer size.
	*/
	explicit SerialPort(std::size_t bufferSize);

	/*!
		Creates the SerialPort, using the given logger and buffer size.
	*/
	SerialPort(Poco::Logger& logger, std::size_t bufferSize = DEFAULT_BUFFER_SIZE);

	/*!
		Creates and opens the SerialPort, using the given parameters.

		See open() for a description of the parameters.
	*/
	SerialPort(const std::string& device, int baudRate = -1, const std::string& parameters = "8N1",
	           FlowControl flowControl = FLOW_NONE, std::size_t bufferSize = DEFAULT_BUFFER_SIZE);

	/*!
		Closes, if necessary, and destroys the SerialPort.
	*/
	~SerialPort();

	/*!
		Opens the port.

		Device sets the serial port device file name and is usually
		something like "/dev/ttyS0", "/dev/ttyUSB0",
		"/dev/tty.usbserial-XXX" or "COM1".

		Baud rate must be one of the following:
		50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400,
		4800, 9600, 19200, 38400, 57600, 115200 or 230400.

		Specify -1 for baudRate to use the currently configured speed.
		Note that not all platforms support all baud rates.

		To specify character size, parity and stop bits, use the
		parameters argument. The parameters argument must be a three
		character string. The first character specifies the serial line
		character width in bits (5, 6, 7 or 8). The second char specifies
		the parity (N for none, E for even, O for odd) and the third
		character specifies the number of stop bits (1 or 2).
		Example: "8N1" for 8 bit characters, no parity, 1 stop bit.

		The flowControl argument can be used to enable or disable
		hardware (CTS/RTS) flow control.
	*/
	void open(const std::string& device, int baudRate = -1, const std::string& parameters = "8N1",
	          FlowControl flowControl = FLOW_NONE);

	/*!
		Returns true if the serial port is opened.
	*/
	bool isOpen() const;

	/*!
		Closes the serial port.
	*/
	void close();

	/*!
		Waits for data to arrive at the port.

		Returns true immediately if data is already in
		the internal buffer, or if data arrives during the
		specified time interval, otherwise false.
	*/
	bool poll(const Poco::Timespan& timeout);

	/*!
		Writes the given data to the port.
		Returns the number of characters written.

		Throws a Poco::IOException if an error occurs.
	*/
	std::size_t write(const std::string& data);

	/*!
		Writes the given data to the port.
		Returns the number of characters written.

		Throws a Poco::IOException if an error occurs.
	*/
	std::size_t write(const char* data, std::size_t size);

	/*!
		Reads up to size characters from the port (or
		internal buffer) and places them in the given buffer.
		If the internal buffer is empty, blocks until data
		arrives at the port.

		Returns the number of characters read.

		Throws a Poco::IOException if an error occurs.
	*/
	std::size_t read(char* data, std::size_t size);

	/*!
		Attempts to read exactly size characters from
		the port. May read less than the requested number
		of characters if the given timeout is exceeded.

		Returns the number of characters read.

		Note: the given timeout is not an absolute timeout, but a timeout
		between blocks of data received. For example, if the timeout
		is 10 seconds, 10 characters are requested, and a character
		appears every 5 seconds, total time for reading will be about 50
		seconds.

		Throws a Poco::IOException if an error occurs.
	*/
	std::size_t read(char* data, std::size_t size, const Poco::Timespan& timeout);

	/*!
		Reads what's currently available from the serial port
		or internal buffer and returns it in data.

		If the internal buffer is empty, blocks until data
		arrives at the port.
	*/
	void read(std::string& data);

	/*!
		Reads a single character from the port.

		If the internal buffer is empty, blocks until data
		arrives at the port.
	*/
	int read();

	/*!
		Returns the number of characters available from
		the internal buffer.
	*/
	std::size_t available() const;

protected:
	void readBuffer();

	static const std::string LOGGER_NAME;

private:
	Poco::Logger& _logger;
	Poco::Buffer<char> _buffer;
	char* _end;
	char* _cur;
};


//
// inlines
//
inline std::size_t SerialPort::available() const
{
	return static_cast<std::size_t>(_end - _cur);
}

}
}
} // end namespace kdrive::io::serial

#endif // __KDRIVE_IO_SERIAL_SERIALPORT_H__
