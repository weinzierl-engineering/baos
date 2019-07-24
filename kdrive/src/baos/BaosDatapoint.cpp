//
// Copyright (c) 2002-2019 WEINZIERL ENGINEERING GmbH
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
#include "kdrive/baos/BaosDatapoint.h"
#include "kdrive/baos/BaosDatapointDescriptions.h"
#include "kdrive/baos/services/GetDatapointValue.h"
#include "kdrive/baos/services/SetDatapointValue.h"
#include "kdrive/baos/services/GetDatapointDescription.h"
#include "kdrive/baos/services/GetDescriptionString.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/BaosConnector.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/knx/datapoint/Datapoint.h"
#include "kdrive/knx/datapoint/DatapointFactory.h"
#include "kdrive/knx/defines/DatapointTypes.h"

using namespace kdrive::connector;
using namespace kdrive::knx;
using namespace kdrive::baos;

BaosDatapoint::BaosDatapoint()

	: cacheEnabled_(false),
	  command_(BaosDatapointCommands::NoCommand)
{
}

BaosDatapoint::BaosDatapoint(BaosConnector::Ptr connector, unsigned short id)

	: connector_(connector),
	  cacheEnabled_(false),
	  command_(BaosDatapointCommands::SetNewValueAndSendOnBus)
{
	serverItem_.id = id;
	serverItem_.serviceData = 0;
	serverItem_.length = 0;
	readDatapointDescription();
}

BaosDatapoint::BaosDatapoint(BaosConnector::Ptr connector, const ServerItem& serverItem)

	: connector_(connector),
	  cacheEnabled_(!serverItem.data.empty()),
	  serverItem_(serverItem),
	  command_(BaosDatapointCommands::SetNewValueAndSendOnBus)
{
	readDatapointDescription();
}

BaosDatapoint::~BaosDatapoint()
{
}

void BaosDatapoint::setId(unsigned short id)
{
	serverItem_.id = id;
	readDatapointDescription();
	clearData();
}

unsigned short BaosDatapoint::getId() const
{
	return serverItem_.id;
}

const BaosDatapointDescription& BaosDatapoint::getDatapointDescription() const
{
	return description_;
}

void BaosDatapoint::setCommand(unsigned char command)
{
	command_ = command;
}

unsigned char BaosDatapoint::getCommand() const
{
	return command_;
}

void BaosDatapoint::readNewValueViaBus()
{
	sendSetDatapointValueCommand(BaosDatapointCommands::ReadNewValueViaBus);
}

void BaosDatapoint::clearTransmissionState()
{
	sendSetDatapointValueCommand(BaosDatapointCommands::ClearTransmissionState);
}

void BaosDatapoint::setData(const std::vector<unsigned char>& data)
{
	write(data);
}

const std::vector<unsigned char>& BaosDatapoint::getData()
{
	return read(0);
}

void BaosDatapoint::clearData()
{
	serverItem_.data.clear();
}

bool BaosDatapoint::isValidFlag() const
{
	return serverItem_.serviceData & ValidMask ? true : false;
}

bool BaosDatapoint::isUpdate() const
{
	return serverItem_.serviceData & UpdateMask ? true : false;
}

bool BaosDatapoint::isDataRequest() const
{
	return serverItem_.serviceData & DataRequestMask ? true : false;
}

int BaosDatapoint::getTransmissionStatus() const
{
	return serverItem_.serviceData & TransmissionStatusMask;
}

std::string BaosDatapoint::getDescriptionString()
{
	GetDescriptionString getDescriptionString(connector_);
	getDescriptionString.rpc(serverItem_.id, 1);
	return getDescriptionString.at(0);
}

const ServerItem& BaosDatapoint::getServerItem() const
{
	return serverItem_;
}

void BaosDatapoint::enableCache(bool cacheEnabled)
{
	cacheEnabled_ = cacheEnabled;
}

void BaosDatapoint::disableCache()
{
	enableCache(false);
}

void BaosDatapoint::setBoolean(bool value)
{
	write(value ? 0x01 : 0x00);
}

bool BaosDatapoint::getBoolean()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_1);
	dpt.setData(read(dpt.getSizeInBytes()));
	return decode_DPT1(dpt);
}

void BaosDatapoint::set1BitControl(bool control, bool value)
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_2);
	knx::encode_DPT2(dpt, control, value);
	write(dpt.getData());
}

bool BaosDatapoint::get1BitControl()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_2);
	dpt.setData(read(dpt.getSizeInBytes()));
	bool control = false;
	bool value = false;
	knx::decode_DPT2(dpt, control, value);
	return control;
}

bool BaosDatapoint::get1BitControlValue()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_2);
	dpt.setData(read(dpt.getSizeInBytes()));
	bool control = false;
	bool value = false;
	knx::decode_DPT2(dpt, control, value);
	return value;
}

void BaosDatapoint::set3BitControl(bool control, unsigned char value)
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_3);
	knx::encode_DPT3(dpt, control, value);
	write(dpt.getData());
}

bool BaosDatapoint::get3BitControl()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_3);
	dpt.setData(read(dpt.getSizeInBytes()));
	bool control = false;
	unsigned char value = 0x00;
	knx::decode_DPT3(dpt, control, value);
	return control;
}

unsigned char BaosDatapoint::get3BitControlValue()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_3);
	dpt.setData(read(dpt.getSizeInBytes()));
	bool control = false;
	unsigned char value = 0x00;
	knx::decode_DPT3(dpt, control, value);
	return value;
}

void BaosDatapoint::setCharacterSet(unsigned char value)
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_4);
	knx::encode_DPT4(dpt, value);
	write(dpt.getData());
}

unsigned char BaosDatapoint::getCharacterSet()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_4);
	dpt.setData(read(dpt.getSizeInBytes()));
	return knx::decode_DPT4(dpt);
}

void BaosDatapoint::set8BitUnsigned(unsigned char value)
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_5);
	knx::encode_DPT5(dpt, value);
	write(dpt.getData());
}

unsigned char BaosDatapoint::get8BitUnsigned()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_5);
	dpt.setData(read(dpt.getSizeInBytes()));
	return knx::decode_DPT5(dpt);
}

void BaosDatapoint::set8BitSigned(char value)
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_6);
	knx::encode_DPT6(dpt, value);
	write(dpt.getData());
}

char BaosDatapoint::get8BitSigned()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_6);
	dpt.setData(read(dpt.getSizeInBytes()));
	return knx::decode_DPT6(dpt);
}

void BaosDatapoint::set2OctetUnsigned(unsigned short value)
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_7);
	knx::encode_DPT7(dpt, value);
	write(dpt.getData());
}

unsigned short BaosDatapoint::get2OctetUnsigned()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_7);
	dpt.setData(read(dpt.getSizeInBytes()));
	return knx::decode_DPT7(dpt);
}

void BaosDatapoint::set2OctetSigned(short value)
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_8);
	knx::encode_DPT8(dpt, value);
	write(dpt.getData());
}

short BaosDatapoint::get2OctetSigned()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_8);
	dpt.setData(read(dpt.getSizeInBytes()));
	return knx::decode_DPT8(dpt);
}

void BaosDatapoint::set2OctetFloat(unsigned char msb, unsigned char lsb)
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_9);
	knx::encode_DPT9_Raw(dpt, msb, lsb);
	write(dpt.getData());
}

unsigned char BaosDatapoint::get2OctetFloatMsb()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_9);
	dpt.setData(read(dpt.getSizeInBytes()));
	const short data = knx::decode_DPT9_Raw(dpt);
	return (data >> 8) & 0xFF;
}

unsigned char BaosDatapoint::get2OctetFloatLsb()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_9);
	dpt.setData(read(dpt.getSizeInBytes()));
	const short data = knx::decode_DPT9_Raw(dpt);
	return data & 0xFF;
}

void BaosDatapoint::set2OctetFloat(float f)
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_9);
	knx::encode_DPT9(dpt, f);
	write(dpt.getData());
}

float BaosDatapoint::get2OctetFloat()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_9);
	dpt.setData(read(dpt.getSizeInBytes()));
	return knx::decode_DPT9(dpt);
}

void BaosDatapoint::setTimeLocal()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_10);
	knx::encode_DPT10_Local(dpt);
	write(dpt.getData());
}

void BaosDatapoint::setTimeUTC()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_10);
	knx::encode_DPT10_UTC(dpt);
	write(dpt.getData());
}

void BaosDatapoint::setTime(int day, int hour, int minute, int second)
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_10);
	knx::encode_DPT10(dpt, day, hour, minute, second);
	write(dpt.getData());
}

int BaosDatapoint::getTimeDay()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_10);
	dpt.setData(read(dpt.getSizeInBytes()));
	int day = 0, hour = 0, minute = 0, second = 0;
	knx::decode_DPT10(dpt, day, hour, minute, second);
	return day;
}

int BaosDatapoint::getTimeHour()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_10);
	dpt.setData(read(dpt.getSizeInBytes()));
	int day = 0, hour = 0, minute = 0, second = 0;
	knx::decode_DPT10(dpt, day, hour, minute, second);
	return hour;
}

int BaosDatapoint::getTimeMinute()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_10);
	dpt.setData(read(dpt.getSizeInBytes()));
	int day = 0, hour = 0, minute = 0, second = 0;
	knx::decode_DPT10(dpt, day, hour, minute, second);
	return minute;
}

int BaosDatapoint::getTimeSecond()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_10);
	dpt.setData(read(dpt.getSizeInBytes()));
	int day = 0, hour = 0, minute = 0, second = 0;
	knx::decode_DPT10(dpt, day, hour, minute, second);
	return second;
}

void BaosDatapoint::setDateLocal()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_11);
	knx::encode_DPT11_Local(dpt);
	write(dpt.getData());
}

void BaosDatapoint::setDateUTC()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_11);
	knx::encode_DPT11_UTC(dpt);
	write(dpt.getData());
}

void BaosDatapoint::setDate(int year, int month, int day)
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_11);
	knx::encode_DPT11_knx(dpt, year, month, day);
	write(dpt.getData());
}

int BaosDatapoint::getDateYear()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_11);
	dpt.setData(read(dpt.getSizeInBytes()));
	int year = 0, month = 0, day = 0;
	knx::decode_DPT11_knx(dpt, year, month, day);
	return year;
}

int BaosDatapoint::getDateMonth()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_11);
	dpt.setData(read(dpt.getSizeInBytes()));
	int year = 0, month = 0, day = 0;
	knx::decode_DPT11(dpt, year, month, day);
	return month;
}

int BaosDatapoint::getDateDay()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_11);
	dpt.setData(read(dpt.getSizeInBytes()));
	int year = 0, month = 0, day = 0;
	knx::decode_DPT11(dpt, year, month, day);
	return day;
}

void BaosDatapoint::set4OctetUnsigned(unsigned int value)
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_12);
	knx::encode_DPT12(dpt, value);
	write(dpt.getData());
}

unsigned int BaosDatapoint::get4OctetUnsigned()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_12);
	dpt.setData(read(dpt.getSizeInBytes()));
	return knx::decode_DPT12(dpt);
}

void BaosDatapoint::set4OctetSigned(int value)
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_13);
	knx::encode_DPT13(dpt, value);
	write(dpt.getData());
}

int BaosDatapoint::get4OctetSigned()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_13);
	dpt.setData(read(dpt.getSizeInBytes()));
	return knx::decode_DPT13(dpt);
}

void BaosDatapoint::set4OctetFloat(float value)
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_14);
	knx::encode_DPT14(dpt, value);
	write(dpt.getData());
}

float BaosDatapoint::get4OctetFloat()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_14);
	dpt.setData(read(dpt.getSizeInBytes()));
	return knx::decode_DPT14(dpt);
}

void BaosDatapoint::setAccess(unsigned int accessCode,
                              bool error,
                              bool permission,
                              bool direction,
                              bool encrypted,
                              unsigned char index)
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_15);
	knx::encode_DPT15(dpt, accessCode, error, permission, direction, encrypted, index);
	write(dpt.getData());
}

unsigned int BaosDatapoint::getAccessCode()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_15);
	dpt.setData(read(dpt.getSizeInBytes()));
	unsigned int accessCode = 0;
	bool error = false;
	bool permission = false;
	bool direction = false;
	bool encrypted = false;
	unsigned char index = 0x00;
	knx::decode_DPT15(dpt, accessCode, error, permission, direction, encrypted, index);
	return accessCode;
}

bool BaosDatapoint::getAccessError()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_15);
	dpt.setData(read(dpt.getSizeInBytes()));
	unsigned int accessCode = 0;
	bool error = false;
	bool permission = false;
	bool direction = false;
	bool encrypted = false;
	unsigned char index = 0x00;
	knx::decode_DPT15(dpt, accessCode, error, permission, direction, encrypted, index);
	return error;
}

bool BaosDatapoint::getAccessPermission()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_15);
	dpt.setData(read(dpt.getSizeInBytes()));
	unsigned int accessCode = 0;
	bool error = false;
	bool permission = false;
	bool direction = false;
	bool encrypted = false;
	unsigned char index = 0x00;
	knx::decode_DPT15(dpt, accessCode, error, permission, direction, encrypted, index);
	return permission;
}

bool BaosDatapoint::getAccessDirection()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_15);
	dpt.setData(read(dpt.getSizeInBytes()));
	unsigned int accessCode = 0;
	bool error = false;
	bool permission = false;
	bool direction = false;
	bool encrypted = false;
	unsigned char index = 0x00;
	knx::decode_DPT15(dpt, accessCode, error, permission, direction, encrypted, index);
	return direction;
}

bool BaosDatapoint::getAccessEncrypted()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_15);
	dpt.setData(read(dpt.getSizeInBytes()));
	unsigned int accessCode = 0;
	bool error = false;
	bool permission = false;
	bool direction = false;
	bool encrypted = false;
	unsigned char index = 0x00;
	knx::decode_DPT15(dpt, accessCode, error, permission, direction, encrypted, index);
	return encrypted;
}

unsigned char BaosDatapoint::getAccessIndex()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_15);
	dpt.setData(read(dpt.getSizeInBytes()));
	unsigned int accessCode = 0;
	bool error = false;
	bool permission = false;
	bool direction = false;
	bool encrypted = false;
	unsigned char index = 0x00;
	knx::decode_DPT15(dpt, accessCode, error, permission, direction, encrypted, index);
	return index;
}

void BaosDatapoint::setString(const std::string& str)
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_16);
	knx::encode_DPT16(dpt, str);
	write(dpt.getData());
}

std::string BaosDatapoint::getString()
{
	Datapoint dpt = DatapointFactory::create(DatapointTypes::DatapointType_16);
	dpt.setData(read(dpt.getSizeInBytes()));
	return knx::decode_DPT16(dpt);
}

void BaosDatapoint::write(unsigned char data)
{
	const std::vector<unsigned char> v(1, data);
	write(v);
}

void BaosDatapoint::write(const std::vector<unsigned char>& data)
{
	if (data.size() != description_.getValueTypeSizeBytes())
	{
		throw ClientException("Invalid Datapoint Value Type");
	}

	serverItem_.length = data.size();
	serverItem_.data = data;

	SetDatapointValue::Value value(serverItem_);
	value.serviceData = command_;

	SetDatapointValue service(connector_);
	service.rpc(serverItem_.id, value);
}

const std::vector<unsigned char>& BaosDatapoint::read(unsigned char expectedLength)
{
	if (!cacheEnabled_)
	{
		clearData();
	}

	if (expectedLength)
	{
		validate(expectedLength);
	}

	if (serverItem_.data.empty())
	{
		GetDatapointValue service(connector_);
		service.rpc(serverItem_.id, 1);
		serverItem_ = service.at(0);
	}

	return serverItem_.data;
}

void BaosDatapoint::validate(unsigned char expectedLength)
{
	if (expectedLength != description_.getValueTypeSizeBytes())
	{
		throw ClientException("Invalid Datapoint Value Type");
	}
}

void BaosDatapoint::readDatapointDescription()
{
	description_ = DatapointDescriptionHolder::instance().get(connector_, serverItem_.id);
}

void BaosDatapoint::sendSetDatapointValueCommand(unsigned char command)
{
	SetDatapointValue::Value value;
	value.id = serverItem_.id;
	value.serviceData = command;
	value.length = 0;

	SetDatapointValue service(connector_);
	service.rpc(value.id, value);
}

