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
#include <kdrive/baos/BaosDatapointDescriptions.h>

namespace unmanaged
{
typedef kdrive::baos::BaosDatapointDescriptions BaosDatapointDescriptions;
typedef kdrive::baos::BaosDatapointDescription BaosDatapointDescription;
typedef kdrive::baos::BaosDatapointTypes BaosDatapointTypes;
}

namespace kdrive
{
namespace baos
{
namespace bindings
{

/// <summary>
/// BAOS data point types (DPT)
/// </summary>
/// <remarks>Specifications: KNX ObjectServer protocol (Version 2.0), Appendix D. Datapoint types (DPT)</remarks>
public enum class BaosDatapointTypes
{
	/// <summary>
	/// Datapoint disabled
	/// </summary>
	DatapointDisabled = unmanaged::BaosDatapointTypes::DatapointDisabled,
	
	/// <summary>
	/// DPT 1 (1 Bit, Boolean)
	/// </summary>
	DPT_1 = unmanaged::BaosDatapointTypes::DPT_1,
	
	/// <summary>
	/// DPT 2 (2 Bit, Control)
	/// </summary>
	DPT_2 = unmanaged::BaosDatapointTypes::DPT_2,
	
	/// <summary>
	/// DPT 3 (4 Bit, Dimming, Blinds)
	/// </summary>
	DPT_3 = unmanaged::BaosDatapointTypes::DPT_3,
	
	/// <summary>
	/// DPT 4 (8 Bit, Character Set)
	/// </summary>
	DPT_4 = unmanaged::BaosDatapointTypes::DPT_4,
	
	/// <summary>
	/// DPT 5 (8 Bit, Unsigned Value)
	/// </summary>
	DPT_5 = unmanaged::BaosDatapointTypes::DPT_5,
	
	/// <summary>
	/// DPT 6 (8 Bit, Signed Value)
	/// </summary>
	DPT_6 = unmanaged::BaosDatapointTypes::DPT_6,
	
	/// <summary>
	/// DPT 7 (2 Byte, Unsigned Value)
	/// </summary>
	DPT_7 = unmanaged::BaosDatapointTypes::DPT_7,
	
	/// <summary>
	/// DPT 8 (2 Byte, Signed Value)
	/// </summary>
	DPT_8 = unmanaged::BaosDatapointTypes::DPT_8,
	
	/// <summary>
	/// DPT 9 (2 Byte, Float Value)
	/// </summary>
	DPT_9 = unmanaged::BaosDatapointTypes::DPT_9,
	
	/// <summary>
	/// DPT 10 (3 Byte, Time)
	/// </summary>
	DPT_10 = unmanaged::BaosDatapointTypes::DPT_10,
	
	/// <summary>
	/// DPT 11 (3 Byte, Date)
	/// </summary>
	DPT_11 = unmanaged::BaosDatapointTypes::DPT_11,
	
	/// <summary>
	/// DPT 12 (4 Byte, Unsigned Value)
	/// </summary>
	DPT_12 = unmanaged::BaosDatapointTypes::DPT_12,
	
	/// <summary>
	/// DPT 13 (4 Byte, Signed Value)
	/// </summary>
	DPT_13 = unmanaged::BaosDatapointTypes::DPT_13,
	
	/// <summary>
	/// DPT 14 (4 Byte, Float Value)
	/// </summary>
	DPT_14 = unmanaged::BaosDatapointTypes::DPT_14,
	
	/// <summary>
	/// DPT 15 (4 Byte, Access)
	/// </summary>
	DPT_15 = unmanaged::BaosDatapointTypes::DPT_15,
	
	/// <summary>
	/// DPT 16 (14 Byte, String)
	/// </summary>
	DPT_16 = unmanaged::BaosDatapointTypes::DPT_16,
	
	/// <summary>
	/// DPT 17 (1 Byte, Scene Number) 
	/// </summary>
	DPT_17 = unmanaged::BaosDatapointTypes::DPT_17,
	
	/// <summary>
	/// DPT 18 (1 Byte, Scene Control)
	/// </summary>
	DPT_18 = unmanaged::BaosDatapointTypes::DPT_18,

	/// <summary>
	/// Unknown DPT
	/// </summary>
	Unknown = unmanaged::BaosDatapointTypes::Unknown
};


/// <summary>
///	A BaosDatapointDescription contains information about a Datapoint Value
/// </summary>
/// <remarks>
/// Interprets the data point description data.
///	You can read a BaosDatapointDescription using the
///	BaosDatapointDescriptions class.
/// <para>
/// A Datapoint Description has four attributes:
/// <list type="bullet">
///		<item><description>data point id</description></item>
///		<item><description>data point value type : indicates the data point value size</description></item>
///		<item><description>data point config flags : indicate the communication flags set in the ETS project</description></item>
///		<item><description>data point type : Protocol Version 1.2 does not support data point type (it will always be 0)</description></item>
/// </list>
/// </para>
/// </remarks>
public ref class BaosDatapointDescription
{
public:

	/// <summary>
	///	Default Constructor.
	/// </summary>
	BaosDatapointDescription()

		: datapointDescription_(0)
	{
		try
		{
			datapointDescription_ = new unmanaged::BaosDatapointDescription();
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Constructor.
	/// </summary>
	BaosDatapointDescription(unsigned short id, unsigned char valueType,
	                         unsigned char configFlags, unsigned char datapointType)

		: datapointDescription_(0)
	{
		try
		{
			datapointDescription_ = new unmanaged::BaosDatapointDescription(id, valueType, configFlags, datapointType);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Destroys the BaosDatapointDescription.
	///	Destructor cleans up unmanaged and managed resources.
	/// </summary>
	~BaosDatapointDescription()
	{
		// call finalizer to release unmanaged resources
		this->!BaosDatapointDescription();
	}

	/// <summary>
	///	Gets the data point id.
	/// </summary>
	unsigned short getId()
	{
		try
		{
			return datapointDescription_->getId();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets the config flags
	/// </summary>
	/// <remarks>
	/// <seealso cref="getTransmitPriority" />
	/// <seealso cref="isCommunication" />
	/// <seealso cref="isReadFromBus" />
	/// <seealso cref="isWriteFromBus" />
	/// <seealso cref="isClientTransmitRequest" />
	/// <seealso cref="isUpdateOnResponse" />
	/// </remarks>
	unsigned char getConfigFlags()
	{
		try
		{
			return datapointDescription_->getConfigFlags();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets the transmit priority
	/// </summary>
	/// <remarks>
	/// <seealso cref="TransmitPriority" />
	/// </remarks>
	unsigned char getTransmitPriority()
	{
		try
		{
			return datapointDescription_->getTransmitPriority();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Returns true if the communication flag is set. Otherwise returns false.
	/// </summary>
	bool isCommunication()
	{
		try
		{
			return datapointDescription_->isCommunication();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Returns true if the read from bus flag is set. Otherwise returns false.
	/// </summary>
	bool isReadFromBus()
	{
		try
		{
			return datapointDescription_->isReadFromBus();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Returns true if the write from bus flag is set. Otherwise returns false.
	/// </summary>
	bool isWriteFromBus()
	{
		try
		{
			return datapointDescription_->isWriteFromBus();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Returns true if the transmit to bus flag is set. Otherwise returns false.
	/// </summary>
	bool isClientTransmitRequest()
	{
		try
		{
			return datapointDescription_->isClientTransmitRequest();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Returns true if the update on response flag is set. Otherwise returns false.
	/// </summary>
	bool isUpdateOnResponse()
	{
		try
		{
			return datapointDescription_->isUpdateOnResponse();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets the value type.
	/// </summary>
	/// <remarks>
	/// <seealso cref="ValueTypes" />
	/// </remarks>
	unsigned char getValueType()
	{
		try
		{
			return datapointDescription_->getValueType();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets the value type in size in bits 
	/// </summary>
	/// <remarks>
	/// <seealso cref="getValueType" />
	/// </remarks>
	unsigned char getValueTypeSizeBits()
	{
		try
		{
			return datapointDescription_->getValueTypeSizeBits();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets the value type in size in bytes.
	///	Values which are smaller than 1 byte e.g. 2 bits returns 1.
	/// </summary>
	/// <remarks>
	/// <seealso cref="getValueType" />
	/// </remarks>
	unsigned char getValueTypeSizeBytes()
	{
		try
		{
			return datapointDescription_->getValueTypeSizeBytes();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Returns true if the value type is samller than 1 byte.
	///	Otherwise returns false.
	/// </summary>
	/// <remarks>
	/// <seealso cref="getValueType" />
	/// </remarks>
	bool isBitType()
	{
		try
		{
			return datapointDescription_->isBitType();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Returns true if the value type is greater than 1 byte.
	///	Otherwise returns false.
	/// </summary>
	/// <remarks>
	/// <seealso cref="getValueType" />
	/// </remarks>
	bool isByteType()
	{
		try
		{
			return datapointDescription_->isByteType();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Gets the datapoint type.
	/// </summary>
	/// <remarks>
	/// <seealso cref="BaosDatapointTypes" />
	/// </remarks>
	unsigned char getDatapointType()
	{
		try
		{
			return datapointDescription_->getDatapointType();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Transmit priority
	/// </summary>
	enum class TransmitPriority
	{
		System = unmanaged::BaosDatapointDescription::System,
		Alarm = unmanaged::BaosDatapointDescription::Alarm,
		High = unmanaged::BaosDatapointDescription::High,
		Low = unmanaged::BaosDatapointDescription::Low
	};

	/// <summary>
	///	BAOS data point value types
	/// </summary>
	enum class ValueTypes
	{
		/// <summary>
		/// 1 bit
		/// </summary>
		Bit1 = unmanaged::BaosDatapointDescription::Bit1,

		/// <summary>
		/// 2 bits
		/// </summary>
		Bit2 = unmanaged::BaosDatapointDescription::Bit2,

		/// <summary>
		/// 3 bits
		/// </summary>
		Bit3 = unmanaged::BaosDatapointDescription::Bit3,

		/// <summary>
		/// 4 bits
		/// </summary>
		Bit4 = unmanaged::BaosDatapointDescription::Bit4,

		/// <summary>
		/// 5 bits
		/// </summary>
		Bit5 = unmanaged::BaosDatapointDescription::Bit5,

		/// <summary>
		/// 6 bits
		/// </summary>
		Bit6 = unmanaged::BaosDatapointDescription::Bit6,

		/// <summary>
		/// 7 bits
		/// </summary>
		Bit7 = unmanaged::BaosDatapointDescription::Bit7,

		/// <summary>
		/// 1 byte
		/// </summary>
		Byte1 = unmanaged::BaosDatapointDescription::Byte1,

		/// <summary>
		/// 2 bytes
		/// </summary>
		Byte2 = unmanaged::BaosDatapointDescription::Byte2,

		/// <summary>
		/// 3 bytes
		/// </summary>
		Byte3 = unmanaged::BaosDatapointDescription::Byte3,

		/// <summary>
		/// 4 bytes
		/// </summary>
		Byte4 = unmanaged::BaosDatapointDescription::Byte4,

		/// <summary>
		/// 6 bytes
		/// </summary>
		Byte6 = unmanaged::BaosDatapointDescription::Byte6,

		/// <summary>
		/// 8 bytes
		/// </summary>
		Byte8 = unmanaged::BaosDatapointDescription::Byte8,

		/// <summary>
		/// 10 bytes
		/// </summary>
		Byte10 = unmanaged::BaosDatapointDescription::Byte10,

		/// <summary>
		/// 14 bytes
		/// </summary>
		Byte14 = unmanaged::BaosDatapointDescription::Byte14
	};

protected:
	/// <summary>
	///	Finalizer (non-deterministic destructor) 
	///	cleans up unmanaged resources.
	/// </summary>
	!BaosDatapointDescription()
	{
		try
		{
			delete datapointDescription_;
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

private:
	unmanaged::BaosDatapointDescription* datapointDescription_;
};


/// <summary>
/// Reads the data point descriptions from the baos server
/// and stores the data point descriptions internally.
/// This retrieval can be done with readFromDevice
/// </summary>
/// <remarks>
///	<code>
///	// C# sample: Read datapoint descriptions
///	void readDatapointDescriptions(Connector connector)
///	{
///		try
///		{
///			BaosDatapointDescriptions baosDatapointDescriptions = new BaosDatapointDescriptions(connector);
///			baosDatapointDescriptions.readFromDevice();
///			List<BaosDatapointDescription> descriptions = baosDatapointDescriptions.getDescriptions();
///
///			Console.WriteLine("{0} items found", descriptions.Count);
///
///			foreach (BaosDatapointDescription desc in descriptions)
///			{
///				Console.WriteLine("");
///				Console.WriteLine("Datapoint id {0}", desc.getId());
///				Console.WriteLine("Datapoint type: {0}", desc.getDatapointType());
///			}
///		}
///		catch (kdrive.KdriveException exception)
///		{
///			Console.WriteLine(exception.Message);
///		}
///	}
/// </code>
/// </remarks>
public ref class BaosDatapointDescriptions
{
public:

	/// <summary>
	///	Creates a empty BaosDatapointDescriptions object.
	/// Note: The description will not read automatic in the constructor. 
	/// You need call readFromDevice for initial reading.
	/// </summary>
	BaosDatapointDescriptions(Connector^ connector)

		: datapointDescriptions_(0)
	{
		try
		{
			datapointDescriptions_ = new unmanaged::BaosDatapointDescriptions(connector->getUnmanaged());
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Destroys the Baos Datapoint Descriptions object.
	///	Destructor cleans up unmanaged and managed resources.
	/// </summary>
	~BaosDatapointDescriptions()
	{
		// call finalizer to release unmanaged resources
		this->!BaosDatapointDescriptions();
	}

	/// <summary>
	///	Clears the internally stored values
	/// </summary>
	void clear()
	{
		try
		{
			datapointDescriptions_->clear();
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Clears the internally stored values from data point ids 
	///	between startId and (startId + count) - 1
	/// </summary>
	void erase(unsigned short startId, unsigned short count)
	{
		try
		{
			datapointDescriptions_->erase(startId, count);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Reads all data point descriptions from the baos server.
	/// </summary>
	void readFromDevice()
	{
		try
		{
			datapointDescriptions_->readFromDevice();
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	/// Requests a range of data point descriptions from the baos server.
	/// Before the new values are read the current values from the request range are erased.
	/// </summary>
	/// <param name="startId">The id of the first data point.</param>
	/// <param name="count">The number of data points to read.</param>
	void readFromDevice(unsigned short startId, unsigned short count)
	{
		try
		{
			datapointDescriptions_->readFromDevice(startId, count);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	/// <summary>
	///	Returns the number of data point descriptors
	/// </summary>
	unsigned short getCount()
	{
		try
		{
			return datapointDescriptions_->getCount();
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Returns a single data point description by id.
	///	If a corresponding description is not found with this id
	///	an exception is throw
	/// </summary>
	BaosDatapointDescription^ get(unsigned int id)
	{
		try
		{
			const unmanaged::BaosDatapointDescription& desc = datapointDescriptions_->get(id);
			return gcnew BaosDatapointDescription(desc.getId(), desc.getValueType(), desc.getConfigFlags(), desc.getDatapointType());
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Returns true if a data point description is found with this id
	/// </summary>
	bool has(unsigned int id)
	{
		try
		{
			return datapointDescriptions_->has(id);
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

	/// <summary>
	///	Returns the data point descriptions
	/// </summary>
	System::Collections::Generic::List<BaosDatapointDescription^>^ getDescriptions()
	{
		try
		{
			const unmanaged::BaosDatapointDescriptions::Descriptions& descs = 
				datapointDescriptions_->getDescriptions();

			System::Collections::Generic::List<BaosDatapointDescription^>^ descriptions = 
				gcnew System::Collections::Generic::List<BaosDatapointDescription^>();

			unmanaged::BaosDatapointDescriptions::Descriptions::const_iterator iter = descs.begin();
			for ( ; iter != descs.end(); ++iter)
			{
				const unmanaged::BaosDatapointDescription& desc = iter->second;
				descriptions->Add(gcnew BaosDatapointDescription(desc.getId(), desc.getValueType(),
					desc.getConfigFlags(), desc.getDatapointType()));
			}

			return descriptions;
		}
		WZ_KDRIVE_CLR_CATCH_BLACK_HOLE
	}

protected:
	/// <summary>
	///	Finalizer (non-deterministic destructor) 
	///	cleans up unmanaged resources.
	/// </summary>
	!BaosDatapointDescriptions()
	{
		try
		{
			if (datapointDescriptions_)
			{
				delete datapointDescriptions_;
				datapointDescriptions_ = 0;
			}
		}
		catch (...)
		{
		}
	}

private:
	unmanaged::BaosDatapointDescriptions* datapointDescriptions_;
};

}
}
} // end namespace kdrive::baos::bindings

