//
// SerialPort_POSIX.cpp
//
// $Id: //projects/AIC/src/SerialPort_POSIX.cpp#1 $
//
// Copyright (c) 2009-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
//

#include "pch/kdrive_pch.h"
#include "kdrive/io/serial/SerialPort_POSIX.h"
//#include "AIC/SerialPort_POSIX.h"
#include "Poco/Format.h"
#include "Poco/Exception.h"
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>
#include <unistd.h>

/*********************************
 ** Added for low latency
 *********************************/

#ifdef LOW_LATENCY

#include <sys/ioctl.h>
#include <linux/serial.h>

#endif // LOW_LATENCY

/*********************************
 ** Added for low latency
 *********************************/

using Poco::format;


//namespace AIC {

namespace kdrive
{
namespace io
{
namespace serial
{

SerialPortImpl::SerialPortImpl():
	_fd(-1)
{
}


SerialPortImpl::~SerialPortImpl()
{
}


void SerialPortImpl::openImpl(const std::string& device, int baudRate, const std::string& parameters, FlowControlImpl flowControl)
{
	_fd = ::open(device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
	if (_fd == -1)
	{
		throw Poco::IOException("cannot open serial port " + device, strerror(errno));
	}

	int rc = fcntl(_fd, F_SETFL, 0); // FNDELAY for non-blocking
	if (rc == -1)
	{
		throw Poco::IOException("error calling fcntl() on " + device, strerror(errno));
	}

	/*********************************
	 ** Added for low latency
	 *********************************/

#ifdef LOW_LATENCY

	struct serial_struct serial;
	ioctl(_fd, TIOCGSERIAL, &serial);
	serial.flags |= ASYNC_LOW_LATENCY;
	ioctl(_fd, TIOCSSERIAL, &serial);

#endif // LOW_LATENCY

	/*********************************
	 ** Added for low latency
	 *********************************/
	struct termios term;
	rc = tcgetattr(_fd, &term);
	if (rc == -1)
	{
		throw Poco::IOException("cannot get serial port configuration for " + device, strerror(errno));
	}

	term.c_cflag &= ~CSIZE;
	term.c_cflag &= ~PARENB;
	term.c_cflag &= ~PARODD;
	term.c_cflag &= ~CSTOPB;
	term.c_cflag &= ~CRTSCTS;
	term.c_cflag |= CLOCAL;
	term.c_cflag |= CREAD;

	switch (parameters[0])
	{
		case '6':
			term.c_cflag |= CS6;
			break;
		case '7':
			term.c_cflag |= CS7;
			// wz : Fixed only bits were received.
			term.c_iflag |= ISTRIP;
			break;
		case '8':
			term.c_cflag |= CS8;
			break;
		default:
			throw Poco::InvalidArgumentException("invalid character size", parameters);
	}

	switch (parameters[1])
	{
		case 'N':
		case 'n':
			term.c_iflag = IGNPAR;
			break;
		case 'E':
		case 'e':
			term.c_cflag |= PARENB;
			term.c_iflag |= INPCK;
			break;
		case 'o':
		case 'O':
			term.c_cflag |= PARENB | PARODD;
			term.c_iflag |= INPCK;
			break;
		default:
			throw Poco::InvalidArgumentException("invalid parity setting", parameters);
	}

	switch (parameters[2])
	{
		case '1':
			break;
		case '2':
			term.c_cflag |= CSTOPB;
			break;
		default:
			throw Poco::InvalidArgumentException("invalid number of stop bits", parameters);
	}

	switch (flowControl)
	{
		case FLOW_NONE:
			break;
		case FLOW_RTSCTS:
			term.c_cflag |= CRTSCTS;
			break;
	}

	// wz : added off for software flow control
	term.c_iflag &= ~(IXON | IXOFF | IXANY);

	// wz : disable change carriage return in line feed
	term.c_iflag &= ~ICRNL;

	// wz: set timeouts, this is relativly fast...
	// wz: maybe need to add setTimeout function
	term.c_cc[VTIME] = 0;
	term.c_cc[VMIN] = 1;

	term.c_oflag &= ~OPOST;
	term.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	speed_t speed(B0);
	switch (baudRate)
	{
		case     -1:
			break;
		case     50:
			speed =     B50;
			break;
		case     75:
			speed =     B75;
			break;
		case    110:
			speed =    B110;
			break;
		case    134:
			speed =    B134;
			break;
		case    150:
			speed =    B150;
			break;
		case    200:
			speed =    B200;
			break;
		case    300:
			speed =    B300;
			break;
		case    600:
			speed =    B600;
			break;
		case   1200:
			speed =   B1200;
			break;
		case   1800:
			speed =   B1800;
			break;
		case   2400:
			speed =   B2400;
			break;
		case   4800:
			speed =   B4800;
			break;
		case   9600:
			speed =   B9600;
			break;
		case  19200:
			speed =  B19200;
			break;
		case  38400:
			speed =  B38400;
			break;
		case  57600:
			speed =  B57600;
			break;
		case 115200:
			speed = B115200;
			break;
		case 230400:
			speed = B230400;
			break;
		default:
			throw Poco::InvalidArgumentException(format("unsupported serial line speed: %d", baudRate));
	}

	if (baudRate != -1)
	{
		rc = cfsetspeed(&term, speed);
		if (rc == -1)
		{
			throw Poco::IOException("error setting baud rate on serial port " + device, strerror(errno));
		}
	}

	rc = tcflush(_fd, TCIFLUSH);
	if (rc == -1)
	{
		throw Poco::IOException("error flushing serial port " + device, strerror(errno));
	}

	rc = tcsetattr(_fd, TCSANOW, &term);
	if (rc == -1)
	{
		throw Poco::IOException("error configuring serial port " + device, strerror(errno));
	}
}


void SerialPortImpl::closeImpl()
{
	::close(_fd);
	_fd = -1;
}


int SerialPortImpl::pollImpl(char* data, std::size_t size, const Poco::Timespan& timeout)
{
	fd_set fdRead;
	fd_set fdWrite;
	fd_set fdExcept;
	FD_ZERO(&fdRead);
	FD_ZERO(&fdWrite);
	FD_ZERO(&fdExcept);
	FD_SET(_fd, &fdRead);
	Poco::Timespan remainingTime(timeout);
	int rc;
	do
	{
		struct timeval tv;
		tv.tv_sec  = (long) remainingTime.totalSeconds();
		tv.tv_usec = (long) remainingTime.useconds();
		Poco::Timestamp start;
		rc = ::select(_fd + 1, &fdRead, &fdWrite, &fdExcept, &tv);
		if (rc < 0 && errno == EINTR)
		{
			Poco::Timestamp end;
			Poco::Timespan waited = end - start;
			if (waited < remainingTime)
			{
				remainingTime -= waited;
			}
			else
			{
				remainingTime = 0;
			}
		}
	}
	while (rc < 0 && errno == EINTR);
	if (rc < 0)
	{
		throw Poco::IOException("serial port poll error", strerror(errno));
	}
	return rc > 0 ? 0 : -1;
}


int SerialPortImpl::writeImpl(const char* buffer, std::size_t size)
{
	return ::write(_fd, buffer, size);
}


int SerialPortImpl::readImpl(char* buffer, std::size_t size)
{
	return ::read(_fd, buffer, size);
}


//} // namespace AIC
}
}
} // end namespace kdrive::io::serial
