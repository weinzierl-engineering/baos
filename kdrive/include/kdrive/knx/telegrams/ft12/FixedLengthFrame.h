
#ifndef zf527b460a4
#define zf527b460a4
#include "kdrive/knx/Config.h"
#include "kdrive/knx/telegrams/formatters/Formatter.h"
namespace kdrive{namespace knx{namespace ft12{class z91680f515b FixedLengthFrame
:public Formatter{public:enum Attributes{z2920358c53=(0x144+1705-0x7ed),
ControlField,Checksum,EndByte,Length};FixedLengthFrame(bool z555d494b60=true);
virtual~FixedLengthFrame();bool isValid()const override;void setDefaults()
override;unsigned char zf538d46467()const;void setControlField(unsigned char 
controlField);unsigned char getControlField()const;void z5205ffbfd7(unsigned 
char checksum);unsigned char z458c6172ca()const;bool z8bb5df7389()const;unsigned
 char z8ca4a7d491()const;private:const bool z7b24692d08;ByteFormatter 
z318af989c1;ByteFormatter z5930a43bb3;ByteFormatter zb6fd1245b5;ByteFormatter 
z5595af419d;};}}}
#endif 

