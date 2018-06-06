
#include "pch/kdrive_pch.h"
#include "kdrive/knx/telegrams/cemi/Frame.h"
#include "kdrive/knx/telegrams/cemi/RfAdditionalInfo.h"
#include "kdrive/knx/core/Buffer.h"
#include "kdrive/knx/telegrams/formatters/ControlField.h"
#include "kdrive/knx/telegrams/formatters/ExtendedControlField.h"
#include "kdrive/knx/telegrams/formatters/TpciApci.h"
#include "kdrive/knx/telegrams/cemi/AdditionalInfo.h"
#include "kdrive/knx/defines/TransportType.h"
using namespace kdrive::knx;using namespace kdrive::knx::cemi;Frame::~Frame(){}
void Frame::setDefaults(){zb6eb8808c0::setDefaults();za14fd0e9bd.setDefaults();
z5b3a8175da.setDefaults();z236d788078.setDefaults();z4eb8aff455.setDefaults();}
void Frame::z1d82003342(const std::vector<unsigned char>&z75aff836ba){
za14fd0e9bd.setData(z75aff836ba);}const std::vector<unsigned char>&Frame::
zfd5c03b75a()const{return za14fd0e9bd.getData();}void Frame::z77d825fd88(
unsigned char z35a951ea12){za14fd0e9bd.z539a137476(z35a951ea12);}unsigned char 
Frame::zb10c293b39()const{return za14fd0e9bd.getLength();}void Frame::
z1ad3842a90(unsigned char z9557a26474){z5b3a8175da.set(z9557a26474);}unsigned 
char Frame::z2b7c7a9243()const{return z5b3a8175da.get();}void Frame::z93a0e900e9
(unsigned char z030213cd03){z236d788078.set(z030213cd03);}unsigned char Frame::
zbe18e5ae86()const{return z236d788078.get();}void Frame::zfae4668299(unsigned 
char zedd172d966){z5b3a8175da.zfae4668299(zedd172d966);}unsigned char Frame::
z0336eaae40()const{return z5b3a8175da.z0336eaae40();}bool Frame::z6507326b0b()
const{return z5b3a8175da.z6507326b0b();}bool Frame::z2fee7808b2()const{return 
z5b3a8175da.z2fee7808b2();}void Frame::z5a4cf0bd20(unsigned char zc9c0819fa9){
z5b3a8175da.z5a4cf0bd20(zc9c0819fa9);}unsigned char Frame::z946dc3a4d1()const{
return z5b3a8175da.z946dc3a4d1();}bool Frame::z555597b57f()const{return 
z5b3a8175da.z555597b57f();}bool Frame::isBroadcast()const{return z5b3a8175da.
isBroadcast();}void Frame::z222d82c49b(unsigned char zf799fec5b6){z236d788078.
z222d82c49b(zf799fec5b6);}unsigned char Frame::z83d73bc9c9()const{return 
z236d788078.z83d73bc9c9();}int Frame::zbb95a510c1()const{if(!ze25425cb88()){
const z4c36bf125c&z63a59adbe1=z661198e8f6();if(z63a59adbe1.z7c7410b9fc()){const 
int z9bfce5eb8f=z63a59adbe1.zb1cc600287();return z63a59adbe1.z46f9466935()?(
z9bfce5eb8f&(0x796+7203-0x23b8)?z3d8e3fe7e9::z50d88f7e34:z3d8e3fe7e9::
z4e70b876a0):(z9bfce5eb8f&(0x8c2+4024-0x1879)?z3d8e3fe7e9::zdb56991e84:
z3d8e3fe7e9::za7ebcbbdd8);}else{return z63a59adbe1.z46f9466935()?z3d8e3fe7e9::
zd89758ff00:z3d8e3fe7e9::z8fa0ea8a01;}}else{return(z0f78ff293d()==zf85dc71173)?
z3d8e3fe7e9::zcb3343fb35:z3d8e3fe7e9::zc4b9c19fbe;}return(0x4bd+6150-0x1cc3);}
Frame::Frame(){zb523c348a5();}void Frame::z87c4e77298(){zb6eb8808c0::z87c4e77298
();if(z04562c4adc()>(0xd66+2220-0x1603)){zfae4668299(zb86da2fa16::zbbcc8d1437);}
}void Frame::z442da0cbec(){addFormatter(&za14fd0e9bd);addFormatter(&z5b3a8175da)
;addFormatter(&z236d788078);addFormatter(&z106aa767bc());addFormatter(&
z4b20abff51());addFormatter(&z4eb8aff455);addFormatter(&z661198e8f6());}void 
Frame::zdcb70f7c70(unsigned char length){z4eb8aff455.set(length);}unsigned char 
Frame::z7599d207db()const{return z4eb8aff455.get();}void Frame::z56ae94b385(
unsigned char z07310dab6b){z5b3a8175da.z53b21e3703(z07310dab6b);}unsigned char 
Frame::z8a4104cb0d()const{return z5b3a8175da.z2b2bfcb7a8();}void Frame::
setPriorityImpl(unsigned char priority){z5b3a8175da.setPriority(priority);}
unsigned char Frame::getPriorityImpl()const{return z5b3a8175da.getPriority();}
void Frame::za230b1de4b(unsigned char zc5aeda9f96){z5b3a8175da.z085e9dee59(
zc5aeda9f96);}unsigned char Frame::z151bac17b2()const{return z5b3a8175da.
z22d11f0f3a();}void Frame::z1f0cb92727(unsigned char z7e658739a1){z5b3a8175da.
z8ad68fb4ea(z7e658739a1);}unsigned char Frame::z4d9c03f095()const{return 
z5b3a8175da.zda8df62f0d();}void Frame::za662e0c766(unsigned char z90de16d7da){
z236d788078.zfef6804589(z90de16d7da);}unsigned char Frame::z0ea5925a1b()const{
return z236d788078.zfc5016f8e0();}void Frame::z3b48f4fbce(unsigned char 
z5cde7031d2){z236d788078.zc5845415f8(z5cde7031d2);}unsigned char Frame::
zc0f4a59344()const{return z236d788078.ze85f31fba4();}void kdrive::knx::cemi::
z11aab8119f(const Frame&frame,std::vector<unsigned char>&zd311e7ca26){if(frame.
z555597b57f()){try{std::vector<unsigned char>z75aff836ba=frame.zfd5c03b75a();
z7a67187a0a z9b04aba9ea;z9b04aba9ea.read(z75aff836ba);if(z9b04aba9ea.isValid()){
zd311e7ca26=z9b04aba9ea.getAddress();}}catch(...){}}}
