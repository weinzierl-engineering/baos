
#include "pch/kdrive_pch.h"
#include "kdrive/knx/telegrams/formatters/Formatter.h"
#include "kdrive/knx/core/ByteStream.h"
#include <boost/assert.hpp>
#include <algorithm>
using namespace kdrive::knx;AbstractFormatter::AbstractFormatter(){}
AbstractFormatter::~AbstractFormatter(){}std::size_t AbstractFormatter::read(std
::vector<unsigned char>&buffer){Buffer b;b.setBuffer(buffer);return read(b);}std
::size_t AbstractFormatter::read(const Buffer&buffer){z907663c9d3();const std::
size_t size=readImpl(buffer);zc1bc2fc770();return size;}std::size_t 
AbstractFormatter::write(std::vector<unsigned char>&buffer){buffer.resize(size()
);Buffer b;b.setBuffer(buffer);return write(b);}std::size_t AbstractFormatter::
write(Buffer&buffer){z87c4e77298();const std::size_t size=writeImpl(buffer);
z164c39c7fe();return size;}void AbstractFormatter::setDefaults(){}void 
AbstractFormatter::z907663c9d3(){}void AbstractFormatter::zc1bc2fc770(){}void 
AbstractFormatter::z87c4e77298(){}void AbstractFormatter::z164c39c7fe(){}
zcd4daefec3::zcd4daefec3(){}zcd4daefec3::zcd4daefec3(unsigned char value){}
zcd4daefec3::~zcd4daefec3(){}std::size_t zcd4daefec3::size()const{return
(0x11cb+2149-0x1a30);}bool zcd4daefec3::isValid()const{return true;}void 
zcd4daefec3::set(unsigned char value){}unsigned char zcd4daefec3::get()const{
return(0x1b3f+1574-0x2165);}std::size_t zcd4daefec3::readImpl(const Buffer&
buffer){return size();}std::size_t zcd4daefec3::writeImpl(Buffer&buffer){return 
size();}ByteFormatter::ByteFormatter():z42bdb1ff44((0x621+1796-0xd25)){}
ByteFormatter::ByteFormatter(unsigned char value):z42bdb1ff44(value){}
ByteFormatter::~ByteFormatter(){}std::size_t ByteFormatter::size()const{return
(0xdb0+2189-0x163c);}bool ByteFormatter::isValid()const{return true;}void 
ByteFormatter::set(unsigned char value){z42bdb1ff44=value;}unsigned char 
ByteFormatter::get()const{return z42bdb1ff44;}std::size_t ByteFormatter::
readImpl(const Buffer&buffer){set(buffer.z02b8347997((0x4fb+4101-0x1500)));
return size();}std::size_t ByteFormatter::writeImpl(Buffer&buffer){buffer.
zb8203d7346((0x6ba+1156-0xb3e),get());return size();}WordFormatter::
WordFormatter():z42bdb1ff44((0x17f4+2423-0x216b)){}WordFormatter::WordFormatter(
unsigned short value):z42bdb1ff44(value){}WordFormatter::~WordFormatter(){}std::
size_t WordFormatter::size()const{return(0xa61+4824-0x1d37);}bool WordFormatter
::isValid()const{return true;}void WordFormatter::set(unsigned short value){
z42bdb1ff44=value;}unsigned short WordFormatter::get()const{return z42bdb1ff44;}
std::size_t WordFormatter::readImpl(const Buffer&buffer){set(buffer.readWord(
(0xb8c+4745-0x1e15)));return size();}std::size_t WordFormatter::writeImpl(Buffer
&buffer){buffer.z740eff6f6e((0x73a+1679-0xdc9),get());return size();}z6548417957
::z6548417957():z42bdb1ff44((0x607+2581-0x101c)){}z6548417957::z6548417957(
unsigned int value):z42bdb1ff44(value){}z6548417957::~z6548417957(){}std::size_t
 z6548417957::size()const{return(0xd7f+428-0xf27);}bool z6548417957::isValid()
const{return true;}void z6548417957::set(unsigned int value){z42bdb1ff44=value;}
unsigned int z6548417957::get()const{return z42bdb1ff44;}std::size_t z6548417957
::readImpl(const Buffer&buffer){set(ze378c24725<unsigned int,(0xdac+5059-0x216b)
>(buffer.getBuffer(),buffer.z727230908f()));return(0x536+5472-0x1a92);}std::
size_t z6548417957::writeImpl(Buffer&buffer){const std::vector<unsigned char>
data=zd5c4ea2fc7<unsigned int,(0x667+4667-0x189e)>(z42bdb1ff44);buffer.
za213db16c9((0x865+2141-0x10c2),&data.at((0x874+2449-0x1205)),data.size());
return(0x3c0+3280-0x108c);}Formatter::Formatter(){}Formatter::~Formatter(){}std
::size_t Formatter::size()const{std::size_t size=(0x98+7360-0x1d58);for(
AbstractFormatter*formatter:zafc83905ab){BOOST_ASSERT(formatter&&
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x46\x6f\x72\x6d\x61\x74\x74\x65\x72");size+=
formatter->size();}return size;}std::size_t Formatter::z7faf559cd5(const Buffer&
buffer){std::size_t size=(0x5e8+2876-0x1124);const unsigned char*bufferPtr=
buffer.getBuffer();std::size_t z3ba388a942=buffer.z727230908f();for(
AbstractFormatter*formatter:zafc83905ab){BOOST_ASSERT(formatter&&
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x46\x6f\x72\x6d\x61\x74\x74\x65\x72");const 
Buffer b(const_cast<unsigned char*>(bufferPtr),z3ba388a942);std::size_t length=
formatter->read(b);size+=length;z3ba388a942-=length;bufferPtr+=length;}return 
size;}std::size_t Formatter::writeToBuffer(Buffer&buffer){std::size_t size=
(0x1a5b+1329-0x1f8c);unsigned char*bufferPtr=buffer.getBuffer();std::size_t 
z3ba388a942=buffer.z727230908f();for(AbstractFormatter*formatter:zafc83905ab){
BOOST_ASSERT(formatter&&
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x46\x6f\x72\x6d\x61\x74\x74\x65\x72");
BufferDecorator<Buffer>b(bufferPtr,z3ba388a942);std::size_t length=formatter->
write(b);size+=length;z3ba388a942-=length;bufferPtr+=length;}return size;}bool 
Formatter::isValid()const{for(AbstractFormatter*formatter:zafc83905ab){
BOOST_ASSERT(formatter&&
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x46\x6f\x72\x6d\x61\x74\x74\x65\x72");if(!
formatter->isValid()){return false;}}return true;}void Formatter::addFormatter(
AbstractFormatter*formatter){BOOST_ASSERT(formatter&&
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x46\x6f\x72\x6d\x61\x74\x74\x65\x72");
zafc83905ab.push_back(formatter);}void Formatter::zcf6d2a1735(AbstractFormatter*
formatter,int index){BOOST_ASSERT(formatter&&
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x46\x6f\x72\x6d\x61\x74\x74\x65\x72");
zafc83905ab.insert(zafc83905ab.begin()+index,formatter);}void Formatter::
z648a5e66eb(AbstractFormatter*formatter){BOOST_ASSERT(formatter&&
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x46\x6f\x72\x6d\x61\x74\x74\x65\x72");
Formatters::iterator iter=std::find(zafc83905ab.begin(),zafc83905ab.end(),
formatter);while(iter!=zafc83905ab.end()){zafc83905ab.erase(iter);iter=std::find
(zafc83905ab.begin(),zafc83905ab.end(),formatter);}}const Formatter::Formatters&
Formatter::z2a3eb910b4()const{return zafc83905ab;}std::size_t Formatter::
readImpl(const Buffer&buffer){return z7faf559cd5(buffer);}std::size_t Formatter
::writeImpl(Buffer&buffer){return writeToBuffer(buffer);}zfb0a48309d::
zfb0a48309d():z74663526b1(-(0x231+6898-0x1d22)){}zfb0a48309d::~zfb0a48309d(){}
std::size_t zfb0a48309d::size()const{return z7ec3461dd4.size();}bool zfb0a48309d
::isValid()const{return true;}void zfb0a48309d::setBuffer(const std::vector<
unsigned char>&buffer){z7ec3461dd4=buffer;if(z7ec3461dd4.size()>static_cast<std
::size_t>(z74663526b1)){z7ec3461dd4.resize(z74663526b1);}}const std::vector<
unsigned char>&zfb0a48309d::getBuffer()const{return z7ec3461dd4;}std::vector<
unsigned char>&zfb0a48309d::getBuffer(){return z7ec3461dd4;}void zfb0a48309d::
z1eabd06696(int limit){z74663526b1=limit;}int zfb0a48309d::zf3574e1a1f()const{
return z74663526b1;}bool zfb0a48309d::z973fb7eeae()const{return(z74663526b1>=
(0x11b8+4479-0x2337))?true:false;}std::size_t zfb0a48309d::readImpl(const Buffer
&buffer){const std::size_t z32ba1f9c98=buffer.z727230908f();const std::size_t 
limit=z74663526b1;const std::size_t z9fcbac7d77=z973fb7eeae()?std::min(
z32ba1f9c98,limit):z32ba1f9c98;if(z9fcbac7d77){z7ec3461dd4.resize(z9fcbac7d77);
const unsigned char*bufferPtr=buffer.z15e6bd8652((0x199+3105-0xdba),z9fcbac7d77)
;std::copy(bufferPtr,bufferPtr+z9fcbac7d77,z7ec3461dd4.begin());}else{
z7ec3461dd4.clear();}return z9fcbac7d77;}std::size_t zfb0a48309d::writeImpl(
Buffer&buffer){std::size_t size=z7ec3461dd4.size();if(size){buffer.za213db16c9(
(0x774+2952-0x12fc),&z7ec3461dd4.at((0x149c+1384-0x1a04)),size);}return size;}
zaaeafbfd0f::zaaeafbfd0f(){}zaaeafbfd0f::~zaaeafbfd0f(){}std::size_t zaaeafbfd0f
::size()const{return z988e257be4.size()*(0x1133+1629-0x178e);}bool zaaeafbfd0f::
isValid()const{return true;}void zaaeafbfd0f::set(const std::vector<unsigned 
short>&values){z988e257be4=values;}const std::vector<unsigned short>&zaaeafbfd0f
::get()const{return z988e257be4;}std::size_t zaaeafbfd0f::readImpl(const Buffer&
buffer){z988e257be4.clear();const std::size_t size=buffer.z727230908f();std::
size_t offset=(0x1ccc+2573-0x26d9);while(offset<size){z988e257be4.push_back(
buffer.readWord(offset));offset+=(0x15af+49-0x15de);}return size;}std::size_t 
zaaeafbfd0f::writeImpl(Buffer&buffer){std::size_t offset=(0x802+6452-0x2136);for
(unsigned short value:z988e257be4){buffer.z740eff6f6e(offset,value);offset+=
(0x4d7+654-0x763);}return size();}
