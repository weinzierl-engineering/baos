
#include "pch/kdrive_pch.h"
#include "kdrive/access/core/details/RfDomainAddressFilter.h"
#include "kdrive/access/core/KnxPacket.h"
#include "kdrive/knx/defines/CemiCodes.h"
#include "kdrive/knx/telegrams/formatters/Telegram.h"
#include "kdrive/knx/telegrams/cemi/Frame.h"
#include "kdrive/knx/telegrams/cemi/RfAdditionalInfo.h"
#include "kdrive/utility/Logger.h"
#include <Poco/Exception.h>
#include <Poco/Logger.h>
using namespace kdrive::access;using kdrive::knx::z2a66522423;using kdrive::knx
::cemi::z5b8ac31779;using kdrive::knx::cemi::z7c55b16331;using kdrive::knx::cemi
::z7a67187a0a;using Poco::Exception;CLASS_LOGGER(
"\x6b\x6e\x78\x2e\x61\x63\x63\x65\x73\x73\x2e\x52\x66\x44\x6f\x6d\x61\x69\x6e\x41\x64\x64\x72\x65\x73\x73\x46\x69\x6c\x74\x65\x72"
)namespace{bool z37f5d68883(const KnxPacket::Ptr packet,z7c55b16331&z702ae9c390)
{try{z2a66522423 frame;frame.read(packet->getBuffer());if(frame.z6b11bcce77()==
z5b8ac31779::z7b7674982a){z702ae9c390.read(packet->getBuffer());return 
z702ae9c390.isValid();}}catch(Exception&e){poco_warning(LOGGER(),e.displayText()
);}return false;}bool z01b99c74a5(const z7c55b16331&z702ae9c390,z7a67187a0a&
z9b04aba9ea){try{if(z702ae9c390.zb10c293b39()>=z9b04aba9ea.size()){std::vector<
unsigned char>z75aff836ba=z702ae9c390.zfd5c03b75a();z9b04aba9ea.read(z75aff836ba
);return z9b04aba9ea.isValid();}}catch(Exception&e){poco_warning(LOGGER(),e.
displayText());}return false;}}bool z2429a4bade::zd47ebe7a90(const KnxPacket::
Ptr packet,const std::vector<unsigned char>&zf92894300e){z7c55b16331 z702ae9c390
;z7a67187a0a z9b04aba9ea;if(!z37f5d68883(packet,z702ae9c390)||!z01b99c74a5(
z702ae9c390,z9b04aba9ea)){return true;}if(z702ae9c390.z555597b57f()||(
z9b04aba9ea.getAddress()==zf92894300e)){return true;}return false;}
