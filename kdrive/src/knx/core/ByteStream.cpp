
#include "pch/kdrive_pch.h"
#include "kdrive/knx/core/ByteStream.h"
using namespace kdrive::knx;using Poco::Exception;template<>void kdrive::knx::
zda00b50860<unsigned char>(z9c9e564eb1<unsigned char>&u){}template<>void kdrive
::knx::zda00b50860<char>(z9c9e564eb1<char>&u){}template<>void kdrive::knx::
zda00b50860<float>(z9c9e564eb1<float>&u){flipBytes(u);}template<>unsigned char 
kdrive::knx::ze378c24725<unsigned char,(0x69d+6741-0x20f1)>(const unsigned char*
buffer,std::size_t z3ba388a942,std::size_t index){if(z3ba388a942<
(0x9d8+6597-0x239c)+index){throw Exception(
"\x42\x75\x66\x66\x65\x72\x20\x4f\x76\x65\x72\x72\x75\x6e");}return*(buffer+
index);};template<>char kdrive::knx::ze378c24725<char,(0x176f+423-0x1915)>(const
 unsigned char*buffer,std::size_t z3ba388a942,std::size_t index){if(z3ba388a942<
(0x10e0+3271-0x1da6)+index){throw Exception(
"\x42\x75\x66\x66\x65\x72\x20\x4f\x76\x65\x72\x72\x75\x6e");}return static_cast<
char>(*(buffer+index));};
