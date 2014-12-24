#!/bin/bash -ex

#echo Initial libraries
#ldconfig -p |sort

export PATH=/home/travis/snowy-deps/bin:/usr/sbin:/sbin:/usr/bin:/bin
export LD_SEARCH_PATH=/home/travis/snowy-deps/lib:/home/travis/snowy-deps/lib64
export PKG_CONFIG_PATH=/home/travis/snowy-deps/lib/pkgconfig

#echo Installed libraries
#ldconfig -p |sort

mkdir m4 && ./autogen.sh

./configure CXXFLAGS='-Wl,--rpath=/home/travis/snowy-deps/lib64 -Wl,--rpath=/home/travis/snowy-deps/lib -I/home/travis/snowy-deps/include -L/home/travis/snowy-deps/lib' && make -j && make check
