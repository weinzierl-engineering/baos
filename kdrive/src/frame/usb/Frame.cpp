
#include "pch/kdrive_pch.h"
#include "kdrive/frame/usb/Frame.h"
#include "kdrive/frame/usb/Telegrams.h"
#include "kdrive/frame/core/Buffer.h"
#include "kdrive/utility/PropertyCollection.h"
using namespace kdrive::frame;using namespace kdrive::frame::usb;using kdrive::
utility::PropertyCollection;bool kdrive::frame::usb::isValid(const Buffer&
z702ae9c390){bool valid=false;if(z702ae9c390.getSize()==z6176029ec5::zd4f8e67a0d
){const z6176029ec5 z55d05b1de0(z702ae9c390.z8d79a69692(),z702ae9c390.getSize(),
false);if((z55d05b1de0.zf259b97dbd()==(0x79c+2003-0xf6e))&&(z55d05b1de0.
zbe81e74e90()>=Frame::z9dd47b9cb0)&&(z55d05b1de0.zbe81e74e90()<=Frame::
za0776c6ea8)&&(z55d05b1de0.zcb2c7e6f21()>=Frame::z36ea2f3727)&&(z55d05b1de0.
zcb2c7e6f21()<=Frame::zf23ff3b732)&&(z55d05b1de0.zf1e6344a84()>=
(0xe85+1283-0x1387))&&(z55d05b1de0.zf1e6344a84()<=z6176029ec5::zf08419cb5d)){
valid=true;}}return valid;}void kdrive::frame::usb::zffac4ee2ab(
PropertyCollection&z44aa351fb2,const Buffer&z702ae9c390){const z6176029ec5 
z55d05b1de0(z702ae9c390.z8d79a69692(),z702ae9c390.getSize(),false);if(
z55d05b1de0.zbe81e74e90()==(0x154+3832-0x104b)){const zadbe67dd03 zbd3df6d0b8(
z702ae9c390.z8d79a69692(),z702ae9c390.getSize(),false);zbd3df6d0b8.zffac4ee2ab(
z44aa351fb2);}else{const z48f475a642 z844324262e(z702ae9c390.z8d79a69692(),
z702ae9c390.getSize(),false);z844324262e.zffac4ee2ab(z44aa351fb2);}}
