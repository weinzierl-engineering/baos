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
#include "kdrive/baos/core/BaosPacketFactory.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/DataPacket.h"
#include "kdrive/connector/Packet.h"

using namespace kdrive::connector;
using namespace kdrive::baos;

BaosPacketFactory::BaosPacketFactory()
{
}

BaosPacketFactory::~BaosPacketFactory()
{
}

Packet::Ptr BaosPacketFactory::create(const unsigned char* buffer, std::size_t bufferLength)
{
	// not sure what this packet is
	Packet::Ptr packet = std::make_shared<Packet>();
	packet->readFromBuffer(buffer, bufferLength);
	return packet;
}

DataPacket::Ptr BaosPacketFactory::createFromSubService(unsigned char subService, unsigned char errorCode)
{
	DataPacket::Ptr packet;

	if (!errorCode)
	{
		if ((subService >= RequestFunctions::MinRequest) &&
		    (subService <= RequestFunctions::MaxRequest))
		{
			packet = std::make_shared<DataRequest>();
		}
		else if ((subService >= ResponseFunctions::MinResponse) &&
		         (subService <= ResponseFunctions::MaxResponse))
		{
			packet = std::make_shared<DataResponse>();
		}
		else if (subService == IndicationFunctions::DatapointValueIndication)
		{
			packet = std::make_shared<DatapointValueIndication>();
		}
		else if (subService == IndicationFunctions::ServerItemIndication)
		{
			packet = std::make_shared<ServerItemIndication>();
		}
	}
	else
	{
		packet = std::make_shared<ErrorResponse>();
	}

	return packet;
}
