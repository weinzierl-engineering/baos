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
#include "kdrive/baos/ft12/FT12Connector.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/DataPacket.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/baos/protocols/Protocol2x.h"
#include "kdrive/baos/protocols/Protocol12.h"
#include "kdrive/connector/Wait.h"
#include "kdrive/knx/telegrams/formatters/Formatter.h"
#include "kdrive/knx/defines/FT12Constants.h"
#include "kdrive/utility/Logger.h"
#include <Poco/Exception.h>

using namespace kdrive::connector;
using namespace kdrive::baos;
using namespace kdrive::ft12;
using Poco::Exception;
using kdrive::knx::ft12::FT12Constants;
using kdrive::knx::Formatter;
using kdrive::knx::Buffer;
using kdrive::knx::ByteFormatter;
using kdrive::knx::WordFormatter;
using kdrive::connector::waitPacketWithPolicy;

CLASS_LOGGER("kdrive.baos.FT12Connector")

/**************************************
** Anonymous namespace
***************************************/

namespace
{

enum Defaults
{
	DefaultBaudrate = 19200,
	RxBufferLength = 30
};

void initProperties(kdrive::utility::PropertyCollection& collection)
{
	collection.setProperty(FT12Connector::PortType, FT12Connector::ConnectorTypeLabel);
	collection.setProperty(FT12Connector::SerialDeviceName, "");
}

enum EmiCodes
{
	Emi_PEI_Identify_Req = 0xA7,
	Emi_PEI_Identify_Con = 0xA8
};

/*******************************
** PEI_Identify_Req
********************************/

/*!
	Telegram Formatter for PEI_Identify.req Services

	<b>System Specifications:</b>
	\li 03_06_03 EMI_IMI v1.1 AS<br />
		3.3.9.5 PEI_Identify.req message (EMI2)

	PEI_Identify.req message
	\verbatim
	|------------|
	|            |
	|   1 byte   |
	|            |
	|------------|
	|     MC     |
	|------------|
	\endverbatim
*/
class PEI_Identify_Req : public Formatter
{
public:
	PEI_Identify_Req();

	bool isValid() const override;
	void setDefaults() override;

private:
	ByteFormatter messageCode_;
};

PEI_Identify_Req::PEI_Identify_Req()
{
	addFormatter(&messageCode_);
	messageCode_.set(EmiCodes::Emi_PEI_Identify_Req);
}

bool PEI_Identify_Req::isValid() const
{
	return (messageCode_.get() == EmiCodes::Emi_PEI_Identify_Req) && Formatter::isValid();
}

void PEI_Identify_Req::setDefaults()
{
	Formatter::setDefaults();
	messageCode_.set(EmiCodes::Emi_PEI_Identify_Req);
}

/*******************************
** PEI_Identify_Con
********************************/

/*!
	Telegram Formatter for PEI_Identify.con Services

	<b>System Specifications:</b>
	\li 03_06_03 EMI_IMI v1.1 AS<br />
		3.3.9.6 PEI_Identify.con message (EMI2)

	PEI_Identify.con message (EMI2)
	\verbatim
	|------------|------------|------------|
	|   1 byte   |   2 bytea  |   6 bytes  |
	|------------|------------|------------|
	|     MC     | Ind. addr. | Serial no  |
	|------------|------------|------------|
	\endverbatim
*/
class PEI_Identify_Con : public Formatter
{
public:
	PEI_Identify_Con();

	bool isValid() const override;
	void setDefaults() override;

private:
	ByteFormatter messageCode_;
	WordFormatter individualAddress_;
	ByteFormatter serialNumber00_;
	ByteFormatter serialNumber01_;
	ByteFormatter serialNumber02_;
	ByteFormatter serialNumber03_;
	ByteFormatter serialNumber04_;
	ByteFormatter serialNumber05_;
};

PEI_Identify_Con::PEI_Identify_Con()
{
	addFormatter(&messageCode_);
	addFormatter(&individualAddress_);
	addFormatter(&serialNumber00_);
	addFormatter(&serialNumber01_);
	addFormatter(&serialNumber02_);
	addFormatter(&serialNumber03_);
	addFormatter(&serialNumber04_);
	addFormatter(&serialNumber05_);

	messageCode_.set(EmiCodes::Emi_PEI_Identify_Con);
}

bool PEI_Identify_Con::isValid() const
{
	return (messageCode_.get() == EmiCodes::Emi_PEI_Identify_Con) && Formatter::isValid();
}

void PEI_Identify_Con::setDefaults()
{
	Formatter::setDefaults();
	messageCode_.set(EmiCodes::Emi_PEI_Identify_Con);
}

/*******************************
** Weinzierl_PEI_Identify_Con
********************************/

/*!
	Telegram Formatter for Weinzierl PEI_Identify.con Services

	PEI_Identify.con message (cEMI)
	\verbatim
	|------------|------------|------------|------------|
	|   1 byte   |   2 bytes  |   6 bytes  |   2 bytes  |
	|------------|------------|------------|------------|
	|     MC     | Ind. addr. | Serial no  | EMI types  |
	|------------|------------|------------|------------|

	EMI types:
		Supported EMI types
		1 = EMI 1
		2 = EMI 2
		4 = cEMI
*/
class Weinzierl_PEI_Identify_Con : public PEI_Identify_Con
{
public:
	Weinzierl_PEI_Identify_Con();

private:
	WordFormatter supportedEmiTypes_;
};

Weinzierl_PEI_Identify_Con::Weinzierl_PEI_Identify_Con()
{
	addFormatter(&supportedEmiTypes_);
}

/*******************************
** Generic_PEI_Identify_Con
********************************/

class Generic_PEI_Identify_Con : public Formatter
{
public:
	Generic_PEI_Identify_Con();

	std::size_t size() const override;
	bool isValid() const override;
	void setDefaults() override;

	bool isEmi2Frame() const;
	bool isEmiCFrame() const;

public:
	enum SupportedProtocols
	{
		SupportedEmi1 = 0x01, /*! reserved for EMI 1 (no device known with FT 1.2 EMI 1) */
		SupportedEmi2 = 0x02, /*! (reserved; NOTE: EMI 2 devives do not send this in PEI_Identify services) */
		SupportedEmiC = 0x04
	};

private:
	std::size_t readImpl(const Buffer& buffer) override;
	std::size_t writeImpl(Buffer& buffer) override;

	std::size_t tryReadEmiCFrame(const Buffer& buffer);

private:
	bool isEmi2Frame_;
	PEI_Identify_Con emi2Frame_;
	Weinzierl_PEI_Identify_Con cemiFrame_;
};

Generic_PEI_Identify_Con::Generic_PEI_Identify_Con()

	: isEmi2Frame_(true)
{
}

std::size_t Generic_PEI_Identify_Con::size() const
{
	return isEmi2Frame_ ? emi2Frame_.size() : cemiFrame_.size();
}

bool Generic_PEI_Identify_Con::isValid() const
{
	return isEmi2Frame_ ? emi2Frame_.isValid() : cemiFrame_.isValid();
}

void Generic_PEI_Identify_Con::setDefaults()
{
	emi2Frame_.setDefaults();
	cemiFrame_.setDefaults();
}

bool Generic_PEI_Identify_Con::isEmi2Frame() const
{
	return isEmi2Frame_;
}

bool Generic_PEI_Identify_Con::isEmiCFrame() const
{
	return !isEmi2Frame_;
}

std::size_t Generic_PEI_Identify_Con::readImpl(const Buffer& buffer)
{
	const std::size_t sizeEmi2 = emi2Frame_.read(buffer);
	const std::size_t sizeEmiC = tryReadEmiCFrame(buffer);

	return isEmi2Frame_ ? sizeEmi2 : sizeEmiC;
}

std::size_t Generic_PEI_Identify_Con::writeImpl(Buffer& buffer)
{
	return isEmi2Frame_ ? emi2Frame_.write(buffer) :
	       cemiFrame_.write(buffer);
}

std::size_t Generic_PEI_Identify_Con::tryReadEmiCFrame(const Buffer& buffer)
{
	std::size_t size = 0;
	try
	{
		size = cemiFrame_.read(buffer);
		isEmi2Frame_ = false;
	}
	catch (...)
	{
		isEmi2Frame_ = true;
	}
	return size;
}

/******************************
** TelegramWaitPolicy
*******************************/

/*!
	Telegram Wait Policy waits for a specific telegram
	using a kdriveKnx Formatter
*/
class TelegramWaitPolicy
{
public:
	TelegramWaitPolicy(Connector& connector,
	                   kdrive::knx::AbstractFormatter& formatter)

		: connector_(connector),
		  formatter_(formatter)
	{
	}

	std::shared_ptr<Packet> operator()(unsigned long timeout)
	{
		Packet::Ptr packet = connector_.waitReceive(timeout);
		Packet::Buffer& buffer = packet->getBuffer();

		// We need this try-catch block, to catch possible exceptions
		// from the formatter read function, if the buffer is to small.
		try
		{
			formatter_.read(buffer);
			if (formatter_.isValid())
			{
				return packet;
			}
		}
		catch (...)
		{
		}

		packet.reset();
		return packet;
	}

private:
	kdrive::connector::Connector& connector_;
	kdrive::knx::AbstractFormatter& formatter_;
};

void readPeiIdentify(FT12Connector& port, Generic_PEI_Identify_Con& con)
{
	ScopedQueueConnectorRxQueue scopedQueue(port);

	PEI_Identify_Req req;
	Packet::Ptr packet = std::make_shared<Packet>(req.size());
	req.write(packet->getBuffer());
	port.send(packet);

	try
	{
		TelegramWaitPolicy policy(scopedQueue, con);
		waitPacketWithPolicy<Packet>(policy, 1000);
	}
	catch (Poco::TimeoutException&)
	{
		throw Poco::TimeoutException("PEI_Identify.Con missing");
	}
}

} // end anonymous namespace

/**************************************
** FT12Connector
***************************************/

#define BIND_SENDER() \
	std::bind(&FT12_Packetizer::sendBuffer, &packetizer_, std::placeholders::_1, std::placeholders::_2)

#define BIND_USER_DATA_CALLBACK() \
	std::bind(&FT12Connector::onTelegramInd, this, std::placeholders::_1)

const std::string FT12Connector::ConnectorTypeLabel = "baos.serial.ft12";
const std::string FT12Connector::SerialDeviceName = "baos.serial.device_name";

/*
	Set default rx timeout to 20ms
	And the rx + tx buffer to 256 bytes
*/
FT12Connector::FT12Connector()

	: BaosConnector(ProtocolVersions::Unknown),
	  txBuffer_(FT12Constants::MaxBufferSize),
	  rxBuffer_(FT12Constants::MaxBufferSize),
	  packetizer_(serialPort_, 20)
{
	initProperties(*this);

	ft12_.setSender(BIND_SENDER());
	ft12_.setUserDataCallback(BIND_USER_DATA_CALLBACK());
}

FT12Connector::~FT12Connector()
{
	try
	{
		close();
	}
	catch (...)
	{
	}
}

void FT12Connector::open(const std::string& serialDeviceName)
{
	setProperty(SerialDeviceName, serialDeviceName);
	BaosConnector::open();
}

std::string FT12Connector::getDescription()
{
	return getSerialDeviceName();
}

std::string FT12Connector::getSerialDeviceName() const
{
	return getProperty(SerialDeviceName);
}

void FT12Connector::openImpl()
{
	try
	{
		setVersion(ProtocolVersions::Unknown);

		serialPort_.open(getSerialDeviceName(), DefaultBaudrate, "8E1", kdrive::io::serial::SerialPort::FLOW_NONE);
		startRxThread();
		ft12_.init();

		// Get version from PeiIdentify confirm
		Generic_PEI_Identify_Con con;
		readPeiIdentify(*this, con);

		if (con.isEmi2Frame())
		{
			setVersion(ProtocolVersions::V12);
			setPacketFactory(std::make_shared<PacketFactory12>());
		}
		else
		{
			setVersion(ProtocolVersions::V20);
			setPacketFactory(std::make_shared<PacketFactory2x>());
		}
	}
	catch (...)
	{
		stopRxThread();
		serialPort_.close();
		throw;
	}
}

void FT12Connector::closeImpl()
{
	stopRxThread();
	serialPort_.close();
}

bool FT12Connector::isOpenImpl() const
{
	return serialPort_.isOpen();
}

void FT12Connector::resetPropertiesImpl()
{
	BaosConnector::resetPropertiesImpl();
	initProperties(*this);
}

void FT12Connector::txImpl(Packet::Ptr packet)
{
	try
	{
		unsigned char* buffer = &txBuffer_.at(0);
		std::memset(buffer, 0, FT12Constants::MaxBufferSize);
		const std::size_t size = packet->writeToBuffer(buffer, FT12Constants::MaxBufferSize);
		ft12_.sendVariableLengthFrame(buffer, size);
		routeTx(packet);
	}
	catch (Exception& exception)
	{
		poco_warning_f1(LOGGER(), "Error in txImpl, %s", exception.displayText());
		raiseError(exception);
	}
}

void FT12Connector::rxImpl()
{
	try
	{
		unsigned char* ptr = &rxBuffer_.at(0);
		const std::size_t length = packetizer_.get(ptr, rxBuffer_.size());

		if (length)
		{
			ft12_.onReceive(ptr, length);
		}
	}
	catch (Exception& exception)
	{
		poco_information_f1(LOGGER(), "Error in rxImpl, %s", exception.displayText());
		raiseError(exception);
	}
}

void FT12Connector::onTelegramInd(const std::vector<unsigned char>& buffer)
{
	if (!buffer.empty())
	{
		Packet::Ptr packet = create(&buffer.at(0), buffer.size());
		routeRx(packet);
	}
}
