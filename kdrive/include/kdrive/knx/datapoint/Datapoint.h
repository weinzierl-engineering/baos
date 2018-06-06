
#ifndef zba1daac698
#define zba1daac698
#include "kdrive/knx/Config.h"
#include "kdrive/utility/PropertyCollection.h"
#include <vector>
#include <string>
namespace kdrive{namespace knx{class z91680f515b Datapoint:public kdrive::
utility::PropertyCollection{public:Datapoint();Datapoint(const std::string id,
const std::string&number,const std::string&name,const std::string&text,const std
::string&z8af7e44e6c);Datapoint(const Datapoint&datapoint);virtual~Datapoint();
Datapoint&operator=(const Datapoint&datapoint);const std::string&zebc3066335()
const;int z697f86f0e1()const;const std::string&getName()const;const std::string&
getText()const;int zb773295431()const;int getSizeInBytes()const;const std::
vector<unsigned char>&getData()const;void setData(const std::vector<unsigned 
char>&data);public:static const std::string Id;static const std::string Number;
static const std::string Name;static const std::string Text;static const std::
string z564c074eac;static const std::string Data;enum z892c95fbd3{z3af9cf42ac=
(0x106a+610-0x12cb),z208354ba84=(0x1c46+2255-0x2513),z4253f448e6=
(0x1ead+867-0x220c),ze0aa40038d=(0x2b4+3823-0x119b),z2fe08c593e=
(0x7d2+7866-0x2684),z3686c11cbf=(0x21e4+1172-0x2670),ze9946e9494=
(0x5ba+2634-0xff4),zeb63e130eb=(0xc0c+873-0xf65),z01b67e3347=(0x2a4+9120-0x2634)
,z695a8e6747=(0x14c8+126-0x152e),zfc115889dd=(0x432+7562-0x21a4),z4e6ebc8170=
(0x1206+1257-0x16cf),z1f6dd941cc=(0x12d2+1427-0x1845),zbce9826f7f=
(0x9b3+7382-0x2669),z18dd853cd9=(0x377+5301-0x180c),z9cb9613e5c=(0xba1+1-0xb32),
zd432a47453=(0xad2+3973-0x1a3f)};private:const std::string&z3c6aa0de0f(const std
::string&key)const;int getSizeInBytes(int z5e1f916d4c)const;};z91680f515b void 
z6bf2f75cea(Datapoint&datapoint,bool value);z91680f515b bool decode_DPT1(const 
Datapoint&datapoint);z91680f515b void encode_DPT2(Datapoint&datapoint,bool 
zaadaf6ab23,bool value);z91680f515b void decode_DPT2(const Datapoint&datapoint,
bool&zaadaf6ab23,bool&value);z91680f515b void encode_DPT3(Datapoint&datapoint,
bool zaadaf6ab23,unsigned char value);z91680f515b void decode_DPT3(const 
Datapoint&datapoint,bool&zaadaf6ab23,unsigned char&value);z91680f515b void 
encode_DPT4(Datapoint&datapoint,unsigned char value);z91680f515b unsigned char 
decode_DPT4(const Datapoint&datapoint);z91680f515b void encode_DPT5(Datapoint&
datapoint,unsigned char value);z91680f515b unsigned char decode_DPT5(const 
Datapoint&datapoint);z91680f515b void encode_DPT6(Datapoint&datapoint,char value
);z91680f515b signed char decode_DPT6(const Datapoint&datapoint);z91680f515b 
void encode_DPT7(Datapoint&datapoint,unsigned short value);z91680f515b unsigned 
short decode_DPT7(const Datapoint&datapoint);z91680f515b void encode_DPT8(
Datapoint&datapoint,short value);z91680f515b signed short decode_DPT8(const 
Datapoint&datapoint);z91680f515b void encode_DPT9_Raw(Datapoint&datapoint,
unsigned char zba1cbc76ee,unsigned char z68419f84d9);z91680f515b void 
encode_DPT9(Datapoint&datapoint,float f);z91680f515b unsigned short 
decode_DPT9_Raw(const Datapoint&datapoint);z91680f515b float decode_DPT9(const 
Datapoint&datapoint);z91680f515b void encode_DPT10_Local(Datapoint&datapoint);
z91680f515b void encode_DPT10_UTC(Datapoint&datapoint);z91680f515b void 
encode_DPT10(Datapoint&datapoint,int day,int hour,int minute,int second);
z91680f515b void decode_DPT10(const Datapoint&datapoint,int&day,int&hour,int&
minute,int&second);z91680f515b void encode_DPT11_Local(Datapoint&datapoint);
z91680f515b void encode_DPT11_UTC(Datapoint&datapoint);z91680f515b void 
zdf135c0fa0(Datapoint&datapoint,int year,int month,int day);z91680f515b void 
encode_DPT11_knx(Datapoint&datapoint,int year,int month,int day);z91680f515b 
void z800ccce10f(Datapoint&datapoint,int year,int month,int day);z91680f515b 
void decode_DPT11(const Datapoint&datapoint,int&year,int&month,int&day);
z91680f515b void decode_DPT11_knx(const Datapoint&datapoint,int&year,int&month,
int&day);z91680f515b void z4d7301ebb3(const Datapoint&datapoint,int&year,int&
month,int&day);z91680f515b void encode_DPT12(Datapoint&datapoint,unsigned int 
value);z91680f515b unsigned int decode_DPT12(const Datapoint&datapoint);
z91680f515b void encode_DPT13(Datapoint&datapoint,int value);z91680f515b signed 
int decode_DPT13(const Datapoint&datapoint);z91680f515b void encode_DPT14(
Datapoint&datapoint,float f);z91680f515b float decode_DPT14(const Datapoint&
datapoint);z91680f515b void encode_DPT15(Datapoint&datapoint,unsigned int 
z7c361264d7,bool error,bool z3a4ce83def,bool zbadde329ec,bool zeb54d212c0,
unsigned char index);z91680f515b void decode_DPT15(const Datapoint&datapoint,
unsigned int&z7c361264d7,bool&error,bool&z3a4ce83def,bool&zbadde329ec,bool&
zeb54d212c0,unsigned char&index);z91680f515b void encode_DPT16(Datapoint&
datapoint,const std::string&str);z91680f515b std::string decode_DPT16(const 
Datapoint&datapoint);z91680f515b void z2c0e220f97(Datapoint&datapoint,unsigned 
char zeec3b2b0b5);z91680f515b unsigned char z22d5a8ab0f(const Datapoint&
datapoint);z91680f515b void zba071ade45(Datapoint&datapoint,bool zaadaf6ab23,
unsigned char zeec3b2b0b5);z91680f515b void z8015252426(const Datapoint&
datapoint,bool&zaadaf6ab23,unsigned char&zeec3b2b0b5);z91680f515b void 
z5e7b87bb95(Datapoint&datapoint,unsigned char r,unsigned char g,unsigned char b)
;z91680f515b void zc61cae9601(const Datapoint&datapoint,unsigned char&r,unsigned
 char&g,unsigned char&b);}}
#endif 

