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
#include "kdrive/baos/core/BaosConnector.h"
#include <atomic>

using namespace kdrive::baos;

/**************************************
** Anonymous namespace
***************************************/

namespace
{

/*!
	The drive classes set RouteTransportPacket to visible, when supported
*/
void initProperties(kdrive::utility::PropertyCollection& collection)
{
	collection.setProperty(BaosConnector::RouteTransportPacket, false);


}

class ConnectorIdHelper
{
public:
	static unsigned int getUniqueId();

private:
	static std::atomic<unsigned int> nextPortId_; /*!<A unique id for the next port */
};

std::atomic<unsigned int> ConnectorIdHelper::nextPortId_ = 1;

unsigned int ConnectorIdHelper::getUniqueId()
{
	return nextPortId_++;
}

} // end anonymous namespace

/**************************************
** BaosConnector
***************************************/

const std::string BaosConnector::ConnectorId = "baos.connector_id";
const std::string BaosConnector::Version = "baos.version";
const std::string BaosConnector::RouteTransportPacket = "baos.route_transport_packet";

BaosConnector::~BaosConnector()
{
	disableSignals();
}

unsigned int BaosConnector::getConnectorId() const
{
	return getProperty(ConnectorId);
}

void BaosConnector::setVersion(unsigned char version)
{
	setProperty(Version, version);
}

unsigned char BaosConnector::getVersion() const
{
	return getProperty(Version);
}

bool BaosConnector::isConnected() const
{
	return getRxCallbackThread().isRunning();
}


BaosConnector::BaosConnector(unsigned char version)
{
	initProperties(*this);
	setProperty(BaosConnector::Version, version);
	setProperty(BaosConnector::ConnectorId, ConnectorIdHelper::getUniqueId());

	enableSignals();
}

void BaosConnector::resetPropertiesImpl()
{
	const unsigned int id = getProperty(BaosConnector::ConnectorId);

	QueueConnector::resetPropertiesImpl();

	initProperties(*this);
	setProperty(BaosConnector::ConnectorId, id);
}

