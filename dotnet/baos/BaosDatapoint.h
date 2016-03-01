//
// Copyright (c) 2002-2016 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//

#pragma once

#include "kdriveManagedConfig.h"
#include "Connector.h"
#include <kdrive/baos/BaosDatapoint.h>

namespace unmanaged
{
typedef kdrive::baos::BaosDatapoint BaosDatapoint;
typedef kdrive::baos::ServerItem ServerItem;
}

namespace kdrive
{
namespace baos
{
namespace bindings
{

/// <summary>
/// The BAOS device holds the datapoint as a byte array
///	(between 1 and 14 bytes) and the BaosDatapoint class
///	provides conversion routines from this raw byte stream
///	to typed values, such as Boolean, 8 Bit Signed, 2 Octet Unsigned etc.
/// <remarks>
///	Internally it uses the BaosDatapointDescription to ensure that
///	the conversion is type safe, that is, it compares the
///	length of the datapoint value in the description with the
///	length of the requested type and if these lengths do not
///	match an exception will be raised. Note: it is possible to
///	convert to/from types of the same length. i.e. if the datapoint
///	value length is 2 bytes all the 2 octet conversion functions
///	will be valid. We've included standard basic datapoint types
///	from the specification however this is still a subset of the C++ API,
///	which includes the datapoint types like Status With Mode, Date, Time
///	and Access for example. The Datapoint is associated with a
///	specific id, which should be configured in the ETS project.
///	Currently the BAOS protocol supports an id range from 1 to 255.
/// </remarks>
/// </summary>
public ref class BaosDatapoint
{
public:

	/// <summary>
	/// Constructor. This is the standard constructor you will use to
	///	create a BaosDatapoint class.
	/// </summary>
	/// <remarks>
	/// You pass in the Connector class
	///	and the associated Data point Value id. This id should correspond
	///	to the id configured in the ETS project and is associated
	///	with a specific Group Value Address.
	/// </remarks>
	/// <param name="connector">The connector.</param>
	/// <param name="id">The data point id.</param>
	BaosDatapoint(Connector^ connector, unsigned short id)

		: connector_(connector),
		  datapoint_(0)
	{
		try
		{
			datapoint_ = new unmanaged::BaosDatapoint(connector->getUnmanaged(), id);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	/// Constructor. This constructor is called from within the
	///	library when a Data point Value Indication is received.
	/// </summary>
	/// <remarks>
	///	It contains the data point value data. You won’t need
	///	to use this and can safely ignore it.
	/// </remarks>
	/// <param name="connector">The connector.</param>
	/// <param name="id">The data point id.</param>
	/// <param name="serviceData">The service data.</param>
	/// <param name="data">The data.</param>
	BaosDatapoint(Connector^ connector, unsigned short id, unsigned char serviceData, array<unsigned char>^ data)

		: connector_(connector),
		  datapoint_(0)
	{
		try
		{
			pin_ptr<unsigned char> pp = &data[0];
			const unsigned char* begin = pp;
			std::vector<unsigned char> v(begin, begin + data->Length);

			unmanaged::ServerItem serverItem;
			serverItem.id = id;
			serverItem.serviceData = serviceData;
			serverItem.length = v.size();
			serverItem.data = v;

			datapoint_ = new unmanaged::BaosDatapoint(connector->getUnmanaged(), serverItem);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	/// Destructor cleans up unmanaged and managed resources.
	/// </summary>
	~BaosDatapoint()
	{
		// to avoid code duplication
		// call finalizer to release unmanaged resources
		this->!BaosDatapoint();
	}

	/// <summary>
	/// Sets the Data point id. 
	/// </summary>
	/// <remarks>
	/// You can use this when you
	///	need to dynamically change the id that this Datapoint
	///	object refers to in the remote BAOS device. For example,
	///	if you have several data points all of the same type
	///	(a Boolean type for example) with contiguous ids you can
	///	iterate over the ids and set their corresponding values
	///	on the remove device using the one BaosDatapoint object.
	/// </remarks>
	/// <param name="id">The data point id.</param>
	void setId(unsigned char id)
	{
		try
		{
			datapoint_->setId(id);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	/// Gets the datapoint id.
	/// </summary>
	/// <returns>The data point id.</returns>
	unsigned short getId()
	{
		try
		{
			return datapoint_->getId();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	/// Sets the command.
	/// </summary>
	/// <remarks>
	/// When a data point value is set on the remote device
	///	it is accompanied by a command. This command defaults to:
	///	Sets new value and send on bus. If you need to change the
	///	command you can do so with this function. The list of
	///	commands can be found in the protocol specification on page 19.
	///	Otherwise you can safely ignore these functions.
	/// </remarks>
	/// <param name="command">The command.</param>
	void setCommand(unsigned char command)
	{
		try
		{
			datapoint_->setCommand(command);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	/// Gets the command.
	/// </summary>
	/// <returns>The command</returns>
	unsigned char getCommand()
	{
		try
		{
			return datapoint_->getCommand();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	/// Requests a read value from the bus for this data point.
	/// </summary>
	/// <remarks>
	///	This uses the set data point value service with command set to
	///	ReadNewValueViaBus (just for this call) and this function has
	///	no lasting effect on the value of the command.
	/// </remarks>
	void readNewValueViaBus()
	{
		try
		{
			datapoint_->readNewValueViaBus();
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	/// Requests that the transmission state is cleared.
	/// Like readNewValueViaBus it has no lasting effect on the command
	/// </summary>
	void clearTransmissionState()
	{
		try
		{
			datapoint_->clearTransmissionState();
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	/// Sets the value of the data point on the remote BAOS device
	/// associated with the current id.
	/// </summary>
	/// <remarks>
	/// This function also sends
	/// the command byte, which can be configured with setCommand
	/// (see setCommand for more information). Note: the length of
	/// data should correspond to the data point value length configured
	/// in the ETS project. Although you can use the command directly
	/// it is preferable to use the specific type conversion functions
	/// such as setBoolean, set8BitUnsigned etc. You should only really
	/// ever need to use this function if a conversion function is
	/// not available. Note: the data should be encoded as Big Endian.
	/// </remarks>
	/// <param name="data">The data.</param>
	void setData(array<unsigned char>^ data)
	{
		try
		{
			pin_ptr<unsigned char> pp = &data[0];
			const unsigned char* begin = pp;
			std::vector<unsigned char> v(begin, begin + data->Length);
			datapoint_->setData(v);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	/// Reads the value of the data point on the remote BAOS device
	/// associated with the current id. 
	/// </summary>
	/// <remarks>
	/// It returns the raw Big Endian
	/// encoded byte stream. The data point values which are less than
	/// 1 byte (Boolean etc) are encoded as outlined in the BAOS protocol specification.
	/// It is preferable to use the specific type conversion functions to get the data.
	/// </remarks>
	array<unsigned char>^ getData()
	{
		try
		{
			const std::vector<unsigned char>& data = datapoint_->getData();
			return interop::ArrayCreator::Copy(&data[0], data.size());
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Clears the internal data.
	/// </summary>
	/// <remarks>
	/// If the cache is enabled this will empty the
	///	data cache, so the next read will read from the BAOS device, and not
	///	from the cache.
	/// </remarks>
	void clearData()
	{
		try
		{
			datapoint_->clearData();
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	/// Returns true: Object has already been received
	/// Returns false: Object value is unknown
	/// </summary>
	bool isValidFlag()
	{
		try
		{
			return datapoint_->isValidFlag();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Returns true: Value is updated from the bus
	///	Returns false: Value was not updated
	/// </summary>
	bool isUpdate()
	{
		try
		{
			return datapoint_->isUpdate();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Returns true: Data request
	///	Returns false: Idle/response
	/// </summary>
	bool isDataRequest()
	{
		try
		{
			return datapoint_->isDataRequest();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	/// Transmission status values
	/// </summary>
	enum class TransmissionStatus
	{
	    TransmissionIdleOk = unmanaged::BaosDatapoint::TransmissionIdleOk,
	    TransmissionIdleError = unmanaged::BaosDatapoint::TransmissionIdleError,
	    TransmissionInProgress = unmanaged::BaosDatapoint::TransmissionInProgress,
	    TransmissionRequest  = unmanaged::BaosDatapoint::TransmissionRequest
	};

	/// <summary>
	///	Returns one of the following transmission status values:
	///	TransmissionIdleOk
	///	TransmissionIdleError
	///	TransmissionInProgress
	///	TransmissionRequest
	/// </summary>
	int getTransmissionStatus()
	{
		try
		{
			return datapoint_->getTransmissionStatus();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Get the Description String associated with the data point
	/// </summary>
	System::String^ getDescription()
	{
		try
		{
			const std::string& description = datapoint_->getDescriptionString();
			System::String^ s = gcnew System::String(description.c_str());
			return s;
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	/// Enable the data cache
	/// </summary>
	void enableCache(bool cacheEnabled)
	{
		try
		{
			datapoint_->enableCache(cacheEnabled);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Disable the cache
	/// </summary>
	void disableCache()
	{
		try
		{
			datapoint_->disableCache();
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/***********************************
	** The following functions read a byte
	** stream from the remove BAOS device
	** and convert it to the requested type.
	************************************/

	/// <summary>
	/// Set Datapoint DPT-1
	/// </summary>
	/// <param name="value">The bool value.</param>
	void setBoolean(bool value)
	{
		try
		{
			datapoint_->setBoolean(value);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets Datapoint DPT-1
	/// </summary>
	bool getBoolean()
	{
		try
		{
			return datapoint_->getBoolean();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Sets Datapoint DPT-2
	/// </summary>
	void set1BitControl(bool control, bool value)
	{
		try
		{
			datapoint_->set1BitControl(control, value);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets Datapoint DPT-2 (control)
	/// </summary>
	bool get1BitControl()
	{
		try
		{
			return datapoint_->get1BitControl();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets Datapoint DPT-2 (value)
	/// </summary>
	bool get1BitControlValue()
	{
		try
		{
			return datapoint_->get1BitControlValue();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Sets Datapoint DPT-3
	/// </summary>
	void set3BitControl(bool control, unsigned char value)
	{
		try
		{
			datapoint_->set3BitControl(control, value);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets Datapoint DPT-3 (control)
	/// </summary>
	bool get3BitControl()
	{
		try
		{
			return datapoint_->get3BitControl();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets Datapoint DPT-3 (value)
	/// </summary>
	unsigned char get3BitControlValue()
	{
		try
		{
			return datapoint_->get3BitControlValue();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Sets Datapoint DPT-4
	/// </summary>
	void setCharacterSet(unsigned char value)
	{
		try
		{
			datapoint_->setCharacterSet(value);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets Datapoint DPT-4
	/// </summary>
	unsigned char getCharacterSet()
	{
		try
		{
			return datapoint_->getCharacterSet();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Sets Datapoint DPT-5
	/// </summary>
	void set8BitUnsigned(unsigned char value)
	{
		try
		{
			datapoint_->set8BitUnsigned(value);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets Datapoint DPT-5
	/// </summary>
	unsigned char get8BitUnsigned()
	{
		try
		{
			return datapoint_->get8BitUnsigned();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Sets Datapoint DPT-6
	/// </summary>
	void set8BitSigned(char value)
	{
		try
		{
			datapoint_->set8BitSigned(value);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets Datapoint DPT-6
	/// </summary>
	char get8BitSigned()
	{
		try
		{
			return datapoint_->get8BitSigned();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Sets Datapoint DPT-7
	/// </summary>
	void set2OctetUnsigned(unsigned short value)
	{
		try
		{
			datapoint_->set2OctetUnsigned(value);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets Datapoint DPT-7
	/// </summary>
	unsigned short get2OctetUnsigned()
	{
		try
		{
			return datapoint_->get2OctetUnsigned();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Sets Datapoint DPT-8
	/// </summary>
	void set2OctetSigned(short value)
	{
		try
		{
			datapoint_->set2OctetSigned(value);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets Datapoint DPT-8
	/// </summary>
	short get2OctetSigned()
	{
		try
		{
			return datapoint_->get2OctetSigned();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Sets Datapoint DPT-9
	/// </summary>
	void set2OctetFloat(unsigned char msb, unsigned char lsb)
	{
		try
		{
			datapoint_->set2OctetFloat(msb, lsb);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets Datapoint DPT-9 (msb)
	/// </summary>
	unsigned char get2OctetFloatMsb()
	{
		try
		{
			return datapoint_->get2OctetFloatMsb();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets Datapoint DPT-9 (lsb)
	/// </summary>
	unsigned char get2OctetFloatLsb()
	{
		try
		{
			return datapoint_->get2OctetFloatLsb();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Sets Datapoint DPT-9, converts a standard IEEE float to a KNX 2 byte float
	/// </summary>
	void set2OctetFloat(float f)
	{
		try
		{
			datapoint_->set2OctetFloat(f);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets Datapoint DPT-9, converts a KNX 2 byte float to a standard IEEE float
	/// </summary>
	float get2OctetFloat()
	{
		try
		{
			return datapoint_->get2OctetFloat();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Sets Datapoint DPT-10 (local time)
	/// </summary>
	void setTimeLocal()
	{
		try
		{
			datapoint_->setTimeLocal();
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Sets Datapoint DPT-10 (utc time)
	/// </summary>
	void setTimeUTC()
	{
		try
		{
			datapoint_->setTimeUTC();
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Sets Datapoint DPT-10
	/// </summary>
	void setTime(int day, int hour, int minute, int second)
	{
		try
		{
			datapoint_->setTime(day, hour, minute, second);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets Datapoint DPT-10 (day)
	/// </summary>
	int getTimeDay()
	{
		try
		{
			return datapoint_->getTimeDay();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets Datapoint DPT-10 (hour)
	/// </summary>
	int getTimeHour()
	{
		try
		{
			return datapoint_->getTimeHour();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets Datapoint DPT-10 (minute)
	/// </summary>
	int getTimeMinute()
	{
		try
		{
			return datapoint_->getTimeMinute();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets Datapoint DPT-10 (second)
	/// </summary>
	int getTimeSecond()
	{
		try
		{
			return datapoint_->getTimeSecond();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Sets Datapoint DPT-11 (local)
	/// </summary>
	void setDateLocal()
	{
		try
		{
			datapoint_->setDateLocal();
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Sets Datapoint DPT-11 (utc)
	/// </summary>
	void setDateUTC()
	{
		try
		{
			datapoint_->setDateUTC();
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Sets Datapoint DPT-11
	/// </summary>
	/// <param name="year">The year.</param>
	/// <param name="month">The month.</param>
	/// <param name="day">The day.</param>
	void setDate(int year, int month, int day)
	{
		try
		{
			datapoint_->setDate(year, month, day);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets Datapoint DPT-11 (year)
	/// </summary>
	int getDateYear()
	{
		try
		{
			return datapoint_->getDateYear();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets Datapoint DPT-11 (month)
	/// </summary>
	int getDateMonth()
	{
		try
		{
			return datapoint_->getDateMonth();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets Datapoint DPT-11 (day)
	/// </summary>
	int getDateDay()
	{
		try
		{
			return datapoint_->getDateDay();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Sets Datapoint DPT-12
	/// </summary>
	void set4OctetUnsigned(unsigned int value)
	{
		try
		{
			datapoint_->set4OctetUnsigned(value);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets Datapoint DPT-12
	/// </summary>
	unsigned int get4OctetUnsigned()
	{
		try
		{
			return datapoint_->get4OctetUnsigned();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Sets Datapoint DPT-13
	/// </summary>
	void set4OctetSigned(int value)
	{
		try
		{
			datapoint_->set4OctetSigned(value);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets Datapoint DPT-13
	/// </summary>
	int get4OctetSigned()
	{
		try
		{
			return datapoint_->get4OctetSigned();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Sets Datapoint DPT-14
	/// </summary>
	void set4OctetFloat(float value)
	{
		try
		{
			datapoint_->set4OctetFloat(value);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets Datapoint DPT-14
	/// </summary>
	float get4OctetFloat()
	{
		try
		{
			return datapoint_->get4OctetFloat();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Sets Datapoint DPT-15
	/// </summary>
	void setAccess(unsigned int accessCode, bool error, bool permission,
	               bool direction, bool encrypted, unsigned char index)
	{
		try
		{
			datapoint_->setAccess(accessCode, error, permission, direction, encrypted, index);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets Datapoint DPT-15 (code)
	/// </summary>
	unsigned int getAccessCode()
	{
		try
		{
			return datapoint_->getAccessCode();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets Datapoint DPT-15 (error)
	/// </summary>
	bool getAccessError()
	{
		try
		{
			return datapoint_->getAccessError();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets Datapoint DPT-15 (permission)
	/// </summary>
	bool getAccessPermission()
	{
		try
		{
			return datapoint_->getAccessPermission();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets Datapoint DPT-15 (direction)
	/// </summary>
	bool getAccessDirection()
	{
		try
		{
			return datapoint_->getAccessDirection();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets Datapoint DPT-15 (encrypted)
	/// </summary>
	bool getAccessEncrypted()
	{
		try
		{
			return datapoint_->getAccessEncrypted();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets Datapoint DPT-15 (index)
	/// </summary>
	unsigned char getAccessIndex()
	{
		try
		{
			return datapoint_->getAccessIndex();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Sets Datapoint DPT-16
	/// </summary>
	void setString(System::String^ str)
	{
		try
		{
			std::string s = interop::StringConvA(str);
			datapoint_->setString(s);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Gets Datapoint DPT-16
	/// </summary>
	System::String^ getString()
	{
		try
		{
			const std::string& s = datapoint_->getString();
			System::String^ str = gcnew System::String(s.c_str());
			return str;
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

protected:
	/// <summary>
	/// Finalizer (non-deterministic destructor)
	/// cleans up unmanaged resources.
	/// </summary>
	!BaosDatapoint()
	{
		try
		{
			if (datapoint_)
			{
				delete datapoint_;
				datapoint_ = 0;
			}
		}
		catch (...)
		{
		}
	}

private:
	Connector^ connector_;
	unmanaged::BaosDatapoint* datapoint_;
};

}
}
} // end namespace kdrive::baos::bindings

