
#include "pch/kdrive_pch.h"
#include "kdrive/baos/usb/UsbConnector.h"
#include "kdrive/access/core/KnxPacket.h"
#include "kdrive/access/baos/BaosKnxPort.h"
#include "kdrive/access/usb/UsbPortEnumerator.h"
#include "kdrive/baos/core/API.h"
#include "kdrive/baos/core/DataPacket.h"
#include "kdrive/baos/core/Exception.h"
#include "kdrive/baos/protocols/Protocol2x.h"
#include "kdrive/knx/defines/KnxLayer.h"
#include "kdrive/io/usbhid/UsbVendors.h"
#include "kdrive/utility/Logger.h"
#include <Poco/Exception.h>
#include <Poco/SingletonHolder.h>
#include <memory>
using namespace kdrive::connector;using namespace kdrive::baos;using kdrive::
access::KnxPacket;using kdrive::access::zfa39e8b445;using kdrive::access::
zfa6c8ef87f;using kdrive::knx::zba36969226;using kdrive::io::usb::UsbVendors;
using Poco::SingletonHolder;CLASS_LOGGER(
"\x6b\x64\x72\x69\x76\x65\x2e\x62\x61\x6f\x73\x2e\x55\x73\x62\x43\x6f\x6e\x6e\x65\x63\x74\x6f\x72"
)namespace{void zdd2e046b74(kdrive::utility::PropertyCollection&z56fa974c3c){
z56fa974c3c.setProperty(UsbConnector::PortType,UsbConnector::ConnectorTypeLabel)
;}class z4726196c8c{public:z4726196c8c(){z7d609e68b6();}static z4726196c8c&
instance(){static SingletonHolder<z4726196c8c>z7354e06518;return*z7354e06518.get
();}private:static void z7d609e68b6(){UsbVendors&zd30c9c952c=UsbVendors::
instance();zd30c9c952c.clear();const std::vector<UsbVendors::Device>z7e75a134d0=
{{(0x19c4+86-0xba3),(0x35a+3429-0xfbb)},{(0x1398+8207-0x2530),8193},};
zd30c9c952c.appendDevices(z7e75a134d0);}};}namespace kdrive{namespace baos{class
 KnxUsbPort:public zfa6c8ef87f{public:KnxUsbPort()=default;private:void openImpl
()override{zfa6c8ef87f::openImpl();z7de2a5ac1c(zba36969226::zf0c17de15e);}};}}
const std::string UsbConnector::ConnectorTypeLabel=
"\x62\x61\x6f\x73\x2e\x75\x73\x62";UsbConnector::UsbConnector():BaosConnector(
ProtocolVersions::V20),knxUsbPort_(new KnxUsbPort){zdd2e046b74(*this);Connector
::PacketSignal&zd07c8e5469=knxUsbPort_->getPacketSignal();
signalConnectionPacket_=zd07c8e5469.connect(std::bind(&UsbConnector::onPacket,
this,std::placeholders::_1,std::placeholders::_2));EventSignal&z26df99c77a=
knxUsbPort_->getEventSignal();signalConnectionEvent_=z26df99c77a.connect(std::
bind(&UsbConnector::onEvent,this,std::placeholders::_1));setPacketFactory(std::
make_shared<PacketFactory2x>());z4726196c8c::instance();}UsbConnector::~
UsbConnector(){try{close();signalConnectionPacket_.disconnect();
signalConnectionEvent_.disconnect();knxUsbPort_.reset(nullptr);}catch(...){}}
void UsbConnector::open(int index){knxUsbPort_->setProperty(KnxUsbPort::
z6f8f16a878,index);BaosConnector::open();}std::string UsbConnector::
getDescription(){return knxUsbPort_->getDescription();}bool UsbConnector::
isConnected()const{return knxUsbPort_->isOpen();}unsigned int UsbConnector::
getUsbIndex()const{return knxUsbPort_->getUsbIndex();}unsigned int UsbConnector
::getUsbVendorId(){return knxUsbPort_->getUsbVendorId();}unsigned int 
UsbConnector::getUsbProductId(){return knxUsbPort_->getUsbProductId();}std::
string UsbConnector::getUsbManufacturerString(){return knxUsbPort_->
getUsbManufacturerString();}std::string UsbConnector::getUsbProductString(){
return knxUsbPort_->getUsbProductString();}std::string UsbConnector::
getUsbSerialNumberString(){return knxUsbPort_->getUsbSerialNumberString();}void 
UsbConnector::openImpl(){knxUsbPort_->open();}void UsbConnector::closeImpl(){
knxUsbPort_->close();}bool UsbConnector::isOpenImpl()const{return knxUsbPort_->
isOpen();}void UsbConnector::resetPropertiesImpl(){BaosConnector::
resetPropertiesImpl();zdd2e046b74(*this);knxUsbPort_->resetProperties();}void 
UsbConnector::txImpl(std::shared_ptr<kdrive::connector::Packet>packet){std::
size_t size=packet->size();std::vector<unsigned char>buffer(size,
(0x99a+459-0xb65));packet->writeToBuffer(&buffer.at((0x13ea+1823-0x1b09)),buffer
.size());KnxPacket::Ptr zfd29354025=std::make_shared<KnxPacket>(buffer);
knxUsbPort_->send(zfd29354025);}void UsbConnector::rxImpl(){knxUsbPort_->receive
();}void UsbConnector::onPacket(kdrive::connector::Packet::Ptr packet,int 
zbadde329ec){const std::vector<unsigned char>buffer=packet->getBuffer();kdrive::
connector::Packet::Ptr z1ff4c37d24=create(&buffer.at((0xe8a+2911-0x19e9)),buffer
.size());if(zbadde329ec==Connector::Rx){routeRx(z1ff4c37d24);}else{routeTx(
z1ff4c37d24);}}void UsbConnector::onEvent(unsigned int zf875a46722){routeEvent(
zf875a46722);}void kdrive::baos::enumerateBaosUsbDevices(std::vector<kdrive::
utility::PropertyCollection>&z7e75a134d0){z4726196c8c::instance();zfa39e8b445::
enumerate(z7e75a134d0,false);}
