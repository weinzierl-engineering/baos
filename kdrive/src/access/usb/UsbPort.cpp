
#include "pch/kdrive_pch.h"
#include "kdrive/access/usb/UsbPort.h"
#include "kdrive/access/usb/UsbPortEnumerator.h"
#include "kdrive/access/core/KnxPacket.h"
#include "kdrive/access/core/TransportPacket.h"
#include "kdrive/access/core/API.h"
#include "kdrive/access/core/Events.h"
#include "kdrive/access/core/Exception.h"
#include "kdrive/connector/Wait.h"
#include "kdrive/connector/ConnectorNotificationHandler.h"
#include "kdrive/knx/core/AddressTranslator.h"
#include "kdrive/knx/defines/KnxLayer.h"
#include "kdrive/knx/defines/KnxProperty.h"
#include "kdrive/knx/core/ByteStream.h"
#include "kdrive/knx/defines/MaskVersion.h"
#include "kdrive/frame/usb/Headers.h"
#include "kdrive/io/usbhid/UsbDriver.h"
#include "kdrive/utility/Logger.h"
#include "kdrive/utility/LoggerFormatter.h"
#include <Poco/Exception.h>
#include <Poco/Format.h>
#include <Poco/Logger.h>
#include <Poco/Bugcheck.h>
#include <vector>
#include <algorithm>
#include <array>
using namespace kdrive::connector;using namespace kdrive::access;using namespace
 kdrive::knx;using namespace kdrive::frame;using kdrive::connector::Packet;using
 kdrive::utility::LoggerFormatter;using kdrive::utility::PropertyCollection;
using Poco::Exception;using Poco::Dynamic::Var;using Poco::format;using Poco::
PropertyNotSupportedException;CLASS_LOGGER(
"\x6b\x64\x72\x69\x76\x65\x2e\x61\x63\x63\x65\x73\x73\x2e\x55\x73\x62\x50\x6f\x72\x74"
)namespace{class DeviceFeaturePacket:public TransportPacket{public:typedef std::
shared_ptr<DeviceFeaturePacket>Ptr;DeviceFeaturePacket(const std::vector<
unsigned char>&buffer):TransportPacket(buffer),zf364646805((0x1150+2615-0x1b87))
{setProtocol("\x75\x73\x62\x5f\x66\x65\x61\x74\x75\x72\x65");}virtual~
DeviceFeaturePacket(){setProtocol("\x75\x73\x62\x5f\x66\x65\x61\x74\x75\x72\x65"
);}void zcb58dc0baf(unsigned char z057b94c01d){zf364646805=z057b94c01d;}unsigned
 char zd982c014bf()const{return zf364646805;}unsigned char z13a39adf84()const{
const Buffer&buffer=getBuffer();return buffer.at((0x490+1812-0xba4));}std::
vector<unsigned char>z286f9d00ee()const{std::vector<unsigned char>v;const Buffer
&buffer=getBuffer();if(buffer.size()>(0x2e2+954-0x69b)){v.assign(buffer.begin()+
(0xf2+8885-0x23a6),buffer.end());}return v;}private:unsigned char zf364646805;};
void zdd2e046b74(kdrive::utility::PropertyCollection&z56fa974c3c){using 
PropertyWriteableMode=zd389c62dfd::PropertyWriteableMode;z56fa974c3c.setProperty
(zd389c62dfd::PortType,zd389c62dfd::ConnectorTypeLabel);z56fa974c3c.setProperty(
zd389c62dfd::za498009d76,static_cast<unsigned int>(za498009d76::Unknown));
z56fa974c3c.setProperty(zd389c62dfd::z9884ee4d6b,static_cast<unsigned int>(
zba36969226::Unknown));z56fa974c3c.setProperty(zd389c62dfd::z6f8f16a878,
(0x1164+504-0x135c));}void zb3aed4b1d9(zd389c62dfd&port){try{port.zbe00e8c303();
}catch(Exception&e){poco_warning_f1(LOGGER(),
"\x45\x72\x72\x6f\x72\x20\x77\x68\x69\x6c\x65\x20\x72\x65\x61\x64\x69\x6e\x67\x20\x74\x68\x65\x20\x69\x6e\x64\x69\x76\x69\x64\x75\x61\x6c\x20\x61\x64\x64\x72\x65\x73\x73\x3a\x20"
,e.displayText());}}std::string zd0cb7726a7(zd389c62dfd&port){try{const unsigned
 int address=port.zbe00e8c303();return zd50e757f97::z83886ba842(address);}catch(
Exception&e){poco_warning_f1(LOGGER(),
"\x45\x72\x72\x6f\x72\x20\x77\x68\x69\x6c\x65\x20\x72\x65\x61\x64\x69\x6e\x67\x20\x74\x68\x65\x20\x69\x6e\x64\x69\x76\x69\x64\x75\x61\x6c\x20\x61\x64\x64\x72\x65\x73\x73\x3a\x20"
,e.displayText());return"";}}unsigned int z1eb0e6e133(unsigned int z7827eb5079){
switch(z7827eb5079){case ze127e0a511::Medium::z1f5ef68b4f:return zb5ec3c9a78::
za0f13fc1a3;case ze127e0a511::Medium::z6cb5bb14f9:return zb5ec3c9a78::
z1bc67624ce;case ze127e0a511::Medium::z575b70b0f4:return zb5ec3c9a78::
z61c8b3cf3a;default:return zb5ec3c9a78::zad8318dff6;}return(0x66b+7503-0x23ba);}
template<class T>typename T::Ptr z9ff186a85c(std::vector<Packet::Ptr>&
z680f35b9d8){std::vector<unsigned char>z4b3281b3a0;for(Packet::Ptr packet:
z680f35b9d8){Packet::Buffer&buffer=packet->getBuffer();usb::z6176029ec5 
z6d61b7f4d3(&buffer.at((0x992+2114-0x11d4)),buffer.size(),false);const int 
z60e99e4156=z6d61b7f4d3.zf1e6344a84();if(z4b3281b3a0.empty()){usb::zadbe67dd03 
zbd3df6d0b8(&buffer.at((0x2229+1097-0x2672)),buffer.size(),false);const int 
zdab55b0495=z60e99e4156-usb::Frame::z81d39de932;kdrive::frame::Buffer b=
zbd3df6d0b8.z76221cc199();z4b3281b3a0.insert(z4b3281b3a0.end(),b.begin(),b.begin
()+zdab55b0495);}else{usb::z48f475a642 z844324262e(&buffer.at(
(0x442+3906-0x1384)),buffer.size(),false);kdrive::frame::Buffer b=z844324262e.
z76221cc199();z4b3281b3a0.insert(z4b3281b3a0.end(),b.begin(),b.begin()+
z60e99e4156);}}typename T::Ptr packet(std::make_shared<T>(z4b3281b3a0));return 
packet;}class UsbPortTransportDriver:public zb7e35db1da{public:
UsbPortTransportDriver():zb7e35db1da(){}virtual~UsbPortTransportDriver(){}void 
open(int index)override{z09767b93a3.open(index);startRxThread();}void close()
override{stopRxThread();z09767b93a3.close();}unsigned int getVendorId()const 
override{return z09767b93a3.getVendorId();}unsigned int getProductId()const 
override{return z09767b93a3.getProductId();}std::string getUsbManufacturerString
()const override{return z09767b93a3.getUsbManufacturerString();}std::string 
getUsbProductString()const override{return z09767b93a3.getUsbProductString();}
std::string getUsbSerialNumberString()const override{return z09767b93a3.
getUsbSerialNumberString();}private:void txImpl(Packet::Ptr packet)override{try{
TransportPacket::Ptr zfa61376f49=TransportPacket::convert(packet,false);if(
zfa61376f49){const Packet::Buffer&z425aa5773c=zfa61376f49->getBuffer();
z09767b93a3.send(&z425aa5773c.at((0x52d+1151-0x9ac)),z425aa5773c.size());routeTx
(zfa61376f49);}}catch(Exception&exception){poco_warning(LOGGER(),exception.
displayText());throw;}}void rxImpl()override{try{const int length=z09767b93a3.
receive(&z4ddc9f00e9.at((0xa88+2040-0x1280)),z4ddc9f00e9.size());if(length>
(0x729+3219-0x13bb)){z0d01069fec(&z4ddc9f00e9.at((0x196d+779-0x1c78)),length);}}
catch(Exception&exception){poco_error_f1(LOGGER(),
"\x45\x72\x72\x6f\x72\x20\x69\x6e\x20\x72\x78\x49\x6d\x70\x6c\x2c\x20\x25\x73",
exception.displayText());routeEvent(z11d7f1cf7b::Terminated);throw;}}private:
kdrive::io::usb::UsbDriver z09767b93a3;std::array<unsigned char,
(0x94d+5803-0x1fb8)>z4ddc9f00e9;};}const std::string zd389c62dfd::
ConnectorTypeLabel="\x6b\x6e\x78\x2e\x75\x73\x62";const std::string zd389c62dfd
::z6f8f16a878=
"\x6b\x6e\x78\x2e\x75\x73\x62\x2e\x69\x6e\x64\x65\x78\x2e\x69\x6e\x74\x65\x72\x6e\x61\x6c"
;const std::string zd389c62dfd::zf399913164=
"\x6b\x6e\x78\x2e\x75\x73\x62\x2e\x76\x65\x6e\x64\x6f\x72\x5f\x69\x64";const std
::string zd389c62dfd::z6006021112=
"\x6b\x6e\x78\x2e\x75\x73\x62\x2e\x70\x72\x6f\x64\x75\x63\x74\x5f\x69\x64";const
 std::string zd389c62dfd::za3db08fb48=
"\x6b\x6e\x78\x2e\x75\x73\x62\x2e\x6d\x61\x6e\x75\x66\x61\x63\x74\x75\x72\x65\x72\x5f\x73\x74\x72\x69\x6e\x67"
;const std::string zd389c62dfd::z987de680b2=
"\x6b\x6e\x78\x2e\x75\x73\x62\x2e\x70\x72\x6f\x64\x75\x63\x74\x5f\x73\x74\x72\x69\x6e\x67"
;const std::string zd389c62dfd::z9d956080e6=
"\x6b\x6e\x78\x2e\x75\x73\x62\x2e\x73\x65\x72\x69\x61\x6c\x5f\x6e\x75\x6d\x62\x65\x72\x5f\x73\x74\x72\x69\x6e\x67"
;zd389c62dfd::zd389c62dfd():zea2d083c85(){zdd2e046b74(*this);}zd389c62dfd::~
zd389c62dfd(){try{close();}catch(...){}}void zd389c62dfd::open(int index){
setProperty(z6f8f16a878,index);zea2d083c85::open();}std::string zd389c62dfd::
getDescription(){const unsigned int z0db62254bc=getUsbIndex()+
(0x94c+4703-0x1baa);if(hasPropertyKey(z13c23c3849)&&hasPropertyKey(z2a66eed75d))
{const std::string address=zd0cb7726a7(*this);return format(
"\x55\x53\x42\x25\x75\x20\x28\x25\x73\x29\x20\x25\x73",z0db62254bc,zc3136dcdfa()
,address);}else{return format("\x55\x53\x42\x25\x75",z0db62254bc);}}unsigned int
 zd389c62dfd::getUsbIndex()const{return getProperty<unsigned int>(z6f8f16a878);}
unsigned int zd389c62dfd::getUsbVendorId(){if(isEmpty(zf399913164)){setProperty(
zf399913164,z40c251ad9c().getVendorId());}return getProperty<unsigned int>(
zf399913164);}unsigned int zd389c62dfd::getUsbProductId(){if(isEmpty(z6006021112
)){setProperty(z6006021112,z40c251ad9c().getProductId());}return getProperty<
unsigned int>(z6006021112);}std::string zd389c62dfd::getUsbManufacturerString(){
if(isEmpty(za3db08fb48)){setProperty(za3db08fb48,z40c251ad9c().
getUsbManufacturerString());}return getProperty<std::string>(za3db08fb48);}std::
string zd389c62dfd::getUsbProductString(){if(isEmpty(z987de680b2)){setProperty(
z987de680b2,z40c251ad9c().getUsbProductString());}return getProperty<std::string
>(z987de680b2);}std::string zd389c62dfd::getUsbSerialNumberString(){if(isEmpty(
z9d956080e6)){setProperty(z9d956080e6,z40c251ad9c().getUsbSerialNumberString());
}return getProperty<std::string>(z9d956080e6);}void zd389c62dfd::z7466c70591(std
::shared_ptr<zb7e35db1da>z25df9e99c8){if(z94bd7d8eab){z240bf3efcd.disconnect();
zdf6a625f58.disconnect();ze466aac0a0.disconnect();}z94bd7d8eab=z25df9e99c8;
zb7e35db1da::PacketSignalRx&z8f45d7a7ae=z94bd7d8eab->getPacketSignalRx();
z240bf3efcd=z8f45d7a7ae.connect(std::bind(&zd389c62dfd::z416530b361,this,std::
placeholders::_1));zb7e35db1da::PacketSignalTx&zaa78368435=z94bd7d8eab->
getPacketSignalTx();zdf6a625f58=zaa78368435.connect(std::bind(&zd389c62dfd::
zb76e5b3ae9,this,std::placeholders::_1));zb7e35db1da::EventSignal&e=z94bd7d8eab
->getEventSignal();ze466aac0a0=e.connect(std::bind(&zd389c62dfd::onEvent,this,
std::placeholders::_1));z94bd7d8eab->enableSignals(true);}zb7e35db1da&
zd389c62dfd::z40c251ad9c(){poco_check_ptr(z94bd7d8eab);return*z94bd7d8eab;}void 
zd389c62dfd::zfd9e3ed405(std::vector<Packet::Ptr>&z680f35b9d8,const Packet::
Buffer&zb4a7952e11,int z6babad3bc5,int z8bf837ad78){if(zb4a7952e11.size()<=usb::
zadbe67dd03::zf08419cb5d){usb::zadbe67dd03 z6d61b7f4d3;z6d61b7f4d3.z12aeb820c7(
(0xac6+4991-0x1e44));z6d61b7f4d3.z5058692388(usb::Frame::z36ea2f3727);
z6d61b7f4d3.z01729c5314(usb::Frame::z81d39de932+zb4a7952e11.size());z6d61b7f4d3.
zc30ad49c26(usb::Frame::zc32c22646b);z6d61b7f4d3.z0c49370f86(usb::Frame::
z81d39de932);z6d61b7f4d3.zb9b72b8dfa(zb4a7952e11.size());z6d61b7f4d3.zbbdd7e7e66
(z6babad3bc5);z6d61b7f4d3.z22b71056e4(z8bf837ad78);z6d61b7f4d3.z38cd644399(usb::
Frame::z8b0e386d95);kdrive::frame::Buffer z7598c9d128=z6d61b7f4d3.z76221cc199();
std::copy(zb4a7952e11.begin(),zb4a7952e11.end(),z7598c9d128.zffce7603f8(
(0x847+2566-0x124d),zb4a7952e11.size()));TransportPacket::Ptr zfa61376f49=std::
make_shared<TransportPacket>(z6d61b7f4d3.zbaa3b4a6ca());z680f35b9d8.push_back(
zfa61376f49);}else{const int za64264f482=zb4a7952e11.size()-usb::zadbe67dd03::
zf08419cb5d;const bool zfd21aca5fc=za64264f482%usb::z48f475a642::zf08419cb5d?
true:false;const int zd2803a22d9=(0xb75+4913-0x1ea5)+(za64264f482/usb::
z48f475a642::zf08419cb5d)+(zfd21aca5fc?(0xce8+2657-0x1748):(0x1d1+3188-0xe45));
int offset=(0x68c+6667-0x2097);int length=usb::zadbe67dd03::zf08419cb5d;Packet::
Buffer::const_iterator iter;Packet::Buffer::const_iterator zd7e8ce6001;for(int 
index=(0x70c+2155-0xf77);index<zd2803a22d9;++index){usb::z6176029ec5 z6d61b7f4d3
;z6d61b7f4d3.z12aeb820c7(index+(0x4d2+3333-0x11d6));z6d61b7f4d3.z5058692388(!
index?usb::Frame::zffc1a949ed:((index+(0x17a1+3083-0x23ab)<zd2803a22d9)?usb::
Frame::z35880dd8af:usb::Frame::zf23ff3b732));iter=zb4a7952e11.begin()+offset;
zd7e8ce6001=iter+length;if(!offset){z6d61b7f4d3.z01729c5314(usb::Frame::
z81d39de932+length);usb::zadbe67dd03 zbd3df6d0b8(z6d61b7f4d3.z8d79a69692(),
z6d61b7f4d3.getSize(),false);zbd3df6d0b8.zc30ad49c26(usb::Frame::zc32c22646b);
zbd3df6d0b8.z0c49370f86(usb::Frame::z81d39de932);zbd3df6d0b8.zb9b72b8dfa(
zb4a7952e11.size());zbd3df6d0b8.zbbdd7e7e66(z6babad3bc5);zbd3df6d0b8.z22b71056e4
(z8bf837ad78);zbd3df6d0b8.z38cd644399(usb::Frame::z8b0e386d95);kdrive::frame::
Buffer z7598c9d128=zbd3df6d0b8.z76221cc199();std::copy(iter,zd7e8ce6001,
z7598c9d128.zffce7603f8((0x11ea+3580-0x1fe6),length));}else{z6d61b7f4d3.
z01729c5314(length);usb::z48f475a642 z844324262e(z6d61b7f4d3.z8d79a69692(),
z6d61b7f4d3.getSize(),false);kdrive::frame::Buffer z7598c9d128=z844324262e.
z76221cc199();std::copy(iter,zd7e8ce6001,z7598c9d128.zffce7603f8(
(0xb4d+4964-0x1eb1),length));}TransportPacket::Ptr zfa61376f49=std::make_shared<
TransportPacket>(z6d61b7f4d3.zbaa3b4a6ca());z680f35b9d8.push_back(zfa61376f49);
offset+=length;length=std::min<int>(usb::z48f475a642::zf08419cb5d,zb4a7952e11.
size()-offset);}}}void zd389c62dfd::z08c13130cf(){std::vector<unsigned char>data
;z717605cbda(z16b7bd8eb2,data);z387eb17426(z16b7bd8eb2,data);}void zd389c62dfd::
enumerateImpl(Ports&zbffeaedfd5){zfa39e8b445::enumerate(zbffeaedfd5);}void 
zd389c62dfd::openImpl(){if(!z94bd7d8eab){std::shared_ptr<zb7e35db1da>z25df9e99c8
=std::make_shared<UsbPortTransportDriver>();z7466c70591(z25df9e99c8);}try{
z94bd7d8eab->open(getProperty(z6f8f16a878));}catch(Exception&exception){
closeImpl();poco_error_f1(LOGGER(),
"\x45\x72\x72\x6f\x72\x20\x69\x6e\x20\x6f\x70\x65\x6e\x49\x6d\x70\x6c\x28\x29\x3a\x20\x25\x73"
,exception.displayText());raiseError(exception);}setProperty(z5b2ecda528,
static_cast<unsigned int>(zea2d083c85::z4e34b5d0f7::Unknown));removeProperty(
z13c23c3849);zda5b0c66b5();zea2d083c85::openImpl();zb3aed4b1d9(*this);}void 
zd389c62dfd::closeImpl(){try{if(z01a2f5d4b7()==za498009d76::z1746fd28fd){try{
zc7087b3e64().z766e2388b4(zba36969226::None);}catch(
WriteLocalDeviceMgmtException&){}}else{z81289a39cd(za498009d76::None);}}catch(
Exception&e){poco_warning_f1(LOGGER(),
"\x57\x61\x72\x6e\x69\x6e\x67\x20\x69\x67\x6e\x6f\x72\x65\x20\x65\x72\x72\x6f\x72\x20\x77\x68\x69\x6c\x65\x20\x63\x6c\x6f\x73\x69\x6e\x67\x2c\x20\x25\x73"
,e.displayText());}poco_check_ptr(z94bd7d8eab);z240bf3efcd.disconnect();
zdf6a625f58.disconnect();ze466aac0a0.disconnect();z94bd7d8eab->close();
z94bd7d8eab.reset();}bool zd389c62dfd::isOpenImpl()const{return z94bd7d8eab?true
:false;}void zd389c62dfd::resetPropertiesImpl(){zea2d083c85::resetPropertiesImpl
();zdd2e046b74(*this);}void zd389c62dfd::txImpl(Packet::Ptr packet){try{
KnxPacket::Ptr zfd29354025=KnxPacket::convert(packet,false);if(zfd29354025){
ScopedQueueConnectorRxQueue connector(*this);zcd4f7f46dd(zfd29354025);
za117cd55de(connector,zfd29354025);}}catch(Exception&exception){poco_error_f1(
LOGGER(),
"\x45\x72\x72\x6f\x72\x20\x69\x6e\x20\x74\x78\x49\x6d\x70\x6c\x2c\x20\x25\x73",
exception.displayText());raiseError(exception);}}unsigned int zd389c62dfd::
z29f4d6d6a3(){try{std::vector<unsigned char>data;z717605cbda(z6f756d1962,data);
const unsigned short zb9dc9070a1=ze378c24725<unsigned short,(0x3a2+8405-0x2475)>
(data);return zb9dc9070a1;}catch(Exception&e){std::string str=
"\x52\x65\x61\x64\x20\x6d\x61\x6e\x75\x66\x61\x63\x74\x75\x72\x65\x72\x20\x69\x64\x20\x76\x69\x61\x20\x27\x44\x65\x76\x69\x63\x65\x20\x46\x65\x61\x74\x75\x72\x65\x20\x47\x65\x74\x27\x20\x66\x61\x69\x6c\x65\x64\x3a\x20"
+e.displayText();str+=
"\x3b\x20\x2d\x3e\x20\x54\x72\x79\x20\x76\x69\x61\x20\x4c\x6f\x63\x61\x6c\x44\x65\x76\x69\x63\x65\x4d\x61\x6e\x61\x67\x65\x72"
;poco_information(LOGGER(),str);}return zea2d083c85::z29f4d6d6a3();}unsigned int
 zd389c62dfd::zc1ee43d1f6(){poco_information(LOGGER(),
"\x72\x65\x61\x64\x53\x75\x70\x70\x6f\x72\x74\x65\x64\x50\x72\x6f\x74\x6f\x63\x6f\x6c\x73\x49\x6d\x70\x6c"
);int z10d5ceb1c6=(0x16a5+2926-0x2213);unsigned int data=(0xa57+3269-0x171c);
bool finished=false;while(!finished){data=zeb85ef63a7();if(data){finished=true;}
else if(++z10d5ceb1c6>zb32e12ceee){poco_error(LOGGER(),
"\x72\x63\x76\x64\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x70\x72\x6f\x74\x6f\x63\x6f\x6c\x73\x20\x69\x73\x20\x30"
);finished=true;}else{poco_warning(LOGGER(),
"\x57\x61\x72\x6e\x69\x6e\x67\x21\x20\x52\x63\x76\x64\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x70\x72\x6f\x74\x6f\x63\x6f\x6c\x73\x20\x69\x73\x20\x30\x2e\x20\x54\x72\x79\x20\x69\x74\x20\x61\x67\x61\x69\x6e\x2e"
"\x28\x52\x65\x61\x73\x6f\x6e\x3a\x20\x4e\x6f\x20\x62\x75\x73\x20\x63\x6f\x6e\x6e\x65\x63\x74\x69\x6f\x6e\x20\x6f\x72\x20\x64\x65\x76\x69\x63\x65\x20\x65\x72\x72\x6f\x72\x29"
);}}unsigned int z45fb7ed6f5=z773f9d77ef(data);if(zea2d083c85::zdf6fe1862a(
z45fb7ed6f5,za498009d76::z26a323d5e5)||zea2d083c85::zdf6fe1862a(z45fb7ed6f5,
za498009d76::zb100d7cac0)){z45fb7ed6f5|=za498009d76::None;}return z45fb7ed6f5;}
void zd389c62dfd::z81289a39cd(unsigned int z5ecb2cdb3d){const unsigned char 
z2bb9fa41ff=z0e29512e8d(z5ecb2cdb3d);std::vector<unsigned char>data;data.
push_back(z589263083f);data.push_back(z2bb9fa41ff);z1809dde2ad(data);}unsigned 
int zd389c62dfd::z93d917156c(){std::vector<unsigned char>data;z717605cbda(
z589263083f,data);const unsigned char z12333f6e4e=ze378c24725<unsigned char,
(0x831+1753-0xf09)>(data);return zb98b4a330a(z12333f6e4e);}unsigned int 
zd389c62dfd::z07a1de2360(){unsigned int z7b2ce21a17=zba36969226::Unknown;const 
unsigned int zd2b01bb0a4=z01a2f5d4b7();if(zd2b01bb0a4==za498009d76::z26a323d5e5)
{z7b2ce21a17=zba36969226::Link|zba36969226::z1340d1c626;}else if(zd2b01bb0a4==
za498009d76::z1746fd28fd){try{z7b2ce21a17=zc7087b3e64().z2e0dcb1a8b();}catch(
Exception&e){z7b2ce21a17=zba36969226::Link|zba36969226::z1340d1c626|zba36969226
::Raw;std::string str=
"\x52\x65\x61\x64\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x6c\x61\x79\x65\x72\x73\x20\x28\x6f\x70\x74\x69\x6f\x6e\x61\x6c\x20\x70\x72\x6f\x70\x65\x72\x74\x79\x29\x20\x76\x69\x61\x20\x27\x4c\x6f\x63\x61\x6c\x44\x65\x76\x69\x63\x65\x4d\x61\x6e\x61\x67\x65\x72\x27\x20\x66\x61\x69\x6c\x65\x64\x3a\x20"
+e.displayText();str+=
"\x20\x75\x73\x65\x20\x73\x74\x61\x6e\x64\x61\x72\x64\x20\x76\x61\x6c\x75\x65\x73\x20\x28\x4c\x69\x6e\x6b\x4c\x61\x79\x65\x72\x2c\x20\x42\x75\x73\x6d\x6f\x6e\x20\x61\x6e\x64\x20\x52\x61\x77\x29"
;poco_debug(LOGGER(),str);}}return z7b2ce21a17;}unsigned int zd389c62dfd::
z4b4d92d5e8(){try{poco_information(LOGGER(),
"\x55\x73\x62\x50\x6f\x72\x74\x3a\x3a\x72\x65\x61\x64\x4d\x61\x73\x6b\x56\x65\x72\x73\x69\x6f\x6e\x49\x6d\x70\x6c\x28\x2e\x29"
);std::vector<unsigned char>data;z717605cbda(z8a10a60f59,data);const unsigned 
short z65fc26404c=ze378c24725<unsigned short,(0x2201+407-0x2396)>(data);return 
z65fc26404c;}catch(Exception&e){std::string str=
"\x52\x65\x61\x64\x20\x6d\x61\x73\x6b\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x76\x69\x61\x20\x27\x44\x65\x76\x69\x63\x65\x20\x46\x65\x61\x74\x75\x72\x65\x20\x47\x65\x74\x27\x20\x66\x61\x69\x6c\x65\x64\x3a\x20"
+e.displayText();str+=
"\x3b\x20\x2d\x3e\x20\x57\x6f\x72\x6b\x61\x72\x6f\x75\x6e\x64\x2c\x20\x74\x72\x79\x20\x76\x69\x61\x20\x4c\x6f\x63\x61\x6c\x44\x65\x76\x69\x63\x65\x4d\x61\x6e\x61\x67\x65\x72"
;poco_warning(LOGGER(),str);}try{return zc7087b3e64().z51177f5ce9();}catch(
Exception&e){const std::string str=
"\x52\x65\x61\x64\x20\x6d\x61\x73\x6b\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x76\x69\x61\x20\x27\x4c\x6f\x63\x61\x6c\x44\x65\x76\x69\x63\x65\x4d\x61\x6e\x61\x67\x65\x72\x27\x20\x66\x61\x69\x6c\x65\x64\x3a\x20"
+e.displayText();poco_warning(LOGGER(),str);if(z01a2f5d4b7()==za498009d76::
z1746fd28fd){const unsigned int z7827eb5079=getProperty(z2a66eed75d,
(0xa03+6814-0x24a1));const unsigned int z65fc26404c=z1eb0e6e133(z7827eb5079);if(
z65fc26404c!=zb5ec3c9a78::zad8318dff6){poco_warning_f1(LOGGER(),
"\x57\x6f\x72\x6b\x61\x72\x6f\x75\x6e\x64\x2c\x20\x61\x73\x73\x75\x6d\x65\x20\x69\x74\x27\x73\x20\x30\x78\x25\x30\x34\x58"
,z65fc26404c);return z65fc26404c;}}throw;}}void zd389c62dfd::z416530b361(Packet
::Ptr packet){KnxPacket::Ptr zfd29354025=KnxPacket::convert(packet,false);if(
zfd29354025){KnxPacket::Ptr z451de0fdde=z4f92549f31(zfd29354025);if(z451de0fdde)
{routeRx(z451de0fdde);}}DeviceFeaturePacket::Ptr zfa429ae5a5=Packet::convert<
DeviceFeaturePacket>(packet,false);if(zfa429ae5a5){if(zfa429ae5a5->zd982c014bf()
==usb::Frame::z21e8632859){z387eb17426(zfa429ae5a5->z13a39adf84(),zfa429ae5a5->
z286f9d00ee());}return;}TransportPacket::Ptr zfa61376f49=TransportPacket::
convert(packet,false);if(zfa61376f49){zae0bb42f7a(zfa61376f49);}}void 
zd389c62dfd::zb76e5b3ae9(Packet::Ptr packet){TransportPacket::Ptr zfa61376f49=
TransportPacket::convert(packet,false);if(zfa61376f49){z174ce8ab4d(zfa61376f49);
}}void zd389c62dfd::onEvent(unsigned int zf875a46722){routeEvent(zf875a46722);}
void zd389c62dfd::zcd4f7f46dd(KnxPacket::Ptr packet){KnxPacket::Ptr z451de0fdde=
zdc8ced637e(packet);if(z451de0fdde){std::vector<Packet::Ptr>z680f35b9d8;const 
TransportPacket::Buffer&buffer=z451de0fdde->getBuffer();zfd9e3ed405(z680f35b9d8,
buffer,usb::Frame::zb4b609d7a4,z0e29512e8d(z01a2f5d4b7()));for(const Packet::Ptr
&z743e63f163:z680f35b9d8){if(z94bd7d8eab){z40c251ad9c().send(z743e63f163);}else{
poco_warning(LOGGER(),
"\x73\x65\x6e\x64\x4b\x6e\x78\x54\x6f\x42\x75\x73\x20\x62\x75\x74\x20\x74\x72\x61\x6e\x73\x70\x6f\x72\x74\x20\x69\x73\x20\x6e\x6f\x74\x20\x6f\x70\x65\x6e\x2e\x20\x49\x67\x6e\x6f\x72\x65\x20\x69\x74"
);}}routeTx(packet);}}void zd389c62dfd::z717605cbda(unsigned char feature,std::
vector<unsigned char>&data){ScopedQueueConnectorRxQueue queue(z40c251ad9c());
zf5f233ec70(feature);Packet::Ptr packet=waitPacket(queue,zc2258de8d6(),[](kdrive
::connector::Packet::Ptr packet){auto zfa429ae5a5=Packet::convert<
DeviceFeaturePacket>(packet,false);if(zfa429ae5a5&&(zfa429ae5a5->zd982c014bf()==
usb::Frame::z1296ad2723)){return true;}return false;});DeviceFeaturePacket::Ptr 
zfa429ae5a5=Packet::convert<DeviceFeaturePacket>(packet,true);if(zfa429ae5a5->
z13a39adf84()!=feature){const AccessPortException e(
"\x55\x6e\x65\x78\x70\x65\x63\x74\x65\x64\x20\x46\x65\x61\x74\x75\x72\x65\x20\x52\x65\x73\x70\x6f\x6e\x73\x65"
);raiseError(e);}data=zfa429ae5a5->z286f9d00ee();}void zd389c62dfd::z1809dde2ad(
const std::vector<unsigned char>&data){std::vector<Packet::Ptr>z680f35b9d8;
zfd9e3ed405(z680f35b9d8,data,usb::Frame::z51132a25d1,usb::Frame::z45a2246ba1);
for(const Packet::Ptr&z743e63f163:z680f35b9d8){z40c251ad9c().send(z743e63f163);}
}void zd389c62dfd::zf5f233ec70(unsigned char feature){const std::vector<unsigned
 char>data((0x2b3+8638-0x2470),feature);std::vector<Packet::Ptr>z680f35b9d8;
zfd9e3ed405(z680f35b9d8,data,usb::Frame::z51132a25d1,usb::Frame::zf559d88801);
for(const Packet::Ptr&z743e63f163:z680f35b9d8){z40c251ad9c().send(z743e63f163);}
}void zd389c62dfd::z387eb17426(unsigned char feature,const std::vector<unsigned 
char>&z3083e34b3f){if((feature==z16b7bd8eb2)&&(!z3083e34b3f.empty())){const 
unsigned char value=z3083e34b3f.at((0x478+5986-0x1bda));if(value==
(0x1e8+5520-0x1777)){zd82f9ac44a(z4e34b5d0f7::Connected);}else if(value==
(0xf1b+3947-0x1e86)){zd82f9ac44a(z4e34b5d0f7::z7571184c3f);}else{zd82f9ac44a(
z4e34b5d0f7::Unknown);}}}unsigned char zd389c62dfd::z0e29512e8d(unsigned int 
zd2b01bb0a4){unsigned int zc39b9e2ff6=z76ed662d49;switch(zd2b01bb0a4){case 
za498009d76::None:zc39b9e2ff6=z76ed662d49;break;case za498009d76::z26a323d5e5:
zc39b9e2ff6=zfd674fa216;break;case za498009d76::z1746fd28fd:zc39b9e2ff6=
zf2ab8ebd73;break;default:{const UnsupportedProtocolException e("");raiseError(e
);}}return zc39b9e2ff6;}unsigned int zd389c62dfd::zb98b4a330a(unsigned char 
zd2b01bb0a4){unsigned int z2bb9fa41ff=za498009d76::None;switch(zd2b01bb0a4){case
 z76ed662d49:z2bb9fa41ff=za498009d76::None;break;case zfd674fa216:z2bb9fa41ff=
za498009d76::z26a323d5e5;break;case zf2ab8ebd73:z2bb9fa41ff=za498009d76::
z1746fd28fd;break;default:{const UnsupportedProtocolException e("");raiseError(e
);}}return z2bb9fa41ff;}unsigned int zd389c62dfd::z773f9d77ef(unsigned int data)
{unsigned int zef30e92c56=(0x13cb+1865-0x1b14);if(data&z924118c46a){zef30e92c56
|=za498009d76::z26a323d5e5;}if(data&z6ae9822e11){zef30e92c56|=za498009d76::
z1746fd28fd;}return zef30e92c56;}unsigned int zd389c62dfd::zeb85ef63a7(){std::
vector<unsigned char>data;z717605cbda(z6659195b32,data);return data.at(
(0xaa8+6662-0x24ae))<<(0x92f+5256-0x1daf)|data.at((0x558+1760-0xc37));}unsigned 
int zd389c62dfd::zc2258de8d6(){if((getUsbVendorId()==(0xe97+2922-0xb8a))&&(
getUsbProductId()==(0xdc2+2743-0x1776))){return(0x9da+2445-0xb97);}return 
z34fee5bbd7;}void zd389c62dfd::zda5b0c66b5(){try{z08c13130cf();}catch(Exception&
exception){poco_warning_f1(LOGGER(),
"\x57\x61\x72\x6e\x69\x6e\x67\x21\x20\x49\x67\x6e\x6f\x72\x65\x20\x65\x72\x72\x6f\x72\x20\x69\x6e\x20\x72\x65\x61\x64\x20\x62\x75\x73\x20\x73\x74\x61\x74\x65\x3a\x20\x25\x73"
,exception.displayText());}}class UsbPacket:public TransportPacket{public:
UsbPacket():TransportPacket(){setProtocol("\x75\x73\x62");}explicit UsbPacket(
const std::vector<unsigned char>&buffer):TransportPacket(buffer){setProtocol(
"\x75\x73\x62");}};zb7e35db1da::zb7e35db1da():z678e3eaf0f(Idle){
ConnectorNotificationHandler::Ptr handler=std::make_shared<
ConnectorNotificationHandler>(*this);setNotificationHandler(handler);}
zb7e35db1da::~zb7e35db1da(){}std::string zb7e35db1da::getDescription(){return"";
}void zb7e35db1da::z0d01069fec(const unsigned char*buffer,int size){if(size!=usb
::z6176029ec5::zd4f8e67a0d){poco_trace(LOGGER(),
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x55\x53\x42\x20\x72\x65\x70\x6f\x72\x74\x20\x66\x72\x61\x6d\x65\x20\x6c\x65\x6e\x67\x74\x68\x2e\x20\x49\x67\x6e\x6f\x72\x69\x6e\x67"
);return;}usb::z6176029ec5 frame(const_cast<unsigned char*>(buffer),size,false);
if(frame.zf259b97dbd()!=(0xfd7+3203-0x1c59)){poco_trace(LOGGER(),
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x55\x53\x42\x20\x72\x65\x70\x6f\x72\x74\x20\x69\x64\x2e\x20\x49\x67\x6e\x6f\x72\x69\x6e\x67"
);return;}const std::vector<unsigned char>v(buffer,buffer+size);Packet::Ptr 
zfa61376f49=std::make_shared<UsbPacket>(v);switch(z678e3eaf0f){case Idle:
z604e5f9a39.clear();switch(frame.zcb2c7e6f21()){case usb::Frame::z36ea2f3727:if(
z1204ac5a4a(zfa61376f49)){z0c8d87e181();}break;case usb::Frame::zffc1a949ed:if(
z1204ac5a4a(zfa61376f49)){z678e3eaf0f=zba79650288;}break;default:poco_trace(
LOGGER(),
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x70\x61\x63\x6b\x65\x74\x20\x74\x79\x70\x65\x2e\x20\x49\x67\x6e\x6f\x72\x69\x6e\x67"
);break;}break;case zba79650288:switch(frame.zcb2c7e6f21()){case usb::Frame::
z36ea2f3727:case usb::Frame::zffc1a949ed:z678e3eaf0f=Idle;z0d01069fec(buffer,
size);break;case usb::Frame::z35880dd8af:if(!z1204ac5a4a(zfa61376f49)){
z678e3eaf0f=Idle;}break;case usb::Frame::zf23ff3b732:if(z1204ac5a4a(zfa61376f49)
){z0c8d87e181();}z678e3eaf0f=Idle;break;default:poco_trace(LOGGER(),
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x70\x61\x63\x6b\x65\x74\x20\x74\x79\x70\x65\x2e\x20\x49\x67\x6e\x6f\x72\x69\x6e\x67"
);z678e3eaf0f=Idle;break;}break;}}bool zb7e35db1da::z1204ac5a4a(Packet::Ptr 
packet){Packet::Buffer buffer=packet->getBuffer();usb::z6176029ec5 frame(&buffer
.at((0x34+8001-0x1f75)),buffer.size(),false);const std::size_t seq=frame.
zbe81e74e90();if((seq<usb::Frame::z9dd47b9cb0)||(seq>usb::Frame::za0776c6ea8)){
poco_trace_f1(LOGGER(),
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x73\x65\x71\x75\x65\x6e\x63\x65\x20\x6e\x75\x6d\x62\x65\x72\x20\x25\x64\x2e\x20\x49\x67\x6e\x6f\x72\x69\x6e\x67"
,static_cast<int>(seq));return false;}else if(seq!=(z604e5f9a39.size()+
(0x1c55+1843-0x2387))){poco_trace_f2(LOGGER(),
"\x4f\x75\x74\x20\x6f\x66\x20\x6f\x72\x64\x65\x72\x20\x73\x65\x71\x75\x65\x6e\x63\x65\x20\x6e\x75\x6d\x62\x65\x72\x20\x25\x64\x2e\x20\x45\x78\x70\x65\x63\x74\x65\x64\x20\x25\x64\x2e\x20\x49\x67\x6e\x6f\x72\x69\x6e\x67"
,static_cast<int>(seq),static_cast<int>(z604e5f9a39.size()+(0xf8+454-0x2bd)));
return false;}if((seq==(0x1769+2440-0x20f0))&&(frame.zf1e6344a84()<=usb::Frame::
z81d39de932)){poco_trace(LOGGER(),
"\x53\x74\x61\x72\x74\x20\x66\x72\x61\x6d\x65\x20\x72\x65\x63\x65\x69\x76\x65\x64\x20\x77\x69\x74\x68\x6f\x75\x74\x20\x64\x61\x74\x61\x2e\x20\x49\x67\x6e\x6f\x72\x69\x6e\x67"
);return false;}z604e5f9a39.push_back(packet);return true;}void zb7e35db1da::
z0c8d87e181(){for(Packet::Ptr packet:z604e5f9a39){routeRx(packet);}Packet::Ptr 
packet=z604e5f9a39.front();Packet::Buffer&buffer=packet->getBuffer();usb::
zadbe67dd03 frame(&buffer.at((0x438+7519-0x2197)),buffer.size(),false);switch(
frame.z52456b46dc()){case usb::Frame::zb4b609d7a4:{routeRx(z9ff186a85c<KnxPacket
>(z604e5f9a39));break;}case usb::Frame::z51132a25d1:{DeviceFeaturePacket::Ptr 
zfa429ae5a5=z9ff186a85c<DeviceFeaturePacket>(z604e5f9a39);zfa429ae5a5->
zcb58dc0baf(frame.z65afec9653());routeRx(zfa429ae5a5);break;}default:{
poco_trace_f1(LOGGER(),
"\x50\x72\x6f\x74\x6f\x63\x6f\x6c\x20\x49\x44\x20\x25\x64\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x62\x79\x20\x55\x73\x62\x50\x6f\x72\x74\x54\x72\x61\x6e\x73\x70\x6f\x72\x74\x2e\x20\x49\x67\x6e\x6f\x72\x69\x6e\x67"
,static_cast<int>(frame.z52456b46dc()));}}}
