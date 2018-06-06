
#include "pch/kdrive_pch.h"
#include "kdrive/access/baos/BaosKnxPort.h"
#include "kdrive/access/core/API.h"
#include "kdrive/access/core/details/TelegramWaitPolicy.h"
#include "kdrive/access/core/KnxPacket.h"
#include "kdrive/access/usb/UsbPortEnumerator.h"
#include "kdrive/connector/Wait.h"
#include "kdrive/knx/defines/KnxLayer.h"
#include "kdrive/knx/defines/KnxProperty.h"
#include "kdrive/knx/telegrams/cemi/MProp.h"
using namespace kdrive::access;using namespace kdrive::connector;using namespace
 kdrive::knx::cemi;using namespace kdrive::knx;using kdrive::utility::
PropertyCollection;namespace{void zdd2e046b74(PropertyCollection&z56fa974c3c){
z56fa974c3c.setProperty(zfa6c8ef87f::PortType,zfa6c8ef87f::ConnectorTypeLabel);}
bool zaff085ae22(Connector&connector,unsigned long timeout=(0x1171+3700-0x1bfd))
{try{z8d3fcb5f7e z4421b0f338;zd630f842fc policy(connector,z4421b0f338);
waitPacketWithPolicy<KnxPacket>(policy,timeout);if(z4421b0f338.z254dc6b154()!=""
){return false;}return true;}catch(Poco::TimeoutException&){return false;}catch(
Poco::Exception){return true;}}bool z49a06fbefa(zfa6c8ef87f&port){if(port.
z01a2f5d4b7()!=za498009d76::z1746fd28fd){return false;}
ScopedQueueConnectorRxQueue zc912cc464d(port);ze50c6f6ca0 zb69c3b48e1;
zb69c3b48e1.z48a824e00c(z3b8af6cac1::zcd7b7b4ad1);zb69c3b48e1.zdd57f327fa(
(0x491+3249-0x1141));zb69c3b48e1.zf46c3b49cc((0x26a3+234-0x26c4));zb69c3b48e1.
z55f5c7ccbb((0x1ba+3915-0x1104));zb69c3b48e1.z79bd7d3c67((0x35+8426-0x211e));
KnxPacket::Ptr zfd29354025=std::make_shared<KnxPacket>(zb69c3b48e1.size());
zb69c3b48e1.write(zfd29354025->getBuffer());port.send(zfd29354025);bool 
z8b0902d5f1=zaff085ae22(zc912cc464d);return z8b0902d5f1;}}const std::string 
zfa6c8ef87f::ConnectorTypeLabel=
"\x6b\x6e\x78\x2e\x62\x61\x6f\x73\x2e\x75\x73\x62";const std::string zfa6c8ef87f
::zd8f975f428=
"\x6b\x6e\x78\x2e\x69\x73\x5f\x62\x61\x6f\x73\x5f\x73\x75\x70\x70\x6f\x72\x74\x65\x64"
;zfa6c8ef87f::zfa6c8ef87f():zd389c62dfd(){zdd2e046b74(*this);}bool zfa6c8ef87f::
z8b0902d5f1(){if(isEmpty(zd8f975f428)){setProperty(zd8f975f428,z49a06fbefa(*this
));}return getProperty(zd8f975f428);}void zfa6c8ef87f::resetPropertiesImpl(){
zd389c62dfd::resetPropertiesImpl();zdd2e046b74(*this);}void zfa6c8ef87f::
enumerateImpl(Ports&zbffeaedfd5){zfa39e8b445::enumerate(zfa6c8ef87f::
ConnectorTypeLabel,zbffeaedfd5);}unsigned int zfa6c8ef87f::z07a1de2360(){
unsigned int z7ecdefe519=zd389c62dfd::z07a1de2360();if(z8b0902d5f1()){
z7ecdefe519|=zba36969226::zf0c17de15e;}return z7ecdefe519;}
