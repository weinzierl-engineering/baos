
#ifndef z1d8499ce83
#define z1d8499ce83
#include "kdrive/knx/Config.h"
#include "kdrive/knx/telegrams/formatters/Formatter.h"
#include "kdrive/knx/core/Types.h" 
namespace kdrive{namespace knx{class z91680f515b z12caacb3c6:public 
AbstractFormatter{public:typedef kdrive::knx::SerialNumber SerialNumber;
z12caacb3c6();virtual~z12caacb3c6();std::size_t size()const override;bool 
isValid()const override;void setDefaults()override;void set(const SerialNumber&
zd311e7ca26);const SerialNumber&get()const;void z5f5fd61d58(const SerialNumber&
zd311e7ca26);const SerialNumber&getSerialNumber()const;private:std::size_t 
readImpl(const Buffer&buffer)override;std::size_t writeImpl(Buffer&buffer)
override;private:SerialNumber zc51b6ade54;};}}
#endif 

