
#include "pch/kdrive_pch.h"
#include "kdrive/knx/datapoint/FloatConverter.h"
#include <Poco/Exception.h>
#include <boost/assert.hpp>
using Poco::Exception;using namespace kdrive::knx;
#ifndef LOBYTE
#define LOBYTE(w)           ((unsigned char)(w))
#endif
#ifndef HIBYTE
#define HIBYTE(w)           ((unsigned char)(((unsigned short)(w) >> \
(0x9dd+7439-0x26e4)) & (0x17ac+344-0x1805)))
#endif
namespace{enum{z29f4a76e7e=((0xa2f+3234-0x16d0)<<(0x113a+643-0x13bd)),
zb7abd287b2=((0x119b+1928-0x1922)<<(0x18fa+3186-0x2565))};inline unsigned short 
zbd8225acd5(unsigned char zd2969cd9a0,unsigned char zbab9feb3b8){return(
zd2969cd9a0<<(0x14cd+3819-0x23b0))|zbab9feb3b8;}inline unsigned int zc774514371(
unsigned int zbcc37c79d8,unsigned int zb9144bc744){return(zbcc37c79d8<<
zb9144bc744);}inline unsigned int zcaf0822456(unsigned int zbcc37c79d8,unsigned 
int zb9144bc744){return(zbcc37c79d8>>zb9144bc744);}bool z96835402e2(const 
unsigned char*zf1b4948a61,int*z4a168aa0ed){unsigned short z3fbf55ec47;unsigned 
short z6a3d60feee;int zc776ffe020;if((zf1b4948a61[(0x1246+906-0x15d0)]==
(0xef1+5987-0x25d5))&&(zf1b4948a61[(0x56+7302-0x1cdb)]==(0x34d+2253-0xb1b))){
return false;}z3fbf55ec47=zbd8225acd5(zf1b4948a61[(0x1f6c+535-0x2183)],
zf1b4948a61[(0x929+627-0xb9b)]);zc776ffe020=z3fbf55ec47&(0x1948+199-0x1210);
z6a3d60feee=zc774514371(z29f4a76e7e,(zcaf0822456(zf1b4948a61[
(0x19bc+1967-0x216b)],(0x1e5d+1336-0x2392))&(0xa27+714-0xce2)));if(zf1b4948a61[
(0x129c+1486-0x186a)]&(0x1793+2387-0x2066)){zc776ffe020-=(0xbb2+6112-0x1b92);}*
z4a168aa0ed=(int)zc776ffe020*z6a3d60feee;return true;}bool zc614577611(int 
za5d37097ad,unsigned char*zf1b4948a61){unsigned int zc776ffe020;unsigned short 
z71c19641b2;unsigned char z1d09706214;unsigned char z54c29ce3a2;if(za5d37097ad>=
(0xb1c+1486-0x10ea)){zc776ffe020=(unsigned int)za5d37097ad;z71c19641b2=
(0x8e6+4658-0x1319);}else{zc776ffe020=(unsigned int)-za5d37097ad;z71c19641b2=
(0xc15+1028-0x819);}z54c29ce3a2=(0x53a+399-0x6c9);z1d09706214=(0xa3b+490-0xc25);
while((zc776ffe020+z54c29ce3a2)>z71c19641b2){z54c29ce3a2=(unsigned char)(
zc776ffe020&(0xfc7+4768-0x2266));zc776ffe020>>=(0x1f65+85-0x1fb9);z1d09706214++;
}zc776ffe020+=z54c29ce3a2;if(z1d09706214>(0x3bd+1364-0x902)){zf1b4948a61[
(0xcb6+1965-0x1463)]=(0xe53+3752-0x1c7c);zf1b4948a61[(0x18c3+2071-0x20d9)]=
(0x30a+4516-0x13af);return false;}if(za5d37097ad>=(0x1a+6389-0x190f)){
zf1b4948a61[(0xc3f+296-0xd67)]=(0x559+6952-0x2081);}else{zc776ffe020=
(0x212c+1868-0x2078)-zc776ffe020;zf1b4948a61[(0x111d+5076-0x24f1)]=zb7abd287b2;}
zf1b4948a61[(0x1877+69-0x18bc)]|=(z1d09706214<<(0x413+7479-0x2147))&
(0x2007+1006-0x237d);zf1b4948a61[(0x115+4637-0x1332)]|=HIBYTE(zc776ffe020);
zf1b4948a61[(0x474+8487-0x259a)]=LOBYTE(zc776ffe020);return true;}bool 
zdef5f59c85(const unsigned char*zf1b4948a61,float*z9cc9e2d328){int z0ebbf53421;
if(z96835402e2(zf1b4948a61,&z0ebbf53421)){*z9cc9e2d328=static_cast<float>(
z0ebbf53421/100.0);return true;}return false;}bool z0c13fe1e16(float z7478171ae5
,unsigned char*zf1b4948a61){int za5d37097ad;z7478171ae5*=100.0;if(z7478171ae5>
(0x14af+4321-0x2590)){za5d37097ad=(int)(z7478171ae5+0.5);}else{za5d37097ad=(int)
(z7478171ae5-0.5);}return zc614577611(za5d37097ad,zf1b4948a61);}}float 
zac29c93fda::z03088b6602(unsigned char zba1cbc76ee,unsigned char z68419f84d9){
return zdfe51b7ee0(zba1cbc76ee,z68419f84d9);}std::tuple<unsigned char,unsigned 
char>zac29c93fda::zb219ab2908(float f){unsigned char z97f999352c[
(0x4b2+1480-0xa78)]={(0x81+1911-0x7f8)};if(!z0c13fe1e16(f,z97f999352c)){throw 
Exception(
"\x56\x61\x6c\x75\x65\x20\x6f\x75\x74\x20\x6f\x66\x20\x4b\x4e\x58\x20\x66\x6c\x6f\x61\x74\x31\x36\x20\x72\x61\x6e\x67\x65"
);}return std::make_tuple(z97f999352c[(0x380+7825-0x2211)],z97f999352c[
(0x10d9+5150-0x24f6)]);}float zac29c93fda::zdfe51b7ee0(unsigned char zba1cbc76ee
,unsigned char z68419f84d9){const unsigned char z97f999352c[(0x57d+5777-0x1c0c)]
={zba1cbc76ee,z68419f84d9};float zb41d1f2878=(0x3ad+6777-0x1e26);if(!zdef5f59c85
(z97f999352c,&zb41d1f2878)){throw Exception(
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x4b\x4e\x58\x20\x66\x6c\x6f\x61\x74\x20\x76\x61\x6c\x75\x65"
);}return zb41d1f2878;}
