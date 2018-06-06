
#ifndef z6982409beb
#define z6982409beb
#include "kdrive/access/Config.h"
#include "kdrive/access/ldm/LocalDeviceManagement.h"
#include <memory>
namespace kdrive{namespace connector{class Connector;}}namespace kdrive{
namespace access{struct z23bd02551e z68a7397df0{enum z9884ee4d6b{Link=
(0x13a2+1494-0x1978),z1340d1c626=(0x15c9+433-0x1779),Raw=(0x6e7+832-0xa25),
za9068249eb=(0x125a+3255-0x1f0b),zf0c17de15e=(0xce3+4009-0x1b9c),None=
(0x1321+5342-0x2700)};};struct z23bd02551e z1fc0d7d5da{enum zd6a7f12a7e{Link=
(0x8e1+6699-0x230b),z1340d1c626=(0x134f+4957-0x26aa),Raw=(0x1518+3700-0x2388),
za9068249eb=(0x5db+1709-0xc80),None=(0x1e5f+390-0x1fe5)};};class z23bd02551e 
LocalDeviceManagementEmiC:public zec7fc1647d{public:typedef std::shared_ptr<
LocalDeviceManagementEmiC>Ptr;LocalDeviceManagementEmiC(zea2d083c85&port);
virtual~LocalDeviceManagementEmiC();public:void z766e2388b4(unsigned int 
z1166f2fdb4)override;unsigned int z6f5601a8cf()override;unsigned int z2e0dcb1a8b
()override;unsigned int z51177f5ce9()override;unsigned short z5da113978e()
override;void z5392ddee85(unsigned int z83744e1e92)override;unsigned int 
zf670e5347d()override;void z6c59c3156d(unsigned int zf92894300e)override;
unsigned int zfa42f5b322()override;void zb488b9244d(const std::vector<unsigned 
char>&zf92894300e)override;void z875dcf85de(std::vector<unsigned char>&
zf92894300e)override;void z2853a8fc86(const std::vector<unsigned char>&
zd311e7ca26)override;void z8039b7bd80(std::vector<unsigned char>&zd311e7ca26)
override;void z00fec7e215(unsigned int zfd606f58be)override;unsigned int 
za4544ba4dc()override;void zc2caea0629(unsigned int ze2fcb9ca3a)override;
unsigned int zbab06955e5()override;void z261ccc1287(unsigned short z83744e1e92)
override;unsigned short z587dd78f85()override;void z3160480dbb(const std::vector
<unsigned short>&addresses)override;void za8754b21ac(std::vector<unsigned short>
&addresses)override;void ze507d8ae58(unsigned short index,unsigned short address
)override;void za66a499387(std::vector<unsigned char>&macAddress)override;void 
zbcdf3a2d1a(const std::string&zf15e490884)override;void zd0d1398630(std::string&
zf15e490884)override;void ze5acd8e45b(bool z2a654b4732)override;bool ze59351aa9c
()override;void zcc247395cd(unsigned char zb55d083cb5);unsigned char z83d4da9f75
();void z563fc10557(unsigned short zb9dc9070a1)override;unsigned short 
z7e6620eb94()override;unsigned short z2afe3965f8()override;void z0d4c9a138c(
unsigned short zde108227b3,unsigned char z092ca22e9d,unsigned char data);void 
z0d4c9a138c(unsigned short zde108227b3,unsigned char z092ca22e9d,const std::
vector<unsigned char>&data);void z3570ca8d16(unsigned short zde108227b3,unsigned
 char z092ca22e9d,unsigned char z9333a4b376,std::vector<unsigned char>&data);
void zbf218e095d(unsigned short zde108227b3,unsigned char z092ca22e9d,unsigned 
char z46ae658472,unsigned char z9333a4b376,std::vector<unsigned char>&data);void
 z5515a7e6b0(unsigned short zde108227b3,unsigned char z092ca22e9d,unsigned char 
z46ae658472,unsigned char z9333a4b376,std::vector<unsigned char>&data);protected
:void zc08cfe981c(unsigned char zb55d083cb5,const std::string&msg);private:
typedef std::shared_ptr<KnxPacket>z5e6d83dc4d;void za817c9ea45(unsigned char 
z3be8a826b8);unsigned char z44023dda1d();void zf1ebe16a79(unsigned char 
z2bd0e78914);unsigned char z74c07aea9b();void zfdb0dea8aa(unsigned short 
zde108227b3,unsigned char z092ca22e9d,unsigned char z46ae658472,unsigned int 
ze357ca9b3a,std::vector<unsigned char>&data);void zdee3d5acd9(unsigned short 
zde108227b3,unsigned char z092ca22e9d,unsigned char z46ae658472,unsigned char 
z9333a4b376,unsigned short ze357ca9b3a,std::vector<unsigned char>&data);
z5e6d83dc4d z039c32ff6c(unsigned short zde108227b3,unsigned char z3f282c6d81,
unsigned char z092ca22e9d,unsigned char z46ae658472,unsigned short ze357ca9b3a,
const std::vector<unsigned char>&data);z5e6d83dc4d z5c4f5a9bd6(unsigned short 
zde108227b3,unsigned char z3f282c6d81,unsigned char z092ca22e9d,unsigned char 
z46ae658472,unsigned short ze357ca9b3a);void z6b2f113f03(z5e6d83dc4d packet,
unsigned short zde108227b3,unsigned char z3f282c6d81,unsigned char z092ca22e9d,
unsigned char z46ae658472,unsigned char z9333a4b376,unsigned short ze357ca9b3a,
std::vector<unsigned char>&data);z5e6d83dc4d zaff085ae22(connector::Connector&
connector,unsigned long timeout=z62421fa3b1);z5e6d83dc4d z3387f63009(connector::
Connector&connector,unsigned long timeout=z62421fa3b1);unsigned int z1b4e121dcb(
unsigned int z1166f2fdb4);unsigned int z04db47e219(unsigned int z1166f2fdb4);
unsigned int z5b1a046ae2(unsigned int z2c49518260);bool z97d8ed9b64(const std::
vector<unsigned char>&zf92894300e);bool z3ca8c1f9d7(std::vector<unsigned char>&
zf92894300e);};}}
#endif 

