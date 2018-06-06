
#ifndef z762afff567
#define z762afff567
#include "kdrive/access/Config.h"
#include "kdrive/access/core/AccessPacket.h"
namespace kdrive{namespace access{class z23bd02551e TransportPacket:public 
zbb5df5657f{public:typedef std::shared_ptr<TransportPacket>Ptr;TransportPacket()
;TransportPacket(const std::size_t size);explicit TransportPacket(const std::
vector<unsigned char>&buffer);virtual~TransportPacket();static Ptr convert(
connector::Packet::Ptr packet,bool validate);};}}
#endif 

