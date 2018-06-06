
#include "pch/kdrive_pch.h"
#include "kdrive/frame/usb/Telegrams.h"
#include "kdrive/frame/usb/Frame.h"
#include "kdrive/frame/core/Exception.h"
#include "kdrive/utility/PropertyCollection.h"
using namespace kdrive::frame;using namespace kdrive::frame::usb;
#define z39bf8c3410(KEY, FN) try { z44aa351fb2.setProperty(KEY, FN); } catch (\
...) { z44aa351fb2.setProperty(KEY, "\x2d\x2d\x2d"); }
#define z6da2875b42(KEY, FN) try { z44aa351fb2.zab8fd3aaf6(KEY, FN); } catch (\
...) {}
z6176029ec5::z6176029ec5():Buffer(zd4f8e67a0d,zd4f8e67a0d){zd41c892f97(
(0xe2a+2670-0x1897));}z6176029ec5::z6176029ec5(value_type*ptr,size_type size,
bool z7e8450ecf2):Buffer(ptr,size,z7e8450ecf2){if(size<z6176029ec5::zd4f8e67a0d)
{throw BufferTooSmallException();}}void z6176029ec5::zd41c892f97(unsigned char 
z346260c7ff){Buffer::set((0xcda+4131-0x1cfd),z346260c7ff&(0x86c+1082-0xba7));}
unsigned char z6176029ec5::zf259b97dbd()const{return(Buffer::get(
(0x193c+1460-0x1ef0))&(0x1809+690-0x19bc));}void z6176029ec5::z12aeb820c7(
unsigned char z80e0f1c035){Buffer::z2e8f9b9806((0x231+5209-0x1689),
(0x12f9+3183-0x1f59)<<(0x1b06+1385-0x206b));Buffer::zcea3a3d899(
(0x33b+8918-0x2610),(z80e0f1c035&(0xa65+6231-0x22ad))<<(0x18ab+3677-0x2704));}
unsigned char z6176029ec5::zbe81e74e90()const{return((Buffer::get(
(0x4a0+6011-0x1c1a))>>(0x9df+4060-0x19b7))&(0x1f1b+286-0x202a));}void 
z6176029ec5::z5058692388(unsigned char z51f76ba943){Buffer::z2e8f9b9806(
(0x3bc+1465-0x974),(0x320+8985-0x262a));Buffer::zcea3a3d899((0x1962+1997-0x212e)
,z51f76ba943&(0x519+255-0x609));}unsigned char z6176029ec5::zcb2c7e6f21()const{
return(Buffer::get((0xcd3+6039-0x2469))&(0x223f+124-0x22ac));}void z6176029ec5::
z01729c5314(unsigned char z60e99e4156){Buffer::set((0x13b9+1480-0x197f),
z60e99e4156&(0x5df+6993-0x2031));}unsigned char z6176029ec5::zf1e6344a84()const{
return(Buffer::get((0xb7f+2332-0x1499))&(0xa5b+2183-0x11e3));}void z6176029ec5::
zce12240a1b(const Buffer&z28e0145df4){Buffer::setBuffer((0x1223+3207-0x1ea7),
(0xf2+3218-0xd47),z28e0145df4);}Buffer z6176029ec5::z76221cc199()const{return 
Buffer::getBuffer((0x990+5203-0x1de0),(0x2583+3-0x2549));}z6176029ec5::
z6176029ec5(const PropertyCollection&z44aa351fb2):Buffer(zd4f8e67a0d,zd4f8e67a0d
){zbd8e48604c(z44aa351fb2);}void z6176029ec5::zffac4ee2ab(PropertyCollection&
z44aa351fb2)const{Buffer::zffac4ee2ab(z44aa351fb2);z44aa351fb2.setProperty(
"\x66\x72\x61\x6d\x65\x2e\x70\x72\x6f\x74\x6f\x63\x6f\x6c","\x75\x73\x62");
z44aa351fb2.setProperty("\x66\x72\x61\x6d\x65\x2e\x6e\x61\x6d\x65",
"\x48\x49\x44\x52\x65\x70\x6f\x72\x74\x46\x72\x61\x6d\x65");z39bf8c3410(
"\x72\x65\x70\x6f\x72\x74\x5f\x69\x64",zf259b97dbd());z39bf8c3410(
"\x73\x65\x71\x75\x65\x6e\x63\x65\x5f\x6e\x75\x6d\x62\x65\x72",zbe81e74e90());
z39bf8c3410("\x70\x61\x63\x6b\x65\x74\x5f\x74\x79\x70\x65",zcb2c7e6f21());
z39bf8c3410("\x64\x61\x74\x61\x5f\x6c\x65\x6e\x67\x74\x68",zf1e6344a84());
z39bf8c3410("\x72\x65\x70\x6f\x72\x74\x5f\x62\x6f\x64\x79",z76221cc199().
zbaa3b4a6ca());}void z6176029ec5::zbd8e48604c(const PropertyCollection&
z44aa351fb2){zd41c892f97(z44aa351fb2.getProperty(
"\x72\x65\x70\x6f\x72\x74\x5f\x69\x64"));z12aeb820c7(z44aa351fb2.getProperty(
"\x73\x65\x71\x75\x65\x6e\x63\x65\x5f\x6e\x75\x6d\x62\x65\x72"));z5058692388(
z44aa351fb2.getProperty("\x70\x61\x63\x6b\x65\x74\x5f\x74\x79\x70\x65"));
z01729c5314(z44aa351fb2.getProperty(
"\x64\x61\x74\x61\x5f\x6c\x65\x6e\x67\x74\x68"));zce12240a1b(Buffer(z44aa351fb2.
getProperty("\x72\x65\x70\x6f\x72\x74\x5f\x62\x6f\x64\x79").extract<std::vector<
unsigned char> >()));}void z6176029ec5::zffac4ee2ab(PropertyCollection&
z44aa351fb2,unsigned char z346260c7ff,unsigned char z80e0f1c035,unsigned char 
z51f76ba943,unsigned char z60e99e4156,const Buffer&z28e0145df4){z44aa351fb2.
setProperty("\x72\x65\x70\x6f\x72\x74\x5f\x69\x64",z346260c7ff);z44aa351fb2.
setProperty("\x73\x65\x71\x75\x65\x6e\x63\x65\x5f\x6e\x75\x6d\x62\x65\x72",
z80e0f1c035);z44aa351fb2.setProperty(
"\x70\x61\x63\x6b\x65\x74\x5f\x74\x79\x70\x65",z51f76ba943);z44aa351fb2.
setProperty("\x64\x61\x74\x61\x5f\x6c\x65\x6e\x67\x74\x68",z60e99e4156);
z44aa351fb2.setProperty("\x72\x65\x70\x6f\x72\x74\x5f\x62\x6f\x64\x79",
z28e0145df4.zbaa3b4a6ca());}z48f475a642::z48f475a642():Buffer(zd4f8e67a0d,
zd4f8e67a0d){zd41c892f97((0x892+1180-0xd2d));}z48f475a642::z48f475a642(
value_type*ptr,size_type size,bool z7e8450ecf2):Buffer(ptr,size,z7e8450ecf2){if(
size<z48f475a642::zd4f8e67a0d){throw BufferTooSmallException();}}void 
z48f475a642::zd41c892f97(unsigned char z346260c7ff){Buffer::set(
(0x1129+3722-0x1fb3),z346260c7ff&(0x710+521-0x81a));}unsigned char z48f475a642::
zf259b97dbd()const{return(Buffer::get((0xf12+1459-0x14c5))&(0x2430+116-0x23a5));
}void z48f475a642::z12aeb820c7(unsigned char z80e0f1c035){Buffer::z2e8f9b9806(
(0x980+1553-0xf90),(0x3dc+6110-0x1bab)<<(0x12f7+2434-0x1c75));Buffer::
zcea3a3d899((0xd87+2848-0x18a6),(z80e0f1c035&(0x140+114-0x1a3))<<
(0x1523+4339-0x2612));}unsigned char z48f475a642::zbe81e74e90()const{return((
Buffer::get((0x401+8566-0x2576))>>(0x16c6+3079-0x22c9))&(0x58a+5127-0x1982));}
void z48f475a642::z5058692388(unsigned char z51f76ba943){Buffer::z2e8f9b9806(
(0xac1+5037-0x1e6d),(0xb84+5997-0x22e2));Buffer::zcea3a3d899((0x728+3255-0x13de)
,z51f76ba943&(0x676+8310-0x26dd));}unsigned char z48f475a642::zcb2c7e6f21()const
{return(Buffer::get((0x6c+3970-0xfed))&(0xb79+6194-0x239c));}void z48f475a642::
z01729c5314(unsigned char z60e99e4156){Buffer::set((0x18f+8928-0x246d),
z60e99e4156&(0x3df+8675-0x24c3));}unsigned char z48f475a642::zf1e6344a84()const{
return(Buffer::get((0x11f+122-0x197))&(0xed0+5991-0x2538));}void z48f475a642::
zce12240a1b(const Buffer&z28e0145df4){Buffer::setBuffer((0x1815+3538-0x25e4),
(0xee1+2160-0x1714),z28e0145df4);}Buffer z48f475a642::z76221cc199()const{return 
Buffer::getBuffer((0x19eb+875-0x1d53),(0x1531+1391-0x1a63));}z48f475a642::
z48f475a642(const PropertyCollection&z44aa351fb2):Buffer(zd4f8e67a0d,zd4f8e67a0d
){zbd8e48604c(z44aa351fb2);}void z48f475a642::zffac4ee2ab(PropertyCollection&
z44aa351fb2)const{Buffer::zffac4ee2ab(z44aa351fb2);z44aa351fb2.setProperty(
"\x66\x72\x61\x6d\x65\x2e\x70\x72\x6f\x74\x6f\x63\x6f\x6c","\x75\x73\x62");
z44aa351fb2.setProperty("\x66\x72\x61\x6d\x65\x2e\x6e\x61\x6d\x65",
"\x48\x49\x44\x52\x65\x70\x6f\x72\x74\x46\x72\x61\x6d\x65\x50\x61\x72\x74\x69\x61\x6c"
);z39bf8c3410("\x72\x65\x70\x6f\x72\x74\x5f\x69\x64",zf259b97dbd());z39bf8c3410(
"\x73\x65\x71\x75\x65\x6e\x63\x65\x5f\x6e\x75\x6d\x62\x65\x72",zbe81e74e90());
z39bf8c3410("\x70\x61\x63\x6b\x65\x74\x5f\x74\x79\x70\x65",zcb2c7e6f21());
z39bf8c3410("\x64\x61\x74\x61\x5f\x6c\x65\x6e\x67\x74\x68",zf1e6344a84());
z39bf8c3410("\x72\x65\x70\x6f\x72\x74\x5f\x62\x6f\x64\x79",z76221cc199().
zbaa3b4a6ca());}void z48f475a642::zbd8e48604c(const PropertyCollection&
z44aa351fb2){zd41c892f97(z44aa351fb2.getProperty(
"\x72\x65\x70\x6f\x72\x74\x5f\x69\x64"));z12aeb820c7(z44aa351fb2.getProperty(
"\x73\x65\x71\x75\x65\x6e\x63\x65\x5f\x6e\x75\x6d\x62\x65\x72"));z5058692388(
z44aa351fb2.getProperty("\x70\x61\x63\x6b\x65\x74\x5f\x74\x79\x70\x65"));
z01729c5314(z44aa351fb2.getProperty(
"\x64\x61\x74\x61\x5f\x6c\x65\x6e\x67\x74\x68"));zce12240a1b(Buffer(z44aa351fb2.
getProperty("\x72\x65\x70\x6f\x72\x74\x5f\x62\x6f\x64\x79").extract<std::vector<
unsigned char> >()));}void z48f475a642::zffac4ee2ab(PropertyCollection&
z44aa351fb2,unsigned char z346260c7ff,unsigned char z80e0f1c035,unsigned char 
z51f76ba943,unsigned char z60e99e4156,const Buffer&z28e0145df4){z44aa351fb2.
setProperty("\x72\x65\x70\x6f\x72\x74\x5f\x69\x64",z346260c7ff);z44aa351fb2.
setProperty("\x73\x65\x71\x75\x65\x6e\x63\x65\x5f\x6e\x75\x6d\x62\x65\x72",
z80e0f1c035);z44aa351fb2.setProperty(
"\x70\x61\x63\x6b\x65\x74\x5f\x74\x79\x70\x65",z51f76ba943);z44aa351fb2.
setProperty("\x64\x61\x74\x61\x5f\x6c\x65\x6e\x67\x74\x68",z60e99e4156);
z44aa351fb2.setProperty("\x72\x65\x70\x6f\x72\x74\x5f\x62\x6f\x64\x79",
z28e0145df4.zbaa3b4a6ca());}zadbe67dd03::zadbe67dd03():Buffer(zd4f8e67a0d,
zd4f8e67a0d){zd41c892f97((0x11c1+5029-0x2565));}zadbe67dd03::zadbe67dd03(
value_type*ptr,size_type size,bool z7e8450ecf2):Buffer(ptr,size,z7e8450ecf2){if(
size<zadbe67dd03::zd4f8e67a0d){throw BufferTooSmallException();}}void 
zadbe67dd03::zd41c892f97(unsigned char z346260c7ff){Buffer::set(
(0x20c6+316-0x2202),z346260c7ff&(0x25d8+219-0x25b4));}unsigned char zadbe67dd03
::zf259b97dbd()const{return(Buffer::get((0x365+3919-0x12b4))&
(0x1219+2753-0x1bdb));}void zadbe67dd03::z12aeb820c7(unsigned char z80e0f1c035){
Buffer::z2e8f9b9806((0x1a2a+213-0x1afe),(0x6c0+3418-0x140b)<<(0xf5f+3834-0x1e55)
);Buffer::zcea3a3d899((0x1a85+1586-0x20b6),(z80e0f1c035&(0xec2+2323-0x17c6))<<
(0x5a6+7589-0x2347));}unsigned char zadbe67dd03::zbe81e74e90()const{return((
Buffer::get((0x471+3802-0x134a))>>(0xf80+4301-0x2049))&(0xf2b+4341-0x2011));}
void zadbe67dd03::z5058692388(unsigned char z51f76ba943){Buffer::z2e8f9b9806(
(0x81f+1231-0xced),(0x1df+7844-0x2074));Buffer::zcea3a3d899((0x1540+4076-0x252b)
,z51f76ba943&(0xac9+6725-0x24ff));}unsigned char zadbe67dd03::zcb2c7e6f21()const
{return(Buffer::get((0x1a35+986-0x1e0e))&(0x1ac8+666-0x1d53));}void zadbe67dd03
::z01729c5314(unsigned char z60e99e4156){Buffer::set((0xb52+1536-0x1150),
z60e99e4156&(0x3f9+1385-0x863));}unsigned char zadbe67dd03::zf1e6344a84()const{
return(Buffer::get((0xcc5+5192-0x210b))&(0x267+4190-0x11c6));}void zadbe67dd03::
zc30ad49c26(unsigned char z9ac5330d0e){Buffer::set((0x1dc5+1023-0x21c1),
z9ac5330d0e&(0x64f+5326-0x1a1e));}unsigned char zadbe67dd03::zd30fb5d9f3()const{
return(Buffer::get((0x164+7182-0x1d6f))&(0x761+6979-0x21a5));}void zadbe67dd03::
z0c49370f86(unsigned char zf279163f39){Buffer::set((0xedf+3222-0x1b71),
zf279163f39&(0xc71+6286-0x2400));}unsigned char zadbe67dd03::z7ae791afa9()const{
return(Buffer::get((0x19e6+2297-0x22db))&(0xf0c+2111-0x164c));}void zadbe67dd03
::zb9b72b8dfa(unsigned short za5409d11ea){Buffer::set((0x15a1+1364-0x1af0),(
za5409d11ea>>(0x17d7+1267-0x1cc2))&(0xd0f+3684-0x1a74));Buffer::set(
(0xfcb+1353-0x150e),za5409d11ea&(0x199+2429-0xa17));}unsigned short zadbe67dd03
::z42369ec0a9()const{return((Buffer::get((0x188d+1250-0x1d6a))&(0x6a5+582-0x7ec)
)<<(0x919+945-0xcc2))|(Buffer::get((0x7a5+4176-0x17ef))&(0x576+5680-0x1aa7));}
void zadbe67dd03::zbbdd7e7e66(unsigned char z6babad3bc5){Buffer::set(
(0x215+7616-0x1fce),z6babad3bc5&(0x9d4+2365-0x1212));}unsigned char zadbe67dd03
::z52456b46dc()const{return(Buffer::get((0x639+6235-0x1e8d))&(0x1815+538-0x1930)
);}void zadbe67dd03::z22b71056e4(unsigned char zf280255f02){Buffer::set(
(0xb1a+5927-0x2239),zf280255f02&(0xc89+5036-0x1f36));}unsigned char zadbe67dd03
::z65afec9653()const{return(Buffer::get((0xfdf+1899-0x1742))&(0xe26+5643-0x2332)
);}void zadbe67dd03::z38cd644399(unsigned short zfa85b31790){Buffer::set(
(0xf61+4941-0x22a5),(zfa85b31790>>(0x1c31+306-0x1d5b))&(0x12e6+4546-0x23a9));
Buffer::set((0x218+3604-0x1022),zfa85b31790&(0x1c2+299-0x1ee));}unsigned short 
zadbe67dd03::zdc10b2c903()const{return((Buffer::get((0x1ed2+1170-0x235b))&
(0x9b8+2044-0x10b5))<<(0x4b6+3353-0x11c7))|(Buffer::get((0x7dd+6963-0x2306))&
(0x2d1+7102-0x1d90));}void zadbe67dd03::zce12240a1b(const Buffer&z28e0145df4){
Buffer::setBuffer((0x1d94+602-0x1fe3),(0xc7+1915-0x80d),z28e0145df4);}Buffer 
zadbe67dd03::z76221cc199()const{return Buffer::getBuffer((0x6d6+4551-0x1892),
(0x741+3125-0x1341));}zadbe67dd03::zadbe67dd03(const PropertyCollection&
z44aa351fb2):Buffer(zd4f8e67a0d,zd4f8e67a0d){zbd8e48604c(z44aa351fb2);}void 
zadbe67dd03::zffac4ee2ab(PropertyCollection&z44aa351fb2)const{Buffer::
zffac4ee2ab(z44aa351fb2);z44aa351fb2.setProperty(
"\x66\x72\x61\x6d\x65\x2e\x70\x72\x6f\x74\x6f\x63\x6f\x6c","\x75\x73\x62");
z44aa351fb2.setProperty("\x66\x72\x61\x6d\x65\x2e\x6e\x61\x6d\x65",
"\x48\x49\x44\x52\x65\x70\x6f\x72\x74\x46\x72\x61\x6d\x65\x53\x74\x61\x72\x74");
z39bf8c3410("\x72\x65\x70\x6f\x72\x74\x5f\x69\x64",zf259b97dbd());z39bf8c3410(
"\x73\x65\x71\x75\x65\x6e\x63\x65\x5f\x6e\x75\x6d\x62\x65\x72",zbe81e74e90());
z39bf8c3410("\x70\x61\x63\x6b\x65\x74\x5f\x74\x79\x70\x65",zcb2c7e6f21());
z39bf8c3410("\x64\x61\x74\x61\x5f\x6c\x65\x6e\x67\x74\x68",zf1e6344a84());
z39bf8c3410("\x70\x72\x6f\x74\x6f\x63\x6f\x6c\x5f\x76\x65\x72\x73\x69\x6f\x6e",
zd30fb5d9f3());z39bf8c3410(
"\x68\x65\x61\x64\x65\x72\x5f\x6c\x65\x6e\x67\x74\x68",z7ae791afa9());
z39bf8c3410("\x62\x6f\x64\x79\x5f\x6c\x65\x6e\x67\x74\x68",z42369ec0a9());
z39bf8c3410("\x70\x72\x6f\x74\x6f\x63\x6f\x6c\x5f\x69\x64",z52456b46dc());
z39bf8c3410("\x65\x6d\x69\x69\x64",z65afec9653());z39bf8c3410(
"\x6d\x61\x6e\x75\x66\x61\x63\x74\x75\x72\x65\x72\x5f\x63\x6f\x64\x65",
zdc10b2c903());z39bf8c3410("\x72\x65\x70\x6f\x72\x74\x5f\x62\x6f\x64\x79",
z76221cc199().zbaa3b4a6ca());}void zadbe67dd03::zbd8e48604c(const 
PropertyCollection&z44aa351fb2){zd41c892f97(z44aa351fb2.getProperty(
"\x72\x65\x70\x6f\x72\x74\x5f\x69\x64"));z12aeb820c7(z44aa351fb2.getProperty(
"\x73\x65\x71\x75\x65\x6e\x63\x65\x5f\x6e\x75\x6d\x62\x65\x72"));z5058692388(
z44aa351fb2.getProperty("\x70\x61\x63\x6b\x65\x74\x5f\x74\x79\x70\x65"));
z01729c5314(z44aa351fb2.getProperty(
"\x64\x61\x74\x61\x5f\x6c\x65\x6e\x67\x74\x68"));zc30ad49c26(z44aa351fb2.
getProperty("\x70\x72\x6f\x74\x6f\x63\x6f\x6c\x5f\x76\x65\x72\x73\x69\x6f\x6e"))
;z0c49370f86(z44aa351fb2.getProperty(
"\x68\x65\x61\x64\x65\x72\x5f\x6c\x65\x6e\x67\x74\x68"));zb9b72b8dfa(z44aa351fb2
.getProperty("\x62\x6f\x64\x79\x5f\x6c\x65\x6e\x67\x74\x68"));zbbdd7e7e66(
z44aa351fb2.getProperty("\x70\x72\x6f\x74\x6f\x63\x6f\x6c\x5f\x69\x64"));
z22b71056e4(z44aa351fb2.getProperty("\x65\x6d\x69\x69\x64"));z38cd644399(
z44aa351fb2.getProperty(
"\x6d\x61\x6e\x75\x66\x61\x63\x74\x75\x72\x65\x72\x5f\x63\x6f\x64\x65"));
zce12240a1b(Buffer(z44aa351fb2.getProperty(
"\x72\x65\x70\x6f\x72\x74\x5f\x62\x6f\x64\x79").extract<std::vector<unsigned 
char> >()));}void zadbe67dd03::zffac4ee2ab(PropertyCollection&z44aa351fb2,
unsigned char z346260c7ff,unsigned char z80e0f1c035,unsigned char z51f76ba943,
unsigned char z60e99e4156,unsigned char z9ac5330d0e,unsigned char zf279163f39,
unsigned short za5409d11ea,unsigned char z6babad3bc5,unsigned char zf280255f02,
unsigned short zfa85b31790,const Buffer&z28e0145df4){z44aa351fb2.setProperty(
"\x72\x65\x70\x6f\x72\x74\x5f\x69\x64",z346260c7ff);z44aa351fb2.setProperty(
"\x73\x65\x71\x75\x65\x6e\x63\x65\x5f\x6e\x75\x6d\x62\x65\x72",z80e0f1c035);
z44aa351fb2.setProperty("\x70\x61\x63\x6b\x65\x74\x5f\x74\x79\x70\x65",
z51f76ba943);z44aa351fb2.setProperty(
"\x64\x61\x74\x61\x5f\x6c\x65\x6e\x67\x74\x68",z60e99e4156);z44aa351fb2.
setProperty("\x70\x72\x6f\x74\x6f\x63\x6f\x6c\x5f\x76\x65\x72\x73\x69\x6f\x6e",
z9ac5330d0e);z44aa351fb2.setProperty(
"\x68\x65\x61\x64\x65\x72\x5f\x6c\x65\x6e\x67\x74\x68",zf279163f39);z44aa351fb2.
setProperty("\x62\x6f\x64\x79\x5f\x6c\x65\x6e\x67\x74\x68",za5409d11ea);
z44aa351fb2.setProperty("\x70\x72\x6f\x74\x6f\x63\x6f\x6c\x5f\x69\x64",
z6babad3bc5);z44aa351fb2.setProperty("\x65\x6d\x69\x69\x64",zf280255f02);
z44aa351fb2.setProperty(
"\x6d\x61\x6e\x75\x66\x61\x63\x74\x75\x72\x65\x72\x5f\x63\x6f\x64\x65",
zfa85b31790);z44aa351fb2.setProperty(
"\x72\x65\x70\x6f\x72\x74\x5f\x62\x6f\x64\x79",z28e0145df4.zbaa3b4a6ca());}
