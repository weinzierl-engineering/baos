
#include "pch/kdrive_pch.h"
#include "kdrive/knx/telegrams/formatters/SerialNumberFormatter.h"
using namespace kdrive::knx;z12caacb3c6::z12caacb3c6(){}z12caacb3c6::~
z12caacb3c6(){}std::size_t z12caacb3c6::size()const{return zc51b6ade54.
z6334f67583().size();}bool z12caacb3c6::isValid()const{return true;}void 
z12caacb3c6::setDefaults(){AbstractFormatter::setDefaults();z498f6d084e::
DataBuffer&z4b3281b3a0=zc51b6ade54.z6334f67583();z4b3281b3a0={{}};}void 
z12caacb3c6::set(const SerialNumber&zd311e7ca26){z5f5fd61d58(zd311e7ca26);}const
 z12caacb3c6::SerialNumber&z12caacb3c6::get()const{return getSerialNumber();}
void z12caacb3c6::z5f5fd61d58(const SerialNumber&zd311e7ca26){zc51b6ade54=
zd311e7ca26;}const z12caacb3c6::SerialNumber&z12caacb3c6::getSerialNumber()const
{return zc51b6ade54;}std::size_t z12caacb3c6::readImpl(const Buffer&buffer){
const unsigned char*ptr=buffer.z15e6bd8652((0x1244+1662-0x18c2),zc51b6ade54.
z6334f67583().size());zc51b6ade54=SerialNumber(ptr,zc51b6ade54.z6334f67583().
size());return zc51b6ade54.z6334f67583().size();}std::size_t z12caacb3c6::
writeImpl(Buffer&buffer){buffer.za213db16c9((0x1554+2884-0x2098),&zc51b6ade54.
z6334f67583().at((0x1cbf+1608-0x2307)),zc51b6ade54.z6334f67583().size());return 
zc51b6ade54.z6334f67583().size();}
