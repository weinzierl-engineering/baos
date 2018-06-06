
#include "pch/kdrive_pch.h"
#include "kdrive/knx/telegrams/formatters/Telegram.h"
using namespace kdrive::knx;z2a66522423::z2a66522423(){addFormatter(&z34a346ae28
);}z2a66522423::~z2a66522423(){}void z2a66522423::za5e4891a53(unsigned char 
z22139f7a06){z34a346ae28.set(z22139f7a06);}unsigned char z2a66522423::
z6b11bcce77()const{return z34a346ae28.get();}bool z2a66522423::zf9f997438f(const
 std::vector<unsigned char>&buffer)const{return false;}void z2a66522423::setData
(const std::vector<unsigned char>&data){z1709ace471.setBuffer(data);}const std::
vector<unsigned char>&z2a66522423::getData()const{return z1709ace471.getBuffer()
;}std::vector<unsigned char>&z2a66522423::getData(){return z1709ace471.getBuffer
();}zfb0a48309d&z2a66522423::z5863bb042e(){return z1709ace471;}
