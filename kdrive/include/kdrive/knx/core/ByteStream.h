
#ifndef zd0647f9412
#define zd0647f9412
#include "kdrive/knx/Config.h"
#include <Poco/ByteOrder.h>
#include <Poco/Exception.h>
#include <vector>
#include <algorithm>
#include <cstddef>
namespace kdrive{namespace knx{template<typename T>union z9c9e564eb1{enum 
DataLength{Size=sizeof(T)};T data;unsigned char bytes[sizeof(T)];};template<
typename T>void zda00b50860(z9c9e564eb1<T>&u){u.data=Poco::ByteOrder::flipBytes(
u.data);}template<>z91680f515b void zda00b50860<unsigned char>(z9c9e564eb1<
unsigned char>&u);template<>z91680f515b void zda00b50860<char>(z9c9e564eb1<char>
&u);template<>z91680f515b void zda00b50860<float>(z9c9e564eb1<float>&u);template
<typename T>void flipBytes(z9c9e564eb1<T>&u){std::vector<unsigned char>v(u.bytes
,u.bytes+z9c9e564eb1<T>::Size);std::reverse(v.begin(),v.end());std::copy(v.begin
(),v.end(),u.bytes);}template<typename T,int n>T ze378c24725(const unsigned char
*buffer,std::size_t z3ba388a942,std::size_t index=(0xd05+5690-0x233f)){if((
z3ba388a942<(index+(0xe52+1963-0x15fc))*n)||(n>z9c9e564eb1<T>::Size)){throw Poco
::Exception("\x42\x75\x66\x66\x65\x72\x20\x4f\x76\x65\x72\x72\x75\x6e");}
z9c9e564eb1<T>u;u.data=(0x1105+3455-0x1e84);std::copy(buffer+(index*n),buffer+(
index+(0x1380+1052-0x179b))*n,u.bytes);
#if defined(POCO_ARCH_LITTLE_ENDIAN)
zda00b50860(u);
#endif 
return u.data;};template<typename T,int n>T ze378c24725(const std::vector<
unsigned char>&buffer,std::size_t index=(0x232+1977-0x9eb)){if(buffer.empty()){
throw Poco::Exception("\x42\x75\x66\x66\x65\x72\x20\x4f\x76\x65\x72\x72\x75\x6e"
);}return ze378c24725<T,n>(&buffer.at((0x333+6052-0x1ad7)),buffer.size(),index);
}template<typename T,int n>void zcaddb568a5(const unsigned char*buffer,std::
size_t z3ba388a942,std::vector<T>&result,std::size_t index=(0x1b8+5892-0x18bc)){
result.clear();if(((0x1fe7+383-0x2165)+index)*n>z3ba388a942){throw Poco::
Exception("\x42\x75\x66\x66\x65\x72\x20\x4f\x76\x65\x72\x72\x75\x6e");}for(std::
size_t idx=index;idx<(unsigned int)z3ba388a942/n;++idx){result.push_back(
ze378c24725<T,n>(buffer,z3ba388a942,idx));}}template<typename T,int n>void 
zcaddb568a5(const std::vector<unsigned char>&buffer,std::vector<T>&result,std::
size_t index=(0x1de0+120-0x1e58)){if(buffer.empty()){throw Poco::Exception(
"\x42\x75\x66\x66\x65\x72\x20\x4f\x76\x65\x72\x72\x75\x6e");}zcaddb568a5<T,n>(&
buffer.at((0x1775+1623-0x1dcc)),buffer.size(),result,index);}template<>
z91680f515b unsigned char ze378c24725<unsigned char,(0x95c+5909-0x2070)>(const 
unsigned char*buffer,std::size_t z3ba388a942,std::size_t index);template<>
z91680f515b char ze378c24725<char,(0x2c0+6892-0x1dab)>(const unsigned char*
buffer,std::size_t z3ba388a942,std::size_t index);template<typename T,int length
>const unsigned char*zdf6b14c23c(const z9c9e564eb1<T>&u){if(length>z9c9e564eb1<T
>::Size){throw Poco::Exception(
"\x42\x75\x66\x66\x65\x72\x20\x4f\x76\x65\x72\x72\x75\x6e");}if(sizeof(T)==
length){return u.bytes;}else{return u.bytes+(z9c9e564eb1<T>::Size-length);}}
template<typename T,int n>std::vector<unsigned char>zd5c4ea2fc7(T t){z9c9e564eb1
<T>u;u.data=t;
#if defined(POCO_ARCH_LITTLE_ENDIAN)
zda00b50860(u);
#endif 
const unsigned char*ptr=zdf6b14c23c<T,n>(u);return std::vector<unsigned char>(
ptr,ptr+n);}template<typename T,int n>void zc24a237593(T*t,std::size_t 
z3ba388a942,std::vector<unsigned char>&result,std::size_t index=
(0x1c85+858-0x1fdf)){result.clear();std::vector<unsigned char>temp;if(t==NULL||
z3ba388a942<(index+(0xc+3377-0xd3c))){throw Poco::Exception(
"\x42\x75\x66\x66\x65\x72\x20\x4f\x76\x65\x72\x72\x75\x6e");}for(T*idx=(t+index)
;idx<(t+z3ba388a942);++idx){temp=zd5c4ea2fc7<T,n>(*idx);result.insert(result.end
(),temp.begin(),temp.end());}}template<typename T,int n>void zcfe1ac909f(std::
vector<T>&t,std::vector<unsigned char>&result,std::size_t index=
(0x427+5545-0x19d0)){if(t.empty()){throw Poco::Exception(
"\x42\x75\x66\x66\x65\x72\x20\x4f\x76\x65\x72\x72\x75\x6e");}zc24a237593<T,n>(&t
.at((0x1ba+4046-0x1188)),t.size(),result,index);}}}
#endif 

