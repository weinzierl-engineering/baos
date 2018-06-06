
#include "pch/kdrive_pch.h"
#include "kdrive/knx/telegrams/formatters/AbstractFrame.h"
#include "kdrive/knx/telegrams/formatters/TpciApci.h"
#include "kdrive/knx/defines/ControlField1.h"
#include "kdrive/knx/defines/ControlField2.h"
#include "kdrive/knx/defines/ApciCodes.h"
using namespace kdrive::knx;zb6eb8808c0::zb6eb8808c0(){}zb6eb8808c0::~
zb6eb8808c0(){}void zb6eb8808c0::setDefaults(){z2a66522423::setDefaults();
z25e0c7c393.set((0x1d14+2390-0x266a));z067b4d26f4.set((0xf32+1390-0x14a0));
ze3c1bf5f3d.setDefaults();}void zb6eb8808c0::z7a4e9f90f5(unsigned short 
z70febf1c08){z25e0c7c393.set(z70febf1c08);}unsigned short zb6eb8808c0::
zf86f8ebac3()const{return z25e0c7c393.get();}void zb6eb8808c0::z60afd5d244(
unsigned short destAddress){z067b4d26f4.set(destAddress);}unsigned short 
zb6eb8808c0::z0f78ff293d()const{return z067b4d26f4.get();}void zb6eb8808c0::
zf263dbb1b0(unsigned char length){zdcb70f7c70(length);}unsigned char zb6eb8808c0
::z04562c4adc()const{return z7599d207db();}void zb6eb8808c0::z8d873abbd0(
unsigned char zec1a0db202){ze3c1bf5f3d.z8d873abbd0(zec1a0db202);}unsigned char 
zb6eb8808c0::z1231e0a0f5()const{return ze3c1bf5f3d.z1231e0a0f5();}void 
zb6eb8808c0::zdc59bacd5e(unsigned short z4374a74052){ze3c1bf5f3d.zdc59bacd5e(
z4374a74052);}unsigned short zb6eb8808c0::zb42f7f4d31()const{return ze3c1bf5f3d.
zb42f7f4d31();}void zb6eb8808c0::zf94736c1b1(unsigned char data){ze3c1bf5f3d.
zf937a56022(data);}unsigned char zb6eb8808c0::z63d0f5c92e()const{return 
ze3c1bf5f3d.zc32421769a();}bool zb6eb8808c0::z23e8b5a205()const{return(
ze3c1bf5f3d.z03ed123847()&&ze3c1bf5f3d.z36aedae3b0());}bool zb6eb8808c0::
zfb5ba01112()const{if(!z23e8b5a205()){return false;}if((ze3c1bf5f3d.zb42f7f4d31(
)==z0e6afe5f14::z7b5414db5f)||(ze3c1bf5f3d.zb42f7f4d31()==z0e6afe5f14::
z209e0371cf)){return(z04562c4adc()==(0x465+3231-0x1103));}else{return true;}}
void zb6eb8808c0::z53b21e3703(unsigned char z07310dab6b){return z56ae94b385(
z07310dab6b);}unsigned char zb6eb8808c0::z2b2bfcb7a8()const{return z8a4104cb0d()
;}void zb6eb8808c0::setPriority(unsigned char priority){setPriorityImpl(priority
);}unsigned char zb6eb8808c0::getPriority()const{return getPriorityImpl();}void 
zb6eb8808c0::z085e9dee59(unsigned char zc5aeda9f96){za230b1de4b(zc5aeda9f96);}
unsigned char zb6eb8808c0::z22d11f0f3a()const{return z151bac17b2();}void 
zb6eb8808c0::z8ad68fb4ea(unsigned char z7e658739a1){z1f0cb92727(z7e658739a1);}
unsigned char zb6eb8808c0::zda8df62f0d()const{return z4d9c03f095();}void 
zb6eb8808c0::zfef6804589(unsigned char z90de16d7da){za662e0c766(z90de16d7da);}
unsigned char zb6eb8808c0::zfc5016f8e0()const{return z0ea5925a1b();}bool 
zb6eb8808c0::z088b874fc9()const{return(zfc5016f8e0()==AddressType::z3e51bf884f);
}bool zb6eb8808c0::ze25425cb88()const{return!z088b874fc9();}void zb6eb8808c0::
zc5845415f8(unsigned char z5cde7031d2){z3b48f4fbce(z5cde7031d2);}unsigned char 
zb6eb8808c0::ze85f31fba4()const{return zc0f4a59344();}void zb6eb8808c0::
zc285551d40(unsigned char zeeff18bf43){ze3c1bf5f3d.z803c69545d(zeeff18bf43);}
unsigned char zb6eb8808c0::z366df26979()const{return ze3c1bf5f3d.z04da7ba69e();}
bool zb6eb8808c0::z7c7410b9fc()const{return ze3c1bf5f3d.z7c7410b9fc();}bool 
zb6eb8808c0::z03ed123847()const{return ze3c1bf5f3d.z03ed123847();}void 
zb6eb8808c0::z1c7fa837ba(unsigned char z3ae14e0357){ze3c1bf5f3d.z1c7fa837ba(
z3ae14e0357);}unsigned char zb6eb8808c0::z0575ab7e39()const{return ze3c1bf5f3d.
z0575ab7e39();}bool zb6eb8808c0::z46f9466935()const{return ze3c1bf5f3d.
z46f9466935();}bool zb6eb8808c0::z2c15b77461()const{return ze3c1bf5f3d.
z2c15b77461();}void zb6eb8808c0::z12aeb820c7(unsigned char z80e0f1c035){
ze3c1bf5f3d.z12aeb820c7(z80e0f1c035);}unsigned char zb6eb8808c0::zbe81e74e90()
const{return ze3c1bf5f3d.zbe81e74e90();}void zb6eb8808c0::z779e83faac(unsigned 
char zebf72c74e7){ze3c1bf5f3d.z492380c81c(zebf72c74e7);}unsigned char 
zb6eb8808c0::z7fa1ef6c88()const{return ze3c1bf5f3d.zb1cc600287();}bool 
zb6eb8808c0::z3b221f8315()const{return(ze25425cb88()&&(z0f78ff293d()==
zf85dc71173));}void zb6eb8808c0::z87c4e77298(){z2a66522423::z87c4e77298();
z6c7b637c0b();}void zb6eb8808c0::zb523c348a5(){z442da0cbec();}WordFormatter&
zb6eb8808c0::z106aa767bc(){return z25e0c7c393;}WordFormatter&zb6eb8808c0::
z4b20abff51(){return z067b4d26f4;}z4c36bf125c&zb6eb8808c0::z661198e8f6(){return 
ze3c1bf5f3d;}const z4c36bf125c&zb6eb8808c0::z661198e8f6()const{return 
ze3c1bf5f3d;}void zb6eb8808c0::z6c7b637c0b(){const Formatters&formatters=
z2a3eb910b4();if(ze3c1bf5f3d.z03ed123847()&&!formatters.empty()){const 
AbstractFormatter*formatter=formatters.back();const unsigned int size=formatter
->size();zf263dbb1b0(size+(0xc0+8096-0x205f));}else{zf263dbb1b0(
(0xb35+355-0xc98));}}void kdrive::knx::za71a6ae562(zb6eb8808c0&frame){frame.
zfef6804589(AddressType::Group);frame.zc285551d40(z4c36bf125c::za97dd29186::
z40b10a1058);frame.z1c7fa837ba(z4c36bf125c::z4126c46cde::zee97a49d5d);frame.
z12aeb820c7((0xa90+6389-0x2385));frame.z60afd5d244(zb6eb8808c0::zf85dc71173);}
void kdrive::knx::zffbf7e3c74(zb6eb8808c0&frame){frame.zfef6804589(AddressType::
Group);frame.zc285551d40(z4c36bf125c::za97dd29186::z40b10a1058);frame.
z1c7fa837ba(z4c36bf125c::z4126c46cde::zee97a49d5d);frame.z12aeb820c7(
(0x421+8851-0x26b4));}void kdrive::knx::zcda8b2d8bf(zb6eb8808c0&frame){frame.
zfef6804589(AddressType::z3e51bf884f);frame.zc285551d40(z4c36bf125c::za97dd29186
::z40b10a1058);frame.z1c7fa837ba(z4c36bf125c::z4126c46cde::zee97a49d5d);frame.
z12aeb820c7((0x11bd+5159-0x25e4));}void kdrive::knx::z510dacca6b(zb6eb8808c0&
frame){frame.zfef6804589(AddressType::z3e51bf884f);frame.zc285551d40(z4c36bf125c
::za97dd29186::z40b10a1058);frame.z1c7fa837ba(z4c36bf125c::z4126c46cde::
z944ec0d992);}void kdrive::knx::z78bed5004d(zb6eb8808c0&frame){frame.zfef6804589
(AddressType::z3e51bf884f);frame.zc285551d40(z4c36bf125c::za97dd29186::
z972707fb3d);frame.z1c7fa837ba(z4c36bf125c::z4126c46cde::zee97a49d5d);frame.
z779e83faac((0xa2b+7373-0x26f8));}void kdrive::knx::z9b03ba007f(zb6eb8808c0&
frame){frame.zfef6804589(AddressType::z3e51bf884f);frame.zc285551d40(z4c36bf125c
::za97dd29186::z972707fb3d);frame.z1c7fa837ba(z4c36bf125c::z4126c46cde::
zee97a49d5d);frame.z779e83faac((0xf8+5826-0x17b9));}void kdrive::knx::
z1a982a8199(zb6eb8808c0&frame){frame.zfef6804589(AddressType::z3e51bf884f);frame
.zc285551d40(z4c36bf125c::za97dd29186::z972707fb3d);frame.z1c7fa837ba(
z4c36bf125c::z4126c46cde::z944ec0d992);frame.z779e83faac((0x8e3+4597-0x1ad6));}
void kdrive::knx::zfade96f740(zb6eb8808c0&frame){frame.zfef6804589(AddressType::
z3e51bf884f);frame.zc285551d40(z4c36bf125c::za97dd29186::z972707fb3d);frame.
z1c7fa837ba(z4c36bf125c::z4126c46cde::z944ec0d992);frame.z779e83faac(
(0x16a0+3206-0x2323));}
