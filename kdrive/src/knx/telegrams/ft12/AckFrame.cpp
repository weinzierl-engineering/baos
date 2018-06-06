
#include "pch/kdrive_pch.h"
#include "kdrive/knx/telegrams/ft12/AckFrame.h"
#include "kdrive/knx/defines/FT12Constants.h"
using namespace kdrive::knx::ft12;AckFrame::AckFrame(){setDefaults();}AckFrame::
~AckFrame(){}bool AckFrame::isValid()const{return get()==FT12Constants::AckFrame
?true:false;}void AckFrame::setDefaults(){set(FT12Constants::AckFrame);}
