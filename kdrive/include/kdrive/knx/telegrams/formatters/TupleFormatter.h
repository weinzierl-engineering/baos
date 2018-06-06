
#ifndef zfa2c586730
#define zfa2c586730
#include "kdrive/knx/Config.h"
#include "kdrive/knx/telegrams/formatters/Formatter.h"
#include <boost/static_assert.hpp>
#include <tuple>
#include <array>
#include <memory>
namespace kdrive{namespace knx{template<int z0644e33e40>struct Bits{enum{Value=
z0644e33e40*(0x769+138-0x7eb)};};template<int z892c95fbd3>struct Bytes{enum{
Value=z892c95fbd3/(0x17d6+1279-0x1ccd),Offset=z892c95fbd3%(0xec4+5716-0x2510),
zf715e08e87=Offset==(0x4ab+7940-0x23af)?true:false,};};template<int index,class 
Tuple>struct ze973aef068{typedef typename std::tuple_element<index,Tuple>::type 
z082d8e54fe;enum{Value=z082d8e54fe::z892c95fbd3+ze973aef068<index-
(0x19c6+3036-0x25a1),Tuple>::Value};};template<class Tuple>struct ze973aef068<
(0x5a3+5272-0x1a3b),Tuple>{typedef typename std::tuple_element<
(0x1738+1950-0x1ed6),Tuple>::type z082d8e54fe;enum{Value=z082d8e54fe::
z892c95fbd3};};template<int index,class Tuple>struct z99fe7e8abf{enum{
z892c95fbd3=ze973aef068<index-(0x181+454-0x346),Tuple>::Value,ByteOffset=Bytes<
z892c95fbd3>::Value,z6ca52afcb1=Bytes<z892c95fbd3>::Offset};};template<class 
Tuple>struct z99fe7e8abf<(0x1083+299-0x11ae),Tuple>{enum{z892c95fbd3=
(0x52+779-0x35d),ByteOffset=(0xb44+5962-0x228e),z6ca52afcb1=(0x1327+2185-0x1bb0)
};};struct z91680f515b zd49fb66547{static unsigned int read(int z202059467a,int 
z43d31e9636,int z5e1f916d4c,const Buffer&buffer);};struct z91680f515b 
z3e0ba55e2c{static void write(int z202059467a,int z43d31e9636,int z5e1f916d4c,
Buffer&buffer,unsigned int value);};template<int zfdaadc77e5,int T1=
(0x1066+4686-0x22b4),int T2=(0xf2a+5888-0x262a),int T3=(0x1ac0+835-0x1e03),int 
T4=(0x10+5045-0x13c5),int T5=(0xa3f+6072-0x21f7),int z87ec4ad8ee=
(0x102a+971-0x13f5),int zc422c570b0=(0x114b+4000-0x20eb),int z01d7d38b56=
(0x10e2+5291-0x258d),int z8fbb5cf7c5=(0x1b06+2492-0x24c2)>class zd1e5842927:
public AbstractFormatter{private:template<int Bits>struct zee7300c16e{enum{
z892c95fbd3=Bits};};typedef std::tuple<zee7300c16e<zfdaadc77e5>,zee7300c16e<T1>,
zee7300c16e<T2>,zee7300c16e<T3>,zee7300c16e<T4>,zee7300c16e<T5>,zee7300c16e<
z87ec4ad8ee>,zee7300c16e<zc422c570b0>,zee7300c16e<z01d7d38b56>,zee7300c16e<
z8fbb5cf7c5> >TypeList;template<int index>struct Element{typedef typename std::
tuple_element<index,TypeList>::type z082d8e54fe;enum{z892c95fbd3=z082d8e54fe::
z892c95fbd3,z0644e33e40=Bytes<z892c95fbd3>::Value,zf715e08e87=Bytes<z892c95fbd3>
::zf715e08e87,z5039e82d36=z892c95fbd3>(0x10ac+485-0x1291)?true:false,ByteOffset=
z99fe7e8abf<index,TypeList>::ByteOffset,z6ca52afcb1=z99fe7e8abf<index,TypeList>
::z6ca52afcb1};};public:typedef zd1e5842927<zfdaadc77e5,T1,T2,T3,T4,T5,
z87ec4ad8ee,zc422c570b0,z01d7d38b56,z8fbb5cf7c5>z3f02cdb302;typedef std::
shared_ptr<z3f02cdb302>Ptr;enum{zca14ceedea=std::tuple_size<TypeList>::value,
z892c95fbd3=ze973aef068<zca14ceedea-(0x830+3400-0x1577),TypeList>::Value,
z0644e33e40=Bytes<z892c95fbd3>::Value,zf715e08e87=Bytes<z892c95fbd3>::
zf715e08e87,z6c5ad13c35=(0x6b2+6194-0x1ec4)};zd1e5842927(){BOOST_STATIC_ASSERT(
z892c95fbd3!=(0x1554+2807-0x204b));BOOST_STATIC_ASSERT(z0644e33e40!=
(0x1790+1885-0x1eed));BOOST_STATIC_ASSERT(zf715e08e87==true);BOOST_STATIC_ASSERT
(sizeof(unsigned int)>=(0x10a5+3190-0x1d17));BOOST_STATIC_ASSERT(zfdaadc77e5<=
z6c5ad13c35);BOOST_STATIC_ASSERT(T1<=z6c5ad13c35);BOOST_STATIC_ASSERT(T2<=
z6c5ad13c35);BOOST_STATIC_ASSERT(T3<=z6c5ad13c35);BOOST_STATIC_ASSERT(T4<=
z6c5ad13c35);BOOST_STATIC_ASSERT(T5<=z6c5ad13c35);BOOST_STATIC_ASSERT(
z87ec4ad8ee<=z6c5ad13c35);BOOST_STATIC_ASSERT(zc422c570b0<=z6c5ad13c35);
BOOST_STATIC_ASSERT(z01d7d38b56<=z6c5ad13c35);BOOST_STATIC_ASSERT(z8fbb5cf7c5<=
z6c5ad13c35);}virtual~zd1e5842927(){}std::size_t size()const override{return 
z0644e33e40;}bool isValid()const override{return true;}template<int index>void 
set(unsigned int value){BOOST_STATIC_ASSERT(Element<index>::z5039e82d36);
z988e257be4[index]=value;}template<int index>unsigned int get()const{
BOOST_STATIC_ASSERT(Element<index>::z5039e82d36);return z988e257be4[index];}
private:typedef std::array<unsigned int,zca14ceedea>Values;template<int index,
class Container>struct Reader{inline static void read(Container&container,const 
Buffer&buffer){Reader<index-(0x295+5311-0x1753),Container>::read(container,
buffer);if(Element<index>::z5039e82d36){const int z202059467a=Element<index>::
ByteOffset;const int z43d31e9636=Element<index>::z6ca52afcb1;const int 
z5e1f916d4c=Element<index>::z892c95fbd3;container[index]=zd49fb66547::read(
z202059467a,z43d31e9636,z5e1f916d4c,buffer);}}};template<class Container>struct 
Reader<(0x3d1+5459-0x1924),Container>{inline static void read(Container&
container,const Buffer&buffer){if(Element<(0x20a+8499-0x233d)>::z5039e82d36){
container[(0x17f+6445-0x1aac)]=zd49fb66547::read((0x13b4+2533-0x1d99),
(0x217b+1420-0x2707),Element<(0x1510+2835-0x2023)>::z892c95fbd3,buffer);}}};
template<int index,class Container>struct Writer{inline static void write(
Container&container,Buffer&buffer){Writer<index-(0xdd3+4822-0x20a8),Container>::
write(container,buffer);if(Element<index>::z5039e82d36){const int z202059467a=
Element<index>::ByteOffset;const int z43d31e9636=Element<index>::z6ca52afcb1;
const int z5e1f916d4c=Element<index>::z892c95fbd3;const unsigned int value=
container[index];z3e0ba55e2c::write(z202059467a,z43d31e9636,z5e1f916d4c,buffer,
value);}}};template<class Container>struct Writer<(0x1b+6418-0x192d),Container>{
inline static void write(Container&container,Buffer&buffer){if(Element<
(0x1ae5+1593-0x211e)>::z5039e82d36){z3e0ba55e2c::write((0x91c+3843-0x181f),
(0x117+5451-0x1662),Element<(0x708+5297-0x1bb9)>::z892c95fbd3,buffer,container[
(0x178+3932-0x10d4)]);}}};std::size_t readImpl(const Buffer&buffer)override{
Reader<zca14ceedea-(0xb14+2568-0x151b),Values>::read(z988e257be4,buffer);return 
z0644e33e40;}std::size_t writeImpl(Buffer&buffer)override{Writer<zca14ceedea-
(0x1463+3321-0x215b),Values>::write(z988e257be4,buffer);return z0644e33e40;}
private:Values z988e257be4;};}}
#endif 

