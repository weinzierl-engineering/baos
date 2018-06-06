
#include "pch/kdrive_pch.h"
#include "kdrive/access/ldm/LocalDeviceManager.h"
#include "kdrive/access/core/Exception.h"
#include "kdrive/access/core/KnxPort.h"
#include "kdrive/access/ldm/LocalDeviceManagementEmiC.h"
#include "kdrive/access/core/API.h"
#include "kdrive/knx/defines/KnxLayer.h"
#include "kdrive/utility/Logger.h"
#include "kdrive/utility/LoggerFormatter.h"
#include <Poco/Format.h>
#include <Poco/Logger.h>
using namespace kdrive::access;using kdrive::knx::zba36969226;using kdrive::
utility::LoggerFormatter;using Poco::format;CLASS_LOGGER(
"\x6b\x6e\x78\x2e\x61\x63\x63\x65\x73\x73\x2e\x4c\x6f\x63\x61\x6c\x44\x65\x76\x69\x63\x65\x4d\x61\x6e\x61\x67\x65\x72"
)z11671f1e0a::z11671f1e0a(zea2d083c85&port):zcdc6474106(port){}z11671f1e0a::~
z11671f1e0a(){}void z11671f1e0a::setProtocol(unsigned int zd2b01bb0a4){switch(
zd2b01bb0a4){case za498009d76::None:z82951ffa8c.reset();poco_debug(LOGGER(),
"\x73\x65\x74\x50\x72\x6f\x74\x6f\x63\x6f\x6c\x20\x28\x6e\x6f\x6e\x65\x29");
break;case za498009d76::z1746fd28fd:z82951ffa8c=std::make_shared<
LocalDeviceManagementEmiC>(zcdc6474106);poco_debug(LOGGER(),
"\x73\x65\x74\x50\x72\x6f\x74\x6f\x63\x6f\x6c\x20\x28\x63\x45\x4d\x49\x29");
break;default:poco_critical_f1(LOGGER(),
"\x73\x65\x74\x50\x72\x6f\x74\x6f\x63\x6f\x6c\x2c\x20\x69\x6e\x76\x61\x6c\x69\x64\x20\x70\x72\x6f\x74\x6f\x63\x6f\x6c\x20\x28\x25\x75\x29"
,zd2b01bb0a4);z82951ffa8c.reset();throw UnsupportedProtocolException(format(
"\x2c\x20\x70\x72\x6f\x74\x6f\x63\x6f\x6c\x20\x28\x25\x75\x29",zd2b01bb0a4));}}
void z11671f1e0a::restart(){poco_information(LOGGER(),
"\x72\x65\x73\x74\x61\x72\x74");za5e68b432b();z82951ffa8c->restart();}void 
z11671f1e0a::z766e2388b4(unsigned int z1166f2fdb4){poco_information_f2(LOGGER(),
"\x77\x72\x69\x74\x65\x4c\x61\x79\x65\x72\x20\x28\x25\x75\x20\x3d\x20\x25\x73\x29"
,z1166f2fdb4,zba36969226::getDescription(z1166f2fdb4));za5e68b432b();z82951ffa8c
->z766e2388b4(z1166f2fdb4);}unsigned int z11671f1e0a::z6f5601a8cf(){
poco_information(LOGGER(),"\x72\x65\x61\x64\x4c\x61\x79\x65\x72");za5e68b432b();
return z82951ffa8c->z6f5601a8cf();}unsigned int z11671f1e0a::z2e0dcb1a8b(){
poco_information(LOGGER(),
"\x72\x65\x61\x64\x53\x75\x70\x70\x6f\x72\x74\x65\x64\x4c\x61\x79\x65\x72\x73");
za5e68b432b();return z82951ffa8c->z2e0dcb1a8b();}unsigned int z11671f1e0a::
z51177f5ce9(){poco_information(LOGGER(),
"\x72\x65\x61\x64\x4d\x61\x73\x6b\x56\x65\x72\x73\x69\x6f\x6e");za5e68b432b();
return z82951ffa8c->z51177f5ce9();}unsigned short z11671f1e0a::z5da113978e(){
poco_information(LOGGER(),
"\x72\x65\x61\x64\x4d\x65\x64\x69\x61\x54\x79\x70\x65\x73");za5e68b432b();return
 z82951ffa8c->z5da113978e();}void z11671f1e0a::z5392ddee85(unsigned int 
z83744e1e92){poco_information_f1(LOGGER(),
"\x77\x72\x69\x74\x65\x49\x6e\x64\x69\x76\x69\x64\x75\x61\x6c\x41\x64\x64\x72\x65\x73\x73\x20\x28\x30\x78\x25\x58\x29"
,z83744e1e92);za5e68b432b();z82951ffa8c->z5392ddee85(z83744e1e92);}unsigned int 
z11671f1e0a::zf670e5347d(){poco_information(LOGGER(),
"\x72\x65\x61\x64\x49\x6e\x64\x69\x76\x69\x64\x75\x61\x6c\x41\x64\x64\x72\x65\x73\x73"
);za5e68b432b();return z82951ffa8c->zf670e5347d();}void z11671f1e0a::z6c59c3156d
(unsigned int zf92894300e){poco_information_f1(LOGGER(),
"\x77\x72\x69\x74\x65\x50\x6c\x44\x6f\x6d\x61\x69\x6e\x41\x64\x64\x72\x65\x73\x73\x20\x28\x30\x78\x25\x58\x29"
,zf92894300e);za5e68b432b();z82951ffa8c->z6c59c3156d(zf92894300e);}unsigned int 
z11671f1e0a::zfa42f5b322(){poco_information(LOGGER(),
"\x72\x65\x61\x64\x50\x6c\x44\x6f\x6d\x61\x69\x6e\x41\x64\x64\x72\x65\x73\x73");
za5e68b432b();return z82951ffa8c->zfa42f5b322();}void z11671f1e0a::zb488b9244d(
const std::vector<unsigned char>&zf92894300e){poco_information_f1(LOGGER(),
"\x77\x72\x69\x74\x65\x52\x66\x44\x6f\x6d\x61\x69\x6e\x41\x64\x64\x72\x65\x73\x73\x20\x28\x25\x73\x29"
,LoggerFormatter::toHex(zf92894300e));za5e68b432b();z82951ffa8c->zb488b9244d(
zf92894300e);}void z11671f1e0a::z875dcf85de(std::vector<unsigned char>&
zf92894300e){poco_information(LOGGER(),
"\x72\x65\x61\x64\x52\x66\x44\x6f\x6d\x61\x69\x6e\x41\x64\x64\x72\x65\x73\x73");
za5e68b432b();z82951ffa8c->z875dcf85de(zf92894300e);}void z11671f1e0a::
z2853a8fc86(const std::vector<unsigned char>&zd311e7ca26){poco_information_f1(
LOGGER(),
"\x77\x72\x69\x74\x65\x53\x65\x72\x69\x61\x6c\x4e\x75\x6d\x62\x65\x72\x20\x28\x25\x73\x29"
,LoggerFormatter::toHex(zd311e7ca26));za5e68b432b();z82951ffa8c->z2853a8fc86(
zd311e7ca26);}void z11671f1e0a::z8039b7bd80(std::vector<unsigned char>&
zd311e7ca26){poco_information(LOGGER(),
"\x72\x65\x61\x64\x53\x65\x72\x69\x61\x6c\x4e\x75\x6d\x62\x65\x72");za5e68b432b(
);z82951ffa8c->z8039b7bd80(zd311e7ca26);}void z11671f1e0a::z00fec7e215(unsigned 
int zfd606f58be){poco_information_f1(LOGGER(),
"\x77\x72\x69\x74\x65\x45\x72\x72\x6f\x72\x46\x6c\x61\x67\x73\x20\x28\x30\x78\x25\x58\x29"
,zfd606f58be);za5e68b432b();z82951ffa8c->z00fec7e215(zfd606f58be);}unsigned int 
z11671f1e0a::za4544ba4dc(){poco_information(LOGGER(),
"\x72\x65\x61\x64\x45\x72\x72\x6f\x72\x46\x6c\x61\x67\x73");za5e68b432b();return
 z82951ffa8c->za4544ba4dc();}void z11671f1e0a::zc2caea0629(unsigned int 
ze2fcb9ca3a){poco_information_f1(LOGGER(),
"\x77\x72\x69\x74\x65\x41\x64\x64\x72\x65\x73\x73\x54\x61\x62\x6c\x65\x4c\x65\x6e\x67\x74\x68\x20\x28\x25\x75\x29"
,ze2fcb9ca3a);za5e68b432b();z82951ffa8c->zc2caea0629(ze2fcb9ca3a);}unsigned int 
z11671f1e0a::zbab06955e5(){poco_information(LOGGER(),
"\x72\x65\x61\x64\x41\x64\x64\x72\x65\x73\x73\x54\x61\x62\x6c\x65\x4c\x65\x6e\x67\x74\x68"
);za5e68b432b();return z82951ffa8c->zbab06955e5();}void z11671f1e0a::z261ccc1287
(unsigned short z83744e1e92){poco_information_f1(LOGGER(),
"\x77\x72\x69\x74\x65\x49\x6e\x64\x69\x76\x69\x64\x75\x61\x6c\x41\x64\x64\x72\x65\x73\x73\x4b\x6e\x78\x4e\x65\x74\x49\x70\x20\x28\x30\x78\x25\x58\x29"
,static_cast<unsigned int>(z83744e1e92));za5e68b432b();z82951ffa8c->z261ccc1287(
z83744e1e92);}unsigned short z11671f1e0a::z587dd78f85(){poco_information(LOGGER(
),
"\x72\x65\x61\x64\x49\x6e\x64\x69\x76\x69\x64\x75\x61\x6c\x41\x64\x64\x72\x65\x73\x73\x4b\x6e\x78\x4e\x65\x74\x49\x70"
);za5e68b432b();return z82951ffa8c->z587dd78f85();}void z11671f1e0a::z3160480dbb
(const std::vector<unsigned short>&addresses){poco_information(LOGGER(),
"\x77\x72\x69\x74\x65\x41\x64\x64\x69\x74\x69\x6f\x6e\x61\x6c\x49\x6e\x64\x69\x76\x69\x64\x75\x61\x6c\x41\x64\x64\x72\x65\x73\x73\x65\x73"
);za5e68b432b();return z82951ffa8c->z3160480dbb(addresses);}void z11671f1e0a::
za8754b21ac(std::vector<unsigned short>&addresses){poco_information(LOGGER(),
"\x72\x65\x61\x64\x41\x64\x64\x69\x74\x69\x6f\x6e\x61\x6c\x49\x6e\x64\x69\x76\x69\x64\x75\x61\x6c\x41\x64\x64\x72\x65\x73\x73\x65\x73"
);za5e68b432b();return z82951ffa8c->za8754b21ac(addresses);}void z11671f1e0a::
ze507d8ae58(unsigned short index,unsigned short address){poco_information_f2(
LOGGER(),
"\x77\x72\x69\x74\x65\x41\x64\x64\x69\x74\x69\x6f\x6e\x61\x6c\x49\x6e\x64\x69\x76\x69\x64\x75\x61\x6c\x41\x64\x64\x72\x65\x73\x73\x28\x69\x6e\x64\x65\x78\x3d\x25\x75\x2c\x20\x61\x64\x64\x72\x65\x73\x73\x3d\x30\x78\x25\x58\x29"
,static_cast<unsigned int>(index),static_cast<unsigned int>(address));
za5e68b432b();return z82951ffa8c->ze507d8ae58(index,address);}void z11671f1e0a::
za66a499387(std::vector<unsigned char>&macAddress){poco_information(LOGGER(),
"\x72\x65\x61\x64\x4d\x61\x63\x41\x64\x64\x72\x65\x73\x73");za5e68b432b();
z82951ffa8c->za66a499387(macAddress);}void z11671f1e0a::zbcdf3a2d1a(const std::
string&zf15e490884){poco_information_f1(LOGGER(),
"\x77\x72\x69\x74\x65\x44\x65\x76\x69\x63\x65\x4e\x61\x6d\x65\x20\x28\x25\x73\x29"
,zf15e490884);za5e68b432b();z82951ffa8c->zbcdf3a2d1a(zf15e490884);}void 
z11671f1e0a::zd0d1398630(std::string&zf15e490884){poco_information(LOGGER(),
"\x72\x65\x61\x64\x44\x65\x76\x69\x63\x65\x4e\x61\x6d\x65");za5e68b432b();
z82951ffa8c->zd0d1398630(zf15e490884);}void z11671f1e0a::ze5acd8e45b(bool 
z2a654b4732){poco_information_f1(LOGGER(),
"\x77\x72\x69\x74\x65\x50\x72\x6f\x67\x72\x61\x6d\x6d\x69\x6e\x67\x4d\x6f\x64\x65\x20\x28\x25\x62\x29"
,z2a654b4732);za5e68b432b();z82951ffa8c->ze5acd8e45b(z2a654b4732);}bool 
z11671f1e0a::ze59351aa9c(){poco_information(LOGGER(),
"\x72\x65\x61\x64\x50\x72\x6f\x67\x72\x61\x6d\x6d\x69\x6e\x67\x4d\x6f\x64\x65");
za5e68b432b();return z82951ffa8c->ze59351aa9c();}void z11671f1e0a::z563fc10557(
unsigned short zb9dc9070a1){poco_information_f1(LOGGER(),
"\x77\x72\x69\x74\x65\x4d\x61\x6e\x75\x66\x61\x63\x74\x75\x72\x65\x72\x49\x64\x20\x28\x30\x78\x25\x58\x29"
,static_cast<unsigned int>(zb9dc9070a1));za5e68b432b();z82951ffa8c->z563fc10557(
zb9dc9070a1);}unsigned short z11671f1e0a::z7e6620eb94(){poco_information(LOGGER(
),"\x72\x65\x61\x64\x4d\x61\x6e\x75\x66\x61\x63\x74\x75\x72\x65\x72\x49\x64");
za5e68b432b();return z82951ffa8c->z7e6620eb94();}unsigned short z11671f1e0a::
z2afe3965f8(){poco_information(LOGGER(),
"\x72\x65\x61\x64\x4d\x61\x78\x41\x70\x64\x75\x4c\x65\x6e\x67\x74\x68");
za5e68b432b();return z82951ffa8c->z2afe3965f8();}void z11671f1e0a::za5e68b432b()
{
#if (0x625+7369-0x22ee)
if(!zcdc6474106.isOpen()){throw PortOpenException();}
#endif
if(!z82951ffa8c){throw ProtocolNotSetException(
"\x53\x65\x74\x20\x61\x20\x76\x61\x6c\x69\x64\x20\x70\x72\x6f\x74\x6f\x63\x6f\x6c\x2c\x20\x62\x65\x66\x6f\x72\x65\x20\x63\x61\x6c\x6c\x20\x74\x68\x65\x20\x6c\x6f\x63\x61\x6c\x20\x64\x65\x76\x69\x63\x65\x20\x6d\x61\x6e\x61\x67\x65\x72\x2e"
);}}
