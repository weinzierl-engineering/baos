
#ifndef z26a1aee66e
#define z26a1aee66e
#include "kdrive/frame/Config.h"
#include <Poco/Exception.h>
namespace kdrive{namespace frame{struct z0aa43889be z62f82588a9{enum{None=
(0xf13+3377-0x1c44),z88d3e284d5=28672,z764ce8d531=28673,z3df49357a9=28674,
z7939876ce2=28675};};
#define zdd93243a3f(CLS, BASE, CODE) \
	POCO_DECLARE_EXCEPTION_CODE(z0aa43889be, CLS, BASE, z62f82588a9::CODE)
zdd93243a3f(FrameException,Poco::Exception,z88d3e284d5)zdd93243a3f(
OutOfBoundsException,FrameException,z764ce8d531)zdd93243a3f(
BufferTooSmallException,FrameException,z3df49357a9)zdd93243a3f(
InvalidRangeException,FrameException,z7939876ce2)
#undef zdd93243a3f
}}
#endif 

