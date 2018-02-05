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

using namespace kdrive::baos;

/**************************************
** BaosConnector
***************************************/

const std::string BaosConnector::Version = "baos.version";

BaosConnector::~BaosConnector()
{
	disableSignals();
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
	setProperty(BaosConnector::Version, version);
	enableSignals();
}
