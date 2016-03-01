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

#include "pch/kdrive_pch.h"
#include "kdrive/connector/Events.h"

using namespace kdrive::connector;

std::string ConnectorEvents::toString(unsigned long eventType)
{
	switch (eventType)
	{
		case Error:
			return "Error";
		case Opening:
			return "Opening";
		case Opened:
			return "Opened";
		case Closing:
			return "Closing";
		case Closed:
			return "Closed";
		case Terminated:
			return "Terminated";
		case TransportConnected:
			return "TransportConnected";
		case TransportDisconnected:
			return "TransportDisconnected";
		case TransportReset:
			return "TransportReset";
		case PacketIndication:
			return "PacketIndication";
		case PacketConfirm:
			return "PacketConfirm";
		case PacketConfirmTimeout:
			return "PacketConfirmTimeout";
		default:
			return "Unknown";
	}
}
