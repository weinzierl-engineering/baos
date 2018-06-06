
#ifndef z1d0b601636
#define z1d0b601636
#include "kdrive/access/Config.h"
#include "kdrive/access/core/KnxPort.h"
#include <vector>
#include <memory>
namespace kdrive{namespace access{class KnxPacket;class zb7e35db1da;class 
z23bd02551e zd389c62dfd:public zea2d083c85{public:typedef std::shared_ptr<
zd389c62dfd>Ptr;zd389c62dfd();virtual~zd389c62dfd();using zea2d083c85::open;void
 open(int index);std::string getDescription()override;unsigned int getUsbIndex()
const;unsigned int getUsbVendorId();unsigned int getUsbProductId();std::string 
getUsbManufacturerString();std::string getUsbProductString();std::string 
getUsbSerialNumberString();void z7466c70591(std::shared_ptr<zb7e35db1da>
z25df9e99c8);zb7e35db1da&z40c251ad9c();static void zfd9e3ed405(std::vector<
kdrive::connector::Packet::Ptr>&z680f35b9d8,const kdrive::connector::Packet::
Buffer&zb4a7952e11,int z6babad3bc5,int z8bf837ad78);void z08c13130cf();public:
static const std::string ConnectorTypeLabel;static const std::string z6f8f16a878
;static const std::string zf399913164;static const std::string z6006021112;
static const std::string za3db08fb48;static const std::string z987de680b2;static
 const std::string z9d956080e6;protected:typedef std::shared_ptr<KnxPacket>
z5e6d83dc4d;void enumerateImpl(Ports&zbffeaedfd5)override;void openImpl()
override;void closeImpl()override;bool isOpenImpl()const override;void 
resetPropertiesImpl()override;void txImpl(connector::Packet::Ptr packet)override
;unsigned int z29f4d6d6a3()override;unsigned int zc1ee43d1f6()override;void 
z81289a39cd(unsigned int z5ecb2cdb3d)override;unsigned int z93d917156c()override
;unsigned int z07a1de2360()override;unsigned int z4b4d92d5e8()override;void 
z416530b361(kdrive::connector::Packet::Ptr packet);void zb76e5b3ae9(kdrive::
connector::Packet::Ptr packet);void onEvent(unsigned int zf875a46722);void 
zcd4f7f46dd(z5e6d83dc4d packet);void z717605cbda(unsigned char feature,std::
vector<unsigned char>&data);void z1809dde2ad(const std::vector<unsigned char>&
data);void zf5f233ec70(unsigned char feature);void z387eb17426(unsigned char 
feature,const std::vector<unsigned char>&z3083e34b3f);unsigned char z0e29512e8d(
unsigned int zd2b01bb0a4);unsigned int zb98b4a330a(unsigned char zd2b01bb0a4);
unsigned int z773f9d77ef(unsigned int data);unsigned int zeb85ef63a7();unsigned 
int zc2258de8d6();void zda5b0c66b5();protected:enum z5031e65207{z76ed662d49=
(0x13d4+4353-0x24d5),zfd674fa216=(0x851+5005-0x1bdd),z8b2c742eda=
(0x1079+5716-0x26cb),zf2ab8ebd73=(0x6f9+5352-0x1bde)};enum z8b957c5a25{
z924118c46a=(0x7c4+4148-0x17f7),z799a1863d7=(0x508+5778-0x1b98),z6ae9822e11=
(0x3f0+2452-0xd80)};enum Features{z6659195b32=(0x679+2328-0xf90),z8a10a60f59=
(0x4ea+5899-0x1bf3),z16b7bd8eb2=(0xe8c+3630-0x1cb7),z6f756d1962=
(0x962+4995-0x1ce1),z589263083f=(0xc68+1872-0x13b3),zda7a60bfc1=
(0x962+2996-0x14c1)};private:enum{zb32e12ceee=(0x10e5+2080-0x1902)};static const
 unsigned int z34fee5bbd7=(0x2221+1017-0x2232);boost::signals2::
scoped_connection z240bf3efcd;boost::signals2::scoped_connection zdf6a625f58;
boost::signals2::scoped_connection ze466aac0a0;std::shared_ptr<zb7e35db1da>
z94bd7d8eab;};class z23bd02551e zb7e35db1da:public kdrive::connector::
QueueConnector{public:zb7e35db1da();virtual~zb7e35db1da();virtual void open(int 
index)=0;virtual void close()=0;std::string getDescription()override;virtual 
unsigned int getVendorId()const=0;virtual unsigned int getProductId()const=0;
virtual std::string getUsbManufacturerString()const=0;virtual std::string 
getUsbProductString()const=0;virtual std::string getUsbSerialNumberString()const
=0;protected:void z0d01069fec(const unsigned char*buffer,int size);private:bool 
z1204ac5a4a(kdrive::connector::Packet::Ptr packet);void z0c8d87e181();enum 
States{Idle,zba79650288};private:std::vector<kdrive::connector::Packet::Ptr>
z604e5f9a39;int z678e3eaf0f;};}}
#endif 

