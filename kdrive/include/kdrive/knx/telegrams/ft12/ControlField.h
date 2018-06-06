
#ifndef z3294baded6
#define z3294baded6
#include "kdrive/knx/Config.h"
#include "kdrive/knx/telegrams/formatters/Formatter.h"
namespace kdrive{namespace knx{namespace ft12{class z91680f515b ControlField:
public ByteFormatter{public:ControlField();ControlField(unsigned char data);
virtual~ControlField();void setDirection(unsigned char zbadde329ec);unsigned 
char zdc2d0e92ea()const;void setPrimaryMessage(unsigned char primaryMessage);
unsigned char z9986705d27()const;void setFrameCountBit(unsigned char z898b3ba7ef
);unsigned char getFrameCountBit()const;void setFrameCountBitValid(unsigned char
 za30e1c245f);unsigned char getFrameCountBitValid()const;void setFunctionCode(
unsigned char zc0f31fe87f);unsigned char getFunctionCode()const;private:enum 
z512be7d538{z0646b897f1=(0xf89+2085-0x172e),z34b2888246=(0x2e3+7047-0x1e2a),
ze41428c42e=(0x534+8211-0x2527),zcee642872d=(0x94c+1377-0xe9d),z94508ce501=
(0xf15+4651-0x2131)};enum Attributes{z53da6e1be7=(0x152d+3383-0x2264),
PrimaryMessage,z7d1e0a89c4,z5efc427619,zf44631336d};};}}}
#endif 

