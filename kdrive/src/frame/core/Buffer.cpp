
#include "pch/kdrive_pch.h"
#include "kdrive/frame/core/Buffer.h"
#include "kdrive/frame/core/Exception.h"
#include "kdrive/utility/LoggerFormatter.h"
#include "kdrive/utility/PropertyCollection.h"
#include <cstring>
#include <memory>
using namespace kdrive::frame;using kdrive::utility::LoggerFormatter;Buffer::
Buffer():z719bdb3268(nullptr),z36f10e99cd((0x692+5508-0x1c16)),z1e742ff128(
(0x1347+2116-0x1b8b)),z48c8eb8550(false){}Buffer::Buffer(size_type size):
z719bdb3268(nullptr),z36f10e99cd((0xab4+6920-0x25bc)),z1e742ff128(
(0xfea+4709-0x224f)),z48c8eb8550(false){setCapacity(size);setSize(size);std::
memset(z719bdb3268,(0x18f2+1877-0x2047),size);}Buffer::Buffer(const std::vector<
value_type>&v):z719bdb3268(nullptr),z36f10e99cd((0x5a7+880-0x917)),z1e742ff128(
(0xff5+577-0x1236)),z48c8eb8550(false){if(!v.empty()){assign(&v[
(0x30b+440-0x4c3)],v.size(),v.size());}}Buffer::Buffer(size_type size,size_type 
capacity):z719bdb3268(nullptr),z36f10e99cd((0xaab+6708-0x24df)),z1e742ff128(
(0x1a3+2792-0xc8b)),z48c8eb8550(false){setCapacity(capacity);setSize(size);std::
memset(z719bdb3268,(0x5df+6102-0x1db5),size);}Buffer::Buffer(value_type*ptr,
size_type size,bool z7e8450ecf2):z719bdb3268(nullptr),z36f10e99cd(
(0xad4+4311-0x1bab)),z1e742ff128((0xeba+4143-0x1ee9)),z48c8eb8550(false){if(
z7e8450ecf2){assign(ptr,size,size);}else{z719bdb3268=ptr;z36f10e99cd=size;
z1e742ff128=size;z48c8eb8550=z7e8450ecf2;}}Buffer::Buffer(const Buffer&buffer):
z719bdb3268(nullptr),z36f10e99cd((0x10d4+4379-0x21ef)),z1e742ff128(
(0xd98+2473-0x1741)),z48c8eb8550(false){if(buffer.z48c8eb8550){assign(buffer.
z719bdb3268,buffer.z36f10e99cd,buffer.z1e742ff128);}else{z719bdb3268=buffer.
z719bdb3268;z36f10e99cd=buffer.z36f10e99cd;z1e742ff128=buffer.z1e742ff128;
z48c8eb8550=buffer.z48c8eb8550;}}Buffer::~Buffer(){release();}Buffer&Buffer::
operator=(const Buffer&buffer){assign(buffer);return*this;}void Buffer::assign(
const Buffer&buffer){if(this!=&buffer){if(buffer.z48c8eb8550){assign(buffer.
z719bdb3268,buffer.z36f10e99cd,buffer.z1e742ff128);}else{release();z719bdb3268=
buffer.z719bdb3268;z36f10e99cd=buffer.z36f10e99cd;z1e742ff128=buffer.z1e742ff128
;z48c8eb8550=buffer.z48c8eb8550;}}}Buffer::value_type*Buffer::z8d79a69692()const
{return z719bdb3268;}Buffer::value_type*Buffer::zffce7603f8(size_type index)
const{return zffce7603f8(index,(0x87f+2390-0x11d4));}Buffer::value_type*Buffer::
zffce7603f8(size_type index,size_type size)const{if((index+size)>Buffer::getSize
()){throw OutOfBoundsException();}return z719bdb3268+index;}Buffer::iterator 
Buffer::begin(){return z719bdb3268;}Buffer::const_iterator Buffer::begin()const{
return z719bdb3268;}Buffer::iterator Buffer::end(){return z719bdb3268+
z36f10e99cd;}Buffer::const_iterator Buffer::end()const{return z719bdb3268+
z36f10e99cd;}bool Buffer::isEmpty()const{return(!z719bdb3268&&!z36f10e99cd&&!
z1e742ff128)?true:false;}void Buffer::setSize(size_type size){z7c6707d75a(size,
z1e742ff128);z36f10e99cd=size;}Buffer::size_type Buffer::getSize()const{return 
z36f10e99cd;}Buffer::size_type Buffer::z4cbc7cada9(size_type index)const{return 
index<z36f10e99cd?z36f10e99cd-index:(0xb9+6019-0x183c);}void Buffer::setCapacity
(size_type capacity){zc8023d9ce4(capacity,true);}Buffer::size_type Buffer::
ze5eea3f1a3()const{return z1e742ff128;}std::string Buffer::toString()const{std::
ostringstream stream;PropertyCollection z44aa351fb2;zffac4ee2ab(z44aa351fb2);std
::vector<std::string>keys;z44aa351fb2.keys(keys);for(const std::string&key:keys)
{stream<<key<<"\x3a\x20"<<LoggerFormatter::toString(z44aa351fb2.getProperty(key)
)<<std::endl;}return stream.str();}void Buffer::zffac4ee2ab(PropertyCollection&
z44aa351fb2)const{z44aa351fb2.setProperty(
"\x66\x72\x61\x6d\x65\x2e\x64\x61\x74\x61",zbaa3b4a6ca());z44aa351fb2.
setProperty("\x66\x72\x61\x6d\x65\x2e\x73\x69\x7a\x65",getSize());}void Buffer::
set(size_type index,unsigned char value){value_type*ptr=zffce7603f8(index,
(0x13c9+4795-0x2683));*ptr=value;}void Buffer::z2e8f9b9806(size_type index,
unsigned char mask){value_type*ptr=zffce7603f8(index,(0x9b0+200-0xa77));*ptr&=~
mask;}void Buffer::zcea3a3d899(size_type index,unsigned char value){value_type*
ptr=zffce7603f8(index,(0x162c+1917-0x1da8));*ptr|=value;}unsigned char Buffer::
get(size_type index)const{const value_type*const ptr=zffce7603f8(index,
(0x2088+716-0x2353));return*ptr;}void Buffer::setBuffer(size_type index,const 
Buffer&buffer){setBuffer(index,buffer.getSize(),buffer);}void Buffer::setBuffer(
size_type index,size_type size,const Buffer&buffer){if(size>buffer.getSize()){
throw BufferTooSmallException();}const size_type zb2456fe885=Buffer::z4cbc7cada9
(index);if(size>zb2456fe885){const size_type newSize=Buffer::getSize()+(size-
zb2456fe885);setCapacity(newSize);setSize(newSize);}if(size){value_type*start=
zffce7603f8(index,size);std::memcpy(start,buffer.z8d79a69692(),size);}}Buffer 
Buffer::getBuffer(size_type index)const{return getBuffer(index,z4cbc7cada9(index
));}Buffer Buffer::getBuffer(size_type index,size_type size)const{const 
value_type*const start=zffce7603f8(index,size);const Buffer b(const_cast<
unsigned char*>(start),size,false);return b;}void Buffer::setString(size_type 
index,size_type size,const std::string&s){Buffer buffer(size);for(size_type i=
(0x2272+735-0x2551);i<s.length()&&i<size;++i){*buffer.zffce7603f8(i)=static_cast
<unsigned char>(s[i]);}for(size_type i=s.length();i<size;++i){*buffer.
zffce7603f8(i)=(0xfa2+1865-0x16eb);}setBuffer(index,size,buffer);}std::string 
Buffer::getString(size_type index,size_type size)const{std::string s;Buffer 
buffer=getBuffer(index,size);for(unsigned char ch:buffer){s+=static_cast<char>(
ch);}return s;}void Buffer::z49cd04e624(size_type index,size_type size,const std
::vector<unsigned char>&v){if(!v.empty()){const Buffer buffer(const_cast<
unsigned char*>(&v.at((0x1022+175-0x10d1))),v.size(),false);setBuffer(index,size
,buffer);}}std::vector<unsigned char>Buffer::zbaa3b4a6ca()const{std::vector<
unsigned char>v;if(z36f10e99cd){v.reserve(z36f10e99cd);v.insert(v.end(),begin(),
end());}return v;}std::vector<unsigned char>Buffer::zbaa3b4a6ca(size_type index)
const{const Buffer buffer=getBuffer(index);return std::vector<unsigned char>(
buffer.begin(),buffer.end());}std::vector<unsigned char>Buffer::zbaa3b4a6ca(
size_type index,size_type size)const{const Buffer buffer=getBuffer(index,size);
return std::vector<unsigned char>(buffer.begin(),buffer.end());}std::vector<
unsigned char>&Buffer::zb87befbd6f(){zb4533d6f54.resize(z36f10e99cd);z719bdb3268
=nullptr;z36f10e99cd=(0x6cc+2532-0x10b0);z1e742ff128=(0x10c9+1406-0x1647);
z48c8eb8550=false;return zb4533d6f54;}void Buffer::z7c6707d75a(){z7c6707d75a(
z36f10e99cd,z1e742ff128);}void Buffer::z7c6707d75a(size_type size,size_type 
capacity){if(size>capacity){throw OutOfBoundsException();}}void Buffer::
zc8023d9ce4(size_type capacity,bool copy){z7c6707d75a(z36f10e99cd,capacity);if(
capacity>z1e742ff128){zb4533d6f54.resize(capacity);z719bdb3268=&zb4533d6f54.at(
(0xcea+4862-0x1fe8));z1e742ff128=capacity;z48c8eb8550=true;}}void Buffer::
release(){zb4533d6f54.clear();z719bdb3268=nullptr;}void Buffer::assign(const 
value_type*ptr,size_type size,size_type capacity){zc8023d9ce4(capacity,false);
setSize(size);copy(ptr,size);}void Buffer::copy(const value_type*ptr,size_type 
size){std::memcpy(z719bdb3268,ptr,size);}bool kdrive::frame::operator==(const 
Buffer&zc48d94fe59,const Buffer&z0ad8726472){return(zc48d94fe59.getSize()==
z0ad8726472.getSize())&&(std::memcmp(zc48d94fe59.z8d79a69692(),z0ad8726472.
z8d79a69692(),zc48d94fe59.getSize())==(0x3ff+3099-0x101a));}bool kdrive::frame::
operator!=(const Buffer&zc48d94fe59,const Buffer&z0ad8726472){return!(
zc48d94fe59==z0ad8726472);}
