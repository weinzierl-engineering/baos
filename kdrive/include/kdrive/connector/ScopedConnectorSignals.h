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

#ifndef __KDRIVE_CONNECTOR_SCOPED_CONNECTOR_SIGNALS_H__
#define __KDRIVE_CONNECTOR_SCOPED_CONNECTOR_SIGNALS_H__

#include "kdrive/connector/Config.h"
#include <boost/signals2.hpp>
#include <memory>
#include <functional>

namespace kdrive
{
namespace connector
{

class Connector;
class Packet;

/*********************************
** ConnectorScopedSignals
**********************************/

/*!
	ScopedConnectorSignals can be used to temporarily (i.e. while in scope)
	enable the connector signals. It defines a scoped connection to hold
	the signal connection, which means that as soon as this class goes out of
	scope, the signal will be disconnected, even if the connectors signals
	are still enabled

	This class is primarily for internal kdrive use.
*/
class kdriveConnector_API ScopedConnectorSignals final
{
public:
	ScopedConnectorSignals(Connector& connector);
	ScopedConnectorSignals(const ScopedConnectorSignals&) = delete;
	~ScopedConnectorSignals();
	ScopedConnectorSignals& operator=(const ScopedConnectorSignals&) = delete;

	void connect(std::function<void (std::shared_ptr<Packet>, int)> fn);
	void connectRx(std::function<void (std::shared_ptr<Packet>)> fn);
	void connectTx(std::function<void (std::shared_ptr<Packet>)> fn);

	Connector& connector_; /*! The connector. */
	bool signalsEnabled_; /*!< Were the signals enabled before we enabled it. */
	boost::signals2::scoped_connection connection_; /*! Signal connection for packet signal. */
};

}
} // end namespace kdrive::connector

#endif // __KDRIVE_CONNECTOR_SCOPED_CONNECTOR_SIGNALS_H__

