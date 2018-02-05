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

#ifndef __KDRIVE_BAOS_DATAPOINT_H__
#define __KDRIVE_BAOS_DATAPOINT_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/BaosDatapointDescriptions.h"
#include "kdrive/baos/core/ServerItem.h"
#include "kdrive/baos/core/Forwards.h"
#include <vector>
#include <memory>

namespace kdrive
{
namespace baos
{

class BaosDatapointDescription;

/*!
	\brief The Baos Datapoint class is used to get and set a datapoint value.

	The BAOS device holds the datapoint as a byte array (between 1 and 14 bytes)
	and the BaosDatapoint class provides conversion routines from this raw byte
	stream to typed values, such as Boolean, 8 Bit Signed, 2 Octet Unsigned etc.
	Internally it uses the BaosDatapointDescription to ensure that the conversion is
	type safe, that is, it compares the length of the datapoint value in the
	description with the length of the requested type and if these lengths do not
	match an exception will be raised. Note: it is possible to convert to/from types
	of the same length. i.e. if the datapoint value length is 2 bytes all the 2 octet
	conversion functions will be valid.

	The Datapoint description is read once from the remote device and cached in the
	DatapointDescriptionHolder singleton class. If the project is changed (i.e via
	ETS download) the cache should be cleared otherwise the old descriptions will be used!
	(i.e. if you lose the TCP/IP connection it's probably a good idea to clear the
	DatapointDescriptionHolder cache on re-connect). To completely disable the
	description cache disable the DatapointDescriptionHolder.

	The Datapoint is associated with a specific id, which is configured in the ETS project.
	This id range is two bytes in length and depends on the BAOS version (and its associated
	database) as to the number of datapoints that are available.

	The BaosDatapoint implements a data cache (which can be disabled).
	When the cache is enabled the first read returns the value
	from the remote device and subsequent reads simply use the cached data.
	Obviously if the data on the remote	device changes the cached data
	will no longer represent the current state on the bus. The cache is only applicable
	to read requests. Write requests will overwrite the value of the stored data.
	Call clearData to force a read if the cache is enabled.
*/
class kdriveRPC_baos_API BaosDatapoint
{
public:
	typedef std::shared_ptr<BaosDatapoint> Ptr;

	BaosDatapoint();

	/*!
		This is the standard constructor you will use to create a
		BaosDatapoint class. You pass in the Connector class and the
		associated Datapoint Value id. This id should correspond to
		the id configured in the ETS project and is associated
		with a specific Group Value Address.

		The data cache is disabled by default. See enableCache

		\param[in] connector The baos connector. This is a shared
		pointer and is held for the life of this class.

		\param[in] id The datapoint id. In the range of 1 to 1000 (for 772, for 770/771: 250).
	*/
	BaosDatapoint(std::shared_ptr<BaosConnector> connector, unsigned short id);

	/*!
		Creates a Baos Datapoint Object associated with a single
		Datapoint on the baos device. This is effectively the same as
		the standard structure however it is also possible to set the
		default datapoint value data in the server item.

		The data cache is enabled by default if serverItem data is not empty.
		That is, subsequent reads will read the data given in serverItem.

		\param[in] connector The baos connector. This is a shared pointer
		and is held for the life of this class.

		\param[in] serverItem Contains the datapoint id.
		In the range of 1 to 1000 (for 772, for 770/771: 250). Also contains a default
		datapoint value in the data buffer.
	*/
	BaosDatapoint(std::shared_ptr<BaosConnector> connector, const ServerItem& serverItem);

	/*!
		Destroys the Baos Datapoint.
		The connector will be released.
	*/
	~BaosDatapoint();

	/*!
		Sets the datapoint id. You can use this when you need to dynamically
		change the id that this Datapoint object refers to in the remote BAOS device.
		For example, if you have several datapoints all of the same type
		(a Boolean type for example) with contiguous ids you can iterate over the ids
		and set their corresponding values on the remove device
		using the one BaosDatapoint object.
	*/
	void setId(unsigned short id);

	/*!
		Returns the datapoint id.
	*/
	unsigned short getId() const;

	/*!
		Gets the datapoint description from the device.
	*/
	const BaosDatapointDescription& getDatapointDescription() const;

	/*!
		Sets the Command. This is one of the BaosDatapointCommands.
		When a datapoint value is set on the remote device it is accompanied by a command.
		This command defaults to: Set new value and send on bus. If you need to change the
		command you can do so with this function. The list of commands can be found in the
		protocol specification on page 19 or in core/API
	*/
	void setCommand(unsigned char command);

	/*!
		Returns the currently set Command.
		This is one of the BaosDatapointCommands
	*/
	unsigned char getCommand() const;

	/*!
		requests a read value from the bus for this datapoint
		This uses the set datapoint value service with command set to
		ReadNewValueViaBus (just for this call) and this function has
		no lasting effect on the value of the command.
	*/
	void readNewValueViaBus();

	/*!
		requests that the transmission state is cleared.
		like readNewValueViaBus it has no lasting effect on the command
	*/
	void clearTransmissionState();

	/*!
		Sets the value of the datapoint on the remote BAOS device
		associated with the current id. This function also sends the command byte,
		which can be configured with setCommand. Note: the length of data should
		correspond to the datapoint value length configured in the ETS project.
		Although you can use the command directly it is preferable to use the
		specific type conversion functions such as setBoolean, set8BitUnsigned etc.
		You should only really ever need to use this function if a conversion function
		is not available. Note: the data should be encoded as Big Endian.

		\param[in] data A big-endian encoded byte stream between 1 and 14 bytes
	*/
	void setData(const std::vector<unsigned char>& data);

	/*!
		Reads the value of the datapoint on the remote BAOS device associated
		with the current id. It returns the raw Big Endian encoded byte stream.
		The datapoint values which are less than 1 byte (Boolean etc) are encoded as
		outlined in the BAOS protocol specification. It is preferable to use the
		specific type conversion functions to get the data.

		\return a copy of the big-endian encoded raw datapoint value data buffer
	*/
	const std::vector<unsigned char>& getData();

	/*!
		Clears the internal data. If the cache is enabled this will empty the
		data cache, so the next read will read from the baos device, and not
		from the cache.
	*/
	void clearData();

	/*!
		Returns true: Object has already been received
		Returns false: false Object value is unknown
	*/
	bool isValidFlag() const;

	/*!
		Returns true: Value is updated from the bus
		Returns false: Value was not updated
	*/
	bool isUpdate() const;

	/*!
		Returns true: Data request
		Returns false: Idle/response
	*/
	bool isDataRequest() const;

	enum TransmissionStatus
	{

	    TransmissionIdleOk = 0,
	    TransmissionIdleError,
	    TransmissionInProgress,
	    TransmissionRequest
	};

	/*!
		Returns one of the following transmission status values:
		TransmissionIdleOk
		TransmissionIdleError
		TransmissionInProgress
		TransmissionRequest
	*/
	int getTransmissionStatus() const;

	/*!
		Get the Description String associated with the datapoint
	*/
	std::string getDescriptionString();

	/*!
		Returns the associated server item. This contains the
		associated id and data buffer.
	*/
	const ServerItem& getServerItem() const;

	/*!
		enable the data cache
	*/
	void enableCache(bool cacheEnabled);

	/*!
		disable the cache
	*/
	void disableCache();

	/********************************************
	** Datapoint format functions
	*********************************************/

	/*!
		set Datapoint DPT-1
	*/
	void setBoolean(bool value);

	/*!
		get Datapoint DPT-1
	*/
	bool getBoolean();

	/*!
		set Datapoint DPT-2
	*/
	void set1BitControl(bool control, bool value);

	/*!
		get Datapoint DPT-2 (control)
	*/
	bool get1BitControl();

	/*!
		get Datapoint DPT-2 (value)
	*/
	bool get1BitControlValue();

	/*!
		set Datapoint DPT-3
	*/
	void set3BitControl(bool control, unsigned char value);

	/*!
		get Datapoint DPT-3 (control)
	*/
	bool get3BitControl();

	/*!
		get Datapoint DPT-3 (value)
	*/
	unsigned char get3BitControlValue();

	/*!
		set Datapoint DPT-4
	*/
	void setCharacterSet(unsigned char value);

	/*!
		get Datapoint DPT-4
	*/
	unsigned char getCharacterSet();

	/*!
		set Datapoint DPT-5
	*/
	void set8BitUnsigned(unsigned char value);

	/*!
		get Datapoint DPT-5
	*/
	unsigned char get8BitUnsigned();

	/*!
		set Datapoint DPT-6
	*/
	void set8BitSigned(char value);

	/*!
		get Datapoint DPT-6
	*/
	char get8BitSigned();

	/*!
		set Datapoint DPT-7
	*/
	void set2OctetUnsigned(unsigned short value);

	/*!
		get Datapoint DPT-7
	*/
	unsigned short get2OctetUnsigned();

	/*!
		set Datapoint DPT-8
	*/
	void set2OctetSigned(short value);

	/*!
		get Datapoint DPT-8
	*/
	short get2OctetSigned();

	/*!
		set Datapoint DPT-9
	*/
	void set2OctetFloat(unsigned char msb, unsigned char lsb);

	/*!
		get Datapoint DPT-9 (msb)
	*/
	unsigned char get2OctetFloatMsb();

	/*!
		get Datapoint DPT-9 (lsb)
	*/
	unsigned char get2OctetFloatLsb();

	/*!
		set Datapoint DPT-9, converts a standard IEEE float to a KNX 2 byte float
	*/
	void set2OctetFloat(float f);

	/*!
		get Datapoint DPT-9, converts a KNX 2 byte float to a standard IEEE float
	*/
	float get2OctetFloat();

	/*!
		set Datapoint DPT-10 (local time)
	*/
	void setTimeLocal();

	/*!
		set Datapoint DPT-10 (utc time)
	*/
	void setTimeUTC();

	/*!
		set Datapoint DPT-10
	*/
	void setTime(int day, int hour, int minute, int second);

	/*!
		get Datapoint DPT-10 (day)
	*/
	int getTimeDay();

	/*!
		get Datapoint DPT-10 (hour)
	*/
	int getTimeHour();

	/*!
		get Datapoint DPT-10 (minute)
	*/
	int getTimeMinute();

	/*!
		get Datapoint DPT-10 (second)
	*/
	int getTimeSecond();

	/*!
		set Datapoint DPT-11 (local)
	*/
	void setDateLocal();

	/*!
		set Datapoint DPT-11 (utc)
	*/
	void setDateUTC();

	/*!
		set Datapoint DPT-11
		\note The year is in KNX DPT11 format: 0..99; >=90 : 20th century; <90 : 21th century <\br>
		e.g. 99 => 1999; 0 => 2000
	*/
	void setDate(int year, int month, int day);

	/*!
		get Datapoint DPT-11 (year)
		\note The year is in KNX DPT11 format: 0..99; >=90 : 20th century; <90 : 21th century <\br>
		e.g. 99 => 1999; 0 => 2000
	*/
	int getDateYear();

	/*!
		get Datapoint DPT-11 (month)
	*/
	int getDateMonth();

	/*!
		get Datapoint DPT-11 (day)
	*/
	int getDateDay();

	/*!
		set Datapoint DPT-12
	*/
	void set4OctetUnsigned(unsigned int value);

	/*!
		get Datapoint DPT-12
	*/
	unsigned int get4OctetUnsigned();

	/*!
		set Datapoint DPT-13
	*/
	void set4OctetSigned(int value);

	/*!
		get Datapoint DPT-13
	*/
	int get4OctetSigned();

	/*!
		set Datapoint DPT-14
	*/
	void set4OctetFloat(float value);

	/*!
		get Datapoint DPT-14
	*/
	float get4OctetFloat();

	/*!
		set Datapoint DPT-15
	*/
	void setAccess(unsigned int accessCode, bool error, bool permission,
	               bool direction, bool encrypted, unsigned char index);

	/*!
		get Datapoint DPT-15 (code)
	*/
	unsigned int getAccessCode();

	/*!
		get Datapoint DPT-15 (error)
	*/
	bool getAccessError();

	/*!
		get Datapoint DPT-15 (permission)
	*/
	bool getAccessPermission();

	/*!
		get Datapoint DPT-15 (direction)
	*/
	bool getAccessDirection();

	/*!
		get Datapoint DPT-15 (encrypted)
	*/
	bool getAccessEncrypted();

	/*!
		get Datapoint DPT-15 (index)
	*/
	unsigned char getAccessIndex();

	/*!
		set Datapoint DPT-16
	*/
	void setString(const std::string& str);

	/*!
		get Datapoint DPT-16
	*/
	std::string getString();

private:
	/*!
		Writes data to the baos device. The write function
		expects a vector, so we simply init the vector and write that.
	*/
	void write(unsigned char data);

	/*!
		Validate that the data size matches the datapoint description size.
		Init the server item and use the SetDatapointValue service
		to set the datapoint value
	*/
	void write(const std::vector<unsigned char>& data);

	/*!
		Reads a datapoint value from the baos device.
		If expectedLength is 0 we don't validate the returned length
		otherwise we ensure that the lengths match
		We use the GetDatapointValue service to read the datapoint value
	*/
	const std::vector<unsigned char>& read(unsigned char expectedLength);

	/*!
		To validate a datapoint value size we read
		the datapoint description associated with the datapoint.
	*/
	void validate(unsigned char expectedLength);

	/*!
		Reads the datapoint description from the device.
		This is used to validate the datapoint value length.
	*/
	void readDatapointDescription();

	/*!
		Sets the current datapoint value command.
		Sends a SetDatapointValue request with empty data.
	*/
	void sendSetDatapointValueCommand(unsigned char command);

private:
	std::shared_ptr<BaosConnector> connector_;
	bool cacheEnabled_;
	BaosDatapointDescription description_;
	ServerItem serverItem_;
	unsigned char command_;
	enum { ValidMask = 0x10, UpdateMask = 0x08, DataRequestMask = 0x04, TransmissionStatusMask = 0x03 };
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_DATAPOINT_H__
