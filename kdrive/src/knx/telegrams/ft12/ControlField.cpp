
#include "pch/kdrive_pch.h"
#include "kdrive/knx/telegrams/ft12/ControlField.h"
#include "kdrive/knx/defines/FT12Constants.h"
#include <boost/assert.hpp>
using namespace kdrive::knx::ft12;ControlField::ControlField(){}ControlField::
ControlField(unsigned char data){set(data);}ControlField::~ControlField(){}void 
ControlField::setDirection(unsigned char zbadde329ec){BOOST_ASSERT((zbadde329ec&
~z0646b897f1)==(0x21c1+58-0x21fb));unsigned char data=get();data&=~z0646b897f1;
data|=zbadde329ec&(0x45a+7378-0x20ac);set(data);}unsigned char ControlField::
zdc2d0e92ea()const{return get()&z0646b897f1;}void ControlField::
setPrimaryMessage(unsigned char primaryMessage){BOOST_ASSERT((primaryMessage&~
z34b2888246)==(0xad+418-0x24f));unsigned char data=get();data&=~z34b2888246;data
|=primaryMessage&z34b2888246;set(data);}unsigned char ControlField::z9986705d27(
)const{return get()&z34b2888246;}void ControlField::setFrameCountBit(unsigned 
char z898b3ba7ef){BOOST_ASSERT((z898b3ba7ef&~ze41428c42e)==(0x3d7+8610-0x2579));
unsigned char data=get();data&=~ze41428c42e;data|=z898b3ba7ef&ze41428c42e;set(
data);}unsigned char ControlField::getFrameCountBit()const{return get()&
ze41428c42e;}void ControlField::setFrameCountBitValid(unsigned char za30e1c245f)
{BOOST_ASSERT((za30e1c245f&~zcee642872d)==(0x189+8437-0x227e));unsigned char 
data=get();data&=~zcee642872d;data|=za30e1c245f&zcee642872d;set(data);}unsigned 
char ControlField::getFrameCountBitValid()const{return get()&(0x7e9+4313-0x18b2)
;}void ControlField::setFunctionCode(unsigned char zc0f31fe87f){BOOST_ASSERT((
zc0f31fe87f&~z94508ce501)==(0x581+4323-0x1664));unsigned char data=get();data&=~
z94508ce501;data|=zc0f31fe87f&z94508ce501;set(data);}unsigned char ControlField
::getFunctionCode()const{return get()&z94508ce501;}
