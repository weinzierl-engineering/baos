
#include "pch/kdrive_pch.h"
#include "kdrive/knx/telegrams/formatters/ExtendedControlField.h"
#include "kdrive/knx/defines/ControlField2.h"
#include <boost/assert.hpp>
using namespace kdrive::knx;z7f3b1fd12c::z7f3b1fd12c():zdd7ec172a0(AddressType::
z3e51bf884f),z5d633fa4fa((0x179d+2139-0x1ff2)),zc8f8c890de(z601f186a16){}
z7f3b1fd12c::~z7f3b1fd12c(){}std::size_t z7f3b1fd12c::size()const{return Size;}
bool z7f3b1fd12c::isValid()const{return true;}void z7f3b1fd12c::setDefaults(){
AbstractFormatter::setDefaults();zdd7ec172a0=AddressType::z3e51bf884f;
z5d633fa4fa=(0x1ad+6648-0x1b9f);zc8f8c890de=z601f186a16;}void z7f3b1fd12c::set(
unsigned char controlField){zdd7ec172a0=(controlField&zf840a35990)>>
(0xe6f+6028-0x25f4);z5d633fa4fa=(controlField&z7c64e75d76)>>(0x1aca+3054-0x26b4)
;zc8f8c890de=controlField&ze3f1653f0c;}unsigned char z7f3b1fd12c::get()const{
unsigned char controlField=(0x1033+3861-0x1f48);controlField|=(zdd7ec172a0<<
(0xeef+1591-0x151f))&zf840a35990;controlField|=(z5d633fa4fa<<(0xe42+1384-0x13a6)
)&z7c64e75d76;controlField|=zc8f8c890de&ze3f1653f0c;return controlField;}void 
z7f3b1fd12c::zfef6804589(unsigned char z90de16d7da){BOOST_ASSERT(((zdd7ec172a0<<
(0x2079+605-0x22cf))&~zf840a35990)==(0xc+2932-0xb80));zdd7ec172a0=z90de16d7da;}
unsigned char z7f3b1fd12c::zfc5016f8e0()const{return zdd7ec172a0;}bool 
z7f3b1fd12c::z088b874fc9()const{return(zdd7ec172a0==AddressType::z3e51bf884f);}
bool z7f3b1fd12c::ze25425cb88()const{return!z088b874fc9();}void z7f3b1fd12c::
zc5845415f8(unsigned char z5cde7031d2){BOOST_ASSERT(((z5d633fa4fa<<
(0x1592+2944-0x210e))&~z7c64e75d76)==(0x16da+2439-0x2061));z5d633fa4fa=
z5cde7031d2;}unsigned char z7f3b1fd12c::ze85f31fba4()const{return z5d633fa4fa;}
void z7f3b1fd12c::z222d82c49b(unsigned char zf799fec5b6){BOOST_ASSERT((
zc8f8c890de&~ze3f1653f0c)==(0x111a+3598-0x1f28));zc8f8c890de=zf799fec5b6;}
unsigned char z7f3b1fd12c::z83d73bc9c9()const{return zc8f8c890de;}std::size_t 
z7f3b1fd12c::readImpl(const Buffer&buffer){set(buffer.z02b8347997(
(0xe4+2106-0x91e)));return size();}std::size_t z7f3b1fd12c::writeImpl(Buffer&
buffer){buffer.zb8203d7346((0x1cb+7133-0x1da8),get());return size();}
