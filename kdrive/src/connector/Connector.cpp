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
#include "kdrive/connector/Connector.h"
#include "kdrive/connector/ConnectorNotificationHandler.h"
#include "kdrive/connector/Packet.h"
#include "kdrive/connector/ErrorCodes.h"
#include "kdrive/connector/Events.h"
#include "kdrive/connector/PacketFactory.h"
#include "kdrive/utility/Logger.h"
#include "kdrive/utility/LoggerFormatter.h"
#include <Poco/Exception.h>
#include <Poco/Format.h>
#include <Poco/Bugcheck.h>
#include <boost/assert.hpp>

using namespace kdrive::connector;
using kdrive::utility::PropertyCollection;
using kdrive::utility::LoggerFormatter;
using Poco::FastMutex;
using Poco::Dynamic::Var;
using Poco::format;
using Poco::ScopedLock;
using Poco::Exception;

CLASS_LOGGER("kdrive.connector.Connector")

/**************************************
** Anonymous namespace
***************************************/

namespace
{

void initProperties(kdrive::utility::PropertyCollection& collection)
{
	collection.setProperty(Connector::PortType, Connector::ConnectorTypeLabel);
	collection.setProperty(Connector::LastErrorCode, static_cast<unsigned int>(ConnectorErrorCodes::None));
	collection.setProperty(Connector::LastErrorMessage, "");
}

} // end anonymous namespace

/**************************************
** Connector
***************************************/

const std::string Connector::PortType = "port.type";
const std::string Connector::ConnectorTypeLabel = "Connector";
const std::string Connector::LastErrorCode = "last_error_code";
const std::string Connector::LastErrorMessage = "last_error_message";

Connector::Connector()

	: packetFactory_(std::make_shared<PacketFactory>()),
	  semaphore_(n, max),
	  open_(false)
{
	initProperties(*this);
}

Connector::Connector(PacketFactory::Ptr packetFactory)

	: packetFactory_(packetFactory),
	  semaphore_(n, max),
	  open_(false)
{
	BOOST_ASSERT(packetFactory_ && "Invalid Packet Factory");
	initProperties(*this);
}

Connector::Connector(const Connector& connector)

	: PropertyCollection(connector),
	  packetFactory_(connector.packetFactory_),
	  semaphore_(n, max),
	  open_(false)
{
}

/*
	Do not call closeUnsafe here, because
	isOpenImpl and closeImpl are virtual functions!
	The drived classes should call this!
*/
Connector::~Connector()
{
	try
	{
		disableSignals();
	}
	catch (...)
	{
	}
}

Connector& Connector::operator=(const Connector& connector)
{
	if (this != &connector)
	{
		packetFactory_ = connector.packetFactory_;
	}

	return *this;
}

void Connector::open()
{
	ScopedLock<FastMutex> lock(mutex_);

	try
	{
		if (!isOpenImpl())
		{
			enableSignals();
			routeEvent(ConnectorEvents::Opening);
			openImpl();
			open_ = true;
			routeEvent(ConnectorEvents::Opened);
		}
	}
	catch (Exception& e)
	{
		poco_error_f1(LOGGER(), "Open failed: %s", e.displayText());
		raiseError(e);
	}
}

void Connector::close()
{
	ScopedLock<FastMutex> lock(mutex_);
	try
	{
		closeUnsafe();
	}
	catch (Exception& e)
	{
		poco_error_f1(LOGGER(), "error close %s", e.displayText());
		raiseError(e);
	}
}

bool Connector::isOpen() const
{
	ScopedLock<FastMutex> lock(mutex_);
	open_ = isOpenImpl();
	return open_;
}

void Connector::send(Packet::Ptr packet)
{
	// nothing to do
	// must be handled by derived classes
}

Packet::Ptr Connector::receive()
{
	// nothing to do
	Packet::Ptr packet;
	return packet;
}

Packet::Ptr Connector::waitReceive(long milliseconds)
{
	// nothing to do
	Packet::Ptr packet;
	return packet;
}

void Connector::clearRx()
{
	// nothing to do
}

void Connector::clearTx()
{
	// nothing to do
}

std::string Connector::getDescription()
{
	return "Connector";
}

void Connector::setProperties(const PropertyCollection& propertyCollection)
{
	join(propertyCollection, true);
}

void Connector::resetProperties()
{
	poco_information(LOGGER(), "resetProperties");
	resetPropertiesImpl();
}

void Connector::enumerate(Ports& ports)
{
	ScopedLock<FastMutex> lock(mutex_);
	enumerateImpl(ports);
}

std::string Connector::getConnectorType() const
{
	return getProperty<std::string>(PortType);
}

void Connector::setPreferredSettings()
{
	setPreferredSettingsImpl();
}

unsigned int Connector::getLastErrorCode() const
{
	return getProperty<unsigned int>(LastErrorCode);
}

std::string Connector::getLastErrorMessage() const
{
	return getProperty<std::string>(LastErrorMessage);
}

Connector::PacketSignal& Connector::getPacketSignal()
{
	return packetSignal_;
}

Connector::PacketSignalRx& Connector::getPacketSignalRx()
{
	return packetSignalRx_;
}

Connector::PacketSignalTx& Connector::getPacketSignalTx()
{
	return packetSignalTx_;
}

Connector::EventSignal& Connector::getEventSignal()
{
	return eventSignal_;
}

Connector::QueueSignal& Connector::getQueueSignal()
{
	return queueSignal_;
}

void Connector::enableSignals(bool enable)
{
	if (enable || notificationHandlerPtr_)
	{
		getNotificationHandler().enableSignals(enable);
	}
}

void Connector::disableSignals()
{
	enableSignals(false);
}

bool Connector::areSignalsEnabled() const
{
	return getNotificationHandler().areSignalsEnabled();
}

void Connector::setPacketFactory(PacketFactory::Ptr packetFactory)
{
	BOOST_ASSERT(packetFactory && "Invalid Packet Factory");
	packetFactory_ = packetFactory;
}

PacketFactory::Ptr Connector::getPacketFactory()
{
	return packetFactory_;
}

void Connector::waitSem()
{
	semaphore_.wait();
}

void Connector::waitSem(long milliseconds)
{
	semaphore_.wait(milliseconds);
}

bool Connector::tryWaitSem(long milliseconds)
{
	return semaphore_.tryWait(milliseconds);
}

void Connector::setSem()
{
	semaphore_.set();
}

void Connector::setQueueSignalTrigger(int queueSignalTrigger)
{
	return getNotificationHandler().setQueueSignalTrigger(queueSignalTrigger);
}

/*
	Set the own connector description only when not already set
*/
void Connector::routeRx(Packet::Ptr packet)
{
	setPacketProperties(packet);
	return getNotificationHandler().routeRx(packet);
}

/*
	Set the own connector description only when not already set
*/
void Connector::routeTx(Packet::Ptr packet)
{
	setPacketProperties(packet);
	return getNotificationHandler().routeTx(packet);
}

void Connector::routeEvent(unsigned long e)
{
	return getNotificationHandler().routeEvent(e);
}

void Connector::setNotificationHandler(NotificationHandlerPtr notificationHandler)
{
	notificationHandlerPtr_ = notificationHandler;
}

void Connector::setPropertyUnsafe(const std::string& key, const Var& value)
{
	poco_trace_f2(LOGGER(), "Setting property: %s -> %s", key, LoggerFormatter::toString(value));
	PropertyCollection::setPropertyUnsafe(key, value);
	routeEvent(ConnectorEvents::PropertyModified);
}

Packet::Ptr Connector::create(const unsigned char* buffer, std::size_t bufferLength)
{
	return packetFactory_->create(buffer, bufferLength);
}

ConnectorNotificationHandler& Connector::getNotificationHandler()
{
	if (!notificationHandlerPtr_)
	{
		notificationHandlerPtr_ = std::make_shared<AsyncConnectorNotificationHandler>(*this);
	}
	return *notificationHandlerPtr_;
}

const ConnectorNotificationHandler& Connector::getNotificationHandler() const
{
	if (!notificationHandlerPtr_)
	{
		Connector& connector = const_cast<Connector&>(*this);
		notificationHandlerPtr_ = std::make_shared<AsyncConnectorNotificationHandler>(connector);
	}
	return *notificationHandlerPtr_;
}

void Connector::closeUnsafe()
{
	if (isOpenImpl())
	{
		routeEvent(ConnectorEvents::Closing);
		closeImpl();
		open_ = false;
		routeEvent(ConnectorEvents::Closed);
		disableSignals();
	}
}

void Connector::setLastErrorCode(unsigned int errorCode)
{
	setProperty(LastErrorCode, errorCode);
}

void Connector::setLastErrorMessage(const std::string& errorMessage)
{
	setProperty(LastErrorMessage, errorMessage);
}

void Connector::raiseError(const Poco::Exception& exception)
{
	kdrive::connector::raiseError(*this, exception);
}

void Connector::resetPropertiesImpl()
{
	clear();
	initProperties(*this);
}

void Connector::enumerateImpl(Ports& ports)
{
	// nothing to do
}

void Connector::openImpl()
{
	// nothing to do
}

void Connector::closeImpl()
{
	// nothing to do
}

bool Connector::isOpenImpl() const
{
	return open_;
}

void Connector::setPreferredSettingsImpl()
{
	// nothing to do
}

void Connector::setPacketProperties(Packet::Ptr packet)
{
	if (packet->arePropertiesEnabled())
	{
		packet->setTimestamp();

		if (packet->getConnectorDescription().empty())
		{
			packet->setConnectorDescription(getDescription());
		}
	}
}
/*****************************
** raiseError
******************************/

void kdrive::connector::raiseError(Connector& connector, const Exception& exception)
{
	const int errorCode = exception.code() ? exception.code() : ConnectorErrorCodes::ConnectorError;

	connector.setLastErrorCode(errorCode);
	connector.setLastErrorMessage(exception.displayText());
	connector.routeEvent(ConnectorEvents::Error);
	exception.rethrow();
}
