
#include "pch/kdrive_pch.h"
#include "kdrive/access/usb/UsbPortEnumerator.h"
#include "kdrive/access/core/AccessPortFactory.h"
#include "kdrive/access/core/API.h"
#include "kdrive/access/usb/UsbPort.h"
#include "kdrive/io/usbhid/UsbDriver.h"
#include "kdrive/utility/Logger.h"
#include <Poco/Exception.h>
#include <Poco/Logger.h>
#include <boost/assert.hpp>
using namespace kdrive::access;using namespace kdrive::io::usb;using Poco::
Exception;CLASS_LOGGER(
"\x6b\x64\x72\x69\x76\x65\x2e\x61\x63\x63\x65\x73\x73\x2e\x55\x73\x62\x50\x6f\x72\x74\x45\x6e\x75\x6d\x65\x72\x61\x74\x6f\x72"
)namespace{static void z69ef28410f(zd389c62dfd::Ptr zb0181fe503){try{if(
zb0181fe503->z01a2f5d4b7()!=za498009d76::z1746fd28fd){zb0181fe503->z12ff055552()
;}}catch(...){}}static void zc4bdfced75(zd389c62dfd::Ptr zb0181fe503){try{
zb0181fe503->z1bf089d014();}catch(...){}}static bool z4e88407e76(const std::
string&z72e98c8b46,unsigned int z1317194a29,z58740d8fff::PropertyCollection&
z44aa351fb2){bool z149f772af3=false;try{kdrive::connector::Connector::Ptr port=
zbf3da5ba57::instance().create(z72e98c8b46);zd389c62dfd::Ptr zb0181fe503=std::
dynamic_pointer_cast<zd389c62dfd>(port);BOOST_ASSERT_MSG(zb0181fe503,
"\x4e\x6f\x74\x20\x61\x20\x75\x73\x62\x20\x70\x6f\x72\x74\x20\x74\x79\x70\x65");
if(!zb0181fe503){throw Exception(
"\x4e\x6f\x74\x20\x61\x20\x75\x73\x62\x20\x70\x6f\x72\x74\x20\x74\x79\x70\x65");
}zb0181fe503->open(z1317194a29);z69ef28410f(zb0181fe503);zc4bdfced75(zb0181fe503
);z44aa351fb2=*zb0181fe503;z149f772af3=true;}catch(...){}return z149f772af3;}}
void zfa39e8b445::enumerate(Ports&zbffeaedfd5,bool tryOpen){return enumerate(
zd389c62dfd::ConnectorTypeLabel,zbffeaedfd5,tryOpen);}void zfa39e8b445::
enumerate(const std::string&z72e98c8b46,Ports&zbffeaedfd5,bool tryOpen){
poco_information(LOGGER(),
"\x53\x65\x61\x72\x63\x68\x20\x6b\x6e\x78\x20\x75\x73\x62\x20\x69\x6e\x74\x65\x72\x66\x61\x63\x65\x73"
);UsbDriverEnumerator&z6c5e7ebb5b=UsbDriverEnumerator::instance();z6c5e7ebb5b.
enumerate();const UsbDriverEnumerator::DeviceInfos&z57c7fa1015=z6c5e7ebb5b.
getDeviceInfos();for(unsigned int z1317194a29=(0x151f+834-0x1861);z1317194a29<
z57c7fa1015.size();++z1317194a29){z58740d8fff::PropertyCollection z44aa351fb2;
const UsbDeviceInfo&z2e8d041d4e=z57c7fa1015.at(z1317194a29);if(!tryOpen||
z4e88407e76(z72e98c8b46,z1317194a29,z44aa351fb2)){z44aa351fb2.setProperty(
zd389c62dfd::zf399913164,z2e8d041d4e.getVendorId());z44aa351fb2.setProperty(
zd389c62dfd::z6006021112,z2e8d041d4e.getProductId());z44aa351fb2.setProperty(
zd389c62dfd::za3db08fb48,z2e8d041d4e.getManufacturer());z44aa351fb2.setProperty(
zd389c62dfd::z987de680b2,z2e8d041d4e.getProduct());const std::string zd311e7ca26
=z2e8d041d4e.getSerialNumber();if(!zd311e7ca26.empty()){z44aa351fb2.setProperty(
zd389c62dfd::z9d956080e6,zd311e7ca26);}zbffeaedfd5.push_back(z44aa351fb2);}}}
