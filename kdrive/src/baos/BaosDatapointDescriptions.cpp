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

#include "pch/kdrive_pch.h"
#include "kdrive/baos/BaosDatapointDescriptions.h"
#include "kdrive/baos/BaosServerItems.h"
#include "kdrive/baos/services/GetDatapointDescription.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/BaosConnector.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/utility/Logger.h"
#include "kdrive/utility/LoggerFormatter.h"
#include <Poco/SingletonHolder.h>
#include <Poco/Format.h>
#include <boost/assert.hpp>
#include <algorithm> // for std::max

using namespace kdrive::connector;
using namespace kdrive::baos;
using Poco::format;
using Poco::FastMutex;
using Poco::ScopedLock;
using Poco::SingletonHolder;

#ifdef max
#undef max // undefine the macro max from WinDef.h. we want to use std::max
#endif

CLASS_LOGGER("kdrive.baos.BaosDatapointDescription")

/*************************************
** BaosDatapointDescription
**************************************/

BaosDatapointDescription::BaosDatapointDescription()

	: id_(0),
	  valueType_(0x00),
	  configFlags_(0x00),
	  datapointType_(0x00)
{
}

BaosDatapointDescription::BaosDatapointDescription(unsigned short id,
        unsigned char valueType,
        unsigned char configFlags,
        unsigned char datapointType)

	: id_(id),
	  valueType_(valueType),
	  configFlags_(configFlags),
	  datapointType_(datapointType)
{
}

BaosDatapointDescription::~BaosDatapointDescription()
{
}

unsigned short BaosDatapointDescription::getId() const
{
	return id_;
}

unsigned char BaosDatapointDescription::getConfigFlags() const
{
	return configFlags_;
}

unsigned char BaosDatapointDescription::getTransmitPriority() const
{
	return configFlags_ & TransmitPriorityMask;
}

bool BaosDatapointDescription::isCommunication() const
{
	return configFlags_ & CommunicationMask ? true : false;
}

bool BaosDatapointDescription::isReadFromBus() const
{
	return configFlags_ & ReadFromBusMask ? true : false;
}

bool BaosDatapointDescription::isWriteFromBus() const
{
	return configFlags_ & WriteFromBusMask ? true : false;
}

bool BaosDatapointDescription::isReadOnInit() const
{
	return configFlags_ & ReadOnInitMask ? true : false;
}

bool BaosDatapointDescription::isClientTransmitRequest() const
{
	return configFlags_ & TransmitRequestMask ? true : false;
}

bool BaosDatapointDescription::isUpdateOnResponse() const
{
	return configFlags_ & UpdateOnResponseMask ? true : false;
}

unsigned char BaosDatapointDescription::getValueType() const
{
	return valueType_;
}

unsigned char BaosDatapointDescription::getValueTypeSizeBits() const
{
	switch (valueType_)
	{
		case Bit1:
			return 1;
		case Bit2:
			return 2;
		case Bit3:
			return 3;
		case Bit4:
			return 4;
		case Bit5:
			return 5;
		case Bit6:
			return 6;
		case Bit7:
			return 7;
	}

	return getValueTypeSizeBytes() * 8;
}

unsigned char BaosDatapointDescription::getValueTypeSizeBytes() const
{
	switch (valueType_)
	{
		case Bit1:
		case Bit2:
		case Bit3:
		case Bit4:
		case Bit5:
		case Bit6:
		case Bit7:
		case Byte1:
			return 1;

		case Byte2:
			return 2;
		case Byte3:
			return 3;
		case Byte4:
			return 4;
		case Byte6:
			return 6;
		case Byte8:
			return 8;
		case Byte10:
			return 10;
		case Byte14:
			return 14;
	}

	return 0;
}

bool BaosDatapointDescription::isBitType() const
{
	return valueType_ < Byte1 ? true : false;
}

bool BaosDatapointDescription::isByteType() const
{
	return valueType_ >= Byte1 ? true : false;
}

unsigned char BaosDatapointDescription::getDatapointType() const
{
	return datapointType_;
}

/*************************************
** BaosDatapointDescriptions
**************************************/

BaosDatapointDescriptions::BaosDatapointDescriptions(BaosConnector::Ptr connector)

	: connector_(connector)
{
}

BaosDatapointDescriptions::~BaosDatapointDescriptions()
{
}

void BaosDatapointDescriptions::clear()
{
	descriptions_.clear();
}

void BaosDatapointDescriptions::erase(unsigned short startId, unsigned short count)
{
	const unsigned int endId = (startId + count) - 1;
	const Descriptions::iterator iterBegin = descriptions_.lower_bound(startId);
	const Descriptions::iterator iterEnd = descriptions_.upper_bound(endId);
	descriptions_.erase(iterBegin, iterEnd);
}

void BaosDatapointDescriptions::readFromDevice()
{
	clear();

	if (connector_->getVersion() == ProtocolVersions::V12)
	{
		readDescriptions_ProtocolV12(1, 250);
	}
	else
	{
		unsigned int count = 0;
		try
		{
			// currently only 777 has server item to get the datapoint count
			BaosServerItems serverItems(connector_);
			count = serverItems.getMaxDatapoints();
		}
		catch (NoItemFoundServerException&)
		{
			// we try to read max 1000 datapoints
			// it's a 771 with 250 or a 772/830 with 1000 datapoints
			count = 1000;
		}

		// We simply read blocks until we on the end or we get a BAD_SERVICE_PARAMETER error
		// (i.e. out of range; e.g. for 771)

		bool finished = false;
		const int blockSize = 50;
		unsigned int offset = 1;
		while (!finished && (offset < count))
		{
			try
			{
				readDescriptions_ProtocolV20(offset, blockSize);
				offset += blockSize;
			}
			catch (BadServiceParameterServerException&)
			{
				finished = true;
			}
		}
	}
}

void BaosDatapointDescriptions::readFromDevice(unsigned short startId, unsigned short count)
{
	erase(startId, count);

	if (connector_->getVersion() == ProtocolVersions::V12)
	{
		readDescriptions_ProtocolV12(startId, count);
	}
	else
	{
		readDescriptions_ProtocolV20(startId, count);
	}
}

unsigned short BaosDatapointDescriptions::getCount() const
{
	return static_cast<unsigned short>(descriptions_.size());
}

const BaosDatapointDescription& BaosDatapointDescriptions::at(unsigned int id) const
{
	return get(id);
}

const BaosDatapointDescription& BaosDatapointDescriptions::get(unsigned int id) const
{
	Descriptions::const_iterator iter = descriptions_.find(id);
	if (iter == descriptions_.end())
	{
		throw ClientException("Datapoint Description not found");
	}
	return iter->second;
}

bool BaosDatapointDescriptions::has(unsigned int id) const
{
	Descriptions::const_iterator iter = descriptions_.find(id);
	return iter != descriptions_.end() ? true : false;
}

const BaosDatapointDescriptions::Descriptions& BaosDatapointDescriptions::getDescriptions() const
{
	return descriptions_;
}

std::vector<BaosDatapointDescription> BaosDatapointDescriptions::getList() const
{
	std::vector<BaosDatapointDescription> v;

	Descriptions::const_iterator iter = descriptions_.begin();
	Descriptions::const_iterator end = descriptions_.end();
	for (; iter != end; ++iter)
	{
		v.push_back(iter->second);
	}

	return v;
}

void BaosDatapointDescriptions::readDescriptions_ProtocolV12(unsigned short startId, unsigned short count)
{
	for (unsigned int index = 0; index < count; ++index)
	{
		try
		{
			const unsigned int currentId = startId + index;
			poco_debug(LOGGER(), format("Read description (id: %u)", currentId));
			readDescriptions(currentId, 1);
		}
		catch (ServerException&)
		{
		}
	}
}

void BaosDatapointDescriptions::readDescriptions_ProtocolV20(unsigned short startId, unsigned short count)
{
	try
	{
		const unsigned int maxId = startId + count - 1;
		unsigned int currentId = startId;
		unsigned int remainingCount = count;
		while (remainingCount)
		{
			poco_debug(LOGGER(), format("Read descriptions (start: %u count: %u) ...", currentId, remainingCount));
			const unsigned short lastReadId = readDescriptions(currentId, remainingCount);
			currentId = lastReadId + 1;
			remainingCount = (lastReadId < maxId) ? (maxId - lastReadId) : 0;
			poco_debug(LOGGER(), format("... until id %u readed", static_cast<unsigned int>(lastReadId)));
		}
	}
	// if no more activate datapoints exists in the range an excetion with "No item found" will throw
	catch (NoItemFoundServerException&)
	{
		poco_debug(LOGGER(), "... no more active datapoint exists");
	}
}

unsigned short BaosDatapointDescriptions::readDescriptions(unsigned short startId, unsigned short count)
{
	unsigned short maxId = 0;

	GetDatapointDescription service(connector_);
	service.rpc(startId, count);
	const GetDatapointDescription::Descriptors& descriptors = service.getDescriptors();

	for (const auto& descriptor : descriptors)
	{
		const unsigned short id = std::get<GetDatapointDescription::Id>(descriptor);
		const unsigned char valueType = std::get<GetDatapointDescription::ValueType>(descriptor);
		const unsigned char configFlags = std::get<GetDatapointDescription::ConfigFlags>(descriptor);
		const unsigned char datapointType = std::get<GetDatapointDescription::DatapointType>(descriptor);
		BaosDatapointDescription datapointDescription(id, valueType, configFlags, datapointType);
		descriptions_.insert(Descriptions::value_type(id, datapointDescription));
		maxId = std::max(maxId, id);
	}

	return maxId;
}

/*************************************
** DatapointDescriptionHolder
**************************************/

DatapointDescriptionHolder::DatapointDescriptionHolder()

	: enabled_(true)
{
}

DatapointDescriptionHolder::~DatapointDescriptionHolder()
{
}

DatapointDescriptionHolder& DatapointDescriptionHolder::instance()
{
	static SingletonHolder<DatapointDescriptionHolder> instance;
	return *instance.get();
}

BaosDatapointDescription DatapointDescriptionHolder::get(BaosConnector::Ptr connector, unsigned short id)
{
	ScopedLock<FastMutex> lock(mutex_);
	return enabled_ ? readFromMap(connector, id) : read(connector, id);
}

void DatapointDescriptionHolder::clear()
{
	ScopedLock<FastMutex> lock(mutex_);
	descriptions_.clear();
}

void DatapointDescriptionHolder::enable(bool enabled)
{
	ScopedLock<FastMutex> lock(mutex_);
	enabled_ = enabled;

	if (!enabled_)
	{
		descriptions_.clear();
	}
}

void DatapointDescriptionHolder::disable()
{
	ScopedLock<FastMutex> lock(mutex_);
	enabled_ = false;
	descriptions_.clear();
}

BaosDatapointDescription DatapointDescriptionHolder::readFromMap(BaosConnector::Ptr connector, unsigned short id)
{
	BaosDatapointDescription baosDatapointDescription;

	Descriptions::const_iterator iter = descriptions_.find(id);
	if (iter != descriptions_.end())
	{
		baosDatapointDescription = iter->second;
	}
	else
	{
		baosDatapointDescription = read(connector, id);
		descriptions_.insert(Descriptions::value_type(id, baosDatapointDescription));
	}

	return baosDatapointDescription;
}

BaosDatapointDescription DatapointDescriptionHolder::read(BaosConnector::Ptr connector, unsigned short id)
{
	BOOST_ASSERT(connector && "Invalid Connector");

	GetDatapointDescription service(connector);
	service.rpc(id, 1);
	const GetDatapointDescription::Descriptor& d = service.at(0);

	return BaosDatapointDescription(std::get<GetDatapointDescription::Id>(d),
	                                std::get<GetDatapointDescription::ValueType>(d),
	                                std::get<GetDatapointDescription::ConfigFlags>(d),
	                                std::get<GetDatapointDescription::DatapointType>(d));
}
