
#include "pch/kdrive_pch.h"
#include "kdrive/knx/telegrams/formatters/ControlField.h"
#include "kdrive/knx/defines/ControlField1.h"
using namespace kdrive::knx;ControlField::ControlField():z8fde0ce433(z546f7ffee3
),zbe28545e04(z5aeb79e17d),z68cee29da9(z571c8035b7::Broadcast),z394b8ce9c3(
z453562ef33),z1726289397(zfb362260af),ze237349bc6(z979a653a0d){}ControlField::~
ControlField(){}std::size_t ControlField::size()const{return Size;}bool 
ControlField::isValid()const{return true;}void ControlField::setDefaults(){
AbstractFormatter::setDefaults();z8fde0ce433=z546f7ffee3;zbe28545e04=z5aeb79e17d
;z68cee29da9=z571c8035b7::Broadcast;z394b8ce9c3=z453562ef33;z1726289397=
zfb362260af;ze237349bc6=z979a653a0d;}void ControlField::set(unsigned char 
controlField){z8fde0ce433=(controlField&z886ba65001)>>(0x2d8+965-0x696);
zbe28545e04=(controlField&ze59a17aad8)>>(0x83+4257-0x111f);z68cee29da9=(
controlField&z56a3470c4a)>>(0x978+2026-0x115e);z394b8ce9c3=(controlField&
z6a0cb0dd62)>>(0xca8+5974-0x23fc);z1726289397=(controlField&z79b469c2ac)>>
(0xb46+2934-0x16bb);ze237349bc6=controlField&z78f9cc4c36;}unsigned char 
ControlField::get()const{unsigned char controlField=(0x1485+393-0x160e);
controlField|=(z8fde0ce433<<(0xc52+2184-0x14d3))&z886ba65001;controlField|=(
zbe28545e04<<(0x86a+1647-0xed4))&ze59a17aad8;controlField|=(z68cee29da9<<
(0x194d+2685-0x23c6))&z56a3470c4a;controlField|=(z394b8ce9c3<<
(0x193f+1250-0x1e1f))&z6a0cb0dd62;controlField|=(z1726289397<<
(0x683+7624-0x244a))&z79b469c2ac;controlField|=ze237349bc6&z78f9cc4c36;return 
controlField;}void ControlField::zfae4668299(unsigned char zedd172d966){
z8fde0ce433=zedd172d966;}unsigned char ControlField::z0336eaae40()const{return 
z8fde0ce433;}bool ControlField::z6507326b0b()const{return(z8fde0ce433==
z546f7ffee3);}bool ControlField::z2fee7808b2()const{return!z6507326b0b();}void 
ControlField::z53b21e3703(unsigned char z07310dab6b){zbe28545e04=z07310dab6b;}
unsigned char ControlField::z2b2bfcb7a8()const{return zbe28545e04;}void 
ControlField::z5a4cf0bd20(unsigned char zc9c0819fa9){z68cee29da9=zc9c0819fa9;}
unsigned char ControlField::z946dc3a4d1()const{return z68cee29da9;}bool 
ControlField::z555597b57f()const{return(z68cee29da9==z571c8035b7::z033e297d46);}
bool ControlField::isBroadcast()const{return!z555597b57f();}void ControlField::
setPriority(unsigned char priority){z394b8ce9c3=priority;}unsigned char 
ControlField::getPriority()const{return z394b8ce9c3;}void ControlField::
z085e9dee59(unsigned char zc5aeda9f96){z1726289397=zc5aeda9f96;}unsigned char 
ControlField::z22d11f0f3a()const{return z1726289397;}void ControlField::
z8ad68fb4ea(unsigned char z7e658739a1){ze237349bc6=z7e658739a1;}unsigned char 
ControlField::zda8df62f0d()const{return ze237349bc6;}std::size_t ControlField::
readImpl(const Buffer&buffer){set(buffer.z02b8347997((0xa59+5630-0x2057)));
return size();}std::size_t ControlField::writeImpl(Buffer&buffer){buffer.
zb8203d7346((0x786+3594-0x1590),get());return size();}
