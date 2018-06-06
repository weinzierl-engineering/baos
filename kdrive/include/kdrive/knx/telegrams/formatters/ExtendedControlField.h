
#ifndef z94f0ced803
#define z94f0ced803
#include "kdrive/knx/Config.h"
#include "kdrive/knx/telegrams/formatters/Formatter.h"
namespace kdrive{namespace knx{class z91680f515b z7f3b1fd12c:public 
AbstractFormatter{public:z7f3b1fd12c();virtual~z7f3b1fd12c();public:std::size_t 
size()const override;bool isValid()const override;void setDefaults()override;
public:void set(unsigned char controlField);unsigned char get()const;void 
zfef6804589(unsigned char z90de16d7da);unsigned char zfc5016f8e0()const;bool 
z088b874fc9()const;bool ze25425cb88()const;void zc5845415f8(unsigned char 
z5cde7031d2);unsigned char ze85f31fba4()const;void z222d82c49b(unsigned char 
zf799fec5b6);unsigned char z83d73bc9c9()const;public:enum z83dbd6d14e{
z601f186a16=(0x1400+960-0x17c0)};private:std::size_t readImpl(const Buffer&
buffer)override;std::size_t writeImpl(Buffer&buffer)override;private:enum{Size=
(0xe7b+4273-0x1f2b)};enum z512be7d538{zf840a35990=(0xaaa+7378-0x26fc),
z7c64e75d76=(0x2183+1503-0x26f2),ze3f1653f0c=(0x12ca+2459-0x1c56)};private:
unsigned char zdd7ec172a0;unsigned char z5d633fa4fa;unsigned char zc8f8c890de;};
}}
#endif 

