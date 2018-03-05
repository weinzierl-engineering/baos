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

#ifndef __KDRIVE_BAOS_CORE_BAOS_CONNECTOR_H__
#define __KDRIVE_BAOS_CORE_BAOS_CONNECTOR_H__

#include "kdrive/baos/Config.h"
#include "kdrive/connector/QueueConnector.h"

namespace kdrive
{
namespace baos
{

/*!
	\class BaosConnector
	The BaosConnector is a QueueConnector which means it is possible
	to use the queue to obtain the Rx packet notifications. You have
	to enable to queue to receive notifications.
	There are several versions of the Baos protocol and each version
	implements its own BaosConnector type (i.e. handles the socket
	communication and the packetization). The BaosConnector type
	is used through the library as the main connector type.
*/
class kdriveRPC_baos_API BaosConnector : public connector::QueueConnector
{
public:
	typedef std::shared_ptr<BaosConnector> Ptr;

	BaosConnector() = delete;

	/*!
		Destroys the BaosConnector
	*/
	virtual ~BaosConnector();

	/*!
		Sets the protocol version
	*/
	void setVersion(unsigned char version);

	/*!
		Returns the protocol version
	*/
	unsigned char getVersion() const;

	/*!
		Indicates whether the rx thread is still running,
		which means that the connector is connected.
		Note: it is possible that the rx thread is still running
		and the connector is not connected, and there is typically a small
		delay before a socket exception is thrown and the rx thread is
		shutdown
	*/
	bool isConnected() const;

public:
	static const std::string Version; /*!< Property Key for version, set by the connector type or enumeration */

protected:
	/*!
		Creates the BaosConnector
		The version should be one of the versions from
		the API ProtocolVersions
		This class is never directly instanced, but is
		derived from by one of the StreamConnector protocol classes
	*/
	BaosConnector(unsigned char version);
};

}
} // end namespace kdrive::baos

#endif // __KDRIVE_BAOS_CORE_BAOS_CONNECTOR_H__
