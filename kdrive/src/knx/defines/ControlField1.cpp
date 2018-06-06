
#include "pch/kdrive_pch.h"
#include "kdrive/knx/defines/ControlField1.h"
using namespace kdrive::knx;std::string Priority::toString(const int priority){
switch(priority){case Normal:return"\x4e\x6f\x72\x6d\x61\x6c";case z1dc3094feb:
return"\x55\x72\x67\x65\x6e\x74";case System:return"\x53\x79\x73\x74\x65\x6d";
case Low:default:return"\x4c\x6f\x77";}}int Priority::z319b7d93d4(const std::
string&priority){if(priority=="\x4e\x6f\x72\x6d\x61\x6c"){return Normal;}else if
(priority=="\x55\x72\x67\x65\x6e\x74"){return z1dc3094feb;}else if(priority==
"\x53\x79\x73\x74\x65\x6d"){return System;}else{return Low;}}
