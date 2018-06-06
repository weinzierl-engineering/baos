
#include "pch/kdrive_pch.h"
#include "kdrive/access/core/details/TelegramWaitPolicy.h"
#include "kdrive/knx/telegrams/formatters/Formatter.h"
#include "kdrive/knx/core/Buffer.h"
#include "kdrive/connector/Packet.h"
#include "kdrive/connector/Connector.h"
using namespace kdrive::access;using namespace kdrive::connector;using namespace
 kdrive::knx;zd630f842fc::zd630f842fc(Connector&connector,AbstractFormatter&
formatter):zba3640e977(connector),z9906b42391(formatter){}Packet::Ptr 
zd630f842fc::operator()(unsigned long timeout){ze48348d435::Formatters 
formatters;formatters.push_back(&z9906b42391);ze48348d435 policy(zba3640e977,
formatters);return policy(timeout);}ze48348d435::ze48348d435(Connector&connector
,const Formatters&formatters):zba3640e977(connector),zafc83905ab(formatters){}
Packet::Ptr ze48348d435::operator()(unsigned long timeout){Packet::Ptr packet=
zba3640e977.waitReceive(timeout);Packet::Buffer&buffer=packet->getBuffer();for(
AbstractFormatter*formatter:zafc83905ab){try{formatter->read(buffer);if(
formatter->isValid()){return packet;}}catch(...){}}packet.reset();return packet;
}
