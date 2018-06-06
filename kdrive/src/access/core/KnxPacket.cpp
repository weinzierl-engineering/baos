
#include "pch/kdrive_pch.h"
#include "kdrive/access/core/KnxPacket.h"
#include "kdrive/knx/telegrams/formatters/AbstractFrame.h"
using namespace kdrive::access;using kdrive::knx::zb6eb8808c0;KnxPacket::
KnxPacket():zbb5df5657f((0xe81+2805-0x18f6)){setProtocol("\x6b\x6e\x78");}
KnxPacket::KnxPacket(const std::size_t size):zbb5df5657f(size){setProtocol(
"\x6b\x6e\x78");}KnxPacket::KnxPacket(const std::vector<unsigned char>&buffer):
zbb5df5657f(buffer){setProtocol("\x6b\x6e\x78");}KnxPacket::KnxPacket(
zb6eb8808c0&z94036d98fc){setProtocol("\x6b\x6e\x78");std::vector<unsigned char>
buffer;z94036d98fc.write(buffer);setBuffer(buffer);}KnxPacket::~KnxPacket(){}
KnxPacket::Ptr KnxPacket::convert(Packet::Ptr packet,bool validate){return 
Packet::convert<KnxPacket>(packet,validate);}
