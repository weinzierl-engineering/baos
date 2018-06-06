
#ifndef z88149ce4fd
#define z88149ce4fd
#include "kdrive/knx/Config.h"
#include "kdrive/knx/telegrams/formatters/Formatter.h"
namespace kdrive{namespace knx{namespace cemi{class z91680f515b zfa304e8ec3:
public AbstractFormatter{public:zfa304e8ec3();virtual~zfa304e8ec3();std::size_t 
size()const override;bool isValid()const override;void setDefaults()override;
void z539a137476(unsigned char length);unsigned char getLength()const;void 
setData(const std::vector<unsigned char>&data);const std::vector<unsigned char>&
getData()const;private:std::size_t readImpl(const Buffer&buffer)override;std::
size_t writeImpl(Buffer&buffer)override;enum{z57a7b7f644=(0xb87+6623-0x2565)};
private:std::vector<unsigned char>z9118dc6ff1;};}}}
#endif 

