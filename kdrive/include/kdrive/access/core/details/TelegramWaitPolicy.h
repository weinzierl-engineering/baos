
#ifndef zbba72c1eb0
#define zbba72c1eb0
#include "kdrive/access/Config.h"
#include "kdrive/connector/Forwards.h"
#include <memory>
#include <vector>
namespace kdrive{namespace knx{struct AbstractFormatter;}}namespace kdrive{
namespace access{struct z23bd02551e zd630f842fc{zd630f842fc(kdrive::connector::
Connector&connector,kdrive::knx::AbstractFormatter&formatter);std::shared_ptr<
connector::Packet>operator()(unsigned long timeout);kdrive::connector::Connector
&zba3640e977;kdrive::knx::AbstractFormatter&z9906b42391;};struct z23bd02551e 
ze48348d435{typedef std::vector<kdrive::knx::AbstractFormatter*>Formatters;
ze48348d435(kdrive::connector::Connector&connector,const Formatters&formatters);
std::shared_ptr<connector::Packet>operator()(unsigned long timeout);kdrive::
connector::Connector&zba3640e977;const Formatters&zafc83905ab;};}}
#endif 

