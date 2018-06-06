
#include "pch/kdrive_pch.h"
#include "kdrive/knx/telegrams/cemi/MProp.h"
#include "kdrive/knx/telegrams/formatters/TupleFormatter.h"
#include "kdrive/knx/defines/MProp.h"
#include <Poco/Exception.h>
using namespace kdrive::knx;using namespace kdrive::knx::cemi;using Poco::
Exception;namespace kdrive{namespace knx{namespace cemi{struct zd47bcf7adc:
public zd1e5842927<(0x18db+2106-0x2105),(0xd87+1530-0x1379),(0x16f5+1370-0x1c47)
,(0x1799+3641-0x25ce),(0x1cc6+58-0x1cf4)>{};}}}z3f64688ceb::z3f64688ceb():
za45b66b509(new zd47bcf7adc()){addFormatter(za45b66b509);}z3f64688ceb::~
z3f64688ceb(){delete za45b66b509;}void z3f64688ceb::z48a824e00c(unsigned short 
zde108227b3){za45b66b509->set<z44a69d48a6>(zde108227b3);}unsigned short 
z3f64688ceb::z38e712c10a()const{return za45b66b509->get<z44a69d48a6>();}void 
z3f64688ceb::zdd57f327fa(unsigned char z3f282c6d81){za45b66b509->set<ze702ff7924
>(z3f282c6d81);}unsigned char z3f64688ceb::z3f5ab81f7c()const{return za45b66b509
->get<ze702ff7924>();}void z3f64688ceb::zf46c3b49cc(unsigned char z092ca22e9d){
za45b66b509->set<PID>(z092ca22e9d);}unsigned char z3f64688ceb::zc3a04ee564()
const{return za45b66b509->get<PID>();}void z3f64688ceb::z55f5c7ccbb(unsigned 
char z46ae658472){za45b66b509->set<zfdaeedf89e>(z46ae658472);}unsigned char 
z3f64688ceb::zb1d5689c1e()const{return za45b66b509->get<zfdaeedf89e>();}unsigned
 char z3f64688ceb::z4ab321079b()const{const unsigned char z46ae658472=
zb1d5689c1e();return z46ae658472?getData().size()/z46ae658472:
(0x8a0+4128-0x18c0);}void z3f64688ceb::z79bd7d3c67(unsigned short ze357ca9b3a){
za45b66b509->set<z03e813dcac>(ze357ca9b3a);}unsigned short z3f64688ceb::
z8f2a3bea9c()const{return za45b66b509->get<z03e813dcac>();}bool z3f64688ceb::
z3b20cfd48a()const{return zb1d5689c1e()==(0x212+1330-0x744);}unsigned char 
z3f64688ceb::za6a0997cc3()const{if(!z3b20cfd48a()){throw Exception(
"\x46\x72\x61\x6d\x65\x20\x69\x73\x20\x6e\x6f\x74\x20\x61\x20\x6e\x65\x67\x61\x74\x69\x76\x65\x20\x72\x65\x73\x70\x6f\x6e\x73\x65"
);}if(getData().empty()){throw Exception(
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x44\x61\x74\x61\x20\x42\x75\x66\x66\x65\x72");
}return getData().at((0x2022+130-0x20a4));}std::string z3f64688ceb::z254dc6b154(
)const{const unsigned char errorCode=za6a0997cc3();return kdrive::knx::
z54c1d8983d::getDescription(errorCode);}
