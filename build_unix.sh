#!/bin/sh

rm -f -r build_unix
mkdir build_unix

cd build_unix

cmake -DCMAKE_BUILD_TYPE=Release -DWZSDK_STATIC=1 -DWZSDK_SAMPLES=1 -DWZSDK_SAMPLES_QT=0 -G "Unix Makefiles" ../
make -j5
make install
cd ..

