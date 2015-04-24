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

#include "pch/kdrive_pch.h"
#include "kdrive/connector/ScopedConnectorSignals.h"
#include "kdrive/connector/Connector.h"
#include "kdrive/connector/Packet.h"

using namespace kdrive::connector;

ScopedConnectorSignals::ScopedConnectorSignals(Connector& connector)

	: connector_(connector),
	  signalsEnabled_(connector_.areSignalsEnabled())
{
	connector_.enableSignals();
}

ScopedConnectorSignals::~ScopedConnectorSignals()
{
	connection_.disconnect();
	connector_.enableSignals(signalsEnabled_);
}

void ScopedConnectorSignals::connect(std::function<void (Packet::Ptr, int)> fn)
{
	connection_ = connector_.getPacketSignal().connect(fn);
}

void ScopedConnectorSignals::connectRx(std::function<void (Packet::Ptr)> fn)
{
	connection_ = connector_.getPacketSignalRx().connect(fn);
}

void ScopedConnectorSignals::connectTx(std::function<void (Packet::Ptr)> fn)
{
	connection_ = connector_.getPacketSignalTx().connect(fn);
}

