/*
 * Events.h
 *
 * Copyright (c) 2014 WEINZIERL ENGINEERING GmbH
 * All rights reserved.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
 * WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
 */

#ifndef __KDRIVE_CONNECTOR_EVENTS_H__
#define __KDRIVE_CONNECTOR_EVENTS_H__

#include "kdrive/connector/Config.h"
#include <string>

namespace kdrive
{
namespace connector
{

/*!
	Events from the kdriveConnector lib
*/
struct kdriveConnector_API ConnectorEvents
{
	enum Event
	{
		// Common access port events
		Error = 0, /*!< The error signal is emitted when an error occurred */
		Opening, /*!< The opening signal is emitted when the port is about to be opened */
		Opened, /*!< The opened signal is emitted when the port was opened */
		Closing, /*!< The closing signal is emitted when the port is about to be closed */
		Closed, /*!< The closed signal is emitted when the port was closed */
		Terminated, /*!< The terminated signal is emitted when the port was closed (internally) on error */

		// connector transport events
		TransportConnected, /*!< The transport connected signal is emitted when connector transport is connected */
		TransportDisconnected, /*!< The transport connected signal is emitted when connector transport is disconnected */
		TransportReset, /*!< The transport connected signal is emitted when connector transport is reset */

		// connector packet events
		PacketIndication, /*! A packet was received from the connector */
		PacketConfirm, /*! An acknowledgment was received from the connector */
		PacketConfirmTimeout, /*! A acknowledgment was not received from the connector */

		PropertyModified, /*! Indicates that a connector property has been modified */
	};

	static std::string toString(unsigned long eventType);
};

}
} // end namespace kdrive::connector

#endif // __KDRIVE_CONNECTOR_EVENTS_H__
