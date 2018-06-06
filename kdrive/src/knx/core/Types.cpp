
#include "pch/kdrive_pch.h"
#include "kdrive/knx/core/Types.h"
#include <Poco/Exception.h>
#include <Poco/NumberFormatter.h>
#include <cstring>
using namespace kdrive::knx;using Poco::NumberFormatter;using Poco::
RangeException;z498f6d084e::z498f6d084e(){}z498f6d084e::z498f6d084e(const 
DataBuffer&data):z8455ff2862(data){}z498f6d084e::z498f6d084e(const std::vector<
unsigned char>&data){if(data.size()!=Length){throw RangeException(
"\x45\x78\x70\x65\x63\x74\x65\x64\x20\x36\x20\x62\x79\x74\x65\x73");}std::copy(
data.begin(),data.end(),z8455ff2862.begin());}z498f6d084e::z498f6d084e(const 
unsigned char*buffer,std::size_t z3ba388a942){if(!buffer||z3ba388a942<Length){
throw RangeException(
"\x45\x78\x70\x65\x63\x74\x65\x64\x20\x36\x20\x62\x79\x74\x65\x73");}std::memcpy
(&z8455ff2862.at((0x30d+1463-0x8c4)),buffer,z3ba388a942);}z498f6d084e::
z498f6d084e(unsigned char z7245eeaf6c,unsigned char zdbd02c81fa,unsigned char 
z3028649c0f,unsigned char z3aa0f3e3c5,unsigned char z3e4dd8e4d0,unsigned char 
zd4fcaa9456){z8455ff2862.at((0x52a+8115-0x24dd))=z7245eeaf6c;z8455ff2862.at(
(0x15fa+1184-0x1a99))=zdbd02c81fa;z8455ff2862.at((0xd8+175-0x185))=z3028649c0f;
z8455ff2862.at((0x136f+3547-0x2147))=z3aa0f3e3c5;z8455ff2862.at(
(0x12d5+2832-0x1de1))=z3e4dd8e4d0;z8455ff2862.at((0x834+6710-0x2265))=
zd4fcaa9456;}z498f6d084e::~z498f6d084e(){}z498f6d084e&z498f6d084e::operator=(
const z498f6d084e&other){if(this!=&other){z8455ff2862=other.z8455ff2862;}return*
this;}bool z498f6d084e::operator==(const z498f6d084e&other)const{return(
z8455ff2862==other.z8455ff2862);}bool z498f6d084e::operator!=(const z498f6d084e&
other)const{return(z8455ff2862!=other.z8455ff2862);}bool z498f6d084e::operator<(
const z498f6d084e&other)const{return(z8455ff2862<other.z8455ff2862);}bool 
z498f6d084e::operator<=(const z498f6d084e&other)const{return(z8455ff2862<=other.
z8455ff2862);}bool z498f6d084e::operator>(const z498f6d084e&other)const{return(
z8455ff2862>other.z8455ff2862);}bool z498f6d084e::operator>=(const z498f6d084e&
other)const{return(z8455ff2862>=other.z8455ff2862);}z498f6d084e&z498f6d084e::
operator++(){DataBuffer::reverse_iterator iter=z8455ff2862.rbegin();for(;iter!=
z8455ff2862.rend();++iter){unsigned char&value=*iter;if(value==
(0x1978+975-0x1c48)){value=(0x802+2774-0x12d8);}else{++value;break;}}return*this
;}uint64_t z498f6d084e::operator-(const z498f6d084e&other)const{uint64_t span=
(0x108c+4441-0x21e5);unsigned int z765a7c896f=(0x137+6637-0x1af4);for(unsigned 
int index=(0x146+9029-0x248b);index<Length;++index){const unsigned char value=
z8455ff2862.at(index)-other.z6334f67583().at(index);z765a7c896f-=
(0x440+5747-0x1aab);span|=(static_cast<uint64_t>(value))<<z765a7c896f;}return 
span;}z498f6d084e::operator std::vector<unsigned char>()const{return z73ef46b8e7
();}z498f6d084e::DataBuffer&z498f6d084e::z6334f67583(){return z8455ff2862;}const
 z498f6d084e::DataBuffer&z498f6d084e::z6334f67583()const{return z8455ff2862;}std
::string z498f6d084e::toString(const std::string&za3ba428180)const{std::string 
str;for(unsigned int index=(0x987+1118-0xde5);index<z8455ff2862.size();++index){
if(index){str+=za3ba428180;}NumberFormatter::appendHex(str,z8455ff2862.at(index)
,(0x253+13-0x25e));}return str;}std::vector<unsigned char>z498f6d084e::
z73ef46b8e7()const{std::vector<unsigned char>data(z8455ff2862.size());std::copy(
z8455ff2862.begin(),z8455ff2862.end(),data.begin());return data;}
