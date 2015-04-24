//
// SerialPort_WIN32.cpp
//
// $Id: //projects/AIC/src/SerialPort_WIN32.cpp#3 $
//
// Copyright (c) 2009-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
//

#include "pch/kdrive_pch.h"
#include "kdrive/io/serial/SerialPort_WIN32.h"
#include "Poco/Format.h"
#include "Poco/UnicodeConverter.h"
#include "Poco/Exception.h"

using Poco::format;

/***********************************
** Anonymous namespace
************************************/

namespace
{

std::string getDevicePath(const std::string& device)
{
	std::string devicePath = device;

#ifdef _WIN32_WCE
	if (devicePath[device.size() - 1] != ':')
	{
		devicePath += ':';
	}
#else
	if (devicePath.substr(0, 4) != "\\\\.\\")
	{
		devicePath.insert(0, "\\\\.\\");
	}
#endif

	return devicePath;
}

/*!
	Returns the error message from a system error.
	This functions returns the message in the system language e.g. English or German.
*/
std::string getSystemErrorString(DWORD errorCode)
{
	LPVOID buffer;
	const DWORD bufferLength = FormatMessageA(
	                               FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
	                               NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&buffer, 0, NULL);

	// FormatMessageA failed
	if (!bufferLength)
	{
		return format("Unknown (%d)", static_cast<int>(errorCode));
	}

	LPCSTR msgStr = (LPCSTR)buffer;
	const std::string errorMessage(msgStr, msgStr+bufferLength);
	LocalFree(buffer);
	return errorMessage;
}

/*!
	Returns the error message from a system error.
	We try to translate the error mesaage to english.
	If not known than use the error mesage from the windows system.
	(disadvantage: it used the system language)
*/
std::string getErrorString(DWORD errorCode)
{
	switch (errorCode)
	{
		case ERROR_FILE_NOT_FOUND:
			return "The system cannot find the file specified";
		case ERROR_PATH_NOT_FOUND:
			return "The system cannot find the path specified";
		case ERROR_ACCESS_DENIED:
			return "Access is denied";
		case ERROR_INVALID_HANDLE:
			return "The handle is invalid";
		case ERROR_SHARING_VIOLATION:
			return "The process cannot access the file because it is being used by another process";
		case ERROR_LOCK_VIOLATION:
			return "The process cannot access the file because another process has locked a portion of the file";
		case ERROR_INVALID_PARAMETER:
			return "The parameter is incorrect";
		default:
			return getSystemErrorString(errorCode);
	}
}

} // end anonymous namespace


namespace kdrive
{
namespace io
{
namespace serial
{

SerialPortImpl::SerialPortImpl():
	_handle(INVALID_HANDLE_VALUE)
{
}


SerialPortImpl::~SerialPortImpl()
{
}

void SerialPortImpl::openImpl(const std::string& device, int baudRate, const std::string& parameters, FlowControlImpl flowControl)
{
	if (device.empty())
	{
		throw Poco::InvalidArgumentException("no device specified");
	}

	const std::string devicePath = getDevicePath(device);

#ifdef UNICODE
	std::wstring wdevicePath;
	Poco::UnicodeConverter::toUTF16(devicePath, wdevicePath);
	_handle = CreateFileW(wdevicePath.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
#else
	_handle = CreateFileA(devicePath.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
#endif

	if (_handle == INVALID_HANDLE_VALUE)
	{
		const DWORD lastError = GetLastError();
		const std::string errorString = getErrorString(lastError);
		throw Poco::IOException(format("cannot open serial port %s:\n%s", device, errorString));
	}

	DCB dcb = {0};
	dcb.DCBlength = sizeof(dcb);
	if (!GetCommState(_handle, &dcb))
	{
		const DWORD lastError = GetLastError();
		const std::string errorString = getErrorString(lastError);
		throw Poco::IOException(format("cannot get serial port configuration for %s:\n%s",
		                               device, errorString));
	}

	switch (parameters[0])
	{
		case '5':
			dcb.ByteSize = 5;
			break;
		case '6':
			dcb.ByteSize = 6;
			break;
		case '7':
			dcb.ByteSize = 7;
			break;
		case '8':
			dcb.ByteSize = 8;
			break;
		default:
			throw Poco::InvalidArgumentException("invalid character size", parameters);
	}

	switch (parameters[1])
	{
		case 'N':
		case 'n':
			dcb.Parity = NOPARITY;
			break;
		case 'E':
		case 'e':
			dcb.Parity = EVENPARITY;
			break;
		case 'o':
		case 'O':
			dcb.Parity = ODDPARITY;
			break;
		case 'm':
		case 'M':
			dcb.Parity = MARKPARITY;
			break;
		case 's':
		case 'S':
			dcb.Parity = SPACEPARITY;
			break;
		default:
			throw Poco::InvalidArgumentException("invalid parity setting", parameters);
	}

	switch (parameters[2])
	{
		case '1':
			dcb.StopBits = ONESTOPBIT;
			break;
		case '2':
			dcb.StopBits = TWOSTOPBITS;
			break;
		case '5':
			dcb.StopBits = ONE5STOPBITS;
			break;
		default:
			throw Poco::InvalidArgumentException("invalid number of stop bits", parameters);
	}

	switch (flowControl)
	{
		case FLOW_NONE:
			dcb.fOutxCtsFlow = FALSE;
			dcb.fOutxDsrFlow = FALSE;
			dcb.fOutX        = FALSE;
			dcb.fInX         = FALSE;
			dcb.fRtsControl  = RTS_CONTROL_DISABLE;
			break;
		case FLOW_RTSCTS:
			dcb.fOutxCtsFlow = TRUE;
			dcb.fOutxDsrFlow = TRUE;
			dcb.fOutX        = FALSE;
			dcb.fInX         = FALSE;
			dcb.fRtsControl  = RTS_CONTROL_HANDSHAKE;
			break;
	}

	DWORD speed = dcb.BaudRate;
	switch (baudRate)
	{
		case     -1:
			break;
		case    110:
			speed =    CBR_110;
			break;
		case    300:
			speed =    CBR_300;
			break;
		case    600:
			speed =    CBR_600;
			break;
		case   1200:
			speed =   CBR_1200;
			break;
		case   2400:
			speed =   CBR_2400;
			break;
		case   4800:
			speed =   CBR_4800;
			break;
		case   9600:
			speed =   CBR_9600;
			break;
		case  14400:
			speed =  CBR_14400;
			break;
		case  19200:
			speed =  CBR_19200;
			break;
		case  38400:
			speed =  CBR_38400;
			break;
		case  57600:
			speed =  CBR_57600;
			break;
		case 115200:
			speed = CBR_115200;
			break;
		case 128000:
			speed = CBR_128000;
			break;
		case 256000:
			speed = CBR_256000;
			break;
		default:
			// custom baudrate
			// We get ERROR_INVALID_PARAMETER from SetCommState if the settings is not supported.
			speed = baudRate;
	}
	dcb.BaudRate = speed;
	if (!SetCommState(_handle, &dcb))
	{
		const DWORD lastError = GetLastError();
		const std::string errorString = getErrorString(lastError);
		throw Poco::IOException(format("error setting serial port parameters on serial port %s:\n%s",
		                               device, errorString));
	}

	COMMTIMEOUTS cto;
	cto.ReadIntervalTimeout         = CHARACTER_TIMEOUT;
	cto.ReadTotalTimeoutConstant    = MAXDWORD;
	cto.ReadTotalTimeoutMultiplier  = 0;
	cto.WriteTotalTimeoutConstant   = MAXDWORD;
	cto.WriteTotalTimeoutMultiplier = 0;
	if (!SetCommTimeouts(_handle, &cto))
	{
		throw Poco::IOException("error setting serial port timeouts on serial port " + device);
	}
}


void SerialPortImpl::closeImpl()
{
	CloseHandle(_handle);
	_handle = INVALID_HANDLE_VALUE;
}


int SerialPortImpl::pollImpl(char* buffer, std::size_t size, const Poco::Timespan& timeout)
{
	COMMTIMEOUTS prevCTO;
	if (!GetCommTimeouts(_handle, &prevCTO))
	{
		throw Poco::IOException("error getting serial port timeouts");
	}

	COMMTIMEOUTS cto;
	cto.ReadIntervalTimeout         = CHARACTER_TIMEOUT;
	cto.ReadTotalTimeoutConstant    = static_cast<DWORD>(timeout.totalMilliseconds());
	cto.ReadTotalTimeoutMultiplier  = 0;
	cto.WriteTotalTimeoutConstant   = MAXDWORD;
	cto.WriteTotalTimeoutMultiplier = 0;
	if (!SetCommTimeouts(_handle, &cto))
	{
		throw Poco::IOException("error setting serial port timeouts on serial port");
	}

	try
	{
		DWORD bytesRead = 0;
		if (!ReadFile(_handle, buffer, size, &bytesRead, NULL))
		{
			throw Poco::IOException("failed to read from serial port");
		}
		SetCommTimeouts(_handle, &prevCTO);
		return (bytesRead == 0) ? -1 : bytesRead;
	}
	catch (...)
	{
		SetCommTimeouts(_handle, &prevCTO);
		throw;
	}
}


int SerialPortImpl::writeImpl(const char* buffer, std::size_t size)
{
	DWORD bytesWritten = 0;
	if (!WriteFile(_handle, buffer, size, &bytesWritten, NULL))
	{
		return -1;
	}
	return bytesWritten;
}


int SerialPortImpl::readImpl(char* buffer, std::size_t size)
{
	DWORD bytesRead = 0;
	if (!ReadFile(_handle, buffer, size, &bytesRead, NULL))
	{
		return -1;
	}
	return bytesRead;
}


}
}
} // end namespace kdrive::io::serial
