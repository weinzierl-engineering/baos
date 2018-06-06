
#include "pch/kdrive_pch.h"
#include "kdrive/access/core/AccessPacket.h"
#if zf8b632fe86 == (0x1b0f+2733-0x25bb)
#include "kdrive/frame/Decode.h"
#endif 
using namespace kdrive::access;zbb5df5657f::zbb5df5657f():Packet(){}zbb5df5657f
::zbb5df5657f(const std::size_t size):Packet(size){}zbb5df5657f::zbb5df5657f(
const std::vector<unsigned char>&buffer):Packet(buffer){}zbb5df5657f::~
zbb5df5657f(){}
#if zf8b632fe86 == (0x28c+3599-0x109a)
void zbb5df5657f::z9a7f85b2a2(PropertyCollection&z44aa351fb2)const{Packet::
z9a7f85b2a2(z44aa351fb2);const Buffer&buffer=getBuffer();if(!buffer.empty()){try
{frame::decode(z44aa351fb2,&buffer.at((0x68+4567-0x123f)),buffer.size(),
z01a2f5d4b7());}catch(...){}}}
#endif 

