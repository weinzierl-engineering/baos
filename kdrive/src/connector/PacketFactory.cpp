//
// Copyright (c) 2002-2019 WEINZIERL ENGINEERING GmbH
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
#include "kdrive/connector/PacketFactory.h"
#include "kdrive/connector/Packet.h"

using namespace kdrive::connector;

PacketFactory::~PacketFactory()
{
}

Packet::Ptr PacketFactory::create(const unsigned char* buffer, std::size_t bufferLength)
{
	Packet::Ptr packet = std::make_shared<Packet>(bufferLength);
	packet->readFromBuffer(buffer, bufferLength);
	return packet;
}
