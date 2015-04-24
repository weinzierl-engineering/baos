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
#include "kdrive/baos/core/BaosPacketFactory.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/DataPacket.h"
#include "kdrive/connector/Packet.h"
#include "kdrive/utility/Logger.h"

using namespace kdrive::connector;
using namespace kdrive::baos;

CLASS_LOGGER("kdrive.baos.BaosPacketFactory")

BaosPacketFactory::BaosPacketFactory()
{
}

BaosPacketFactory::~BaosPacketFactory()
{
}

Packet::Ptr BaosPacketFactory::create(const unsigned char* buffer, std::size_t bufferLength)
{
	// not sure what this packet is
	Packet::Ptr packet(new Packet);
	packet->readFromBuffer(buffer, bufferLength);
	return packet;
}

DataPacket::Ptr BaosPacketFactory::createFromSubService(unsigned char subService, unsigned char errorCode)
{
	DataPacket::Ptr packet;

	if (!errorCode)
	{
		switch (subService)
		{
			case RequestFunctions::GetServerItem:
			case RequestFunctions::SetServerItem:
			case RequestFunctions::GetDatapointDescription:
			case RequestFunctions::GetDescriptionString:
			case RequestFunctions::GetDatapointValue:
			case RequestFunctions::SetDatapointValue:
			case RequestFunctions::GetParameterByte:
				packet.reset(new DataRequest);
				break;

			case ResponseFunctions::GetServerItem:
			case ResponseFunctions::SetServerItem:
			case ResponseFunctions::GetDatapointDescription:
			case ResponseFunctions::GetDescriptionString:
			case ResponseFunctions::GetDatapointValue:
			case ResponseFunctions::SetDatapointValue:
			case ResponseFunctions::GetParameterByte:
				packet.reset(new DataResponse);
				break;

			case IndicationFunctions::DatapointValueIndication:
				packet.reset(new DatapointValueIndication);
				break;

			case IndicationFunctions::ServerItemIndication:
				packet.reset(new ServerItemIndication);
				break;
		}
	}
	else
	{
		packet.reset(new ErrorResponse);
	}

	return packet;
}
