
#include "pch/kdrive_pch.h"
#include "kdrive/knx/core/AddressTranslator.h"
#include <Poco/Exception.h>
#include <Poco/String.h>
#include <Poco/NumberParser.h>
#include <Poco/NumberFormatter.h>
#include <Poco/StringTokenizer.h>
#include <iterator>
using Poco::translate;using Poco::Exception;using Poco::NumberParser;using Poco
::NumberFormatter;using Poco::StringTokenizer;using namespace kdrive::knx;
namespace{unsigned int z16820c8421(unsigned int z905237f00d){return((z905237f00d
&63488)>>(0x1710+3780-0x25c9));}unsigned int z62a0e9628c(unsigned int 
z905237f00d){return(z905237f00d&(0x1d0b+3752-0x23b4));}unsigned int zd759dfb947(
unsigned int za8cb85e695,unsigned int z3634fd4b4a){return(((za8cb85e695&
(0x390+5206-0x17c7))<<(0xf18+1265-0x13fe))+(z3634fd4b4a&(0x1878+4838-0x235f)));}
bool z95d86195d5(unsigned int z4ed3a11b88){return(((z4ed3a11b88&~65535)!=
(0xa6f+4381-0x1b8c))?false:true);}bool zba7fe68576(unsigned int za8cb85e695,
unsigned int z3634fd4b4a){return((((za8cb85e695&~(0x16d0+3037-0x228e))!=
(0x1364+4733-0x25e1))||((z3634fd4b4a&~(0x1f0b+3674-0x2566))!=
(0x1127+2912-0x1c87)))?false:true);}bool zf84f8ec1ac(unsigned int z2964297872,
unsigned int zfef244f946,unsigned int zd285163723){return((((z2964297872&~
(0x1b31+2900-0x2666))!=(0x18a3+2479-0x2252))||((zfef244f946&~(0xdb7+5354-0x229a)
)!=(0x2062+1253-0x2547))||((zd285163723&~(0x11b+4017-0xfcd))!=(0x16a3+4-0x16a7))
)?false:true);}bool z9a3875aed3(unsigned int z4ed3a11b88){return(z4ed3a11b88<=
65535)?true:false;}bool zf67caf7717(unsigned int za8cb85e695,unsigned int 
z3634fd4b4a){return((za8cb85e695<=(0x827+4047-0x17d7))&&(z3634fd4b4a<=
(0xfd8+1951-0xf78)))?true:false;}bool z9399cdbc44(unsigned int z2964297872,
unsigned int zfef244f946,unsigned int zd285163723){return((z2964297872<=
(0xc74+5215-0x20b4))&&(zfef244f946<=(0xe4a+4460-0x1faf))&&(zd285163723<=
(0x149d+131-0x1421)))?true:false;}bool za3820ec500(unsigned int z93da87acb1){
return(((z93da87acb1&~65535)!=(0xc62+2433-0x15e3))?false:true);}bool zd763cd6314
(unsigned int z9a1e0d07db,unsigned int zdb1be7094d,unsigned int za453ba9d20){
return((((z9a1e0d07db&~(0x1a5f+412-0x1bec))!=(0x491+5048-0x1849))||((zdb1be7094d
&~(0x117+5881-0x1801))!=(0x46f+1507-0xa52))||((za453ba9d20&~(0x1671+1082-0x19ac)
)!=(0x1345+2915-0x1ea8)))?false:true);}bool z134ffd00ef(unsigned int z9a1e0d07db
,unsigned int zdb1be7094d,unsigned int za453ba9d20){return((z9a1e0d07db<=
(0x66c+6525-0x1fda))&&(zdb1be7094d<=(0xa78+2991-0x1618))&&(za453ba9d20<=
(0x12d+312-0x166)))?true:false;}}std::string zd50e757f97::z83886ba842(unsigned 
int address){z84e0846308 z78d89b0e90;return z78d89b0e90.z21c97a3e18(address,
z84e0846308::z6b1cd26923);}std::string zd50e757f97::z5a7d47b7b1(unsigned int 
address){z84e0846308 z78d89b0e90(true);return z78d89b0e90.z21c97a3e18(address,
z84e0846308::z6b1cd26923);}std::string zd50e757f97::formatHex(unsigned int 
address){z84e0846308 z78d89b0e90(true);return z78d89b0e90.z21c97a3e18(address,
z84e0846308::Hex);}unsigned int zb30da5c583::ze002111468(const std::string&
address){z84e0846308 z78d89b0e90;return z78d89b0e90.getInt(address);}unsigned 
int zb30da5c583::zc969471dba(const std::string&address){z84e0846308 z78d89b0e90(
true);return z78d89b0e90.getInt(address);}unsigned int zb30da5c583::parseHex(
const std::string&address){z84e0846308 z78d89b0e90(true);return z78d89b0e90.
getInt(address);}z84e0846308::z84e0846308(bool ze25425cb88):z600f0730bc(
ze25425cb88){}z84e0846308::~z84e0846308(){}unsigned int z84e0846308::getInt(
const std::string&zce35d6a054)const{const std::string join=z600f0730bc?"\x2f":
"\x2e";StringTokenizer zb5fe3c0b56(zce35d6a054,join,StringTokenizer::TOK_TRIM);
std::vector<std::string>parts;std::copy(zb5fe3c0b56.begin(),zb5fe3c0b56.end(),
std::back_inserter(parts));return z600f0730bc?z242a550188(parts):zd904b5934c(
parts);}bool z84e0846308::zedfb9625be(const std::string&zce35d6a054,unsigned int
&z1d6097b17a)const{try{z1d6097b17a=getInt(zce35d6a054);}catch(Exception&){return
 false;}return true;}std::string z84e0846308::z21c97a3e18(unsigned int 
z1d6097b17a,int zadd2990e72,bool zc09616a55e)const{switch(zadd2990e72){case Hex:
return NumberFormatter::formatHex(z1d6097b17a,(0x39b+7860-0x224b));case 
zeb5d9461a4:return z854487245a(z1d6097b17a);case z6b1cd26923:return z600f0730bc?
z2dbaaa8663(z1d6097b17a):z86b195e86d(z1d6097b17a,zc09616a55e);}throw Exception(
"\x55\x6e\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x64\x69\x73\x70\x6c\x61\x79\x20\x66\x6f\x72\x6d\x61\x74"
);}bool z84e0846308::z897b9597c4(unsigned int z1d6097b17a,int zadd2990e72,std::
string&zce35d6a054)const{try{zce35d6a054=z21c97a3e18(z1d6097b17a,zadd2990e72);}
catch(Exception&){return false;}return true;}void z84e0846308::z60c37a0521(bool 
z58e7a38156){z600f0730bc=z58e7a38156;}bool z84e0846308::ze25425cb88()const{
return z600f0730bc;}unsigned int z84e0846308::z242a550188(const std::vector<std
::string>&parts)const{unsigned int z1d6097b17a=(0x13d3+2814-0x1ed1);switch(parts
.size()){case(0xc4a+4049-0x1c1a):{z1d6097b17a=NumberParser::parseHex(parts[
(0xd20+5168-0x2150)]);if(!z95d86195d5(z1d6097b17a)||!z9a3875aed3(z1d6097b17a)){
throw Exception(
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x41\x64\x64\x72\x65\x73\x73\x20\x42\x79\x74\x65\x73"
);}}break;case(0x21d+1555-0x82e):{int za8cb85e695=NumberParser::parseUnsigned(
parts[(0x15bc+161-0x165d)]);int z3634fd4b4a=NumberParser::parseUnsigned(parts[
(0x2bf+7345-0x1f6f)]);if(!zba7fe68576(za8cb85e695,z3634fd4b4a)){throw Exception(
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x41\x64\x64\x72\x65\x73\x73\x20\x42\x79\x74\x65\x73"
);}if(!zf67caf7717(za8cb85e695,z3634fd4b4a)){throw Exception(
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x41\x64\x64\x72\x65\x73\x73");}z1d6097b17a=
zd759dfb947(za8cb85e695,z3634fd4b4a);}break;case(0x238f+696-0x2644):{int 
z2964297872=NumberParser::parseUnsigned(parts[(0x69+6666-0x1a73)]);int 
zfef244f946=NumberParser::parseUnsigned(parts[(0x163+4304-0x1232)]);int 
zd285163723=NumberParser::parseUnsigned(parts[(0x46f+1273-0x966)]);if(!
zf84f8ec1ac(z2964297872,zfef244f946,zd285163723)){throw Exception(
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x41\x64\x64\x72\x65\x73\x73\x20\x42\x79\x74\x65\x73"
);}if(!z9399cdbc44(z2964297872,zfef244f946,zd285163723)){throw Exception(
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x41\x64\x64\x72\x65\x73\x73");}z1d6097b17a=
z16d0bb0f01::z267d60d08e(z2964297872,zfef244f946,zd285163723);}break;default:
throw Exception(
"\x46\x6f\x72\x6d\x61\x74\x20\x6e\x6f\x74\x20\x72\x65\x63\x6f\x67\x6e\x69\x73\x65\x64"
);break;}return z1d6097b17a;}unsigned int z84e0846308::zd904b5934c(const std::
vector<std::string>&parts)const{unsigned int z1d6097b17a=(0x480+887-0x7f7);
switch(parts.size()){case(0x1330+3630-0x215d):{z1d6097b17a=NumberParser::
parseHex(parts[(0xbe7+4226-0x1c69)]);if(!za3820ec500(z1d6097b17a)){throw 
Exception(
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x41\x64\x64\x72\x65\x73\x73\x20\x42\x79\x74\x65\x73"
);}}break;case(0xa26+3333-0x1728):{int zb8871a6e21=NumberParser::parseUnsigned(
parts[(0xc4d+6339-0x2510)]);int line=NumberParser::parseUnsigned(parts[
(0x9aa+2005-0x117e)]);int device=NumberParser::parseUnsigned(parts[
(0xc23+6579-0x25d4)]);if(!zd763cd6314(zb8871a6e21,line,device)){throw Exception(
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x41\x64\x64\x72\x65\x73\x73\x20\x42\x79\x74\x65\x73"
);}z1d6097b17a=z16d0bb0f01::zbe00e8c303(zb8871a6e21,line,device);}break;default:
throw Exception(
"\x46\x6f\x72\x6d\x61\x74\x20\x6e\x6f\x74\x20\x72\x65\x63\x6f\x67\x6e\x69\x73\x65\x64"
);break;}if(!z134ffd00ef(z16d0bb0f01::ze026f9cffa(z1d6097b17a),z16d0bb0f01::
getLine(z1d6097b17a),z16d0bb0f01::getDevice(z1d6097b17a))){throw Exception(
"\x49\x6e\x76\x61\x6c\x69\x64\x20\x50\x68\x79\x73\x69\x63\x61\x6c\x20\x41\x64\x64\x72\x65\x73\x73"
);}return z1d6097b17a;}std::string z84e0846308::z854487245a(unsigned int 
z1d6097b17a)const{if(!z600f0730bc){throw Exception(
"\x55\x6e\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x66\x6f\x72\x6d\x61\x74");}int
 za8cb85e695=z16820c8421(z1d6097b17a);int z3634fd4b4a=z62a0e9628c(z1d6097b17a);
std::string str=NumberFormatter::format(za8cb85e695);str.append("\x2f");str.
append(NumberFormatter::format(z3634fd4b4a));return str;}std::string z84e0846308
::z2dbaaa8663(unsigned int z1d6097b17a)const{if(!z600f0730bc){throw Exception(
"\x55\x6e\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x66\x6f\x72\x6d\x61\x74");}int
 main=z16d0bb0f01::z1f8c7ce952(z1d6097b17a);int middle=z16d0bb0f01::z692168cb86(
z1d6097b17a);int zeb6c6bdfe2=z16d0bb0f01::z6e6696ea75(z1d6097b17a);std::string 
str=NumberFormatter::format(main);str.append("\x2f");str.append(NumberFormatter
::format(middle));str.append("\x2f");str.append(NumberFormatter::format(
zeb6c6bdfe2));return str;}std::string z84e0846308::z86b195e86d(unsigned int 
z1d6097b17a,bool zc09616a55e)const{if(z600f0730bc){throw Exception(
"\x55\x6e\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x66\x6f\x72\x6d\x61\x74");}int
 zb8871a6e21=z16d0bb0f01::ze026f9cffa(z1d6097b17a);int line=z16d0bb0f01::getLine
(z1d6097b17a);int device=z16d0bb0f01::getDevice(z1d6097b17a);std::string str;if(
zc09616a55e){str=NumberFormatter::format(zb8871a6e21,(0xa25+6665-0x242c));str.
append("\x2e");str.append(NumberFormatter::format(line,(0x1638+966-0x19fc)));str
.append("\x2e");str.append(NumberFormatter::format(device,(0x241c+266-0x2523)));
}else{str=NumberFormatter::format(zb8871a6e21);str.append("\x2e");str.append(
NumberFormatter::format(line));str.append("\x2e");str.append(NumberFormatter::
format(device));}return str;}unsigned int z16d0bb0f01::zbe00e8c303(unsigned int 
zb8871a6e21,unsigned int line,unsigned int device){return(((zb8871a6e21&
(0x266+2860-0xd83))<<(0x122d+1967-0x19d0))+((line&(0x7c1+4477-0x192f))<<
(0x48b+2123-0xcce))+(device&(0x22db+1285-0x26e1)));}unsigned int z16d0bb0f01::
ze026f9cffa(unsigned int address){return((address&61440)>>(0xa02+3470-0x1784));}
unsigned int z16d0bb0f01::getLine(unsigned int address){return((address&
(0x19b4+3239-0x175b))>>(0xf03+464-0x10cb));}unsigned int z16d0bb0f01::getDevice(
unsigned int address){return(address&(0xccf+5341-0x20ad));}unsigned int 
z16d0bb0f01::z267d60d08e(unsigned int main,unsigned int middle,unsigned int 
zeb6c6bdfe2){return(((main&(0xf08+2471-0x1890))<<(0x2db+6432-0x1bf0))+((middle&
(0x11a+2651-0xb6e))<<(0xe38+6132-0x2624))+(zeb6c6bdfe2&(0x1ea7+313-0x1ee1)));}
unsigned int z16d0bb0f01::z1f8c7ce952(unsigned int address){return((address&
63488)>>(0x1627+1356-0x1b68));}unsigned int z16d0bb0f01::z692168cb86(unsigned 
int address){return((address&(0xb4b+1631-0xaaa))>>(0x10d0+2029-0x18b5));}
unsigned int z16d0bb0f01::z6e6696ea75(unsigned int address){return(address&
(0xffc+2789-0x19e2));}
