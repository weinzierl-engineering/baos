//
// SerialPort_POSIX.h
//
// $Id: //poco/1.4/IO/Serial/include/Poco/IO/Serial/SerialPort_POSIX.h#2 $
//
// Library: IoT/Serial
// Package: Serial
// Module: SerialPort
//
// Definition of the SerialPortImpl class for POSIX.
//
// Copyright (c) 2009-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//

#ifndef AIC_SerialPort_POSIX_INCLUDED
#define AIC_SerialPort_POSIX_INCLUDED


#include "Poco/Logger.h"
#include "Poco/Timespan.h"
#include <cctype>


// namespace AIC {

namespace kdrive
{
namespace io
{
namespace serial
{

class wzfIOSerial_API SerialPortImpl
	/// This class provides an interface to a POSIX serial interface.
{
public:
	enum FlowControlImpl
	{
	    FLOW_NONE,
	    FLOW_RTSCTS
	};

	SerialPortImpl();
	~SerialPortImpl();

	void openImpl(const std::string& device, int baudRate, const std::string& parameters, FlowControlImpl flowControl);
	void closeImpl();
	bool isOpenImpl() const;

	int pollImpl(char* data, std::size_t size, const Poco::Timespan& timeout);
	int readImpl(char* data, std::size_t size);
	int writeImpl(const char* data, std::size_t size);

private:
	int _fd;
};


//
// inlines
//
inline bool SerialPortImpl::isOpenImpl() const
{
	return _fd != -1;
}


//} //  namespace AIC

}
}
} // end namespace kdrive::io::serial


#endif // AIC_SerialPort_POSIX_INCLUDED
