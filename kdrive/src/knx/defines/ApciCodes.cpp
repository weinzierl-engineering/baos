
#include "pch/kdrive_pch.h"
#include "kdrive/knx/defines/ApciCodes.h"
using namespace kdrive::knx;namespace{bool zb65825df47(unsigned short 
zd44ef4c68e){const unsigned int z013ff1c8bc=(0x2207+303-0x1f3e);const unsigned 
int zb29f3eec7f=(0x1ddc+1599-0x229b);const unsigned int zb40ce52370=
(0xa74+2788-0x1398);const unsigned int zb04fc344c6=(zd44ef4c68e&z013ff1c8bc);
const bool z439356e3aa=((zb04fc344c6==zb29f3eec7f)||(zb04fc344c6==zb40ce52370))?
true:false;return z439356e3aa;}}bool z0e6afe5f14::z36aedae3b0(unsigned short 
z3350356cdc){switch(z3350356cdc&z0a14389825){case z209e0371cf:case z7b5414db5f:
case z441c1beace:case z6b54ad6766:case ze5fe2b0df9:case z43182f060d:case 
z0339fcdfd4:return true;case zb6868b4bbd:case zb9f131b6d0:return zb65825df47(
z3350356cdc)?true:false;default:return false;};}
