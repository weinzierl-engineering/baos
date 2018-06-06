
#include "pch/kdrive_pch.h"
#include "kdrive/access/core/AccessPortFactory.h"
#include "kdrive/access/Headers.h"
#include <Poco/Exception.h>
#include <Poco/SingletonHolder.h>
#if z94a9d99f91 == (0x7d8+3577-0x15d0)
#include "kdrive/baos/ft12/FT12Connector.h"
#include "kdrive/baos/stream/StreamConnector12.h"
#include "kdrive/baos/stream/StreamConnector2x.h"
#endif 
#if z8e08b3d0fb == (0x7b3+3291-0x148d)
#include "kdrive/mock/MockPort.h"
#endif 
using namespace kdrive::access;using kdrive::connector::Connector;using Poco::
NotImplementedException;using Poco::SingletonHolder;namespace{std::shared_ptr<
Connector>zfd1483f02a(const std::string&z72e98c8b46){std::shared_ptr<Connector>
z3aafe8bd70;
#define z1a59266c3a(C) \
	if (!z3aafe8bd70) z3aafe8bd70 = zbf3da5ba57::zfd1483f02a<C>(z72e98c8b46)
#if zcd0e891628 == (0x201f+472-0x21f6)
z1a59266c3a(z4311eba219);z1a59266c3a(zb29f9cb5d2);
#endif
#if zcd0e891628 == (0x269+5017-0x1601) && z1b8e4afc71 == (0x359+672-0x5f8)
z1a59266c3a(zd2fbeea00c);
#endif
#if zdbf4fc04d2 == (0xfa2+3575-0x1d98)
z1a59266c3a(zb779067727);z1a59266c3a(z474a91cc8c);
#endif
#if za7ae158721 == (0x1559+705-0x1819)
z1a59266c3a(zd389c62dfd);
#endif
#if z696f095bea == (0x14c7+656-0x1756)
z1a59266c3a(zc155069ba3);
#endif
#if z94a9d99f91 == (0x70d+7224-0x2344)
z1a59266c3a(kdrive::baos::zcc043281ec);z1a59266c3a(kdrive::baos::zb194a73166);
z1a59266c3a(kdrive::baos::ze73c6764d4);
#endif
#if z24e21dd097 == (0x2c0+937-0x668)
z1a59266c3a(z400e5a4333);
#endif
#if z055ef7cb53 == (0x833+1523-0xe25)
z1a59266c3a(z4bf3cf713b);z1a59266c3a(z05bc90a8e1);
#endif
#if z3856533630 == (0x1c92+400-0x1e21)
z1a59266c3a(zf074556e6f);
#endif
#if z8e08b3d0fb == (0x1cf5+2010-0x24ce)
z1a59266c3a(z897d7a3c58);
#endif
#undef z1a59266c3a
return z3aafe8bd70;}void z3fecfd9123(std::vector<std::string>&z5f27e64d39){
#define z18c474ae88(C) \
	z5f27e64d39.push_back(C::ConnectorTypeLabel)
#if zcd0e891628 == (0x602+2000-0xdd1)
z18c474ae88(z4311eba219);z18c474ae88(zb29f9cb5d2);
#endif
#if zcd0e891628 == (0xd7c+6416-0x268b) && z1b8e4afc71 == (0xcd1+6170-0x24ea)
z18c474ae88(zd2fbeea00c);
#endif
#if zdbf4fc04d2 == (0x723+5958-0x1e68)
z18c474ae88(zb779067727);z18c474ae88(z474a91cc8c);
#endif
#if za7ae158721 == (0xc60+1865-0x13a8)
z18c474ae88(zd389c62dfd);
#endif
#if z696f095bea == (0x44b+7288-0x20c2)
z18c474ae88(zc155069ba3);
#endif
#if z94a9d99f91 == (0x46b+573-0x6a7)
z18c474ae88(kdrive::baos::zcc043281ec);z18c474ae88(kdrive::baos::zb194a73166);
z18c474ae88(kdrive::baos::ze73c6764d4);
#endif
#if z24e21dd097 == (0x10b6+3186-0x1d27)
z18c474ae88(z400e5a4333);
#endif
#if z055ef7cb53 == (0x1b19+1569-0x2139)
z18c474ae88(z4bf3cf713b);z18c474ae88(z05bc90a8e1);
#endif
#if z3856533630 == (0xe30+4706-0x2091)
z18c474ae88(zf074556e6f);
#endif
#if z8e08b3d0fb == (0xd5+2664-0xb3c)
z18c474ae88(z897d7a3c58);
#endif
#undef z18c474ae88
}}zbf3da5ba57::zbf3da5ba57(){z3fde7bb20e(&::zfd1483f02a);z8323704001(&::
z3fecfd9123);}zbf3da5ba57&zbf3da5ba57::instance(){static SingletonHolder<
zbf3da5ba57>instance;return*instance.get();}std::shared_ptr<Connector>
zbf3da5ba57::create(const std::string&z72e98c8b46){std::shared_ptr<Connector>
z3aafe8bd70;for(za5546bfd28 zfd1483f02a:zccf977910c){z3aafe8bd70=zfd1483f02a(
z72e98c8b46);if(z3aafe8bd70){return z3aafe8bd70;}}throw 
UnsupportedPortTypeException(z72e98c8b46);}std::vector<std::string>zbf3da5ba57::
z6caaec609a(){std::vector<std::string>z5f27e64d39;for(z51ff6993f7 z3fecfd9123:
z20dd1cefd2){z3fecfd9123(z5f27e64d39);}return z5f27e64d39;}void zbf3da5ba57::
z3fde7bb20e(za5546bfd28 zfd1483f02a){zccf977910c.push_back(zfd1483f02a);}void 
zbf3da5ba57::z8323704001(z51ff6993f7 z3fecfd9123){z20dd1cefd2.push_back(
z3fecfd9123);}
