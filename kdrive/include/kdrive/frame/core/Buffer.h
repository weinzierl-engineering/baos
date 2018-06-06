
#ifndef ze74c66d015
#define ze74c66d015
#include "kdrive/frame/Config.h"
#include <cstddef>
#include <string>
#include <vector>
#include <memory>
namespace kdrive{namespace utility{class PropertyCollection;}}namespace kdrive{
namespace frame{class z0aa43889be Buffer{public:typedef std::shared_ptr<Buffer>
Ptr;typedef unsigned char value_type;typedef std::size_t size_type;typedef 
unsigned char*iterator;typedef const value_type*const_iterator;typedef kdrive::
utility::PropertyCollection PropertyCollection;Buffer();explicit Buffer(
size_type size);explicit Buffer(const std::vector<value_type>&v);explicit Buffer
(size_type size,size_type capacity);explicit Buffer(value_type*ptr,size_type 
size,bool z7e8450ecf2);Buffer(const Buffer&buffer);virtual~Buffer();Buffer&
operator=(const Buffer&buffer);void assign(const Buffer&buffer);value_type*
z8d79a69692()const;value_type*zffce7603f8(size_type index)const;value_type*
zffce7603f8(size_type index,size_type size)const;iterator begin();const_iterator
 begin()const;iterator end();const_iterator end()const;bool isEmpty()const;void 
setSize(size_type size);size_type getSize()const;size_type z4cbc7cada9(size_type
 index)const;void setCapacity(size_type capacity);size_type ze5eea3f1a3()const;
std::string toString()const;virtual void zffac4ee2ab(PropertyCollection&
z44aa351fb2)const;void set(size_type index,unsigned char value);void z2e8f9b9806
(size_type index,unsigned char mask);void zcea3a3d899(size_type index,unsigned 
char value);unsigned char get(size_type index)const;void setBuffer(size_type 
index,const Buffer&buffer);void setBuffer(size_type index,size_type size,const 
Buffer&buffer);Buffer getBuffer(size_type index)const;Buffer getBuffer(size_type
 index,size_type size)const;void setString(size_type index,size_type size,const 
std::string&s);std::string getString(size_type index,size_type size)const;void 
z49cd04e624(size_type index,size_type size,const std::vector<unsigned char>&v);
std::vector<unsigned char>zbaa3b4a6ca()const;std::vector<unsigned char>
zbaa3b4a6ca(size_type index)const;std::vector<unsigned char>zbaa3b4a6ca(
size_type index,size_type size)const;std::vector<unsigned char>&zb87befbd6f();
private:void z7c6707d75a();void z7c6707d75a(size_type size,size_type capacity);
void zc8023d9ce4(size_type capacity,bool copy);void release();void assign(const 
value_type*ptr,size_type size,size_type capacity);void copy(const value_type*ptr
,size_type size);private:value_type*z719bdb3268;std::vector<value_type>
zb4533d6f54;size_type z36f10e99cd;size_type z1e742ff128;bool z48c8eb8550;};bool 
operator==(const Buffer&zc48d94fe59,const Buffer&z0ad8726472);bool operator!=(
const Buffer&zc48d94fe59,const Buffer&z0ad8726472);}}
#endif 

