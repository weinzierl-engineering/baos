
#include "pch/kdrive_pch.h"
#include "kdrive/knx/datapoint/Datapoint.h"
#include "kdrive/knx/datapoint/FloatConverter.h"
#include "kdrive/knx/core/ByteStream.h"
#include <Poco/Exception.h>
#include <Poco/DateTime.h>
#include <Poco/LocalDateTime.h>
#include <boost/assert.hpp>
using namespace kdrive::knx;using Poco::Dynamic::Var;using Poco::
DataFormatException;using Poco::DateTime;using Poco::LocalDateTime;namespace{
unsigned char z930e31f79d(const Datapoint&datapoint,std::size_t z6aeae56d87){
BOOST_ASSERT(z6aeae56d87&&
"\x50\x72\x65\x63\x6f\x6e\x64\x69\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x65\x64");
const std::vector<unsigned char>&data=datapoint.getData();if(data.size()!=
z6aeae56d87){throw DataFormatException(
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x64\x61\x74\x61\x20\x6c\x65\x6e\x67\x74\x68");
}return data.at((0x171a+3161-0x2373));}const std::vector<unsigned char>&getData(
const Datapoint&datapoint,std::size_t z6aeae56d87){BOOST_ASSERT(z6aeae56d87&&
"\x50\x72\x65\x63\x6f\x6e\x64\x69\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x65\x64");
const std::vector<unsigned char>&data=datapoint.getData();if(data.size()!=
z6aeae56d87){throw DataFormatException(
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x64\x61\x74\x61\x20\x6c\x65\x6e\x67\x74\x68");
}return data;}void setData(Datapoint&datapoint,const std::vector<unsigned char>&
data,std::size_t z6aeae56d87){BOOST_ASSERT(z6aeae56d87&&
"\x50\x72\x65\x63\x6f\x6e\x64\x69\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x65\x64");
if(data.size()!=z6aeae56d87){throw DataFormatException(
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x64\x61\x74\x61\x20\x6c\x65\x6e\x67\x74\x68");
}datapoint.setData(data);}}const std::string Datapoint::Id=
"\x44\x70\x74\x2e\x49\x64";const std::string Datapoint::Number=
"\x44\x70\x74\x2e\x4e\x75\x6d\x62\x65\x72";const std::string Datapoint::Name=
"\x44\x70\x74\x2e\x4e\x61\x6d\x65";const std::string Datapoint::Text=
"\x44\x70\x74\x2e\x54\x65\x78\x74";const std::string Datapoint::z564c074eac=
"\x44\x70\x74\x2e\x53\x69\x7a\x65\x49\x6e\x42\x69\x74";const std::string 
Datapoint::Data="\x44\x70\x74\x2e\x44\x61\x74\x61";Datapoint::Datapoint(){}
Datapoint::Datapoint(const std::string id,const std::string&number,const std::
string&name,const std::string&text,const std::string&z8af7e44e6c){setProperty(Id
,id);setProperty(Number,number);setProperty(Name,name);setProperty(Text,text);
setProperty(z564c074eac,z8af7e44e6c);std::vector<unsigned char>data(
getSizeInBytes(),(0xd3b+5483-0x22a6));setProperty(Data,data);}Datapoint::
Datapoint(const Datapoint&datapoint):PropertyCollection(datapoint){}Datapoint::~
Datapoint(){}Datapoint&Datapoint::operator=(const Datapoint&datapoint){
PropertyCollection::operator=(datapoint);return*this;}const std::string&
Datapoint::zebc3066335()const{return z3c6aa0de0f(Id);}int Datapoint::z697f86f0e1
()const{return getProperty(Number);}const std::string&Datapoint::getName()const{
return z3c6aa0de0f(Name);}const std::string&Datapoint::getText()const{return 
z3c6aa0de0f(Text);}int Datapoint::zb773295431()const{return getProperty(
z564c074eac);}int Datapoint::getSizeInBytes()const{return getSizeInBytes(
zb773295431());}const std::vector<unsigned char>&Datapoint::getData()const{const
 Var&var=getProperty(Data);return var.extract<std::vector<unsigned char> >();}
void Datapoint::setData(const std::vector<unsigned char>&data){setProperty(Data,
data);}const std::string&Datapoint::z3c6aa0de0f(const std::string&key)const{
const Var&var=getProperty(key);return var.extract<std::string>();}int Datapoint
::getSizeInBytes(int z5e1f916d4c)const{return z5e1f916d4c<(0xcd1+4268-0x1d75)?
(0x1485+3422-0x21e2):z5e1f916d4c/(0x1b49+2457-0x24da);}void kdrive::knx::
z6bf2f75cea(Datapoint&datapoint,bool value){const std::vector<unsigned char>data
((0x491+3124-0x10c4),value);setData(datapoint,data,(0x3e6+3395-0x1128));}bool 
kdrive::knx::decode_DPT1(const Datapoint&datapoint){return z930e31f79d(datapoint
,(0xf48+2434-0x18c9))?(0x4bd+4319-0x159b):(0x877+4912-0x1ba7);}void kdrive::knx
::encode_DPT2(Datapoint&datapoint,bool zaadaf6ab23,bool value){unsigned char 
data=zaadaf6ab23?(0x872+7409-0x2561):(0x64c+5013-0x19e1);if(value){data|=
(0x4c4+3317-0x11b8);}const std::vector<unsigned char>v((0x2df+2945-0xe5f),data);
setData(datapoint,v,(0x1114+1674-0x179d));}void kdrive::knx::decode_DPT2(const 
Datapoint&datapoint,bool&zaadaf6ab23,bool&value){const unsigned char data=
z930e31f79d(datapoint,(0x229+1165-0x6b5));zaadaf6ab23=(data&(0x11dc+1001-0x15c3)
)?true:false;value=(data&(0xbf6+3521-0x19b6))?true:false;}void kdrive::knx::
encode_DPT3(Datapoint&datapoint,bool zaadaf6ab23,unsigned char value){const 
unsigned char data=(zaadaf6ab23?(0x26f+1394-0x7d9):(0x202+1950-0x9a0))|(value&
(0xa64+1015-0xe54));const std::vector<unsigned char>v((0x52a+454-0x6ef),data);
setData(datapoint,v,(0x25f+4583-0x1445));}void kdrive::knx::decode_DPT3(const 
Datapoint&datapoint,bool&zaadaf6ab23,unsigned char&value){const unsigned char 
data=z930e31f79d(datapoint,(0xf69+2020-0x174c));zaadaf6ab23=(data&
(0x795+2456-0x1125))?true:false;value=data&(0x1265+2245-0x1b23);}void kdrive::
knx::encode_DPT4(Datapoint&datapoint,unsigned char value){const std::vector<
unsigned char>data((0x1a36+2869-0x256a),value);setData(datapoint,data,
(0x3ef+8104-0x2396));}unsigned char kdrive::knx::decode_DPT4(const Datapoint&
datapoint){return z930e31f79d(datapoint,(0x484+1470-0xa41));}void kdrive::knx::
encode_DPT5(Datapoint&datapoint,unsigned char value){const std::vector<unsigned 
char>data((0x1840+3475-0x25d2),value);setData(datapoint,data,(0xef+4057-0x10c7))
;}unsigned char kdrive::knx::decode_DPT5(const Datapoint&datapoint){return 
z930e31f79d(datapoint,(0xd32+1760-0x1411));}void kdrive::knx::encode_DPT6(
Datapoint&datapoint,char value){const std::vector<unsigned char>data(
(0xb15+6474-0x245e),static_cast<unsigned char>(value));setData(datapoint,data,
(0x1213+414-0x13b0));}signed char kdrive::knx::decode_DPT6(const Datapoint&
datapoint){return static_cast<signed char>(z930e31f79d(datapoint,
(0x9e3+1294-0xef0)));}void kdrive::knx::encode_DPT7(Datapoint&datapoint,unsigned
 short value){setData(datapoint,zd5c4ea2fc7<unsigned short,(0x7d6+6341-0x2099)>(
value),(0x1527+4362-0x262f));}unsigned short kdrive::knx::decode_DPT7(const 
Datapoint&datapoint){const std::vector<unsigned char>&data=getData(datapoint,
(0xd87+3212-0x1a11));return ze378c24725<unsigned short,(0x1398+462-0x1564)>(&
data.at((0x1a87+2975-0x2626)),data.size());}void kdrive::knx::encode_DPT8(
Datapoint&datapoint,short value){setData(datapoint,zd5c4ea2fc7<short,
(0xaac+3586-0x18ac)>(value),(0x937+6681-0x234e));}signed short kdrive::knx::
decode_DPT8(const Datapoint&datapoint){const std::vector<unsigned char>&data=
getData(datapoint,(0x16d4+1316-0x1bf6));return ze378c24725<signed short,
(0xd79+2441-0x1700)>(&data.at((0xeb1+5363-0x23a4)),data.size());}void kdrive::
knx::encode_DPT9_Raw(Datapoint&datapoint,unsigned char zba1cbc76ee,unsigned char
 z68419f84d9){std::vector<unsigned char>data;data.push_back(zba1cbc76ee);data.
push_back(z68419f84d9);setData(datapoint,data,(0xe91+2746-0x1949));}void kdrive
::knx::encode_DPT9(Datapoint&datapoint,float f){std::tuple<unsigned char,
unsigned char>t=zac29c93fda::zb219ab2908(f);encode_DPT9_Raw(datapoint,std::get<
(0x90+2343-0x9b7)>(t),std::get<(0x249d+356-0x2600)>(t));}unsigned short kdrive::
knx::decode_DPT9_Raw(const Datapoint&datapoint){const std::vector<unsigned char>
&data=getData(datapoint,(0x7f1+1885-0xf4c));return data.at((0x237d+726-0x2653))
<<(0x21d+2395-0xb70)|data.at((0x981+4465-0x1af1));}float kdrive::knx::
decode_DPT9(const Datapoint&datapoint){const std::vector<unsigned char>&data=
getData(datapoint,(0x1060+1571-0x1681));return zac29c93fda::zdfe51b7ee0(data.at(
(0xc90+789-0xfa5)),data.at((0xab1+5615-0x209f)));}void kdrive::knx::
encode_DPT10_Local(Datapoint&datapoint){LocalDateTime now;int day=now.dayOfWeek(
);if(!day){day=(0x13b1+2024-0x1b92);}return encode_DPT10(datapoint,day,now.hour(
),now.minute(),now.second());}void kdrive::knx::encode_DPT10_UTC(Datapoint&
datapoint){DateTime now;int day=now.dayOfWeek();if(!day){day=(0x616+5932-0x1d3b)
;}return encode_DPT10(datapoint,day,now.hour(),now.minute(),now.second());}void 
kdrive::knx::encode_DPT10(Datapoint&datapoint,int day,int hour,int minute,int 
second){std::vector<unsigned char>data;data.push_back(((day&(0xed7+4010-0x1e7a))
<<(0xe0+5853-0x17b8))|(hour&(0x122d+1869-0x195b)));data.push_back(minute&
(0xd36+523-0xf02));data.push_back(second&(0x1033+3759-0x1ea3));setData(datapoint
,data,(0x9a2+1275-0xe9a));}void kdrive::knx::decode_DPT10(const Datapoint&
datapoint,int&day,int&hour,int&minute,int&second){const std::vector<unsigned 
char>&data=getData(datapoint,(0x402+261-0x504));const unsigned char z25275926f1=
data.at((0xe0+2602-0xb0a));const unsigned char ch1=data.at((0x1738+4018-0x26e9))
;const unsigned char z8d438dbe68=data.at((0x115b+4098-0x215b));day=z25275926f1>>
(0x164b+428-0x17f2);hour=z25275926f1&(0xcbf+6131-0x2493);minute=ch1&
(0x136c+976-0x16fd);second=z8d438dbe68&(0xba8+4145-0x1b9a);}void kdrive::knx::
encode_DPT11_Local(Datapoint&datapoint){LocalDateTime now;return z800ccce10f(
datapoint,now.year(),now.month(),now.day());}void kdrive::knx::encode_DPT11_UTC(
Datapoint&datapoint){DateTime now;return z800ccce10f(datapoint,now.year(),now.
month(),now.day());}void kdrive::knx::zdf135c0fa0(Datapoint&datapoint,int year,
int month,int day){encode_DPT11_knx(datapoint,year,month,day);}void kdrive::knx
::encode_DPT11_knx(Datapoint&datapoint,int year,int month,int day){if((year<
(0xd03+4975-0x2072))||(year>(0x24f7+59-0x24cf))){const std::string message=
"\x45\x78\x70\x65\x63\x74\x65\x64\x20\x66\x6f\x72\x20\x79\x65\x61\x72\x3a\x20\x30\x2e\x2e\x39\x39\x2e\x20\x47\x65\x74\x3a\x20"
+std::to_string(year);throw Poco::RangeException(message);}std::vector<unsigned 
char>data;data.push_back(day&(0x17e5+3277-0x2493));data.push_back(month&
(0x1470+2071-0x1c78));data.push_back(year&(0xb37+3652-0x18fc));setData(datapoint
,data,(0x1264+4126-0x227f));}void kdrive::knx::z800ccce10f(Datapoint&datapoint,
int year,int month,int day){if((year<(0xccd+1066-0x931))||(year>
(0x1c86+4171-0x24a8))){const std::string message=
"\x45\x78\x70\x65\x63\x74\x65\x64\x20\x66\x6f\x72\x20\x79\x65\x61\x72\x3a\x20\x31\x39\x39\x30\x2e\x2e\x32\x30\x38\x39\x2e\x20\x47\x65\x74\x3a\x20"
+std::to_string(year);throw Poco::RangeException(message);}const int zc404dcd6bb
=(year<(0x125c+5199-0x1edb))?(year-(0xb8c+1432-0x9b8)):(year-
(0x1ea4+3822-0x25c2));encode_DPT11_knx(datapoint,zc404dcd6bb,month,day);}void 
kdrive::knx::decode_DPT11(const Datapoint&datapoint,int&year,int&month,int&day){
decode_DPT11_knx(datapoint,year,month,day);}void kdrive::knx::decode_DPT11_knx(
const Datapoint&datapoint,int&year,int&month,int&day){const std::vector<unsigned
 char>&data=getData(datapoint,(0x926+7305-0x25ac));const unsigned char 
z25275926f1=data.at((0x8f+329-0x1d8));const unsigned char ch1=data.at(
(0x16a1+3449-0x2419));const unsigned char z8d438dbe68=data.at(
(0x1893+3236-0x2535));day=z25275926f1&(0x10bf+5377-0x25a1);month=ch1&
(0x13f+4432-0x1280);year=z8d438dbe68&(0x1485+2289-0x1cf7);}void kdrive::knx::
z4d7301ebb3(const Datapoint&datapoint,int&year,int&month,int&day){int 
zc404dcd6bb=(0xe73+4702-0x20d1);decode_DPT11_knx(datapoint,zc404dcd6bb,month,day
);year=(zc404dcd6bb<(0x720+2654-0x1124))?(zc404dcd6bb+(0xe98+7254-0x231e)):
zc404dcd6bb+(0x25bf+699-0x210e);}void kdrive::knx::encode_DPT12(Datapoint&
datapoint,unsigned int value){setData(datapoint,zd5c4ea2fc7<unsigned int,
(0x123+6959-0x1c4e)>(value),(0x467+370-0x5d5));}unsigned int kdrive::knx::
decode_DPT12(const Datapoint&datapoint){const std::vector<unsigned char>&data=
getData(datapoint,(0x152b+1463-0x1ade));return ze378c24725<unsigned int,
(0x9b5+5688-0x1fe9)>(&data.at((0xee1+2272-0x17c1)),data.size());}void kdrive::
knx::encode_DPT13(Datapoint&datapoint,int value){setData(datapoint,zd5c4ea2fc7<
int,(0x1564+2909-0x20bd)>(value),(0xc80+1924-0x1400));}signed int kdrive::knx::
decode_DPT13(const Datapoint&datapoint){const std::vector<unsigned char>&data=
getData(datapoint,(0xaf9+5341-0x1fd2));return ze378c24725<signed int,
(0x5c5+4170-0x160b)>(&data.at((0x1cd1+2038-0x24c7)),data.size());}void kdrive::
knx::encode_DPT14(Datapoint&datapoint,float f){setData(datapoint,zd5c4ea2fc7<
float,(0x568+7858-0x2416)>(f),(0x1abc+2828-0x25c4));}float kdrive::knx::
decode_DPT14(const Datapoint&datapoint){const std::vector<unsigned char>&data=
getData(datapoint,(0xf90+2403-0x18ef));return ze378c24725<float,
(0x14bb+1677-0x1b44)>(&data.at((0x1133+2263-0x1a0a)),data.size());}void kdrive::
knx::encode_DPT15(Datapoint&datapoint,unsigned int z7c361264d7,bool error,bool 
z3a4ce83def,bool zbadde329ec,bool zeb54d212c0,unsigned char index){std::vector<
unsigned char>v;v.push_back((z7c361264d7>>(0x372+391-0x4e9))&
(0x198a+1977-0x2044));v.push_back((z7c361264d7>>(0x73c+2196-0xfc8))&
(0x70c+3583-0x140c));v.push_back(z7c361264d7&(0x5c9+3920-0x141a));unsigned char 
data=(0x1121+2047-0x1920);if(error){data|=(0xe62+305-0xf13);}if(z3a4ce83def){
data|=(0x34c+7774-0x216a);}if(zbadde329ec){data|=(0x30d+8415-0x23cc);}if(
zeb54d212c0){data|=(0x1df1+1531-0x23dc);}data|=index&(0x1262+4066-0x2235);v.
push_back(data);setData(datapoint,v,(0x1559+2243-0x1e18));}void kdrive::knx::
decode_DPT15(const Datapoint&datapoint,unsigned int&z7c361264d7,bool&error,bool&
z3a4ce83def,bool&zbadde329ec,bool&zeb54d212c0,unsigned char&index){const std::
vector<unsigned char>&data=getData(datapoint,(0x215+8575-0x2390));const unsigned
 char z25275926f1=data.at((0xebf+1122-0x1321));const unsigned char ch1=data.at(
(0x60b+925-0x9a7));const unsigned char z8d438dbe68=data.at((0x18a+5578-0x1752));
const unsigned char z2e44465404=data.at((0xfc5+2870-0x1af8));z7c361264d7=(
z25275926f1<<(0x5d8+7531-0x2333))|(ch1<<(0x1cd4+924-0x2068))|z8d438dbe68;error=
z2e44465404&(0x6e7+7609-0x2420)?true:false;z3a4ce83def=z2e44465404&
(0xef4+704-0x1174)?true:false;zbadde329ec=z2e44465404&(0x1063+4037-0x2008)?true:
false;zeb54d212c0=z2e44465404&(0x13ff+3084-0x1ffb)?true:false;index=z2e44465404&
(0x47+8544-0x2198);}void kdrive::knx::encode_DPT16(Datapoint&datapoint,const std
::string&str){static const int zb18c852c31=(0xba8+4511-0x1d39);std::vector<
unsigned char>data;for(char ch:str){data.push_back(static_cast<unsigned char>(ch
));}if(data.size()<zb18c852c31){data.resize(zb18c852c31,(0xc78+3824-0x1b68));}
setData(datapoint,data,zb18c852c31);}std::string kdrive::knx::decode_DPT16(const
 Datapoint&datapoint){std::string str;const std::vector<unsigned char>&data=
getData(datapoint,(0x65f+6153-0x1e5a));for(unsigned char ch:data){if(!ch){break;
}str+=static_cast<char>(ch);}return str;}void kdrive::knx::z2c0e220f97(Datapoint
&datapoint,unsigned char zeec3b2b0b5){const std::vector<unsigned char>data(
(0x14ad+4618-0x26b6),zeec3b2b0b5);setData(datapoint,data,(0x183d+1713-0x1eed));}
unsigned char kdrive::knx::z22d5a8ab0f(const Datapoint&datapoint){return 
z930e31f79d(datapoint,(0x1ad+2359-0xae3));}void kdrive::knx::zba071ade45(
Datapoint&datapoint,bool zaadaf6ab23,unsigned char zeec3b2b0b5){unsigned char 
data=zaadaf6ab23?(0x8bc+6672-0x224c):(0x666+7577-0x23ff);data|=zeec3b2b0b5&
(0x13df+3852-0x22ac);const std::vector<unsigned char>v((0x2410+302-0x253d),data)
;setData(datapoint,v,(0x1167+489-0x134f));}void kdrive::knx::z8015252426(const 
Datapoint&datapoint,bool&zaadaf6ab23,unsigned char&zeec3b2b0b5){const unsigned 
char data=z930e31f79d(datapoint,(0x1437+275-0x1549));zaadaf6ab23=(data&
(0x1717+3286-0x236d))?true:false;zeec3b2b0b5=data&(0x1594+2284-0x1e41);}void 
kdrive::knx::z5e7b87bb95(Datapoint&datapoint,unsigned char r,unsigned char g,
unsigned char b){const std::vector<unsigned char>v={r,g,b};setData(datapoint,v,
(0x379+2492-0xd32));}void kdrive::knx::zc61cae9601(const Datapoint&datapoint,
unsigned char&r,unsigned char&g,unsigned char&b){const std::vector<unsigned char
>&data=getData(datapoint,(0x1cbc+2144-0x2519));r=data.at((0x378+8230-0x239e));g=
data.at((0xc9+5761-0x1749));b=data.at((0x8d4+7669-0x26c7));}
