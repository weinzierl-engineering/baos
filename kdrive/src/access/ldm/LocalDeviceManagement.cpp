
#include "pch/kdrive_pch.h"
#include "kdrive/access/core/KnxPort.h"
#include "kdrive/access/core/Exception.h"
#include "kdrive/access/ldm/LocalDeviceManagement.h"
#include "kdrive/access/core/KnxPacket.h"
#include "kdrive/connector/Wait.h"
#include <algorithm>
using namespace kdrive::access;using kdrive::connector::waitPacket;zec7fc1647d::
zec7fc1647d(zea2d083c85&port):zcdc6474106(port){}zec7fc1647d::~zec7fc1647d(){}
void zec7fc1647d::restart(){}unsigned short zec7fc1647d::z2afe3965f8(){return 
zea2d083c85::z81eda64581;}zea2d083c85&zec7fc1647d::getPort(){return zcdc6474106;
}const zea2d083c85&zec7fc1647d::getPort()const{return zcdc6474106;}void 
zec7fc1647d::za4528c2f93(unsigned int z1166f2fdb4,const std::string&msg){if(
z6f5601a8cf()!=z1166f2fdb4){throw WriteLocalDeviceMgmtException(msg);}}void 
zec7fc1647d::z75eed006b0(unsigned int z83744e1e92,const std::string&msg){if(
zf670e5347d()!=z83744e1e92){throw WriteLocalDeviceMgmtException(msg);}}void 
zec7fc1647d::z85480faf6f(unsigned int zf92894300e,const std::string&msg){if(
zfa42f5b322()!=zf92894300e){throw WriteLocalDeviceMgmtException(msg);}}void 
zec7fc1647d::zd02eaa9824(const std::vector<unsigned char>&zf92894300e,const std
::string&msg){std::vector<unsigned char>da;z875dcf85de(da);if(da!=zf92894300e){
throw WriteLocalDeviceMgmtException(msg);}}void zec7fc1647d::z501eae5473(const 
std::vector<unsigned char>&zd311e7ca26,const std::string&msg){std::vector<
unsigned char>z97d3478633;z8039b7bd80(z97d3478633);if(z97d3478633!=zd311e7ca26){
throw WriteLocalDeviceMgmtException(msg);}}void zec7fc1647d::z99dab55337(
unsigned int zfd606f58be,const std::string&msg){if(za4544ba4dc()!=zfd606f58be){
throw WriteLocalDeviceMgmtException(msg);}}void zec7fc1647d::za6acd56ff2(
unsigned int z83744e1e92,const std::string&msg){if(z587dd78f85()!=z83744e1e92){
throw WriteLocalDeviceMgmtException(msg);}}void zec7fc1647d::z0269f1e89b(const 
std::vector<unsigned short>&addresses,const std::string&msg){std::vector<
unsigned short>z98b719801c;za8754b21ac(z98b719801c);if(z98b719801c!=addresses){
throw WriteLocalDeviceMgmtException(msg);}}void zec7fc1647d::z11e15a5722(
unsigned int ze2fcb9ca3a,const std::string&msg){if(zbab06955e5()!=ze2fcb9ca3a){
throw WriteLocalDeviceMgmtException(msg);}}void zec7fc1647d::z7475b3f872(const 
std::string&zf15e490884,const std::string&msg){std::string z07f4508ba9;
zd0d1398630(z07f4508ba9);if(z07f4508ba9!=zf15e490884){throw 
WriteLocalDeviceMgmtException(msg);}}void zec7fc1647d::z0f3b34e3a9(unsigned 
short zb9dc9070a1,const std::string&msg){if(z7e6620eb94()!=zb9dc9070a1){throw 
WriteLocalDeviceMgmtException(msg);}}KnxPacket::Ptr zec7fc1647d::zbe3acf8982(
unsigned int timeout){KnxPacket::Ptr packet;try{packet=waitPacket<KnxPacket>(
zcdc6474106,timeout);}catch(...){}return packet;}KnxPacket::Ptr zec7fc1647d::
zbe3acf8982(const unsigned char*buffer,unsigned int z3ba388a942,unsigned int 
offset,unsigned int timeout){Poco::Timestamp timestamp;Poco::Timestamp::TimeDiff
 z6485c7d3af=timeout*(0x12d4+5536-0x248c);bool elapsed=false;KnxPacket::Ptr 
packet;while(!elapsed){packet=zbe3acf8982(timeout);if(packet){const KnxPacket::
Buffer&z852de6af8a=packet->getBuffer();if(offset+z3ba388a942<=z852de6af8a.size()
){KnxPacket::Buffer::const_iterator begin=z852de6af8a.begin()+offset;KnxPacket::
Buffer::const_iterator end=begin+z3ba388a942;if(std::equal(begin,end,buffer)){
return packet;}}}elapsed=timestamp.isElapsed(z6485c7d3af);if(!elapsed){const 
unsigned long z662146e9f6=static_cast<unsigned long>(timestamp.elapsed())/
(0xe68+5277-0x1f1d);if(timeout<z662146e9f6){elapsed=true;}else{timeout-=
z662146e9f6;}}}throw TelegramTimeoutException();}
