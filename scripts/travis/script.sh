#!/bin/bash -ex

export PATH=/home/travis/snowy-deps/bin:/usr/sbin:/sbin:/usr/bin:/bin
export LD_SEARCH_PATH=/home/travis/snowy-deps/lib:/home/travis/snowy-deps/lib64
export PKG_CONFIG_PATH=/home/travis/snowy-deps/lib/pkgconfig

mkdir -p m4 && ./autogen.sh

./configure CXXFLAGS='-Wno-deprecated-register -Wl,--rpath=/home/travis/snowy-deps/lib64 -Wl,--rpath=/home/travis/snowy-deps/lib -I/home/travis/snowy-deps/include -L/home/travis/snowy-deps/lib' --enable-debug
make
make check
