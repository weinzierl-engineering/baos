
#include "pch/kdrive_pch.h"
#include "kdrive/knx/defines/ApciCodes.h"
#include "kdrive/knx/telegrams/formatters/TpciApci.h"
#include <Poco/Exception.h>
using namespace kdrive::knx;using Poco::Exception;namespace{struct z512be7d538{
enum{zea9bde779f=(0x292+990-0x66d),SequenceNumber=(0xbbc+6396-0x247c),
z4126c46cde=(0x631+3450-0x136b),z5fc5d414e4=(0xb93+4314-0x1bed),zfd8107ee1e=
z5fc5d414e4|z4126c46cde|SequenceNumber,z9a7e3ad412=(0x3e2+8453-0x24e4),
z6dc0505be1=(0xb78+5488-0x1fe9),z9515462931=(0xd78+2444-0x1644),z9b5519084e=
(0x591+2522-0xf2c)};};}z4c36bf125c::z4c36bf125c(){setDefaults();}z4c36bf125c::~
z4c36bf125c(){}std::size_t z4c36bf125c::size()const{return z7c7410b9fc()?
(0x1b8+6878-0x1c95):(0x199b+3002-0x2553);}bool z4c36bf125c::isValid()const{
return true;}void z4c36bf125c::setDefaults(){z03981fae6e=(0x1fcc+1562-0x25e6);
zecc39ca911=(0x1790+1761-0x1e71);}void z4c36bf125c::z8d873abbd0(unsigned char 
zec1a0db202){if(zec1a0db202&z512be7d538::z5fc5d414e4){z03981fae6e=zec1a0db202;}
else{z03981fae6e&=~z512be7d538::zfd8107ee1e;z03981fae6e|=zec1a0db202&z512be7d538
::zfd8107ee1e;}}unsigned char z4c36bf125c::z1231e0a0f5()const{return z03ed123847
()?(z03981fae6e&z512be7d538::zfd8107ee1e):z03981fae6e;}void z4c36bf125c::
z803c69545d(unsigned char zee9005f7d0){if(zee9005f7d0==za97dd29186::z972707fb3d)
{z03981fae6e|=z512be7d538::z5fc5d414e4;}else{z03981fae6e&=~z512be7d538::
z5fc5d414e4;}}unsigned char z4c36bf125c::z04da7ba69e()const{return(z03981fae6e&
z512be7d538::z5fc5d414e4)?za97dd29186::z972707fb3d:za97dd29186::z40b10a1058;}
bool z4c36bf125c::z7c7410b9fc()const{return(z04da7ba69e()==za97dd29186::
z972707fb3d);}bool z4c36bf125c::z03ed123847()const{return(z04da7ba69e()==
za97dd29186::z40b10a1058);}void z4c36bf125c::z1c7fa837ba(unsigned char 
z3ae14e0357){if(z3ae14e0357==z4126c46cde::z944ec0d992){z03981fae6e|=z512be7d538
::z4126c46cde;}else{z03981fae6e&=~z512be7d538::z4126c46cde;}}unsigned char 
z4c36bf125c::z0575ab7e39()const{return(z03981fae6e&z512be7d538::z4126c46cde)?
z4126c46cde::z944ec0d992:z4126c46cde::zee97a49d5d;}bool z4c36bf125c::z46f9466935
()const{return(z0575ab7e39()==z4126c46cde::z944ec0d992);}bool z4c36bf125c::
z2c15b77461()const{return(z0575ab7e39()==z4126c46cde::zee97a49d5d);}void 
z4c36bf125c::z12aeb820c7(unsigned char z80e0f1c035){z03981fae6e&=~z512be7d538::
SequenceNumber;z03981fae6e|=(z80e0f1c035<<(0x1885+1906-0x1ff5))&z512be7d538::
SequenceNumber;}unsigned char z4c36bf125c::zbe81e74e90()const{return(z03981fae6e
&z512be7d538::SequenceNumber)>>(0x11b2+2479-0x1b5f);}void z4c36bf125c::
z492380c81c(unsigned char z9bfce5eb8f){z03981fae6e&=~z512be7d538::zea9bde779f;
z03981fae6e|=z9bfce5eb8f&z512be7d538::zea9bde779f;}unsigned char z4c36bf125c::
zb1cc600287()const{return z03981fae6e&z512be7d538::zea9bde779f;}void z4c36bf125c
::zdc59bacd5e(unsigned short z4374a74052){if(z0e6afe5f14::z36aedae3b0(
z4374a74052)){z4374a74052>>=(0x823+5703-0x1e64);z03981fae6e&=~z512be7d538::
z9a7e3ad412;z03981fae6e|=(z4374a74052>>(0x2b6+3876-0x11d8))&z512be7d538::
z9a7e3ad412;zecc39ca911&=~z512be7d538::z9515462931;zecc39ca911|=(z4374a74052&
(0xcfc+2712-0x1791))<<(0x115+2641-0xb60);}else{z03981fae6e&=~z512be7d538::
z9a7e3ad412;z03981fae6e|=(z4374a74052>>(0xd91+3038-0x1967))&z512be7d538::
z9a7e3ad412;zecc39ca911=z4374a74052&(0x4cc+6563-0x1d70);}}unsigned short 
z4c36bf125c::zb42f7f4d31()const{unsigned short z4374a74052=((z03981fae6e&
(0xf51+3221-0x1be3))<<(0x643+7050-0x21c5))|zecc39ca911;if(z0e6afe5f14::
z36aedae3b0(z4374a74052)){z4374a74052&=~z512be7d538::z9b5519084e;}return 
z4374a74052;}void z4c36bf125c::zf937a56022(unsigned char z00e0e5a03c){
zecc39ca911&=~z512be7d538::z9b5519084e;zecc39ca911|=z00e0e5a03c&z512be7d538::
z9b5519084e;}unsigned char z4c36bf125c::zc32421769a()const{return zecc39ca911&
z512be7d538::z9b5519084e;}std::size_t z4c36bf125c::readImpl(const Buffer&buffer)
{int size=(0x1b25+2441-0x24ad);z03981fae6e=buffer.z02b8347997((0x983+1384-0xeeb)
);if(z03ed123847()){zecc39ca911=buffer.z02b8347997((0x134+6021-0x18b8));++size;}
else{zecc39ca911=(0x454+858-0x7ae);}return size;}std::size_t z4c36bf125c::
writeImpl(Buffer&buffer){int size=(0xe87+5306-0x2340);buffer.zb8203d7346(
(0x312+5113-0x170b),z03981fae6e);if(z03ed123847()){buffer.zb8203d7346(
(0x636+4618-0x183f),zecc39ca911);++size;}return size;}bool z4c36bf125c::
z36aedae3b0()const{return z0e6afe5f14::z36aedae3b0(zb42f7f4d31());}
