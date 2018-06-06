
#include "pch/kdrive_pch.h"
#include "kdrive/knx/core/Buffer.h"
#include <Poco/Exception.h>
#include <boost/assert.hpp>
#include <cstring>
using namespace kdrive::knx;using Poco::Exception;Buffer::Buffer():z7ec3461dd4(
nullptr),z4de44892fb((0x2ed+2921-0xe56)){}Buffer::Buffer(unsigned char*buffer,
std::size_t bufferSize):z7ec3461dd4(buffer),z4de44892fb(bufferSize){if(
bufferSize){BOOST_ASSERT(buffer&&
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x50\x6f\x69\x6e\x74\x65\x72");}}Buffer::~
Buffer(){}void Buffer::setBuffer(unsigned char*buffer,std::size_t bufferSize){if
(bufferSize){BOOST_ASSERT(buffer&&
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x50\x6f\x69\x6e\x74\x65\x72");}z7ec3461dd4=
buffer;z4de44892fb=bufferSize;}void Buffer::setBuffer(std::vector<unsigned char>
&buffer){if(!buffer.empty()){z7ec3461dd4=&buffer.at((0x178b+3151-0x23da));
z4de44892fb=buffer.size();}else{reset();}}const unsigned char*Buffer::getBuffer(
)const{return z7ec3461dd4;}unsigned char*Buffer::getBuffer(){return z7ec3461dd4;
}std::size_t Buffer::z727230908f()const{return z4de44892fb;}bool Buffer::
zd1b5fa7c57()const{return(!z7ec3461dd4||!z4de44892fb);}void Buffer::reset(){
z7ec3461dd4=nullptr;z4de44892fb=(0x4c3+578-0x705);}void Buffer::assign(unsigned 
char data){if(!zd1b5fa7c57()){std::memset(z7ec3461dd4,data,z4de44892fb);}}void 
Buffer::zb8203d7346(unsigned int offset,unsigned char data){z1d943f3f75(offset);
z7ec3461dd4[offset]=data;}void Buffer::z740eff6f6e(unsigned int offset,unsigned 
short data){z1d943f3f75(offset+(0x2da+9243-0x26f4));z7ec3461dd4[offset]=(data>>
(0x257+3075-0xe52))&(0x2e8+4233-0x1272);z7ec3461dd4[offset+(0x803+6757-0x2267)]=
data&(0x1515+3369-0x213f);}void Buffer::za213db16c9(unsigned int offset,const 
unsigned char*buffer,std::size_t bufferSize){if(buffer&&bufferSize){z1d943f3f75(
(offset+bufferSize)-(0x892+7481-0x25ca));unsigned char*ptr=z7ec3461dd4+offset;
std::memcpy(ptr,buffer,bufferSize);}}unsigned char Buffer::z02b8347997(unsigned 
int offset)const{z1d943f3f75(offset);return z7ec3461dd4[offset];}unsigned short 
Buffer::readWord(unsigned int offset)const{z1d943f3f75(offset+
(0x871+5914-0x1f8a));unsigned short data=z7ec3461dd4[offset]<<
(0xad5+3990-0x1a63);data|=z7ec3461dd4[offset+(0x1535+4068-0x2518)];return data;}
unsigned char*Buffer::z15e6bd8652(unsigned int offset,std::size_t bufferSize){
z1d943f3f75((offset+bufferSize)-(0x14a0+2176-0x1d1f));return z7ec3461dd4+offset;
}const unsigned char*Buffer::z15e6bd8652(unsigned int offset,std::size_t 
bufferSize)const{z1d943f3f75((offset+bufferSize)-(0xd1a+3398-0x1a5f));return 
z7ec3461dd4+offset;}void Buffer::z1d943f3f75(unsigned int offset)const{if(!
z7ec3461dd4||(offset>=z4de44892fb)){throw Exception(
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x42\x75\x66\x66\x65\x72");}}
