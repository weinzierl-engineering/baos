
#include "pch/kdrive_pch.h"
#include "kdrive/knx/telegrams/ft12/VariableLengthFrame.h"
#include "kdrive/knx/defines/FT12Constants.h"
#include <algorithm>
#include <numeric>
using namespace kdrive::knx::ft12;using kdrive::knx::Buffer;VariableLengthFrame
::VariableLengthFrame(){}VariableLengthFrame::~VariableLengthFrame(){}std::
size_t VariableLengthFrame::size()const{return HeaderLength+z14e0d1edf3.size()+
(0xecb+5300-0x237e);}bool VariableLengthFrame::isValid()const{return((
z5c1f42d812.get()==FT12Constants::StartVarLengthFrame)&&(z5595af419d.get()==
FT12Constants::EndFrame)&&(z979d270e80.get()==z86680312bc.get())&&(z979d270e80.
get()==(z14e0d1edf3.size()+(0x129f+2720-0x1d3e)))&&(zb6fd1245b5.get()==
zc69eabd572()));}void VariableLengthFrame::setDefaults(){z5c1f42d812.set(
FT12Constants::StartVarLengthFrame);z979d270e80.set((0x5fb+1818-0xd14));
z86680312bc.set((0x7a3+7409-0x2493));zb8718915ff.set(FT12Constants::
StartVarLengthFrame);z5930a43bb3.set((0x841+1222-0xd07));zb6fd1245b5.set(
(0xab8+379-0xc33));z5595af419d.set(FT12Constants::EndFrame);}unsigned char 
VariableLengthFrame::z43309a7992()const{return z5c1f42d812.get();}unsigned char 
VariableLengthFrame::z2042692c9b()const{return z979d270e80.get();}unsigned char 
VariableLengthFrame::z528afb8f77()const{return z86680312bc.get();}unsigned char 
VariableLengthFrame::z512ec18926()const{return zb8718915ff.get();}void 
VariableLengthFrame::setControlField(unsigned char controlField){z5930a43bb3.set
(controlField);}unsigned char VariableLengthFrame::getControlField()const{return
 z5930a43bb3.get();}void VariableLengthFrame::setUserData(const unsigned char*
buffer,std::size_t bufferSize){if(buffer&&bufferSize){z14e0d1edf3.resize(
bufferSize);std::copy(buffer,buffer+bufferSize,z14e0d1edf3.begin());}else{
z14e0d1edf3.clear();}}const std::vector<unsigned char>&VariableLengthFrame::
getUserData()const{return z14e0d1edf3;}void VariableLengthFrame::z5205ffbfd7(
unsigned char checksum){zb6fd1245b5.set(checksum);}unsigned char 
VariableLengthFrame::z458c6172ca()const{return zb6fd1245b5.get();}unsigned char 
VariableLengthFrame::z8ca4a7d491()const{return z5595af419d.get();}void 
VariableLengthFrame::setVariableAttributes(){const unsigned char length=
static_cast<unsigned char>(z14e0d1edf3.size())+(0xf24+779-0x122e);const unsigned
 char checkSum=zc69eabd572();z979d270e80.set(length);z86680312bc.set(length);
zb6fd1245b5.set(checkSum);}std::size_t VariableLengthFrame::readImpl(const 
Buffer&buffer){z5c1f42d812.set(buffer.z02b8347997(za7a197b82a));z979d270e80.set(
buffer.z02b8347997(Length1));z86680312bc.set(buffer.z02b8347997(Length2));
zb8718915ff.set(buffer.z02b8347997(StartByte2));z5930a43bb3.set(buffer.
z02b8347997(ControlField));const int z883553e471=z979d270e80.get()-
(0x91b+4334-0x1a08);const unsigned char*ptr=buffer.z15e6bd8652(zab2a784894,
z883553e471);setUserData(ptr,z883553e471);const int z125eac62a4=zf7d6122444();
zb6fd1245b5.set(buffer.z02b8347997(z125eac62a4));z5595af419d.set(buffer.
z02b8347997(z125eac62a4+(0x1123+1235-0x15f5)));return size();}std::size_t 
VariableLengthFrame::writeImpl(Buffer&buffer){buffer.zb8203d7346(za7a197b82a,
z5c1f42d812.get());buffer.zb8203d7346(Length1,z979d270e80.get());buffer.
zb8203d7346(Length2,z86680312bc.get());buffer.zb8203d7346(StartByte2,zb8718915ff
.get());buffer.zb8203d7346(ControlField,z5930a43bb3.get());if(!z14e0d1edf3.empty
()){buffer.za213db16c9(zab2a784894,&z14e0d1edf3.at((0x783+2054-0xf89)),
z14e0d1edf3.size());}const int z125eac62a4=zf7d6122444();buffer.zb8203d7346(
z125eac62a4,zb6fd1245b5.get());buffer.zb8203d7346(z125eac62a4+
(0x1b0+6037-0x1944),z5595af419d.get());return size();}unsigned char 
VariableLengthFrame::zc69eabd572()const{return std::accumulate(z14e0d1edf3.begin
(),z14e0d1edf3.end(),z5930a43bb3.get());}int VariableLengthFrame::zf7d6122444()
const{return Checksum+(z14e0d1edf3.size()-(0x9c6+6657-0x23c6));}
