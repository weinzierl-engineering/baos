
#ifndef z790b07e008
#define z790b07e008
#include "kdrive/knx/Config.h"
#include <vector>
namespace kdrive{namespace knx{class z91680f515b Buffer{public:Buffer();Buffer(
unsigned char*buffer,std::size_t bufferSize);Buffer(const Buffer&)=delete;
virtual~Buffer();Buffer&operator=(const Buffer&)=delete;void setBuffer(unsigned 
char*buffer,std::size_t bufferSize);void setBuffer(std::vector<unsigned char>&
buffer);const unsigned char*getBuffer()const;unsigned char*getBuffer();std::
size_t z727230908f()const;bool zd1b5fa7c57()const;void reset();void assign(
unsigned char data);void zb8203d7346(unsigned int offset,unsigned char data);
void z740eff6f6e(unsigned int offset,unsigned short data);void za213db16c9(
unsigned int offset,const unsigned char*buffer,std::size_t bufferSize);unsigned 
char z02b8347997(unsigned int offset)const;unsigned short readWord(unsigned int 
offset)const;unsigned char*z15e6bd8652(unsigned int offset,std::size_t 
bufferSize);const unsigned char*z15e6bd8652(unsigned int offset,std::size_t 
bufferSize)const;private:void z1d943f3f75(unsigned int offset)const;private:
unsigned char*z7ec3461dd4;std::size_t z4de44892fb;};template<class T>struct 
BufferDecorator:public T{BufferDecorator(unsigned char*buffer,std::size_t 
bufferSize){T::setBuffer(buffer,bufferSize);}BufferDecorator(std::vector<
unsigned char>&buffer){T::setBuffer(buffer);}};}}
#endif 

