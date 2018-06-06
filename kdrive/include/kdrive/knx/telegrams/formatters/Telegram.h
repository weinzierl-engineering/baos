
#ifndef zb206cff014
#define zb206cff014
#include "kdrive/knx/Config.h"
#include "kdrive/knx/telegrams/formatters/Formatter.h"
#include <vector>
namespace kdrive{namespace knx{class z91680f515b z2a66522423:public Formatter{
public:enum zee723f0e8d{ze3ff7b3558=(0x87c+4593-0x19ed)};enum Attributes{
z3ddf5f3c68=(0x90a+396-0xa96),};z2a66522423();virtual~z2a66522423();void 
za5e4891a53(unsigned char z22139f7a06);unsigned char z6b11bcce77()const;bool 
zf9f997438f(const std::vector<unsigned char>&buffer)const;void setData(const std
::vector<unsigned char>&data);const std::vector<unsigned char>&getData()const;
std::vector<unsigned char>&getData();protected:zfb0a48309d&z5863bb042e();private
:ByteFormatter z34a346ae28;zfb0a48309d z1709ace471;};template<class base,int 
zf2ffcf0663,bool z07650a5db9,bool z03bff56f55=true>class zc61eee6dc0:public base
{public:enum{z3ddf5f3c68=zf2ffcf0663,z53a7a6235e=z07650a5db9};zc61eee6dc0(){base
::za5e4891a53(z3ddf5f3c68);if(z07650a5db9){base::addFormatter(&base::z5863bb042e
());}}virtual~zc61eee6dc0(){}virtual bool isValid()const{return zc28e6c199c()&&
base::isValid();}private:bool zc28e6c199c()const{return z03bff56f55?base::
z6b11bcce77()==z3ddf5f3c68:true;}};}}
#endif 

