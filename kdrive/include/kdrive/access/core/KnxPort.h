
#ifndef zccd5405545
#define zccd5405545
#include "kdrive/access/Config.h"
#include "kdrive/access/core/AccessPort.h"
#include "kdrive/access/ldm/LocalDeviceManager.h"
#include "kdrive/connector/Packet.h"
#include <Poco/Mutex.h>
namespace kdrive{namespace connector{class ScopedQueueConnectorRxQueue;}}
namespace kdrive{namespace access{class KnxPacket;class TransportPacket;class 
z23bd02551e zea2d083c85:public z58740d8fff{public:typedef std::shared_ptr<
zea2d083c85>Ptr;zea2d083c85();virtual~zea2d083c85();void routeRx(kdrive::
connector::Packet::Ptr packet)override;void zb44d474e62(unsigned int timeout);
unsigned int z0eb4f337db()const;void zbac9796807(bool enable);bool z680ad25263()
const;void z367d96a272(bool enable);bool zddad992be2()const;void z76d6965e85(
bool enable);bool z605bfe297a()const;unsigned int z791c5fd335();void setProtocol
(unsigned int zd2b01bb0a4);unsigned int z01a2f5d4b7();bool zdf6fe1862a(unsigned 
int zd2b01bb0a4);static bool zdf6fe1862a(unsigned int zef30e92c56,unsigned int 
zd2b01bb0a4);unsigned int z089addfe48(unsigned int zef30e92c56)const;void 
zd897a67e14();unsigned int z524baf8256();void z7de2a5ac1c(unsigned int 
z1166f2fdb4);unsigned int z42de9bb630();bool z4011fc21c2(unsigned int 
z1166f2fdb4);static bool z4011fc21c2(unsigned int z7ecdefe519,unsigned int 
z1166f2fdb4);unsigned int z340f3e6eca(unsigned int z7ecdefe519)const;void 
za8d5adfa57();bool z19cee9e459();void z371132a440(bool enable=true);unsigned int
 z12ff055552();std::string z3251ee4772();unsigned short z1bf089d014();std::
string zc3136dcdfa();void zf52767dc71(unsigned int z83744e1e92);unsigned int 
zbe00e8c303();void z22c631a890(unsigned int zf92894300e);unsigned int 
zbb04277d6f();void z3a2f8fbb8f(const std::vector<unsigned char>&zf92894300e);
const std::vector<unsigned char>&zafeaeec64f();void z5f5fd61d58(const std::
vector<unsigned char>&zd311e7ca26);const std::vector<unsigned char>&
getSerialNumber();void z68349079eb(unsigned int zb9dc9070a1);unsigned int 
z19770e1430();void z64a5d004ba(bool enable);bool z2a654b4732();unsigned int 
z175c5f0532()const;unsigned int zaff92585a2();void z4fb044e67b(bool enable);bool
 z0be6f75ca1()const;public:static const std::string ConnectorTypeLabel;static 
const std::string zb18866bb87;static const std::string z39ec4d1ae7;static const 
std::string z0ad2fe7ad5;static const std::string ze2fc87d94b;static const std::
string z8b957c5a25;static const std::string za498009d76;static const std::string
 za6f43e69a4;static const std::string z9884ee4d6b;static const std::string 
z74dda860c7;static const std::string zb5ec3c9a78;static const std::string 
z2a66eed75d;static const std::string z13c23c3849;static const std::string 
zc3e6a1886e;static const std::string zee467d54fc;static const std::string 
SerialNumber;static const std::string zdc8dff356e;static const std::string 
z1be699fe9f;static const std::string z5b2ecda528;static const std::string 
z83d2649f20;static const std::string za6f2fc65f0;struct z4e34b5d0f7{enum State{
Unknown=(0x1ca9+2645-0x26fe),z7571184c3f,Connected};};enum{z61d5be1f36=
(0x74f+1583-0x996)};enum{z81eda64581=(0x1e8f+86-0x1ed6),z507acb30fa=
(0x39d+4140-0x12cb)};protected:typedef std::shared_ptr<KnxPacket>z5e6d83dc4d;
void openImpl()override;void resetPropertiesImpl()override;void 
setPreferredSettingsImpl()override;virtual bool z021857951d();virtual void 
zbe0f21419f(bool enable=true);virtual unsigned int z1f86c15fd0();virtual 
unsigned short z716d13ecdd();unsigned short z21e0db8628();virtual void 
zd0d51f5d95(unsigned int z83744e1e92);virtual unsigned int zfbca701d15();virtual
 void za08556178a(unsigned int zf92894300e);virtual unsigned int z7bc42300fa();
virtual void z57588f181e(const Poco::Dynamic::Var&zf92894300e);virtual void 
zee1690ad9d(std::vector<unsigned char>&zf92894300e);virtual void za8e4013ca3(
const Poco::Dynamic::Var&zd311e7ca26);virtual void zc153fe5430(std::vector<
unsigned char>&zd311e7ca26);virtual void zf52cc38da1(unsigned int zb9dc9070a1);
virtual unsigned int z29f4d6d6a3();virtual void zeb33dc19f4(bool enable);virtual
 bool zf21c0140ae();virtual unsigned int z50193a49a9();z11671f1e0a&zc7087b3e64()
;const z11671f1e0a&zc7087b3e64()const;z5e6d83dc4d zdc8ced637e(const z5e6d83dc4d 
z0c57cdab20);z5e6d83dc4d z4f92549f31(const z5e6d83dc4d packet);void za117cd55de(
connector::ScopedQueueConnectorRxQueue&queue,z5e6d83dc4d packet);void 
zd82f9ac44a(z4e34b5d0f7::State z7619915478);void zae0bb42f7a(std::shared_ptr<
TransportPacket>zfa61376f49);void z174ce8ab4d(std::shared_ptr<TransportPacket>
zfa61376f49);virtual unsigned int zc1ee43d1f6()=0;virtual void z81289a39cd(
unsigned int zd2b01bb0a4)=0;virtual unsigned int z93d917156c()=0;virtual 
unsigned int z07a1de2360()=0;virtual void zd8cf4148d6(unsigned int z1166f2fdb4);
virtual unsigned int z6fe0401c37();virtual unsigned int zf4cd0c79bd();virtual 
unsigned int z4b4d92d5e8();private:unsigned short z442e211ba0();void z674533ad46
();void z3101dee849();void onEvent(unsigned long e);private:z11671f1e0a 
z8a3623983b;mutable Poco::FastMutex zf31a9d5745;unsigned int z7eae6471dd;boost::
signals2::scoped_connection signalConnectionEvent_;};}}
#endif 

