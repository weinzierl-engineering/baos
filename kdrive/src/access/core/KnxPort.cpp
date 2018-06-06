
#include "pch/kdrive_pch.h"
#include "kdrive/access/core/KnxPort.h"
#include "kdrive/access/core/Exception.h"
#include "kdrive/access/ldm/LocalDeviceManager.h"
#include "kdrive/access/ldm/LinkLayerManagement.h"
#include "kdrive/access/core/KnxPacket.h"
#include "kdrive/access/core/TransportPacket.h"
#include "kdrive/access/core/Events.h"
#include "kdrive/access/core/API.h"
#include "kdrive/access/core/details/RfDomainAddressFilter.h"
#include "kdrive/knx/defines/KnxLayer.h"
#include "kdrive/knx/telegrams/cemi/Frame.h"
#include "kdrive/knx/defines/MaskVersion.h"
#include "kdrive/knx/defines/KnxProperty.h"
#include "kdrive/knx/telegrams/formatters/Telegram.h"
#include "kdrive/utility/Logger.h"
#include <Poco/Exception.h>
#include <Poco/Format.h>
#include <Poco/Logger.h>
#include <Poco/NumberFormatter.h>
#include <map>
using namespace kdrive::connector;using namespace kdrive::access;using kdrive::
utility::PropertyCollection;using kdrive::knx::ze127e0a511;using kdrive::knx::
zba36969226;using kdrive::knx::cemi::z5655d09358;using kdrive::knx::zb5ec3c9a78;
using kdrive::knx::cemi::z5b8ac31779;using kdrive::knx::z2a66522423;using kdrive
::knx::zc61eee6dc0;using Poco::Dynamic::Var;using Poco::Exception;using Poco::
FastMutex;using Poco::format;using Poco::NumberFormatter;using Poco::ScopedLock;
CLASS_LOGGER(
"\x6b\x6e\x78\x2e\x61\x63\x63\x65\x73\x73\x2e\x4b\x6e\x78\x50\x6f\x72\x74")
namespace{void za640e45333(PropertyCollection&z56fa974c3c,const std::string&key,
const Poco::Dynamic::Var&value,const std::string&description,bool isReadOnly=
false){z56fa974c3c.setProperty(key,value);}void zdd2e046b74(kdrive::utility::
PropertyCollection&z56fa974c3c){using PropertyWriteableMode=zea2d083c85::
PropertyWriteableMode;za640e45333(z56fa974c3c,zea2d083c85::PortType,zea2d083c85
::ConnectorTypeLabel,"\x50\x6f\x72\x74\x20\x54\x79\x70\x65",true);za640e45333(
z56fa974c3c,zea2d083c85::zb18866bb87,static_cast<unsigned int>(zea2d083c85::
z61d5be1f36),
"\x4c\x2d\x44\x61\x74\x61\x2e\x63\x6f\x6e\x20\x54\x69\x6d\x65\x6f\x75\x74\x20\x28\x6d\x73\x29"
);za640e45333(z56fa974c3c,zea2d083c85::z39ec4d1ae7,false,
"\x4c\x61\x7a\x79\x20\x43\x6f\x6e\x66\x69\x72\x6d");za640e45333(z56fa974c3c,
zea2d083c85::z0ad2fe7ad5,true,
"\x41\x75\x74\x6f\x20\x72\x65\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x20\x61\x66\x74\x65\x72\x20\x52\x65\x73\x65\x74\x2e\x69\x6e\x64"
);za640e45333(z56fa974c3c,zea2d083c85::ze2fc87d94b,true,
"\x46\x69\x6c\x74\x65\x72\x20\x52\x46\x20\x44\x6f\x6d\x61\x69\x6e\x20\x41\x64\x64\x72\x65\x73\x73"
);za640e45333(z56fa974c3c,zea2d083c85::z5b2ecda528,static_cast<unsigned int>(
zea2d083c85::z4e34b5d0f7::Unknown),
"\x4b\x4e\x58\x20\x42\x75\x73\x20\x53\x74\x61\x74\x65",true);za640e45333(
z56fa974c3c,zea2d083c85::za6f2fc65f0,false,
"\x53\x68\x6f\x77\x20\x54\x72\x61\x6e\x73\x70\x6f\x72\x74\x20\x46\x72\x61\x6d\x65\x73"
);}bool z171490f0fd(Packet::Ptr packet){bool z8877986cc8=false;try{KnxPacket::
Ptr zfd29354025=KnxPacket::convert(packet,false);if(zfd29354025){const std::
vector<unsigned char>&buffer=zfd29354025->getBuffer();z8877986cc8=(buffer.size()
==(0x7a+8877-0x2326))&&(buffer.at((0x1ba5+936-0x1f4d))==z5b8ac31779::z60a21285a4
);}}catch(...){}return z8877986cc8;}bool z6a86f9a0fc(Packet::Ptr packet){try{
z2a66522423 frame;frame.read(packet->getBuffer());if(frame.z6b11bcce77()==
z5b8ac31779::zcb37dec9d5){return true;}}catch(Exception&e){poco_warning_f1(
LOGGER(),
"\x45\x72\x72\x6f\x72\x20\x69\x6e\x20\x69\x73\x4c\x44\x61\x74\x61\x52\x65\x71\x20\x25\x73"
,e.displayText());}return false;}}const std::string zea2d083c85::
ConnectorTypeLabel="\x4b\x6e\x78\x50\x6f\x72\x74";const std::string zea2d083c85
::zb18866bb87=
"\x6b\x6e\x78\x2e\x6c\x5f\x64\x61\x74\x61\x5f\x63\x6f\x6e\x66\x69\x72\x6d\x5f\x74\x69\x6d\x65\x6f\x75\x74"
;const std::string zea2d083c85::z39ec4d1ae7=
"\x6b\x6e\x78\x2e\x6c\x61\x7a\x79\x5f\x63\x6f\x6e\x66\x69\x72\x6d";const std::
string zea2d083c85::z0ad2fe7ad5=
"\x6b\x6e\x78\x2e\x61\x75\x74\x6f\x5f\x72\x65\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x5f\x61\x66\x74\x65\x72\x5f\x72\x65\x73\x65\x74"
;const std::string zea2d083c85::ze2fc87d94b=
"\x6b\x6e\x78\x2e\x66\x69\x6c\x74\x65\x72\x5f\x72\x66\x5f\x64\x6f\x6d\x61\x69\x6e\x5f\x61\x64\x64\x72\x65\x73\x73"
;const std::string zea2d083c85::z8b957c5a25=
"\x6b\x6e\x78\x2e\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x5f\x70\x72\x6f\x74\x6f\x63\x6f\x6c\x73"
;const std::string zea2d083c85::za498009d76=
"\x6b\x6e\x78\x2e\x70\x72\x6f\x74\x6f\x63\x6f\x6c";const std::string zea2d083c85
::za6f43e69a4=
"\x6b\x6e\x78\x2e\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x5f\x6c\x61\x79\x65\x72\x73"
;const std::string zea2d083c85::z9884ee4d6b=
"\x6b\x6e\x78\x2e\x6c\x61\x79\x65\x72";const std::string zea2d083c85::
z74dda860c7=
"\x6b\x6e\x78\x2e\x69\x73\x5f\x74\x6c\x6c\x5f\x73\x75\x70\x70\x6f\x72\x74\x65\x64"
;const std::string zea2d083c85::zb5ec3c9a78=
"\x6b\x6e\x78\x2e\x6d\x61\x73\x6b\x5f\x76\x65\x72\x73\x69\x6f\x6e";const std::
string zea2d083c85::z2a66eed75d=
"\x6b\x6e\x78\x2e\x6d\x65\x64\x69\x61\x5f\x74\x79\x70\x65\x73";const std::string
 zea2d083c85::z13c23c3849=
"\x6b\x6e\x78\x2e\x69\x6e\x64\x69\x76\x69\x64\x75\x61\x6c\x5f\x61\x64\x64\x72\x65\x73\x73"
;const std::string zea2d083c85::zc3e6a1886e=
"\x6b\x6e\x78\x2e\x70\x6c\x5f\x64\x6f\x6d\x61\x69\x6e\x5f\x61\x64\x64\x72\x65\x73\x73"
;const std::string zea2d083c85::zee467d54fc=
"\x6b\x6e\x78\x2e\x72\x66\x5f\x64\x6f\x6d\x61\x69\x6e\x5f\x61\x64\x64\x72\x65\x73\x73"
;const std::string zea2d083c85::SerialNumber=
"\x6b\x6e\x78\x2e\x73\x65\x72\x69\x61\x6c\x5f\x6e\x75\x6d\x62\x65\x72";const std
::string zea2d083c85::zdc8dff356e=
"\x6b\x6e\x78\x2e\x6d\x61\x6e\x75\x66\x61\x63\x74\x75\x72\x65\x72\x5f\x69\x64";
const std::string zea2d083c85::z1be699fe9f=
"\x6b\x6e\x78\x2e\x70\x72\x6f\x67\x72\x61\x6d\x6d\x69\x6e\x67\x5f\x6d\x6f\x64\x65"
;const std::string zea2d083c85::z5b2ecda528=
"\x6b\x6e\x78\x2e\x6b\x6e\x78\x5f\x62\x75\x73\x5f\x73\x74\x61\x74\x65";const std
::string zea2d083c85::z83d2649f20=
"\x6b\x6e\x78\x2e\x6d\x61\x78\x5f\x61\x70\x64\x75\x5f\x6c\x65\x6e\x67\x74\x68";
const std::string zea2d083c85::za6f2fc65f0=
"\x6b\x6e\x78\x2e\x72\x6f\x75\x74\x65\x5f\x74\x72\x61\x6e\x73\x70\x6f\x72\x74\x5f\x70\x61\x63\x6b\x65\x74"
;zea2d083c85::zea2d083c85():z58740d8fff(),z8a3623983b(*this),z7eae6471dd(
(0x1a62+2935-0x25d9)){zdd2e046b74(*this);z674533ad46();}zea2d083c85::~
zea2d083c85(){try{z3101dee849();}catch(...){}}void zea2d083c85::routeRx(Packet::
Ptr packet){KnxPacket::Ptr zfd29354025=KnxPacket::convert(packet,false);bool 
zd47ebe7a90=true;const unsigned int z7827eb5079=getProperty(z2a66eed75d,
(0x3a6+6069-0x1b5b));const bool z3990f18c27=ze127e0a511::z0266f230d6(z7827eb5079
);if(zfd29354025&&z3990f18c27&&z605bfe297a()){std::vector<unsigned char>
zf92894300e;try{zf92894300e=getProperty(zee467d54fc).extract<std::vector<
unsigned char> >();}catch(...){}zd47ebe7a90=z2429a4bade::zd47ebe7a90(zfd29354025
,zf92894300e);}if(zd47ebe7a90){z58740d8fff::routeRx(packet);if(zfd29354025){
routeEvent(z11d7f1cf7b::zefe6385ec5);}}if(z171490f0fd(packet)){poco_warning(
LOGGER(),
"\x52\x65\x63\x65\x69\x76\x65\x64\x20\x61\x20\x52\x65\x73\x65\x74\x2e\x69\x6e\x64"
);routeEvent(z11d7f1cf7b::z00c580762c);}}void zea2d083c85::zb44d474e62(unsigned 
int timeout){setProperty(zb18866bb87,timeout);}unsigned int zea2d083c85::
z0eb4f337db()const{return getProperty(zb18866bb87);}void zea2d083c85::
zbac9796807(bool enable){setProperty(z39ec4d1ae7,enable);}bool zea2d083c85::
z680ad25263()const{return getProperty(z39ec4d1ae7);}void zea2d083c85::
z367d96a272(bool enable){enable?z674533ad46():z3101dee849();setProperty(
z0ad2fe7ad5,enable);}bool zea2d083c85::zddad992be2()const{return getProperty(
z0ad2fe7ad5);}void zea2d083c85::z76d6965e85(bool enable){setProperty(ze2fc87d94b
,enable);}bool zea2d083c85::z605bfe297a()const{return getProperty(ze2fc87d94b);}
unsigned int zea2d083c85::z791c5fd335(){if(isEmpty(z8b957c5a25)){setProperty(
z8b957c5a25,zc1ee43d1f6());}return getProperty(z8b957c5a25);}void zea2d083c85::
setProtocol(unsigned int zd2b01bb0a4){if(!zdf6fe1862a(zd2b01bb0a4)){const 
UnsupportedProtocolException e(NumberFormatter::format(zd2b01bb0a4));raiseError(
e);}z8a3623983b.setProtocol(zd2b01bb0a4);z81289a39cd(zd2b01bb0a4);const unsigned
 int z5f793390e9=z93d917156c();if(z5f793390e9!=zd2b01bb0a4){const 
ProtocolWriteValidationException e(format(
"\x77\x72\x69\x74\x65\x20\x25\x75\x2c\x20\x72\x65\x61\x64\x20\x25\x75",
zd2b01bb0a4,z5f793390e9));raiseError(e);}setProperty(za498009d76,zd2b01bb0a4);}
unsigned int zea2d083c85::z01a2f5d4b7(){if(isEmpty(za498009d76)){const unsigned 
int zd2b01bb0a4=z93d917156c();zc7087b3e64().setProtocol(zd2b01bb0a4);setProperty
(za498009d76,zd2b01bb0a4);}return getProperty(za498009d76);}bool zea2d083c85::
zdf6fe1862a(unsigned int zd2b01bb0a4){const unsigned int z45fb7ed6f5=z791c5fd335
();return zdf6fe1862a(z45fb7ed6f5,zd2b01bb0a4);}bool zea2d083c85::zdf6fe1862a(
unsigned int zef30e92c56,unsigned int zd2b01bb0a4){if(zd2b01bb0a4==za498009d76::
Unknown){return false;}return((zef30e92c56&zd2b01bb0a4)==zd2b01bb0a4)?true:false
;}unsigned int zea2d083c85::z089addfe48(unsigned int zef30e92c56)const{unsigned 
int zd2b01bb0a4=za498009d76::Unknown;if(zdf6fe1862a(zef30e92c56,za498009d76::
z1746fd28fd)){zd2b01bb0a4=za498009d76::z1746fd28fd;}return zd2b01bb0a4;}void 
zea2d083c85::zd897a67e14(){const unsigned int zef30e92c56=z791c5fd335();const 
unsigned int zef47cdc64c=z089addfe48(zef30e92c56);if(zef47cdc64c==za498009d76::
Unknown){const NoPreferredProtocolFoundException e(format(
"\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x70\x72\x6f\x74\x6f\x63\x6f\x6c\x73\x20\x25\x75"
,zef30e92c56));raiseError(e);}setProtocol(zef47cdc64c);}unsigned int zea2d083c85
::z524baf8256(){if(isEmpty(za6f43e69a4)){setProperty(za6f43e69a4,z07a1de2360());
}return getProperty(za6f43e69a4);}void zea2d083c85::z7de2a5ac1c(unsigned int 
z1166f2fdb4){if(!z4011fc21c2(z1166f2fdb4)){const UnsupportedLayerException e(
NumberFormatter::format(z1166f2fdb4));raiseError(e);}const unsigned int 
z799b0099b5=!isEmpty(z9884ee4d6b)?z42de9bb630():static_cast<unsigned int>(
zba36969226::Unknown);try{setProperty(z9884ee4d6b,z1166f2fdb4);zd8cf4148d6(
z1166f2fdb4);}catch(Exception&e){setProperty(z9884ee4d6b,z799b0099b5);raiseError
(e);}}unsigned int zea2d083c85::z42de9bb630(){unsigned int z1166f2fdb4=
zba36969226::Unknown;if(isEmpty(z9884ee4d6b)){if(z01a2f5d4b7()==za498009d76::
z1746fd28fd){z1166f2fdb4=z6fe0401c37();setProperty(z9884ee4d6b,z1166f2fdb4);}}
else{z1166f2fdb4=getProperty(z9884ee4d6b);}return z1166f2fdb4;}bool zea2d083c85
::z4011fc21c2(unsigned int z1166f2fdb4){unsigned int z7b2ce21a17=z524baf8256();
return z4011fc21c2(z7b2ce21a17,z1166f2fdb4);}bool zea2d083c85::z4011fc21c2(
unsigned int z7ecdefe519,unsigned int z1166f2fdb4){if(z1166f2fdb4==zba36969226::
Unknown){return false;}return((z7ecdefe519&z1166f2fdb4)==z1166f2fdb4)?true:false
;}unsigned int zea2d083c85::z340f3e6eca(unsigned int z7ecdefe519)const{unsigned 
int z1166f2fdb4=zba36969226::Unknown;if(z4011fc21c2(z7ecdefe519,zba36969226::
Link)){z1166f2fdb4=zba36969226::Link;}else if(z4011fc21c2(z7ecdefe519,
zba36969226::z1340d1c626)){z1166f2fdb4=zba36969226::z1340d1c626;}else if(
z4011fc21c2(z7ecdefe519,zba36969226::Raw)){z1166f2fdb4=zba36969226::Raw;}return 
z1166f2fdb4;}void zea2d083c85::za8d5adfa57(){const unsigned int z7ecdefe519=
z524baf8256();const unsigned int zef47cdc64c=z340f3e6eca(z7ecdefe519);if(
zef47cdc64c==zba36969226::Unknown){const NoPreferredLayerFoundException error(
format(
"\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x6c\x61\x79\x65\x72\x73\x20\x25\x75",
z7ecdefe519));raiseError(error);}z7de2a5ac1c(zef47cdc64c);}bool zea2d083c85::
z19cee9e459(){if(isEmpty(z74dda860c7)){setProperty(z74dda860c7,z021857951d());}
return getProperty(z74dda860c7);}void zea2d083c85::z371132a440(bool enable){if(!
z19cee9e459()){const AccessPortException error(
"\x63\x45\x4d\x49\x20\x4c\x6f\x63\x61\x6c\x20\x54\x72\x61\x6e\x73\x70\x6f\x72\x74\x20\x4c\x61\x79\x65\x72\x20\x69\x73\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64"
,zfa668fdf8b::z1bcf406118);raiseError(error);}zbe0f21419f(enable);}unsigned int 
zea2d083c85::z12ff055552(){if(isEmpty(zb5ec3c9a78)){setProperty(zb5ec3c9a78,
z1f86c15fd0());}return getProperty(zb5ec3c9a78);}std::string zea2d083c85::
z3251ee4772(){return zb5ec3c9a78::getDescription(z12ff055552());}unsigned short 
zea2d083c85::z1bf089d014(){if(isEmpty(z2a66eed75d)){if(z01a2f5d4b7()==
za498009d76::z1746fd28fd){try{setProperty(z2a66eed75d,z716d13ecdd());}catch(
Exception&exception){LOGGER().log(exception);poco_warning(LOGGER(),
"\x67\x65\x74\x4d\x65\x64\x69\x61\x54\x79\x70\x65\x73\x20\x66\x61\x69\x6c\x65\x64\x2c\x20\x67\x65\x74\x74\x69\x6e\x67\x20\x6d\x65\x64\x69\x61\x20\x74\x79\x70\x65\x73\x20\x66\x72\x6f\x6d\x20\x74\x68\x65\x20\x6d\x61\x73\x6b\x20\x76\x65\x72\x73\x69\x6f\x6e"
);setProperty(z2a66eed75d,z21e0db8628());}}else{setProperty(z2a66eed75d,
z21e0db8628());}}return getProperty(z2a66eed75d);}std::string zea2d083c85::
zc3136dcdfa(){return ze127e0a511::zed9c5ebd97(z1bf089d014());}void zea2d083c85::
zf52767dc71(unsigned int z83744e1e92){zd0d51f5d95(z83744e1e92);setProperty(
z13c23c3849,z83744e1e92);}unsigned int zea2d083c85::zbe00e8c303(){if(isEmpty(
z13c23c3849)){setProperty(z13c23c3849,zfbca701d15());}return getProperty(
z13c23c3849);}void zea2d083c85::z22c631a890(unsigned int zf92894300e){
za08556178a(zf92894300e);setProperty(zc3e6a1886e,zf92894300e);}unsigned int 
zea2d083c85::zbb04277d6f(){if(isEmpty(zc3e6a1886e)){setProperty(zc3e6a1886e,
z7bc42300fa());}return getProperty(zc3e6a1886e);}void zea2d083c85::z3a2f8fbb8f(
const std::vector<unsigned char>&zf92894300e){z57588f181e(zf92894300e);
setProperty(zee467d54fc,zf92894300e);}const std::vector<unsigned char>&
zea2d083c85::zafeaeec64f(){if(isEmpty(zee467d54fc)){std::vector<unsigned char>v;
zee1690ad9d(v);setProperty(zee467d54fc,v);}return extract<std::vector<unsigned 
char> >(zee467d54fc);}void zea2d083c85::z5f5fd61d58(const std::vector<unsigned 
char>&zd311e7ca26){za8e4013ca3(zd311e7ca26);setProperty(SerialNumber,zd311e7ca26
);}const std::vector<unsigned char>&zea2d083c85::getSerialNumber(){if(isEmpty(
SerialNumber)){std::vector<unsigned char>v;zc153fe5430(v);setProperty(
SerialNumber,v);}return extract<std::vector<unsigned char> >(SerialNumber);}void
 zea2d083c85::z68349079eb(unsigned int zb9dc9070a1){zf52cc38da1(zb9dc9070a1);
setProperty(zdc8dff356e,zb9dc9070a1);}unsigned int zea2d083c85::z19770e1430(){if
(isEmpty(zdc8dff356e)){setProperty(zdc8dff356e,z29f4d6d6a3());}return 
getProperty(zdc8dff356e);}void zea2d083c85::z64a5d004ba(bool enable){zeb33dc19f4
(enable);setProperty(z1be699fe9f,enable);}bool zea2d083c85::z2a654b4732(){const 
bool z2772cce074=zf21c0140ae();setProperty(z1be699fe9f,z2772cce074);return 
z2772cce074;}unsigned int zea2d083c85::z175c5f0532()const{return getProperty(
z5b2ecda528);}unsigned int zea2d083c85::zaff92585a2(){if(isEmpty(z83d2649f20)){
try{setProperty(z83d2649f20,z50193a49a9());}catch(
DeviceManagementAlreadyOpenException&e){poco_warning_f1(LOGGER(),
"\x52\x65\x61\x64\x69\x6e\x67\x20\x6d\x61\x78\x20\x41\x50\x44\x55\x20\x6c\x65\x6e\x67\x74\x68\x20\x66\x61\x69\x6c\x65\x64\x20\x28\x25\x73\x29\x2c\x20\x75\x73\x65\x20\x73\x74\x61\x6e\x64\x61\x72\x64\x20\x76\x61\x6c\x75\x65\x20\x28\x31\x35\x29"
,e.displayText());return z81eda64581;}}return getProperty(z83d2649f20);}void 
zea2d083c85::z4fb044e67b(bool enable){setProperty(za6f2fc65f0,enable);}bool 
zea2d083c85::z0be6f75ca1()const{return getProperty(za6f2fc65f0);}void 
zea2d083c85::openImpl(){zd897a67e14();za8d5adfa57();removeProperty(zee467d54fc);
unsigned int z7827eb5079=z1bf089d014();const bool z0266f230d6=ze127e0a511::
z0266f230d6(z7827eb5079);if(z0266f230d6){zafeaeec64f();getSerialNumber();}
zaff92585a2();z19cee9e459();}void zea2d083c85::resetPropertiesImpl(){z58740d8fff
::resetPropertiesImpl();zdd2e046b74(*this);}void zea2d083c85::
setPreferredSettingsImpl(){zd897a67e14();za8d5adfa57();}bool zea2d083c85::
z021857951d(){return z4011fc21c2(zba36969226::za9068249eb);}void zea2d083c85::
zbe0f21419f(bool enable){if(enable){z7eae6471dd=z42de9bb630();z7de2a5ac1c(
zba36969226::za9068249eb);}else{z7de2a5ac1c(z7eae6471dd);}}unsigned int 
zea2d083c85::z1f86c15fd0(){const unsigned int z65fc26404c=z4b4d92d5e8();
setProperty(zb5ec3c9a78,z65fc26404c);return z65fc26404c;}unsigned short 
zea2d083c85::z716d13ecdd(){const unsigned short z7827eb5079=zf4cd0c79bd();
setProperty(z2a66eed75d,z7827eb5079);return z7827eb5079;}unsigned short 
zea2d083c85::z21e0db8628(){const unsigned short z7827eb5079=z442e211ba0();
setProperty(z2a66eed75d,z7827eb5079);return z7827eb5079;}void zea2d083c85::
zd0d51f5d95(unsigned int z83744e1e92){z8a3623983b.z5392ddee85(z83744e1e92);
setProperty(z13c23c3849,z83744e1e92);}unsigned int zea2d083c85::zfbca701d15(){
const unsigned int z83744e1e92=z8a3623983b.zf670e5347d();setProperty(z13c23c3849
,z83744e1e92);return z83744e1e92;}void zea2d083c85::za08556178a(unsigned int 
zf92894300e){z8a3623983b.z6c59c3156d(zf92894300e);setProperty(zc3e6a1886e,
zf92894300e);}unsigned int zea2d083c85::z7bc42300fa(){const unsigned int 
zf92894300e=z8a3623983b.zfa42f5b322();setProperty(zc3e6a1886e,zf92894300e);
return zf92894300e;}void zea2d083c85::z57588f181e(const Var&zf92894300e){const 
std::vector<unsigned char>address=zf92894300e.extract<std::vector<unsigned char>
 >();z8a3623983b.zb488b9244d(address);setProperty(zee467d54fc,zf92894300e);}void
 zea2d083c85::zee1690ad9d(std::vector<unsigned char>&zf92894300e){z8a3623983b.
z875dcf85de(zf92894300e);setProperty(zee467d54fc,zf92894300e);}void zea2d083c85
::za8e4013ca3(const Poco::Dynamic::Var&zd311e7ca26){const std::vector<unsigned 
char>ze205a3dad4=zd311e7ca26.extract<std::vector<unsigned char> >();z8a3623983b.
z2853a8fc86(ze205a3dad4);setProperty(SerialNumber,ze205a3dad4);}void zea2d083c85
::zc153fe5430(std::vector<unsigned char>&zd311e7ca26){z8a3623983b.z8039b7bd80(
zd311e7ca26);setProperty(SerialNumber,zd311e7ca26);}void zea2d083c85::
zf52cc38da1(unsigned int zb9dc9070a1){z8a3623983b.z563fc10557(zb9dc9070a1);
setProperty(zdc8dff356e,zb9dc9070a1);}unsigned int zea2d083c85::z29f4d6d6a3(){
const unsigned int zb9dc9070a1=z8a3623983b.z7e6620eb94();setProperty(zdc8dff356e
,zb9dc9070a1);return zb9dc9070a1;}void zea2d083c85::zeb33dc19f4(bool enable){
zc7087b3e64().ze5acd8e45b(enable);setProperty(z1be699fe9f,enable);}bool 
zea2d083c85::zf21c0140ae(){const bool z2772cce074=zc7087b3e64().ze59351aa9c();
setProperty(z1be699fe9f,z2772cce074);return z2772cce074;}unsigned int 
zea2d083c85::z50193a49a9(){unsigned int zae41a04420=z81eda64581;try{zae41a04420=
zc7087b3e64().z2afe3965f8();if(zae41a04420<z81eda64581){zae41a04420=z81eda64581;
poco_warning_f1(LOGGER(),
"\x49\x6e\x74\x65\x72\x66\x61\x63\x65\x20\x72\x65\x74\x75\x72\x6e\x20\x61\x6e\x20\x69\x6e\x76\x61\x6c\x69\x64\x20\x6d\x61\x78\x20\x41\x50\x44\x55\x20\x6c\x65\x6e\x67\x74\x68\x20\x28\x25\x75\x29\x2c\x20\x75\x73\x65\x20\x73\x74\x61\x6e\x64\x61\x72\x64\x20\x76\x61\x6c\x75\x65"
,zae41a04420);}}catch(DeviceManagementAlreadyOpenException&){throw;}catch(
Exception&){poco_warning(LOGGER(),
"\x52\x65\x61\x64\x69\x6e\x67\x20\x6d\x61\x78\x20\x41\x50\x44\x55\x20\x6c\x65\x6e\x67\x74\x68\x20\x66\x61\x69\x6c\x65\x64\x2c\x20\x75\x73\x65\x20\x73\x74\x61\x6e\x64\x61\x72\x64\x20\x76\x61\x6c\x75\x65\x20\x28\x31\x35\x29"
);}return zae41a04420;}z11671f1e0a&zea2d083c85::zc7087b3e64(){return z8a3623983b
;}const z11671f1e0a&zea2d083c85::zc7087b3e64()const{return z8a3623983b;}
KnxPacket::Ptr zea2d083c85::zdc8ced637e(const KnxPacket::Ptr packet){return 
packet;}KnxPacket::Ptr zea2d083c85::z4f92549f31(const KnxPacket::Ptr packet){
return packet;}void zea2d083c85::za117cd55de(ScopedQueueConnectorRxQueue&queue,
KnxPacket::Ptr packet){const unsigned int z00601023bd=z0eb4f337db();if(
z00601023bd&&z6a86f9a0fc(packet)){try{zaa4f795dda::z6eae11ab53(queue,z00601023bd
);routeEvent(z11d7f1cf7b::z294e2e57c8);}catch(Poco::TimeoutException&e){
routeEvent(z11d7f1cf7b::zc10d61ac8e);poco_warning_f1(LOGGER(),
"\x77\x61\x69\x74\x43\x6f\x6e\x66\x69\x72\x6d\x3a\x20\x25\x73",e.displayText());
if(!z680ad25263()){const LDataConfirmTimeoutException e("");raiseError(e);}}}}
void zea2d083c85::zd82f9ac44a(z4e34b5d0f7::State z7619915478){ScopedLock<
FastMutex>lock(zf31a9d5745);const int z57c0ade8ca=getProperty(z5b2ecda528);if(
z57c0ade8ca!=z7619915478){setProperty(z5b2ecda528,static_cast<unsigned int>(
z7619915478));if(z7619915478!=z4e34b5d0f7::Unknown){routeEvent(z7619915478==
z4e34b5d0f7::Connected?z11d7f1cf7b::za7b5aa463a:z11d7f1cf7b::z740394bba8);}}}
void zea2d083c85::zae0bb42f7a(TransportPacket::Ptr zfa61376f49){if(getProperty(
za6f2fc65f0)==true){routeRx(zfa61376f49);}}void zea2d083c85::z174ce8ab4d(
TransportPacket::Ptr zfa61376f49){if(getProperty(za6f2fc65f0)==true){routeTx(
zfa61376f49);}}void zea2d083c85::zd8cf4148d6(unsigned int z1166f2fdb4){
z8a3623983b.z766e2388b4(z1166f2fdb4);}unsigned int zea2d083c85::z6fe0401c37(){
return z8a3623983b.z6f5601a8cf();}unsigned int zea2d083c85::zf4cd0c79bd(){return
 z8a3623983b.z5da113978e();}unsigned int zea2d083c85::z4b4d92d5e8(){return 
z8a3623983b.z51177f5ce9();}unsigned short zea2d083c85::z442e211ba0(){const 
unsigned int ze723c17414=zb5ec3c9a78::za2a7a09218(z12ff055552());unsigned short 
z7827eb5079=(0xef4+5364-0x23e8);switch(ze723c17414){case zb5ec3c9a78::
z1f5ef68b4f:z7827eb5079=ze127e0a511::Medium::z1f5ef68b4f;break;case zb5ec3c9a78
::z6cb5bb14f9:z7827eb5079=ze127e0a511::Medium::z6cb5bb14f9;break;case 
zb5ec3c9a78::z575b70b0f4:z7827eb5079=ze127e0a511::Medium::z575b70b0f4;break;case
 zb5ec3c9a78::IP:z7827eb5079=ze127e0a511::Medium::IP;break;}return z7827eb5079;}
void zea2d083c85::z674533ad46(){EventSignal&signal=getEventSignal();
signalConnectionEvent_=signal.connect(std::bind(&zea2d083c85::onEvent,this,std::
placeholders::_1));}void zea2d083c85::z3101dee849(){signalConnectionEvent_.
disconnect();}void zea2d083c85::onEvent(unsigned long e){if((e==z11d7f1cf7b::
z00c580762c)&&zddad992be2()){poco_information(LOGGER(),
"\x54\x72\x79\x20\x74\x6f\x20\x72\x65\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x20\x6c\x61\x79\x65\x72\x20\x61\x66\x74\x65\x72\x20\x72\x65\x73\x65\x74"
);try{z7de2a5ac1c(z42de9bb630());}catch(Exception&e){poco_warning_f1(LOGGER(),
"\x52\x65\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x20\x66\x61\x69\x6c\x65\x64\x3a\x20\x25\x73"
,e.displayText());}}}
