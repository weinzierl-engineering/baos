
boost 1.80.0 subset
It includes:
- boost/assert.hpp
- boost/signals2.hpp
 

Created with (VS 2022):
cd BOOSTROOT
bootstrap.bat
cd dist/bin
bcp.exe --boost=../.. boost/assert.hpp boost/signals2.hpp boost-subset