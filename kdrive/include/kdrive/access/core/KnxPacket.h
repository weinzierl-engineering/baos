
#ifndef z5fe71f7723
#define z5fe71f7723
#include "kdrive/access/Config.h"
#include "kdrive/access/core/AccessPacket.h"
namespace kdrive{namespace knx{class zb6eb8808c0;}}namespace kdrive{namespace 
access{class z23bd02551e KnxPacket:public zbb5df5657f{public:typedef std::
shared_ptr<KnxPacket>Ptr;KnxPacket();KnxPacket(const std::size_t size);explicit 
KnxPacket(const std::vector<unsigned char>&buffer);explicit KnxPacket(kdrive::
knx::zb6eb8808c0&z94036d98fc);virtual~KnxPacket();template<class z0b55957dc5>
bool z5369660e9e(){try{z0b55957dc5 formatter;formatter.read(getBuffer());return 
formatter.isValid();}catch(...){}return false;}static Ptr convert(connector::
Packet::Ptr packet,bool validate);};}}
#endif 

