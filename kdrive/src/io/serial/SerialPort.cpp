//
// Copyright (c) 2009-2010, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
//

#include "pch/kdrive_pch.h"
#include "kdrive/io/serial/SerialPort.h"
#include <Poco/Format.h>
#include <Poco/Exception.h>

using Poco::format;


#if defined(_WIN32)
#include "SerialPort_WIN32.cpp"
#else
#include "SerialPort_POSIX.cpp"
#endif


namespace kdrive
{
namespace io
{
namespace serial
{

const std::string SerialPort::LOGGER_NAME("kdrive.io.serial.SerialPort");


SerialPort::SerialPort():
	_logger(Poco::Logger::get(LOGGER_NAME)),
	_buffer(DEFAULT_BUFFER_SIZE),
	_end(_buffer.begin()),
	_cur(_buffer.begin())
{
}


SerialPort::SerialPort(std::size_t bufferSize):
	_logger(Poco::Logger::get(LOGGER_NAME)),
	_buffer(bufferSize),
	_end(_buffer.begin()),
	_cur(_buffer.begin())
{
}


SerialPort::SerialPort(Poco::Logger& logger, std::size_t bufferSize):
	_logger(logger),
	_buffer(bufferSize),
	_end(_buffer.begin()),
	_cur(_buffer.begin())
{
}


SerialPort::SerialPort(const std::string& device, int baudRate, const std::string& parameters, FlowControl flowControl, std::size_t bufferSize):
	_logger(Poco::Logger::get(LOGGER_NAME)),
	_buffer(bufferSize),
	_end(_buffer.begin()),
	_cur(_buffer.begin())
{
	open(device, baudRate, parameters, flowControl);
}


SerialPort::~SerialPort()
{
	close();
}


void SerialPort::open(const std::string& device, int baudRate, const std::string& parameters, FlowControl flowControl)
{
	if (isOpenImpl())
	{
		throw Poco::IllegalStateException("Port is already open", device);
	}
	if (parameters.size() != 3)
	{
		throw Poco::InvalidArgumentException("Parameters string must be three characters long", parameters);
	}

	if (_logger.debug())
	{
		_logger.debug(format("Opening serial port %s, speed %d, parameters %s, flow control %s", device, baudRate, parameters, std::string(flowControl == FLOW_NONE ? "none" : "RTS/CTS")));
	}

	_cur = _end = _buffer.begin();
	openImpl(device, baudRate, parameters, static_cast<FlowControlImpl>(flowControl));
}

bool SerialPort::isOpen() const
{
	return isOpenImpl();
}

void SerialPort::close()
{
	if (isOpenImpl())
	{
		if (_logger.debug())
		{
			_logger.debug("Closing serial port");
		}
		closeImpl();
		_cur = _end = _buffer.begin();
	}
}


bool SerialPort::poll(const Poco::Timespan& timeout)
{
	if (!isOpenImpl())
	{
		throw Poco::IllegalStateException("Port is not open");
	}

	if (available())
	{
		return true;
	}
	else
	{
		_cur = _end = _buffer.begin();
		int n = pollImpl(_cur, _buffer.size(), timeout);
		if (n >= 0)
		{
			_end += n;
			return true;
		}
		else
		{
			return false;
		}
	}
}


std::size_t SerialPort::write(const char* data, std::size_t size)
{
	if (!isOpenImpl())
	{
		throw Poco::IllegalStateException("Port is not open");
	}

	if (_logger.debug())
	{
		_logger.dump(format("Sending %z byte(s)", size), data, size, Poco::Message::PRIO_DEBUG);
	}
	int n = writeImpl(data, size);
	if (n < 0)
	{
		throw Poco::IOException("serial port write error");
	}
	else if (n < static_cast<int>(size))
	{
		throw Poco::IOException(format("short write on serial port: %d of %z bytes", n, size));
	}
	else
	{
		if (txCallback_)
		{
			txCallback_(data, static_cast<std::size_t>(n));
		}

		return static_cast<std::size_t>(n);
	}
}


std::size_t SerialPort::write(const std::string& data)
{
	return write(data.data(), static_cast<int>(data.size()));
}


std::size_t SerialPort::read(char* data, std::size_t size)
{
	if (_cur == _end)
	{
		readBuffer();
	}
	std::size_t n = _end - _cur;
	if (n > size)
	{
		n = size;
	}
	std::memcpy(data, _cur, n);
	_cur += n;
	return n;
}


std::size_t SerialPort::read(char* data, std::size_t size, const Poco::Timespan& timeout)
{
	std::size_t n = 0;
	while (n < size)
	{
		if (available() || poll(timeout))
		{
			std::size_t rd = read(data + n, size - n);
			n += rd;
		}
		else
		{
			break;
		}
	}
	return n;
}


void SerialPort::read(std::string& data)
{
	if (_cur == _end)
	{
		readBuffer();
	}
	data.assign(_cur, _end);
	_cur = _end;
}


int SerialPort::read()
{
	if (_cur == _end)
	{
		readBuffer();
	}
	if (_cur < _end)
	{
		return static_cast<int>(static_cast<unsigned char>(*_cur++));
	}
	else
	{
		return -1;
	}
}

void SerialPort::setRxCallback(DataCallback dataCallback)
{
	rxCallback_ = dataCallback;
}

void SerialPort::setTxCallback(DataCallback dataCallback)
{
	txCallback_ = dataCallback;
}

void SerialPort::readBuffer()
{
	if (!isOpenImpl())
	{
		throw Poco::IllegalStateException("Port is not open");
	}

	_cur = _end = _buffer.begin();
	int n = readImpl(_cur, _buffer.size());
	if (n >= 0)
	{
		_end += n;

		if (rxCallback_)
		{
			rxCallback_(_cur, static_cast<std::size_t>(n));
		}

		if (_logger.debug())
		{
			_logger.dump(format("Received %d byte(s)", n), _cur, n, Poco::Message::PRIO_DEBUG);
		}
	}
	else
	{
		throw Poco::IOException("serial port read error");
	}
}

}
}
} // end namespace kdrive::io::serial
