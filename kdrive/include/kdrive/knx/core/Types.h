
#ifndef z89c2731d39
#define z89c2731d39
#include "kdrive/knx/Config.h"
#include <vector>
#include <string>
#include <array>
namespace kdrive{namespace knx{class z91680f515b z498f6d084e{public:enum{Length=
(0xc90+3334-0x1990)};typedef std::array<unsigned char,Length>DataBuffer;
z498f6d084e();z498f6d084e(const DataBuffer&data);z498f6d084e(const std::vector<
unsigned char>&data);z498f6d084e(const unsigned char*zd311e7ca26,std::size_t 
z3ba388a942);z498f6d084e(unsigned char z7245eeaf6c,unsigned char zdbd02c81fa,
unsigned char z3028649c0f,unsigned char z3aa0f3e3c5,unsigned char z3e4dd8e4d0,
unsigned char zd4fcaa9456);virtual~z498f6d084e();z498f6d084e&operator=(const 
z498f6d084e&other);bool operator==(const z498f6d084e&other)const;bool operator!=
(const z498f6d084e&other)const;bool operator<(const z498f6d084e&other)const;bool
 operator<=(const z498f6d084e&other)const;bool operator>(const z498f6d084e&other
)const;bool operator>=(const z498f6d084e&other)const;z498f6d084e&operator++();
uint64_t operator-(const z498f6d084e&other)const;operator std::vector<unsigned 
char>()const;DataBuffer&z6334f67583();const DataBuffer&z6334f67583()const;std::
string toString(const std::string&za3ba428180=" ")const;std::vector<unsigned 
char>z73ef46b8e7()const;private:DataBuffer z8455ff2862;};typedef z498f6d084e 
z585ea4e09c;typedef z498f6d084e zee467d54fc;typedef z498f6d084e SerialNumber;}}
#endif 

