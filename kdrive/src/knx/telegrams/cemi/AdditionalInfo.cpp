
#include "pch/kdrive_pch.h"
#include "kdrive/knx/telegrams/cemi/AdditionalInfo.h"
#include "kdrive/knx/core/Buffer.h"
using namespace kdrive::knx;using namespace kdrive::knx::cemi;zfa304e8ec3::
zfa304e8ec3(){}zfa304e8ec3::~zfa304e8ec3(){}std::size_t zfa304e8ec3::size()const
{return z57a7b7f644+z9118dc6ff1.size();}bool zfa304e8ec3::isValid()const{return 
true;}void zfa304e8ec3::setDefaults(){z9118dc6ff1.clear();}void zfa304e8ec3::
z539a137476(unsigned char length){z9118dc6ff1.resize(length,(0xa4f+3711-0x18ce))
;}unsigned char zfa304e8ec3::getLength()const{return z9118dc6ff1.size();}void 
zfa304e8ec3::setData(const std::vector<unsigned char>&data){z9118dc6ff1=data;}
const std::vector<unsigned char>&zfa304e8ec3::getData()const{return z9118dc6ff1;
}std::size_t zfa304e8ec3::readImpl(const Buffer&buffer){const unsigned char 
length=buffer.z02b8347997((0xd05+1906-0x1477));z539a137476(length);const 
unsigned int offset=z57a7b7f644;const unsigned char*bufferPtr=buffer.z15e6bd8652
(offset,length);std::copy(bufferPtr,bufferPtr+length,z9118dc6ff1.begin());return
 size();}std::size_t zfa304e8ec3::writeImpl(Buffer&buffer){const unsigned char 
length=getLength();buffer.zb8203d7346((0x11c3+1031-0x15ca),length);if(length){
const unsigned int offset=z57a7b7f644;buffer.za213db16c9(offset,&z9118dc6ff1.at(
(0x1f53+484-0x2137)),length);}return size();}
