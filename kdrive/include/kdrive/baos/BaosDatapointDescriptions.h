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

#ifndef __KDRIVE_BAOS_DATAPOINT_DESCRIPTIONS_H__
#define __KDRIVE_BAOS_DATAPOINT_DESCRIPTIONS_H__

#include "kdrive/baos/Config.h"
#include "kdrive/baos/core/Forwards.h"
#include <Poco/Mutex.h>
#include <map>
#include <memory>
#include <vector>

namespace kdrive
{
namespace baos
{

/*!
    \class BaosDatapointDescription
	\brief A BaosDatapointDescription contains
	information about a Datapoint Value

	Interprets the datapoint description data.
	You can read a BaosDatapointDescription using the
	BaosDatapointDescriptions class.

	A Datapoint Description has four attributes:
		datapoint id
		datapoint value type : indicates the datapoint value size
		datapoint config flags : indicate the communication flags set in the ETS project
		datapoint type : Protocol Version 1.2 does not support datapoint type (it will always be 0)
*/

class kdriveRPC_baos_API BaosDatapointDescription
{
public:
	/*!
		Default Constructor.
	*/
	BaosDatapointDescription();

	/*!
		Constructor.
	*/
	BaosDatapointDescription(unsigned short id, unsigned char valueType,
	                         unsigned char configFlags, unsigned char datapointType);

	/*!
		Destroys the BaosDatapointDescription
	*/
	~BaosDatapointDescription();

	/*!
		Gets the datapoint id.
	*/
	unsigned short getId() const;

	/*!
		Gets the config flags
		\see getTransmitPriority
		\see isCommunication
		\see isReadFromBus
		\see isWriteFromBus
		\see isClientTransmitRequest
		\see isUpdateOnResponse
	*/
	unsigned char getConfigFlags() const;

	/*!
		Gets the transmit priority
		\see TransmitPriority
	*/
	unsigned char getTransmitPriority() const;

	/*!
		Returns true if the communication flag is set. Otherwise returns false.
	*/
	bool isCommunication() const;

	/*!
		Returns true if the read from bus flag is set. Otherwise returns false.
	*/
	bool isReadFromBus() const;

	/*!
		Returns true if the write from bus flag is set. Otherwise returns false.
	*/
	bool isWriteFromBus() const;

	/*!
		Returns true if the read on init flag is set. Otherwise returns false.
	*/
	bool isReadOnInit() const;

	/*!
		Returns true if the transmit to bus flag is set. Otherwise returns false.
	*/
	bool isClientTransmitRequest() const;

	/*!
		Returns true if the update on response flag is set. Otherwise returns false.
	*/
	bool isUpdateOnResponse() const;

	/*!
		Gets the value type.
		\see ValueTypes
	*/
	unsigned char getValueType() const;

	/*!
		Gets the value type in size in bits
		\see getValueType
	*/
	unsigned char getValueTypeSizeBits() const;

	/*!
		Gets the value type in size in bytes.
		Values which are smaller than 1 byte e.g. 2 bits returns 1.
		\see getValueType
	*/
	unsigned char getValueTypeSizeBytes() const;

	/*!
		Returns true if the value type is samller than 1 byte.
		Otherwise returns false.
		\see getValueType
	*/
	bool isBitType() const;

	/*!
		Returns true if the value type is greater than 1 byte.
		Otherwise returns false.
		\see getValueType
	*/
	bool isByteType() const;

	/*!
		Gets the datapoint type.
		\see BaosDatapointTypes
	*/
	unsigned char getDatapointType() const;

	/*!
		Transmit priority
	*/
	enum TransmitPriority
	{
	    System = 0,
	    Alarm,
	    High,
	    Low
	};

	/*!
		BAOS datapoint value types
	*/
	enum ValueTypes
	{
	    Bit1 = 0, /*!< 1 bit */
	    Bit2 = 1, /*!< 2 bit */
	    Bit3 = 2, /*!< 3 bit */
	    Bit4 = 3, /*!< 4 bit */
	    Bit5 = 4, /*!< 5 bit */
	    Bit6 = 5, /*!< 6 bit */
	    Bit7 = 6, /*!< 7 bit */
	    Byte1 = 7, /*!< 1 byte */
	    Byte2 = 8, /*!< 2 bytes */
	    Byte3 = 9, /*!< 3 bytes */
	    Byte4 = 10, /*!< 4 bytes */
	    Byte6 = 11, /*!< 6 bytes */
	    Byte8 = 12, /*!< 8 bytes */
	    Byte10 = 13, /*!< 10 bytes */
	    Byte14 = 14 /*!< 14 bytes */
	};

private:
	unsigned short id_;
	unsigned char valueType_;
	unsigned char configFlags_;
	unsigned char datapointType_;

	enum Masks
	{
	    TransmitPriorityMask = 0x03,
	    CommunicationMask = 0x04,
	    ReadFromBusMask = 0x08,
	    WriteFromBusMask = 0x10,
	    ReadOnInitMask = 0x20,
	    TransmitRequestMask = 0x40,
	    UpdateOnResponseMask = 0x80
	};
};

/*!
    Reads the datapoint descriptions from the baos server
    and stores the datapoint descriptions internally.
    This retrieval can be done with readFromDevice.

	\code{.cpp}
		// Read datapoint descriptions
		void readDatapointDescriptions(BaosConnector::Ptr connector)
		{
			try
			{
				BaosDatapointDescriptions baosDatapointDescriptions(connector);

				baosDatapointDescriptions.readFromDevice();
				const BaosDatapointDescriptions::Descriptions descriptions = baosDatapointDescriptions.getDescriptions();

				const unsigned int count = descriptions.size();
				std::cout << count << " items found" << std::endl;

				for (const auto& item : descriptions)
				{
					const BaosDatapointDescription& desc = item.second;
					std::cout << std::endl;
					std::cout << "Datapoint id: " << desc.getId() << std::endl;
					std::cout << "Datapoint type: " << desc.getDatapointType() << std::endl;
				}
			}
			catch (Exception& exception)
			{
				std::cerr << exception.displayText() << std::endl;
			}
		}
	\endcode
*/
class kdriveRPC_baos_API BaosDatapointDescriptions
{
public:
	typedef std::map<unsigned int, BaosDatapointDescription> Descriptions;

	/*!
		Creates a empty BaosDatapointDescriptions object.
		\note The description will not read automatic in the constructor.
		You need call readFromDevice for initial reading.
	*/
	BaosDatapointDescriptions(std::shared_ptr<BaosConnector> connector);

	/*!
		Destroys the Baos Datapoint Descriptions object.
	*/
	~BaosDatapointDescriptions();

	/*!
		Clears the internally stored values
	*/
	void clear();

	/*!
		Clears the internally stored values from datapoint ids
		between startId and (startId + count) - 1
	*/
	void erase(unsigned short startId, unsigned short count);

	/*!
		Reads all datapoint descriptions from the baos server
		when it is possible to determine how many datapoints
		have been allocated. This is either via the protocol version
		(i.e. protocol version 1.2 has a max of 250 datapoints)
		or via the server item getMaxDatapoints. If the limit
		can not be found we try to read a max of 1000 datapoints
	*/
	void readFromDevice();

	/*!
		Requests a range of datapoint descriptions from the baos server.
		Before the new values are read the current values from the request range are erased.
		\param startId the id of the first datapoint
		\param count the number of datapoints to read
		\return the datapoint id of the last get descriptions
	*/
	void readFromDevice(unsigned short startId, unsigned short count);

	/*!
		Returns the number of datapoint descriptors
	*/
	unsigned short getCount() const;

	/*!
		Returns a single datapoint description by id.
		If a corresponding description is not found with this id
		an exception is throw
		\deprecated use get instead
	*/
	const BaosDatapointDescription& at(unsigned int id) const;

	/*!
		Returns a single datapoint description by id.
		If a corresponding description is not found with this id
		an exception is throw
	*/
	const BaosDatapointDescription& get(unsigned int id) const;

	/*!
		Returns true if a datapoint description is found with this id
	*/
	bool has(unsigned int id) const;

	/*!
		Returns the datapoint descriptions
	*/
	const Descriptions& getDescriptions() const;

	/*!
		Returns the list of datapoint descriptions
	*/
	std::vector<BaosDatapointDescription> getList() const;

private:
	void readDescriptions_ProtocolV12(unsigned short startId, unsigned short count);
	void readDescriptions_ProtocolV20(unsigned short startId, unsigned short count);
	unsigned short readDescriptions(unsigned short startId, unsigned short count);

private:
	std::shared_ptr<BaosConnector> connector_;
	Descriptions descriptions_;
};

/*!
	\class DatapointDescriptionHolder
	\brief Cache for Baos Datapoint Descriptions
	Holds BaosDatapointDescriptions so we don't have to continually read
	them from the remote device. If a description is available it is returned,
	otherwise it is read from the device. Subsequence reads will return the
	description without reading from the device.
	This is a singleton class.
*/
class kdriveRPC_baos_API DatapointDescriptionHolder
{
public:
	/*!
		Creates a default DatapointDescriptionHolder
	*/
	DatapointDescriptionHolder();

	/*!
		Destroys the DatapointDescriptionHolder
	*/
	~DatapointDescriptionHolder();

	/*!
		\return the single DatapointDescriptionHolder instance
	*/
	static DatapointDescriptionHolder& instance();

	/*!
		Gets the description associated with the datapoint id.
		Either locally from the cache, or remotely from the device
		if not in the cache
	*/
	BaosDatapointDescription get(std::shared_ptr<BaosConnector> connector, unsigned short id);

	/*!
		empties the cache
	*/
	void clear();

	/*!
		enable/disable the caching mechanism
		by default the cache is enabled
	*/
	void enable(bool enabled = true);

	/*!
		disable the cache, the description will always be read from the bus
	*/
	void disable();

private:
	BaosDatapointDescription readFromMap(std::shared_ptr<BaosConnector> connector, unsigned short id);
	BaosDatapointDescription read(std::shared_ptr<BaosConnector> connector, unsigned short id);

private:
	typedef std::map<unsigned int, BaosDatapointDescription> Descriptions;
	Descriptions descriptions_;
	Poco::FastMutex mutex_;
	bool enabled_;
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_DATAPOINT_DESCRIPTIONS_H__
