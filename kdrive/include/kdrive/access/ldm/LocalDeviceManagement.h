
#ifndef zd6951db7e1
#define zd6951db7e1
#include "kdrive/access/Config.h"
#include <string>
#include <vector>
#include <memory>
namespace kdrive{namespace access{class zea2d083c85;class KnxPacket;class 
z23bd02551e zec7fc1647d{public:typedef std::shared_ptr<zec7fc1647d>Ptr;
zec7fc1647d(zea2d083c85&port);virtual~zec7fc1647d();public:virtual void restart(
);virtual void z766e2388b4(unsigned int z1166f2fdb4)=0;virtual unsigned int 
z6f5601a8cf()=0;virtual unsigned int z2e0dcb1a8b()=0;virtual unsigned int 
z51177f5ce9()=0;virtual unsigned short z5da113978e()=0;virtual void z5392ddee85(
unsigned int z83744e1e92)=0;virtual unsigned int zf670e5347d()=0;virtual void 
z6c59c3156d(unsigned int zf92894300e)=0;virtual unsigned int zfa42f5b322()=0;
virtual void zb488b9244d(const std::vector<unsigned char>&zf92894300e)=0;virtual
 void z875dcf85de(std::vector<unsigned char>&zf92894300e)=0;virtual void 
z2853a8fc86(const std::vector<unsigned char>&zd311e7ca26)=0;virtual void 
z8039b7bd80(std::vector<unsigned char>&zd311e7ca26)=0;virtual void z00fec7e215(
unsigned int zfd606f58be)=0;virtual unsigned int za4544ba4dc()=0;virtual void 
zc2caea0629(unsigned int ze2fcb9ca3a)=0;virtual unsigned int zbab06955e5()=0;
virtual void z261ccc1287(unsigned short z83744e1e92)=0;virtual unsigned short 
z587dd78f85()=0;virtual void z3160480dbb(const std::vector<unsigned short>&
addresses)=0;virtual void za8754b21ac(std::vector<unsigned short>&addresses)=0;
virtual void ze507d8ae58(unsigned short index,unsigned short address)=0;virtual 
void za66a499387(std::vector<unsigned char>&macAddress)=0;virtual void 
zbcdf3a2d1a(const std::string&zf15e490884)=0;virtual void zd0d1398630(std::
string&zf15e490884)=0;virtual void ze5acd8e45b(bool z2a654b4732)=0;virtual bool 
ze59351aa9c()=0;virtual void z563fc10557(unsigned short zb9dc9070a1)=0;virtual 
unsigned short z7e6620eb94()=0;virtual unsigned short z2afe3965f8();protected:
enum z1e21a5225e{z62421fa3b1=(0x199d+3473-0x2346),};protected:typedef std::
shared_ptr<KnxPacket>z5e6d83dc4d;zea2d083c85&getPort();const zea2d083c85&getPort
()const;void za4528c2f93(unsigned int z1166f2fdb4,const std::string&msg);void 
z75eed006b0(unsigned int z83744e1e92,const std::string&msg);void z85480faf6f(
unsigned int zf92894300e,const std::string&msg);void zd02eaa9824(const std::
vector<unsigned char>&zf92894300e,const std::string&msg);void z501eae5473(const 
std::vector<unsigned char>&zd311e7ca26,const std::string&msg);void z99dab55337(
unsigned int zfd606f58be,const std::string&msg);void za6acd56ff2(unsigned int 
z83744e1e92,const std::string&msg);void z0269f1e89b(const std::vector<unsigned 
short>&addresses,const std::string&msg);void z11e15a5722(unsigned int 
ze2fcb9ca3a,const std::string&msg);void z7475b3f872(const std::string&
zf15e490884,const std::string&msg);void z0f3b34e3a9(unsigned short zb9dc9070a1,
const std::string&msg);z5e6d83dc4d zbe3acf8982(unsigned int timeout);z5e6d83dc4d
 zbe3acf8982(const unsigned char*buffer,unsigned int z3ba388a942,unsigned int 
offset,unsigned int timeout);private:zea2d083c85&zcdc6474106;};}}
#endif 

