
#include "pch/kdrive_pch.h"
#include "kdrive/knx/telegrams/cemi/RfAdditionalInfo.h"
using namespace kdrive::knx;using namespace kdrive::knx::cemi;z7a67187a0a::
z7a67187a0a(){addFormatter(&zff3b419262);addFormatter(&z4bd60052e2);addFormatter
(&z24086b7caf);addFormatter(&z8a729e8447);addFormatter(&z1261f544f8);}
z7a67187a0a::~z7a67187a0a(){}bool z7a67187a0a::isValid()const{return(zbfd7d2bb9b
()==TypeId)&&(getLength()==Length);}void z7a67187a0a::setDefaults(){Formatter::
setDefaults();zff3b419262.set(TypeId);z4bd60052e2.set(Length);}unsigned char 
z7a67187a0a::zbfd7d2bb9b()const{return zff3b419262.get();}unsigned char 
z7a67187a0a::getLength()const{return z4bd60052e2.get();}void z7a67187a0a::
ze08fc529a9(unsigned char zee6bb9ea1d){z24086b7caf.set(zee6bb9ea1d);}unsigned 
char z7a67187a0a::z0d337d47d5()const{return z24086b7caf.get();}void z7a67187a0a
::setAddress(const std::vector<unsigned char>&address){z8a729e8447.set(address);
}std::vector<unsigned char>z7a67187a0a::getAddress()const{return z8a729e8447.get
();}void z7a67187a0a::zf7a93e33ac(unsigned char zf5c66aa14d){z1261f544f8.set(
zf5c66aa14d);}unsigned char z7a67187a0a::z0821ada427()const{return z1261f544f8.
get();}
