
#include "pch/kdrive_pch.h"
#include "kdrive/access/ldm/LocalDeviceManagementEmiC.h"
#include "kdrive/access/core/Exception.h"
#include "kdrive/access/core/KnxPort.h"
#include "kdrive/access/core/KnxPacket.h"
#include "kdrive/access/core/details/TelegramWaitPolicy.h"
#include "kdrive/connector/Wait.h"
#include "kdrive/knx/defines/KnxLayer.h"
#include "kdrive/knx/core/ByteStream.h"
#include "kdrive/knx/defines/MaskVersion.h"
#include "kdrive/knx/defines/KnxProperty.h"
#include "kdrive/knx/telegrams/cemi/MProp.h"
#include "kdrive/knx/telegrams/formatters/Telegram.h"
#include "kdrive/utility/Logger.h"
#include <Poco/Exception.h>
#include "Poco/Latin1Encoding.h"
#include "Poco/UTF8Encoding.h"
#include "Poco/TextConverter.h"
#include <Poco/Logger.h>
#include <Poco/Format.h>
using namespace kdrive::access;using namespace kdrive::connector;using namespace
 kdrive::knx;using namespace kdrive::knx::cemi;using Poco::Exception;using Poco
::Latin1Encoding;using Poco::UTF8Encoding;using Poco::TextConverter;using Poco::
format;using kdrive::connector::waitPacketWithPolicy;CLASS_LOGGER(
"\x6b\x6e\x78\x2e\x61\x63\x63\x65\x73\x73\x2e\x4c\x6f\x63\x61\x6c\x44\x65\x76\x69\x63\x65\x4d\x61\x6e\x61\x67\x65\x6d\x65\x6e\x74\x45\x6d\x69\x43"
)namespace{std::string z07002adfa4(const std::string&utf8){UTF8Encoding 
utf8Encoding;Latin1Encoding latin1Encoding;TextConverter z9cb8e058d8(
utf8Encoding,latin1Encoding);std::string latin1;z9cb8e058d8.convert(utf8,latin1)
;return latin1;}std::string z10bf21bedd(const std::string&latin1){Latin1Encoding
 latin1Encoding;UTF8Encoding utf8Encoding;TextConverter z9cb8e058d8(
latin1Encoding,utf8Encoding);std::string utf8;z9cb8e058d8.convert(latin1,utf8);
return utf8;}}LocalDeviceManagementEmiC::LocalDeviceManagementEmiC(zea2d083c85&
port):zec7fc1647d(port){}LocalDeviceManagementEmiC::~LocalDeviceManagementEmiC()
{}void LocalDeviceManagementEmiC::z766e2388b4(unsigned int z1166f2fdb4){unsigned
 char z5aa3537913=z1b4e121dcb(z1166f2fdb4);std::vector<unsigned char>data=
zd5c4ea2fc7<unsigned char,(0x6aa+4223-0x1728)>(z5aa3537913);z0d4c9a138c(
z3b8af6cac1::zcd7b7b4ad1,z67a443d064::z8ab4a7899f,data);if(z5aa3537913!=
z68a7397df0::None){za4528c2f93(z1166f2fdb4,
"\x4c\x61\x79\x65\x72\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x77\x72\x69\x74\x74\x65\x6e"
);}}unsigned int LocalDeviceManagementEmiC::z6f5601a8cf(){std::vector<unsigned 
char>data;z3570ca8d16(z3b8af6cac1::zcd7b7b4ad1,z67a443d064::z8ab4a7899f,
(0x1531+4180-0x2584),data);const unsigned char z0bc9bca071=ze378c24725<unsigned 
char,(0xc77+5583-0x2245)>(data);return z04db47e219(z0bc9bca071);}unsigned int 
LocalDeviceManagementEmiC::z2e0dcb1a8b(){std::vector<unsigned char>data;
z3570ca8d16(z3b8af6cac1::zcd7b7b4ad1,z67a443d064::zb134102dc9,
(0x371+6132-0x1b63),data);const unsigned short z7b2ce21a17=ze378c24725<unsigned 
short,(0x1366+5029-0x2709)>(data);return z5b1a046ae2(z7b2ce21a17);}unsigned int 
LocalDeviceManagementEmiC::z51177f5ce9(){std::vector<unsigned char>data;
z3570ca8d16(z3b8af6cac1::Device,z67a443d064::z3e7c39ff27,(0x7d5+7117-0x23a0),
data);return ze378c24725<unsigned short,(0x1223+1212-0x16dd)>(data);}unsigned 
short LocalDeviceManagementEmiC::z5da113978e(){std::vector<unsigned char>data;
z3570ca8d16(z3b8af6cac1::zcd7b7b4ad1,z67a443d064::z46964ea527,
(0x375+5761-0x19f4),data);return ze378c24725<unsigned short,(0x4f2+2081-0xd11)>(
data);}void LocalDeviceManagementEmiC::z5392ddee85(unsigned int z83744e1e92){
const unsigned char z0ac3189784=(z83744e1e92>>(0x246f+322-0x25a9))&
(0x118f+3584-0x1e90);const unsigned char z2bd0e78914=z83744e1e92&
(0xc29+4847-0x1e19);za817c9ea45(z0ac3189784);zf1ebe16a79(z2bd0e78914);
z75eed006b0(z83744e1e92,
"\x49\x6e\x64\x69\x76\x69\x64\x75\x61\x6c\x20\x61\x64\x64\x72\x65\x73\x73\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x77\x72\x69\x74\x74\x65\x6e"
);}unsigned int LocalDeviceManagementEmiC::zf670e5347d(){const unsigned char 
z0ac3189784=z44023dda1d();const unsigned char z2bd0e78914=z74c07aea9b();unsigned
 short z83744e1e92=z0ac3189784<<(0x56b+6548-0x1ef7);z83744e1e92|=z2bd0e78914;
return z83744e1e92;}void LocalDeviceManagementEmiC::z6c59c3156d(unsigned int 
zf92894300e){std::vector<unsigned char>data=zd5c4ea2fc7<unsigned short,
(0xb9c+6327-0x2451)>(zf92894300e);z0d4c9a138c(z3b8af6cac1::Device,z67a443d064::
z1928172365,data);z85480faf6f(zf92894300e,
"\x50\x4c\x20\x64\x6f\x6d\x61\x69\x6e\x20\x61\x64\x64\x72\x65\x73\x73\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x77\x72\x69\x74\x74\x65\x6e"
);}unsigned int LocalDeviceManagementEmiC::zfa42f5b322(){std::vector<unsigned 
char>data;z3570ca8d16(z3b8af6cac1::Device,z67a443d064::z1928172365,
(0x1454+2745-0x1f0b),data);return ze378c24725<unsigned short,(0x285+720-0x553)>(
data);}void LocalDeviceManagementEmiC::zb488b9244d(const std::vector<unsigned 
char>&zf92894300e){BOOST_ASSERT((zf92894300e.size()==(0x124a+5224-0x26ac))&&
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x52\x46\x20\x64\x6f\x6d\x61\x69\x6e\x20\x61\x64\x64\x72\x65\x73\x73"
);try{std::vector<unsigned char>data=zf92894300e;z0d4c9a138c(z3b8af6cac1::Device
,z67a443d064::z90676c82a7,data);zd02eaa9824(zf92894300e,
"\x52\x66\x20\x64\x6f\x6d\x61\x69\x6e\x20\x61\x64\x64\x72\x65\x73\x73\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x77\x72\x69\x74\x74\x65\x6e"
);}catch(Exception&){if(!z97d8ed9b64(zf92894300e)){throw;}}}void 
LocalDeviceManagementEmiC::z875dcf85de(std::vector<unsigned char>&zf92894300e){
try{z3570ca8d16(z3b8af6cac1::Device,z67a443d064::z90676c82a7,
(0x1824+2618-0x2258),zf92894300e);}catch(Exception&){if(!z3ca8c1f9d7(zf92894300e
)){throw;}}}void LocalDeviceManagementEmiC::z2853a8fc86(const std::vector<
unsigned char>&zd311e7ca26){BOOST_ASSERT((zd311e7ca26.size()==
(0x359+5348-0x1837))&&
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x73\x65\x72\x69\x61\x6c\x20\x6e\x75\x6d\x62\x65\x72"
);z0d4c9a138c(z3b8af6cac1::Device,z67a443d064::z95f0137b7d,zd311e7ca26);
z501eae5473(zd311e7ca26,
"\x53\x65\x72\x69\x61\x6c\x20\x6e\x75\x6d\x62\x65\x72\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x77\x72\x69\x74\x74\x65\x6e"
);}void LocalDeviceManagementEmiC::z8039b7bd80(std::vector<unsigned char>&
zd311e7ca26){z3570ca8d16(z3b8af6cac1::Device,z67a443d064::z95f0137b7d,
(0x1959+307-0x1a86),zd311e7ca26);}void LocalDeviceManagementEmiC::z00fec7e215(
unsigned int zfd606f58be){std::vector<unsigned char>data=zd5c4ea2fc7<unsigned 
char,(0xf15+944-0x12c4)>(zfd606f58be);z0d4c9a138c(z3b8af6cac1::Device,
z67a443d064::z7922599680,data);z99dab55337(zfd606f58be,
"\x45\x72\x72\x6f\x72\x20\x66\x6c\x61\x67\x73\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x77\x72\x69\x74\x74\x65\x6e"
);}unsigned int LocalDeviceManagementEmiC::za4544ba4dc(){std::vector<unsigned 
char>data;z3570ca8d16(z3b8af6cac1::Device,z67a443d064::z7922599680,
(0x2a+402-0x1bb),data);return ze378c24725<unsigned char,(0x394+5731-0x19f6)>(
data);}void LocalDeviceManagementEmiC::zc2caea0629(unsigned int){throw 
UnsupportedLocalDeviceMgmtPropertyException(
"\x41\x64\x64\x72\x65\x73\x73\x20\x74\x61\x62\x6c\x65\x20\x6c\x65\x6e\x67\x74\x68\x20\x69\x73\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x69\x6e\x20\x63\x45\x4d\x49"
);}unsigned int LocalDeviceManagementEmiC::zbab06955e5(){throw 
UnsupportedLocalDeviceMgmtPropertyException(
"\x41\x64\x64\x72\x65\x73\x73\x20\x74\x61\x62\x6c\x65\x20\x6c\x65\x6e\x67\x74\x68\x20\x69\x73\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x69\x6e\x20\x63\x45\x4d\x49"
);}void LocalDeviceManagementEmiC::z261ccc1287(unsigned short z83744e1e92){std::
vector<unsigned char>data=zd5c4ea2fc7<unsigned short,(0x1c97+613-0x1efa)>(
z83744e1e92);z0d4c9a138c(z3b8af6cac1::z6447bc235b,z67a443d064::z5b09cfe193,data)
;za6acd56ff2(z83744e1e92,
"\x49\x6e\x64\x69\x76\x69\x64\x75\x61\x6c\x20\x61\x64\x64\x72\x65\x73\x73\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x77\x72\x69\x74\x74\x65\x6e"
);}unsigned short LocalDeviceManagementEmiC::z587dd78f85(){std::vector<unsigned 
char>data;z3570ca8d16(z3b8af6cac1::z6447bc235b,z67a443d064::z5b09cfe193,
(0x11ba+883-0x152b),data);return ze378c24725<unsigned short,(0x3c8+6609-0x1d97)>
(data);}void LocalDeviceManagementEmiC::z3160480dbb(const std::vector<unsigned 
short>&addresses){std::vector<unsigned char>data;for(unsigned short addr:
addresses){data.push_back((addr>>(0xd4d+3352-0x1a5d))&(0x122a+24-0x1143));data.
push_back(addr&(0x9cd+7399-0x25b5));}zbf218e095d(z3b8af6cac1::z6447bc235b,
z67a443d064::zb46d99ee7d,addresses.size(),(0xe00+2290-0x16f0),data);z0269f1e89b(
addresses,
"\x41\x64\x64\x69\x74\x69\x6f\x6e\x61\x6c\x20\x69\x6e\x64\x69\x76\x69\x64\x75\x61\x6c\x20\x61\x64\x64\x72\x65\x73\x73\x65\x73\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x77\x72\x69\x74\x74\x65\x6e"
);}void LocalDeviceManagementEmiC::za8754b21ac(std::vector<unsigned short>&
addresses){std::vector<unsigned char>data;zdee3d5acd9(z3b8af6cac1::z6447bc235b,
z67a443d064::zb46d99ee7d,(0x5e7+7589-0x238b),(0xdf6+5772-0x2480),
(0x1a3d+2029-0x222a),data);const unsigned char z775912b5d7=data.at(
(0x233+4803-0x14f5));data.clear();z5515a7e6b0(z3b8af6cac1::z6447bc235b,
z67a443d064::zb46d99ee7d,z775912b5d7,(0xd08+4594-0x1ef8),data);unsigned int end=
data.empty()?(0x786+5123-0x1b89):data.size()-(0x103c+4040-0x2003);for(unsigned 
int index=(0x1378+4634-0x2592);index<end;index+=(0x206+8509-0x2341)){unsigned 
short addr=data.at(index)<<(0x20+4435-0x116b);addr|=data.at(index+
(0x489+5322-0x1952));addresses.push_back(addr);}}void LocalDeviceManagementEmiC
::ze507d8ae58(unsigned short index,unsigned short address){const unsigned int 
ze357ca9b3a=index+(0xb5c+2545-0x154c);std::vector<unsigned char>data=zd5c4ea2fc7
<unsigned short,(0x16f+8609-0x230e)>(address);zfdb0dea8aa(z3b8af6cac1::
z6447bc235b,z67a443d064::zb46d99ee7d,(0x1406+4529-0x25b6),ze357ca9b3a,data);}
void LocalDeviceManagementEmiC::za66a499387(std::vector<unsigned char>&
macAddress){z3570ca8d16(z3b8af6cac1::z6447bc235b,z67a443d064::z9338b23f4d,
(0x29f+4692-0x14ed),macAddress);}void LocalDeviceManagementEmiC::zbcdf3a2d1a(
const std::string&zf15e490884){std::string str=z07002adfa4(zf15e490884);str.
resize((0x2a5+986-0x661));std::vector<unsigned char>data(str.begin(),str.end());
zbf218e095d(z3b8af6cac1::z6447bc235b,z67a443d064::z74b41aa74c,(0x7e3+1595-0xe00)
,(0x1d7a+2007-0x2550),data);z7475b3f872(zf15e490884,
"\x44\x65\x76\x69\x63\x65\x20\x6e\x61\x6d\x65\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x77\x72\x69\x74\x74\x65\x6e"
);}void LocalDeviceManagementEmiC::zd0d1398630(std::string&zf15e490884){std::
vector<unsigned char>data;z5515a7e6b0(z3b8af6cac1::z6447bc235b,z67a443d064::
z74b41aa74c,(0x195a+1680-0x1fcc),(0x1ca2+419-0x1e44),data);const std::string 
latin1=std::string(data.begin(),data.end()).c_str();zf15e490884=z10bf21bedd(
latin1);}void LocalDeviceManagementEmiC::ze5acd8e45b(bool z2a654b4732){const 
unsigned char zb75c9143f0=zefd7d72c00::z2278e5df92(z83d4da9f75(),z2a654b4732);
zcc247395cd(zb75c9143f0);}bool LocalDeviceManagementEmiC::ze59351aa9c(){unsigned
 char zb55d083cb5=z83d4da9f75();return zefd7d72c00::z2a654b4732(zb55d083cb5);}
void LocalDeviceManagementEmiC::zcc247395cd(unsigned char zb55d083cb5){std::
vector<unsigned char>data=zd5c4ea2fc7<unsigned char,(0x51b+4198-0x1580)>(
zb55d083cb5);z0d4c9a138c(z3b8af6cac1::Device,z67a443d064::z72b5ac2cfb,data);
zc08cfe981c(zb55d083cb5,
"\x44\x65\x76\x69\x63\x65\x20\x73\x74\x61\x74\x75\x73\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x77\x72\x69\x74\x74\x65\x6e"
);}unsigned char LocalDeviceManagementEmiC::z83d4da9f75(){std::vector<unsigned 
char>data;z3570ca8d16(z3b8af6cac1::Device,z67a443d064::z72b5ac2cfb,
(0xd2b+383-0xea9),data);return ze378c24725<unsigned char,(0xb86+6154-0x238f)>(
data);}void LocalDeviceManagementEmiC::z563fc10557(unsigned short zb9dc9070a1){
std::vector<unsigned char>data=zd5c4ea2fc7<unsigned short,(0x48+1828-0x76a)>(
zb9dc9070a1);z0d4c9a138c(z3b8af6cac1::Device,z67a443d064::zd880c2d628,data);
z0f3b34e3a9(zb9dc9070a1,
"\x4d\x61\x6e\x75\x66\x61\x63\x74\x75\x72\x65\x72\x20\x69\x64\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x77\x72\x69\x74\x74\x65\x6e"
);}unsigned short LocalDeviceManagementEmiC::z7e6620eb94(){std::vector<unsigned 
char>data;z3570ca8d16(z3b8af6cac1::Device,z67a443d064::zd880c2d628,
(0x526+6848-0x1fe4),data);return ze378c24725<unsigned short,(0x1c9b+2084-0x24bd)
>(data);}unsigned short LocalDeviceManagementEmiC::z2afe3965f8(){std::vector<
unsigned char>data;z3570ca8d16(z3b8af6cac1::Device,z67a443d064::z46e7adb14f,
(0x1ae1+2456-0x2477),data);return ze378c24725<unsigned short,(0x2dc+2830-0xde8)>
(data);}void LocalDeviceManagementEmiC::z0d4c9a138c(unsigned short zde108227b3,
unsigned char z092ca22e9d,unsigned char data){std::vector<unsigned char>d(
(0x23b7+689-0x2667),data);z0d4c9a138c(zde108227b3,z092ca22e9d,d);}void 
LocalDeviceManagementEmiC::z0d4c9a138c(unsigned short zde108227b3,unsigned char 
z092ca22e9d,const std::vector<unsigned char>&data){ScopedQueueConnectorRxQueue 
zc912cc464d(getPort());const unsigned char z3f282c6d81=(0x5bd+950-0x972);const 
unsigned char z46ae658472=(0x17c4+2165-0x2038);const unsigned short ze357ca9b3a=
(0x21ef+456-0x23b6);KnxPacket::Ptr zfd29354025=z039c32ff6c(zde108227b3,
z3f282c6d81,z092ca22e9d,z46ae658472,ze357ca9b3a,data);getPort().send(zfd29354025
);z3387f63009(zc912cc464d);}void LocalDeviceManagementEmiC::z3570ca8d16(unsigned
 short zde108227b3,unsigned char z092ca22e9d,unsigned char z9333a4b376,std::
vector<unsigned char>&data){ScopedQueueConnectorRxQueue zc912cc464d(getPort());
const unsigned char z3f282c6d81=(0x1457+4492-0x25e2);const unsigned char 
z46ae658472=(0x228+19-0x23a);const unsigned short ze357ca9b3a=
(0x44f+6691-0x1e71);KnxPacket::Ptr zfd29354025=z5c4f5a9bd6(zde108227b3,
z3f282c6d81,z092ca22e9d,z46ae658472,ze357ca9b3a);getPort().send(zfd29354025);
zfd29354025=zaff085ae22(zc912cc464d);z6b2f113f03(zfd29354025,zde108227b3,
z3f282c6d81,z092ca22e9d,z46ae658472,z9333a4b376,ze357ca9b3a,data);}void 
LocalDeviceManagementEmiC::zbf218e095d(unsigned short zde108227b3,unsigned char 
z092ca22e9d,unsigned char z46ae658472,unsigned char z9333a4b376,std::vector<
unsigned char>&data){BOOST_ASSERT(z46ae658472*z9333a4b376==data.size());const 
unsigned int z40713058ee=(0x1e16+863-0x216b)/z9333a4b376;std::vector<unsigned 
char>::const_iterator z0352f7c072=data.begin();for(unsigned short ze357ca9b3a=
(0x1e9a+910-0x2227);ze357ca9b3a<=z46ae658472;ze357ca9b3a+=z40713058ee){const 
unsigned int z075ec3c4d2=z46ae658472-ze357ca9b3a+(0x6bf+3075-0x12c1);const 
unsigned int z46be03dd5e=(z075ec3c4d2>z40713058ee)?z40713058ee:z075ec3c4d2;const
 std::vector<unsigned char>::const_iterator z5a482c193a=z0352f7c072+z46be03dd5e*
z9333a4b376;std::vector<unsigned char>z5e133d3992(z0352f7c072,z5a482c193a);
zfdb0dea8aa(zde108227b3,z092ca22e9d,z46be03dd5e,ze357ca9b3a,z5e133d3992);
z0352f7c072=z5a482c193a;}}void LocalDeviceManagementEmiC::z5515a7e6b0(unsigned 
short zde108227b3,unsigned char z092ca22e9d,unsigned char z46ae658472,unsigned 
char z9333a4b376,std::vector<unsigned char>&data){const unsigned int z40713058ee
=(0x1b91+1242-0x2061)/z9333a4b376;for(unsigned short ze357ca9b3a=
(0x1f56+1584-0x2585);ze357ca9b3a<=z46ae658472;ze357ca9b3a+=z40713058ee){const 
unsigned int z075ec3c4d2=z46ae658472-ze357ca9b3a+(0xae9+2676-0x155c);const 
unsigned int z46be03dd5e=(z075ec3c4d2>z40713058ee)?z40713058ee:z075ec3c4d2;std::
vector<unsigned char>z5e133d3992;zdee3d5acd9(zde108227b3,z092ca22e9d,z46be03dd5e
,z9333a4b376,ze357ca9b3a,z5e133d3992);data.insert(data.end(),z5e133d3992.begin()
,z5e133d3992.end());}}void LocalDeviceManagementEmiC::zc08cfe981c(unsigned char 
zb55d083cb5,const std::string&msg){if(z83d4da9f75()!=zb55d083cb5){throw 
WriteLocalDeviceMgmtException(msg);}}void LocalDeviceManagementEmiC::za817c9ea45
(unsigned char z3be8a826b8){std::vector<unsigned char>data=zd5c4ea2fc7<unsigned 
char,(0xa6b+917-0xdff)>(z3be8a826b8);z0d4c9a138c(z3b8af6cac1::Device,z67a443d064
::z374edaa85f,data);}unsigned char LocalDeviceManagementEmiC::z44023dda1d(){std
::vector<unsigned char>data;z3570ca8d16(z3b8af6cac1::Device,z67a443d064::
z374edaa85f,(0x1aa5+1000-0x1e8c),data);return ze378c24725<unsigned char,
(0x1315+1531-0x190f)>(data);}void LocalDeviceManagementEmiC::zf1ebe16a79(
unsigned char z2bd0e78914){std::vector<unsigned char>data=zd5c4ea2fc7<unsigned 
char,(0x58c+3184-0x11fb)>(z2bd0e78914);z0d4c9a138c(z3b8af6cac1::Device,
z67a443d064::z62f66ab15f,data);}unsigned char LocalDeviceManagementEmiC::
z74c07aea9b(){std::vector<unsigned char>data;z3570ca8d16(z3b8af6cac1::Device,
z67a443d064::z62f66ab15f,(0xfb5+5134-0x23c2),data);return ze378c24725<unsigned 
char,(0xe64+5385-0x236c)>(data);}unsigned int LocalDeviceManagementEmiC::
z1b4e121dcb(unsigned int z1166f2fdb4){switch(z1166f2fdb4){case zba36969226::None
:return z68a7397df0::None;case zba36969226::Link:return z68a7397df0::Link;case 
zba36969226::z1340d1c626:return z68a7397df0::z1340d1c626;case zba36969226::Raw:
return z68a7397df0::Raw;case zba36969226::za9068249eb:return z68a7397df0::
za9068249eb;case zba36969226::zf0c17de15e:return z68a7397df0::zf0c17de15e;
default:throw UnsupportedLayerException();}}unsigned int 
LocalDeviceManagementEmiC::z04db47e219(unsigned int z1166f2fdb4){switch(
z1166f2fdb4){case z68a7397df0::None:return zba36969226::None;case z68a7397df0::
Link:return zba36969226::Link;case z68a7397df0::z1340d1c626:return zba36969226::
z1340d1c626;case z68a7397df0::Raw:return zba36969226::Raw;case z68a7397df0::
za9068249eb:return zba36969226::za9068249eb;case z68a7397df0::zf0c17de15e:return
 zba36969226::zf0c17de15e;default:throw UnsupportedLayerException();}}unsigned 
int LocalDeviceManagementEmiC::z5b1a046ae2(unsigned int z2c49518260){unsigned 
int z7b2ce21a17=zba36969226::Unknown;if(z2c49518260&z1fc0d7d5da::Link){
z7b2ce21a17|=zba36969226::Link;}if(z2c49518260&z1fc0d7d5da::z1340d1c626){
z7b2ce21a17|=zba36969226::z1340d1c626;}if(z2c49518260&z1fc0d7d5da::Raw){
z7b2ce21a17|=zba36969226::Raw;}if(z2c49518260&z1fc0d7d5da::za9068249eb){
z7b2ce21a17|=zba36969226::za9068249eb;}return z7b2ce21a17;}void 
LocalDeviceManagementEmiC::zfdb0dea8aa(unsigned short zde108227b3,unsigned char 
z092ca22e9d,unsigned char z46ae658472,unsigned int ze357ca9b3a,std::vector<
unsigned char>&data){ScopedQueueConnectorRxQueue zc912cc464d(getPort());const 
unsigned char z3f282c6d81=(0x519+3400-0x1260);KnxPacket::Ptr zfd29354025=
z039c32ff6c(zde108227b3,z3f282c6d81,z092ca22e9d,z46ae658472,ze357ca9b3a,data);
getPort().send(zfd29354025);z3387f63009(zc912cc464d);}void 
LocalDeviceManagementEmiC::zdee3d5acd9(unsigned short zde108227b3,unsigned char 
z092ca22e9d,unsigned char z46ae658472,unsigned char z9333a4b376,unsigned short 
ze357ca9b3a,std::vector<unsigned char>&data){ScopedQueueConnectorRxQueue 
zc912cc464d(getPort());const unsigned char z3f282c6d81=(0xd00+5202-0x2151);
KnxPacket::Ptr zfd29354025=z5c4f5a9bd6(zde108227b3,z3f282c6d81,z092ca22e9d,
z46ae658472,ze357ca9b3a);getPort().send(zfd29354025);zfd29354025=zaff085ae22(
zc912cc464d);z6b2f113f03(zfd29354025,zde108227b3,z3f282c6d81,z092ca22e9d,
z46ae658472,z9333a4b376,ze357ca9b3a,data);}KnxPacket::Ptr 
LocalDeviceManagementEmiC::z039c32ff6c(unsigned short zde108227b3,unsigned char 
z3f282c6d81,unsigned char z092ca22e9d,unsigned char z46ae658472,unsigned short 
ze357ca9b3a,const std::vector<unsigned char>&data){z003e4f91df formatter;
formatter.z48a824e00c(zde108227b3);formatter.zdd57f327fa(z3f282c6d81);formatter.
zf46c3b49cc(z092ca22e9d);formatter.z55f5c7ccbb(z46ae658472);formatter.
z79bd7d3c67(ze357ca9b3a);formatter.setData(data);KnxPacket::Ptr zfd29354025=std
::make_shared<KnxPacket>(formatter.size());formatter.write(zfd29354025->
getBuffer());return zfd29354025;}KnxPacket::Ptr LocalDeviceManagementEmiC::
z5c4f5a9bd6(unsigned short zde108227b3,unsigned char z3f282c6d81,unsigned char 
z092ca22e9d,unsigned char z46ae658472,unsigned short ze357ca9b3a){ze50c6f6ca0 
formatter;formatter.z48a824e00c(zde108227b3);formatter.zdd57f327fa(z3f282c6d81);
formatter.zf46c3b49cc(z092ca22e9d);formatter.z55f5c7ccbb(z46ae658472);formatter.
z79bd7d3c67(ze357ca9b3a);KnxPacket::Ptr zfd29354025=std::make_shared<KnxPacket>(
formatter.size());formatter.write(zfd29354025->getBuffer());return zfd29354025;}
void LocalDeviceManagementEmiC::z6b2f113f03(KnxPacket::Ptr packet,unsigned short
 zde108227b3,unsigned char z3f282c6d81,unsigned char z092ca22e9d,unsigned char 
z46ae658472,unsigned char z9333a4b376,unsigned short ze357ca9b3a,std::vector<
unsigned char>&data){const unsigned char z60e99e4156=z9333a4b376*z46ae658472;
z8d3fcb5f7e formatter;formatter.read(packet->getBuffer());if(formatter.
z3b20cfd48a()){std::string str=format(
"\x52\x65\x61\x64\x20\x6c\x6f\x63\x61\x6c\x20\x64\x65\x76\x69\x63\x65\x20\x6d\x67\x6d\x74\x20\x66\x61\x69\x6c\x65\x64\x20\x28\x6f\x74\x3d\x25\x75\x2c\x20\x70\x69\x64\x3d\x25\x75\x29\x3a\x20\x4e\x65\x67\x61\x74\x69\x76\x65\x20\x72\x65\x73\x70\x6f\x6e\x73\x65\x3a\x20\x25\x73"
,static_cast<unsigned int>(zde108227b3),static_cast<unsigned int>(z092ca22e9d),
formatter.z254dc6b154());throw InvalidTelegramException(str);}if((!formatter.
isValid())||(formatter.z38e712c10a()!=zde108227b3)||(formatter.z3f5ab81f7c()!=
z3f282c6d81)||(formatter.zc3a04ee564()!=z092ca22e9d)||(formatter.zb1d5689c1e()!=
z46ae658472)||(formatter.z8f2a3bea9c()!=ze357ca9b3a)||(formatter.getData().size(
)!=z60e99e4156)){std::string str=format(
"\x52\x65\x61\x64\x20\x6c\x6f\x63\x61\x6c\x20\x64\x65\x76\x69\x63\x65\x20\x6d\x67\x6d\x74\x20\x66\x61\x69\x6c\x65\x64\x20\x28\x6f\x74\x3d\x25\x75\x2c\x20\x70\x69\x64\x3d\x25\x75\x29"
,static_cast<unsigned int>(zde108227b3),static_cast<unsigned int>(z092ca22e9d));
throw InvalidTelegramException(str);}data=formatter.getData();}KnxPacket::Ptr 
LocalDeviceManagementEmiC::zaff085ae22(Connector&connector,unsigned long timeout
){try{z8d3fcb5f7e formatter;zd630f842fc policy(connector,formatter);return 
waitPacketWithPolicy<KnxPacket>(policy,timeout);}catch(Poco::TimeoutException&){
throw TelegramTimeoutException(
"\x4d\x5f\x50\x72\x6f\x70\x52\x65\x61\x64\x2e\x43\x6f\x6e");}}KnxPacket::Ptr 
LocalDeviceManagementEmiC::z3387f63009(Connector&connector,unsigned long timeout
){typedef zc61eee6dc0<z3f64688ceb,(0xd75+1483-0x1340),true>z4202e5a69b;
z5ed44f6d50 f1;z8d3fcb5f7e f2;z4202e5a69b f3;ze48348d435::Formatters formatters;
formatters.push_back(&f1);formatters.push_back(&f2);formatters.push_back(&f3);
KnxPacket::Ptr packet;try{ze48348d435 policy(connector,formatters);packet=
waitPacketWithPolicy<KnxPacket>(policy,timeout);}catch(Poco::TimeoutException&){
throw TelegramTimeoutException(
"\x4d\x5f\x50\x72\x6f\x70\x57\x72\x69\x74\x65\x2e\x43\x6f\x6e");}z5ed44f6d50 
formatter;formatter.read(packet->getBuffer());const unsigned char z22139f7a06=
formatter.z6b11bcce77();if(z22139f7a06==z5b8ac31779::z8d3fcb5f7e){std::string 
str=
"\x4c\x6f\x63\x61\x6c\x44\x65\x76\x69\x63\x65\x4d\x61\x6e\x61\x67\x65\x6d\x65\x6e\x74\x45\x6d\x69\x43\x3a\x3a\x77\x61\x69\x74\x5f\x50\x72\x6f\x70\x57\x72\x69\x74\x65\x5f\x43\x6f\x6e\x28\x2e\x29\x3a\x20\x57\x6f\x72\x6b\x61\x72\x6f\x75\x6e\x64\x20\x61\x63\x63\x65\x70\x74\x20\x61\x20\x4d\x5f\x50\x72\x6f\x70\x52\x65\x61\x64\x5f\x43\x6f\x6e\x2e"
;poco_warning(LOGGER(),str);}else if(z22139f7a06==(0x1227+3932-0x2183)){std::
string str=
"\x4c\x6f\x63\x61\x6c\x44\x65\x76\x69\x63\x65\x4d\x61\x6e\x61\x67\x65\x6d\x65\x6e\x74\x45\x6d\x69\x43\x3a\x3a\x77\x61\x69\x74\x5f\x50\x72\x6f\x70\x57\x72\x69\x74\x65\x5f\x43\x6f\x6e\x28\x2e\x29\x3a\x20\x57\x6f\x72\x6b\x61\x72\x6f\x75\x6e\x64\x20\x61\x63\x63\x65\x70\x74\x20\x61\x20\x74\x65\x6c\x65\x67\x72\x61\x6d\x20\x77\x69\x74\x68\x20\x6d\x65\x73\x73\x61\x67\x65\x20\x63\x6f\x64\x65\x20\x3d\x20\x30\x2e"
;poco_warning(LOGGER(),str);}else{if(formatter.z3b20cfd48a()){zc301b332c7 
zc341e9606b;zc341e9606b.read(packet->getBuffer());std::string str=
"\x4e\x65\x67\x61\x74\x69\x76\x65\x20\x72\x65\x73\x70\x6f\x6e\x73\x65\x3a\x20"+
zc341e9606b.z254dc6b154();throw(WriteLocalDeviceMgmtException(str));}}return 
packet;}bool LocalDeviceManagementEmiC::z97d8ed9b64(const std::vector<unsigned 
char>&zf92894300e){bool success=false;try{if(getPort().z12ff055552()==
zb5ec3c9a78::zd25ef314c9){poco_warning(LOGGER(),
"\x55\x73\x65\x20\x77\x6f\x72\x6b\x61\x72\x6f\x75\x6e\x64\x20\x77\x72\x69\x74\x65\x20\x52\x46\x20\x64\x6f\x6d\x61\x69\x6e\x20\x61\x64\x64\x72\x65\x73\x73\x20\x76\x69\x61\x20\x50\x49\x44\x5f\x44\x4f\x4d\x41\x49\x4e\x5f\x41\x44\x44\x52\x45\x53\x53\x2e"
);std::vector<unsigned char>data=zf92894300e;z0d4c9a138c(z3b8af6cac1::Device,
z67a443d064::z1928172365,data);zd02eaa9824(zf92894300e,
"\x52\x66\x20\x64\x6f\x6d\x61\x69\x6e\x20\x61\x64\x64\x72\x65\x73\x73\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x77\x72\x69\x74\x74\x65\x6e"
);success=true;}}catch(...){}return success;}bool LocalDeviceManagementEmiC::
z3ca8c1f9d7(std::vector<unsigned char>&zf92894300e){bool success=false;try{if(
getPort().z12ff055552()==zb5ec3c9a78::zd25ef314c9){poco_warning(LOGGER(),
"\x55\x73\x65\x20\x77\x6f\x72\x6b\x61\x72\x6f\x75\x6e\x64\x20\x72\x65\x61\x64\x20\x52\x46\x20\x64\x6f\x6d\x61\x69\x6e\x20\x61\x64\x64\x72\x65\x73\x73\x20\x76\x69\x61\x20\x50\x49\x44\x5f\x44\x4f\x4d\x41\x49\x4e\x5f\x41\x44\x44\x52\x45\x53\x53\x2e"
);z3570ca8d16(z3b8af6cac1::Device,z67a443d064::z1928172365,(0x1579+2492-0x1f2f),
zf92894300e);success=true;}}catch(...){}return success;}
