
#include "pch/kdrive_pch.h"
#include "kdrive/access/ldm/LinkLayerManagement.h"
#include "kdrive/access/core/KnxPort.h"
#include "kdrive/access/core/KnxPacket.h"
#include "kdrive/access/core/details/TelegramWaitPolicy.h"
#include "kdrive/knx/telegrams/cemi/Frame.h"
#include "kdrive/connector/Wait.h"
#include <vector>
using namespace kdrive::access;using namespace kdrive::connector;using kdrive::
knx::cemi::zb63199b615;void zaa4f795dda::z6eae11ab53(Connector&connector,
unsigned long timeout){zb63199b615 formatter;zd630f842fc policy(connector,
formatter);waitPacketWithPolicy<KnxPacket>(policy,timeout);}
