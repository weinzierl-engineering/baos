#!/bin/sh

rm -f -r build_raspbian
mkdir build_raspbian

cd build_raspbian

cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/raspbian-toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DWZSDK_STATIC=1 -DWZSDK_SAMPLES=1 -DWZSDK_SAMPLES_QT=0 -G "Unix Makefiles" ../
make -j5
make install
cd ..

