
#ifndef ze56b33e9a3
#define ze56b33e9a3
#include "kdrive/access/Config.h"
#include "kdrive/connector/Forwards.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>
namespace kdrive{namespace access{class z23bd02551e zbf3da5ba57{public:typedef 
std::function<std::shared_ptr<kdrive::connector::Connector>(const std::string&)>
za5546bfd28;typedef std::function<void(std::vector<std::string>&)>z51ff6993f7;
zbf3da5ba57();static zbf3da5ba57&instance();std::shared_ptr<kdrive::connector::
Connector>create(const std::string&z72e98c8b46);std::vector<std::string>
z6caaec609a();void z3fde7bb20e(za5546bfd28 zfd1483f02a);void z8323704001(
z51ff6993f7 z3fecfd9123);template<class T>static std::shared_ptr<kdrive::
connector::Connector>zfd1483f02a(const std::string&z72e98c8b46){std::shared_ptr<
kdrive::connector::Connector>t;if(z72e98c8b46==T::ConnectorTypeLabel){t=std::
make_shared<T>();}return t;}private:std::vector<za5546bfd28>zccf977910c;std::
vector<z51ff6993f7>z20dd1cefd2;};}}
#endif 

