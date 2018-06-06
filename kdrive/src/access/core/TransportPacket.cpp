
#include "pch/kdrive_pch.h"
#include "kdrive/access/core/TransportPacket.h"
using namespace kdrive::access;TransportPacket::TransportPacket():zbb5df5657f(
(0x1d88+2546-0x26fa)){}TransportPacket::TransportPacket(const std::size_t size):
zbb5df5657f(size){}TransportPacket::TransportPacket(const std::vector<unsigned 
char>&buffer):zbb5df5657f(buffer){}TransportPacket::~TransportPacket(){}
TransportPacket::Ptr TransportPacket::convert(Packet::Ptr packet,bool validate){
return Packet::convert<TransportPacket>(packet,validate);}
