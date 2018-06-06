
#include "pch/kdrive_pch.h"
#include "kdrive/knx/telegrams/formatters/TupleFormatter.h"
#include "kdrive/knx/core/ByteStream.h"
using namespace kdrive::knx;static unsigned char z6e08813f2a(const Buffer&buffer
,int z43d31e9636);static unsigned char z31f50de9ca(const std::vector<unsigned 
char>&bits,int bit);static void setBit(std::vector<unsigned char>&v,int bit,bool
 set=true);static unsigned char z3a5600b8f2(int bit);unsigned int zd49fb66547::
read(int z202059467a,int z43d31e9636,int z5e1f916d4c,const Buffer&buffer){
unsigned int value=(0x1158+450-0x131a);bool zc28285ef02=true;if(!z43d31e9636&&!(
z5e1f916d4c%(0x1476+3736-0x2306))){const unsigned char*ptr=buffer.z15e6bd8652(
z202059467a,z5e1f916d4c/(0x485+3136-0x10bd));switch(z5e1f916d4c){case
(0x4ec+8700-0x26e0):value=ze378c24725<unsigned char,(0x255+3273-0xf1d)>(ptr,
(0x1129+3454-0x1ea6));zc28285ef02=false;break;case(0x1de6+1116-0x2232):value=
ze378c24725<unsigned short,(0x18e5+1431-0x1e7a)>(ptr,(0x70a+7246-0x2356));
zc28285ef02=false;break;case(0x8e5+2639-0x1314):value=ze378c24725<unsigned int,
(0x11e8+5277-0x2681)>(ptr,(0xc02+1937-0x138f));zc28285ef02=false;break;}}if(
zc28285ef02){const int zbc178aa3d1=(z202059467a*(0xf88+184-0x1038))+z43d31e9636;
std::vector<unsigned char>v((0x15aa+3257-0x225f),(0x7b8+946-0xb6a));for(int 
index=(0x1068+1523-0x165b);index<z5e1f916d4c;++index){const unsigned char bit=
z6e08813f2a(buffer,zbc178aa3d1+index);if(bit){setBit(v,(z5e1f916d4c-
(0x6b5+2846-0x11d2))-index);}}value=ze378c24725<unsigned int,(0x863+6998-0x23b5)
>(v);}return value;}void z3e0ba55e2c::write(int z202059467a,int z43d31e9636,int 
z5e1f916d4c,Buffer&buffer,unsigned int value){std::vector<unsigned char>v;if(!
z43d31e9636&&!(z5e1f916d4c%(0x1a07+2967-0x2596))){switch(z5e1f916d4c){case
(0x2c1+5720-0x1911):v=zd5c4ea2fc7<unsigned char,(0x961+1318-0xe86)>(value&
(0x957+1394-0xdca));break;case(0x19d4+2111-0x2203):v=zd5c4ea2fc7<unsigned short,
(0xc61+3072-0x185f)>(value&65535);break;case(0x100+891-0x45b):v=zd5c4ea2fc7<
unsigned int,(0x1e78+1535-0x2473)>(value);break;}}if(v.empty()){const int 
zaedc3f0d88=z43d31e9636+z5e1f916d4c;const int bytes=(zaedc3f0d88/
(0xa4a+2135-0x1299))+(zaedc3f0d88%(0x108+5952-0x1840)?(0x15aa+4159-0x25e8):
(0xe81+4338-0x1f73));const unsigned char*ptr=buffer.z15e6bd8652(z202059467a,
bytes);v.resize(bytes);std::copy(ptr,ptr+bytes,v.begin());const std::vector<
unsigned char>bits=zd5c4ea2fc7<unsigned int,(0x5f+9391-0x250a)>(value);const int
 zd75d054e02=z43d31e9636+z5e1f916d4c;const int zc5ec778132=(bytes*
(0x1332+405-0x14bf))-zd75d054e02;for(int index=(0x8fa+4342-0x19f0);index<
z5e1f916d4c;++index){const unsigned char bit=z31f50de9ca(bits,index);setBit(v,
index+zc5ec778132,bit?true:false);}}buffer.za213db16c9(z202059467a,&v.at(
(0x26a+8937-0x2553)),v.size());}static unsigned char z6e08813f2a(const Buffer&
buffer,int z43d31e9636){const int z202059467a=z43d31e9636/(0x1b9a+299-0x1cbd);
const unsigned char*ptr=buffer.z15e6bd8652(z202059467a,(0x783+2166-0xff8));
return*ptr&z3a5600b8f2((0xd8d+1226-0x1250)-(z43d31e9636%(0xcef+4854-0x1fdd)))?
(0xa6+6535-0x1a2c):(0x1dcd+699-0x2088);}static unsigned char z31f50de9ca(const 
std::vector<unsigned char>&bits,int bit){const int z202059467a=bits.size()-(bit/
(0x9fc+2398-0x1352))-(0x21b4+41-0x21dc);return bits[z202059467a]&z3a5600b8f2(bit
%(0xb01+2852-0x161d))?(0xf2+9402-0x25ab):(0xf7+8598-0x228d);}static void setBit(
std::vector<unsigned char>&v,int bit,bool set){const int z202059467a=v.size()-(
bit/(0x175d+301-0x1882))-(0x3bf+7697-0x21cf);if(set){v[z202059467a]|=
(0x1bf4+759-0x1eea)<<(bit%(0x2d2+435-0x47d));}else{v[z202059467a]&=~(
(0x900+4625-0x1b10)<<(bit%(0xad+335-0x1f4)));}}static unsigned char z3a5600b8f2(
int bit){return(0x45b+8851-0x26ed)<<bit;}
