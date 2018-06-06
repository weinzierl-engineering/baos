
#ifndef z2f76a78a94
#define z2f76a78a94
#include "kdrive/knx/Config.h"
#include "kdrive/knx/defines/CemiCodes.h"
#include "kdrive/knx/telegrams/formatters/AbstractFrame.h"
#include "kdrive/knx/telegrams/formatters/ControlField.h"
#include "kdrive/knx/telegrams/formatters/ExtendedControlField.h"
#include "kdrive/knx/telegrams/cemi/AdditionalInfo.h"
#include <vector>
namespace kdrive{namespace knx{namespace cemi{class zfa304e8ec3;class 
z91680f515b Frame:public zb6eb8808c0{public:virtual~Frame();void setDefaults()
override;void z1d82003342(const std::vector<unsigned char>&z75aff836ba);const 
std::vector<unsigned char>&zfd5c03b75a()const;void z77d825fd88(unsigned char 
z35a951ea12);unsigned char zb10c293b39()const;void z1ad3842a90(unsigned char 
z9557a26474);unsigned char z2b7c7a9243()const;void z93a0e900e9(unsigned char 
z030213cd03);unsigned char zbe18e5ae86()const;void zfae4668299(unsigned char 
zedd172d966);unsigned char z0336eaae40()const;bool z6507326b0b()const;bool 
z2fee7808b2()const;void z5a4cf0bd20(unsigned char zc9c0819fa9);unsigned char 
z946dc3a4d1()const;bool z555597b57f()const;bool isBroadcast()const;void 
z222d82c49b(unsigned char zf799fec5b6);unsigned char z83d73bc9c9()const;int 
zbb95a510c1()const;protected:Frame();void z87c4e77298()override;private:void 
z442da0cbec()override;void zdcb70f7c70(unsigned char length)override;unsigned 
char z7599d207db()const override;void z56ae94b385(unsigned char z07310dab6b)
override;unsigned char z8a4104cb0d()const override;void setPriorityImpl(unsigned
 char priority)override;unsigned char getPriorityImpl()const override;void 
za230b1de4b(unsigned char zc5aeda9f96)override;unsigned char z151bac17b2()const 
override;void z1f0cb92727(unsigned char z7e658739a1)override;unsigned char 
z4d9c03f095()const override;void za662e0c766(unsigned char z90de16d7da)override;
unsigned char z0ea5925a1b()const override;void z3b48f4fbce(unsigned char 
z5cde7031d2)override;unsigned char zc0f4a59344()const override;private:
zfa304e8ec3 za14fd0e9bd;ControlField z5b3a8175da;z7f3b1fd12c z236d788078;
ByteFormatter z4eb8aff455;};z91680f515b void z11aab8119f(const Frame&frame,std::
vector<unsigned char>&zd311e7ca26);typedef zc61eee6dc0<Frame,(0x8da+1802-0xfe4),
true,false>ze5f61a7065;typedef zc61eee6dc0<Frame,z5b8ac31779::z31637e39f8,true>
zb63199b615;typedef zc61eee6dc0<Frame,z5b8ac31779::zcb37dec9d5,true>z5655d09358;
typedef zc61eee6dc0<Frame,z5b8ac31779::z7b7674982a,true>z7c55b16331;}}}
#endif 

