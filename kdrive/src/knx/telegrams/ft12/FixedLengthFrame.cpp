
#include "pch/kdrive_pch.h"
#include "kdrive/knx/telegrams/ft12/FixedLengthFrame.h"
#include "kdrive/knx/defines/FT12Constants.h"
using namespace kdrive::knx::ft12;FixedLengthFrame::FixedLengthFrame(bool 
z555d494b60):z7b24692d08(z555d494b60){addFormatter(&z318af989c1);addFormatter(&
z5930a43bb3);addFormatter(&zb6fd1245b5);addFormatter(&z5595af419d);}
FixedLengthFrame::~FixedLengthFrame(){}bool FixedLengthFrame::isValid()const{
return((zf538d46467()==FT12Constants::StartFixedLengthFrame)&&z8bb5df7389()&&(
z8ca4a7d491()==FT12Constants::EndFrame));}void FixedLengthFrame::setDefaults(){
z318af989c1.set(FT12Constants::StartFixedLengthFrame);z5930a43bb3.set(
(0x75+6926-0x1b83));zb6fd1245b5.set((0x1556+10-0x1560));z5595af419d.set(
FT12Constants::EndFrame);}unsigned char FixedLengthFrame::zf538d46467()const{
return z318af989c1.get();}void FixedLengthFrame::setControlField(unsigned char 
controlField){z5930a43bb3.set(controlField);if(z7b24692d08){z5205ffbfd7(
controlField);}}unsigned char FixedLengthFrame::getControlField()const{return 
z5930a43bb3.get();}void FixedLengthFrame::z5205ffbfd7(unsigned char checksum){
zb6fd1245b5.set(checksum);}unsigned char FixedLengthFrame::z458c6172ca()const{
return zb6fd1245b5.get();}bool FixedLengthFrame::z8bb5df7389()const{return(
getControlField()==z458c6172ca());}unsigned char FixedLengthFrame::z8ca4a7d491()
const{return z5595af419d.get();}
