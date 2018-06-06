
#ifndef za56cbc5be2
#define za56cbc5be2
#include "kdrive/knx/Config.h"
#include "kdrive/knx/telegrams/formatters/Formatter.h"
namespace kdrive{namespace knx{class z91680f515b z4c36bf125c:public 
AbstractFormatter{public:z4c36bf125c();virtual~z4c36bf125c();public:std::size_t 
size()const override;bool isValid()const override;void setDefaults()override;
void z8d873abbd0(unsigned char zec1a0db202);unsigned char z1231e0a0f5()const;
void z803c69545d(unsigned char zee9005f7d0);unsigned char z04da7ba69e()const;
bool z7c7410b9fc()const;bool z03ed123847()const;void z1c7fa837ba(unsigned char 
z3ae14e0357);unsigned char z0575ab7e39()const;bool z46f9466935()const;bool 
z2c15b77461()const;void z12aeb820c7(unsigned char z80e0f1c035);unsigned char 
zbe81e74e90()const;void z492380c81c(unsigned char z9bfce5eb8f);unsigned char 
zb1cc600287()const;void zdc59bacd5e(unsigned short z4374a74052);unsigned short 
zb42f7f4d31()const;void zf937a56022(unsigned char z00e0e5a03c);unsigned char 
zc32421769a()const;bool z36aedae3b0()const;public:struct za97dd29186{enum Values
{z40b10a1058=(0x536+1463-0xaed),z972707fb3d=(0x12c3+931-0x1665)};};struct 
z4126c46cde{enum Values{zee97a49d5d=(0x2309+420-0x24ad),z944ec0d992=
(0x3e0+8037-0x2344)};};private:std::size_t readImpl(const Buffer&buffer)override
;std::size_t writeImpl(Buffer&buffer)override;private:unsigned char z03981fae6e;
unsigned char zecc39ca911;};}}
#endif 

