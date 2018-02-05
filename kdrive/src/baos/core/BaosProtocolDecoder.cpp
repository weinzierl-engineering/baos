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
#include "kdrive/baos/core/BaosProtocolDecoder.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/DataPacket.h"
#include "kdrive/connector/Connector.h"
#include "kdrive/utility/Logger.h"
#include "kdrive/utility/LoggerFormatter.h"
#include <Poco/NumberFormatter.h>
#include <Poco/Logger.h>
#include <iostream>
#include <sstream>
#include <functional>

using Poco::NumberFormatter;
using namespace kdrive::connector;
using namespace kdrive::baos;
using namespace kdrive::utility;

CLASS_LOGGER("kdrive.baos.ProtocolDecoder")

#define BIND(function) \
	Connector::PacketSignal::slot_type(std::bind(&ProtocolDecoder::function, this, \
		std::placeholders::_1, std::placeholders::_2))

ProtocolDecoder::ProtocolDecoder()
{
}

ProtocolDecoder::ProtocolDecoder(Connector& connector)
{
	connect(connector);
}

ProtocolDecoder::~ProtocolDecoder()
{
	disconnect();
}

void ProtocolDecoder::connect(Connector& connector)
{
	disconnect();
	Connector::PacketSignal& s = connector.getPacketSignal();
	connection_ = s.connect(BIND(onPacket));
}

void ProtocolDecoder::disconnect()
{
	connection_.disconnect();
}

void ProtocolDecoder::decode(std::string& s, Packet::Ptr packet, int direction)
{
	s.append(direction == Connector::Rx ? "Rx" : "Tx");
	s.append(" : ");
	formatString(s, packet);
}

void ProtocolDecoder::onPacket(Packet::Ptr packet, int direction)
{
	std::string s;
	decode(s, packet, direction);
	poco_information(LOGGER(), s);
}

void ProtocolDecoder::formatString(std::string& s, Packet::Ptr packet)
{
	DataPacket::Ptr dataPacket = std::dynamic_pointer_cast<DataPacket>(packet);

	if (dataPacket)
	{
		s.append(log(dataPacket->getSubService()));
		s.append("\n");
	}

	if (packet && packet->size())
	{
		std::vector<unsigned char> v(packet->size());
		packet->writeToBuffer(&v.at(0), v.size());
		s.append(LoggerFormatter::toHex(&v.at(0), v.size()));
	}
	else
	{
		s.append("(null packet)");
	}
}

std::string ProtocolDecoder::log(unsigned char subService)
{
	switch (subService)
	{
			/***************************
			** Requests
			****************************/
		case RequestFunctions::GetServerItem:
			return "RequestFunctions::GetServerItem";
		case RequestFunctions::SetServerItem:
			return "RequestFunctions::SetServerItem";
		case RequestFunctions::GetDatapointDescription:
			return "RequestFunctions::GetDatapointDescription";
		case RequestFunctions::GetDescriptionString:
			return "RequestFunctions::GetDescriptionString";
		case RequestFunctions::GetDatapointValue:
			return "RequestFunctions::GetDatapointValue";
		case RequestFunctions::SetDatapointValue:
			return "RequestFunctions::SetDatapointValue";
		case RequestFunctions::GetParameterByte:
			return "RequestFunctions::GetParameterByte";
		case RequestFunctions::GetDatapointHistoryCommand:
			return "RequestFunctions::GetDatapointHistoryCommand";
		case RequestFunctions::GetDatapointHistoryState:
			return "RequestFunctions::GetDatapointHistoryState";
		case RequestFunctions::GetDatapointHistory:
			return "RequestFunctions::GetDatapointHistory";
		case RequestFunctions::GetTimer:
			return "RequestFunctions::GetTimer";
		case RequestFunctions::SetTimer:
			return "RequestFunctions::SetTimer";

			/***************************
			** Responses
			****************************/
		case ResponseFunctions::GetServerItem:
			return "ResponseFunctions::GetServerItem";
		case ResponseFunctions::SetServerItem:
			return "ResponseFunctions::SetServerItem";
		case ResponseFunctions::GetDatapointDescription:
			return "ResponseFunctions::GetDatapointDescription";
		case ResponseFunctions::GetDescriptionString:
			return "ResponseFunctions::GetDescriptionString";
		case ResponseFunctions::GetDatapointValue:
			return "ResponseFunctions::GetDatapointValue";
		case ResponseFunctions::SetDatapointValue:
			return "ResponseFunctions::SetDatapointValue";
		case ResponseFunctions::GetParameterByte:
			return "ResponseFunctions::GetParameterByte";
		case ResponseFunctions::GetDatapointHistoryCommand:
			return "ResponseFunctions::GetDatapointHistoryCommand";
		case ResponseFunctions::GetDatapointHistoryState:
			return "ResponseFunctions::GetDatapointHistoryState";
		case ResponseFunctions::GetDatapointHistory:
			return "ResponseFunctions::GetDatapointHistory";
		case ResponseFunctions::GetTimer:
			return "ResponseFunctions::GetTimer";
		case ResponseFunctions::SetTimer:
			return "ResponseFunctions::SetTimer";

			/***************************
			** Indications
			****************************/
		case IndicationFunctions::DatapointValueIndication:
			return "IndicationFunctions::DatapointValueIndication";
		case IndicationFunctions::ServerItemIndication:
			return "IndicationFunctions::ServerItemIndication";
	}

	return "Unknown Sub Service";
}
