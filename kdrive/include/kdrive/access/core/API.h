
#ifndef ze2ec3a82fd
#define ze2ec3a82fd
#include "kdrive/access/Config.h"
#include <string>
namespace kdrive{namespace access{struct z23bd02551e BusType{static const 
unsigned int Unknown=(0x96a+7369-0x2633);static const unsigned int z43532822e8=
(0x839+4481-0x18ba);static const unsigned int ze7d25e6b7d=(0x2df+3907-0x1082);
static const unsigned int za9166dba58=(0x1af2+1377-0x1e53);static const unsigned
 int z1f3e01a8d3=(0x2387+537-0x1ba0);static const unsigned int Mask=65535;};
struct z23bd02551e zb3e0b864a4{static const unsigned int Unknown=
(0x3e5+8743-0x260c);static const unsigned int zde1a3f75da=65536;static const 
unsigned int zfc2a03fb7b=131072;static const unsigned int z5c0da4e005=196608;
static const unsigned int zd7079456aa=262144;static const unsigned int 
zfadbd77e70=327680;static const unsigned int ze8f651f47b=393216;static const 
unsigned int z26e2160d04=458752;static const unsigned int Mask=16711680;};struct
 z23bd02551e PortType{static const unsigned int Unknown=BusType::Unknown|
zb3e0b864a4::Unknown;static const unsigned int zd67ccd1c5d=BusType::z43532822e8|
zb3e0b864a4::zde1a3f75da;static const unsigned int z377d41a288=BusType::
z43532822e8|zb3e0b864a4::zfc2a03fb7b;static const unsigned int zf2d41bfaa3=
BusType::z43532822e8|zb3e0b864a4::zfadbd77e70;static const unsigned int 
zc9f491f48e=BusType::z43532822e8|zb3e0b864a4::ze8f651f47b;static const unsigned 
int z753a0201dc=BusType::z43532822e8|zb3e0b864a4::z5c0da4e005;static const 
unsigned int zedd692a3fe=BusType::z43532822e8|zb3e0b864a4::zd7079456aa;static 
const unsigned int zf88f0e3b1a=BusType::z43532822e8|zb3e0b864a4::z26e2160d04;};
struct z23bd02551e za498009d76{enum z5031e65207{Unknown=(0x4f+5265-0x14e0),None=
(0x1022+2225-0x18c3),z26a323d5e5=(0xc30+1611-0x127a),zb100d7cac0=
(0x8af+3754-0x1757),z1746fd28fd=(0x48+7328-0x1ce4),};static std::string 
getDescription(unsigned int zd2b01bb0a4);};struct z23bd02551e zd521a6809b{enum 
zfe13db3c77{PortType=(0x9ed+111-0xa5b),z756d42fa3c,za498009d76,z9884ee4d6b,
zb5ec3c9a78,Address,z794a4bb896,z46b1b5b271,BaudRate,Parity,z27e627203d,
z8fe7055b5e,ze8ba4cefcf,z37cb7e5f16,z829f62376e,MediumType};};struct z23bd02551e
 z8c5d8f9b53{static const unsigned int Unknown=(0x1a17+1019-0x1e12);static const
 unsigned int ze2af0c1d2c=16777216;static const unsigned int z109cde3d4c=
33554432;static const unsigned int Mask=4278190080;};struct z23bd02551e 
za381e09502{static const unsigned int zc17ea40b11=(0x27d+3151-0xecc);static 
const unsigned int z228f1cc6d4=z8c5d8f9b53::ze2af0c1d2c;static const unsigned 
int Rx=z8c5d8f9b53::z109cde3d4c;static const unsigned int z3e6a70b68a=Rx|
z228f1cc6d4;};}}
#endif 

