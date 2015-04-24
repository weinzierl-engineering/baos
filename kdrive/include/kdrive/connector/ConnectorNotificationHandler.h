//
// Copyright (c) 2002-2015 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//

#ifndef __KDRIVE_CONNECTOR_CONNECTOR_NOTIFICATION_H__
#define __KDRIVE_CONNECTOR_CONNECTOR_NOTIFICATION_H__

#include "kdrive/connector/Config.h"
#include "kdrive/connector/Forwards.h"
#include "kdrive/connector/CallbackThread.h"
#include "kdrive/connector/PacketNotification.h"
#include <Poco/AtomicCounter.h>
#include <boost/noncopyable.hpp>
#include <memory>

namespace kdrive
{
namespace connector
{

class Connector;

/*****************************
** ConnectorNotificationHandler
******************************/

class kdriveConnector_API ConnectorNotificationHandler : private boost::noncopyable
{
public:
	typedef std::shared_ptr<ConnectorNotificationHandler> Ptr;

	ConnectorNotificationHandler(Connector& connector);
	virtual ~ConnectorNotificationHandler();

	virtual void enableSignals(bool enabled = true);
	virtual void disableSignals();
	virtual bool areSignalsEnabled() const;
	virtual void setQueueSignalTrigger(int queueSignalTrigger);
	virtual void routeRx(std::shared_ptr<Packet> packet);
	virtual void routeTx(std::shared_ptr<Packet> packet);
	virtual void routeEvent(unsigned long e);
	virtual void routeQueueSignal(int current, int previous);

protected:
	Connector& getConnector();
	int getQueueSignalTrigger() const;
	void setPreviousQueueSize(int previousQueueSize);
	int getPreviousQueueSize() const;
	void emitRouteRx(std::shared_ptr<Packet> packet);
	void emitRouteTx(std::shared_ptr<Packet> packet);
	void emitRouteEvent(unsigned long e);
	void emitRouteQueueSignal(int current, int previous);

private:
	Connector& connector_;
	Poco::AtomicCounter enabled_;
	Poco::AtomicCounter queueSignalTrigger_;
	int previousQueueSize_;
};

/*****************************
** AsyncConnectorNotificationHandler
******************************/

class PacketNotification;

class kdriveConnector_API AsyncConnectorNotificationHandler : public ConnectorNotificationHandler
{
public:
	using Ptr = std::shared_ptr<AsyncConnectorNotificationHandler>;

	AsyncConnectorNotificationHandler(Connector& connector);
	virtual ~AsyncConnectorNotificationHandler();

	virtual void enableSignals(bool enabled = true);
	virtual void routeRx(std::shared_ptr<Packet> packet);
	virtual void routeTx(std::shared_ptr<Packet> packet);
	virtual void routeEvent(unsigned long e);

protected:
	using ConnectorNotificationHandler::routeQueueSignal;

private:
	void enqueue(std::shared_ptr<PacketNotification> notification);
	void onThreadCallback();
	void onNotification(std::shared_ptr<PacketNotification> notification);

private:
	PacketNotificationQueue queue_;
	CallbackThread callbackThread_;
	CallbackThreadManager callbackThreadManager_;
};

}
} // end namespace kdrive::connector

#endif // __KDRIVE_CONNECTOR_CONNECTOR_NOTIFICATION_H__
