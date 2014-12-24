#!/bin/bash -ex

echo Initial libraries
ldconfig -p |sort

export PATH=/home/travis/snowy-deps/glib-2.43.2/bin:/home/travis/snowy-deps/bison-3.0.2/bin:/home/travis/snowy-deps/flex-2.5.39/bin:/home/travis/snowy-deps/llvm-3.5.0/bin:/home/travis/snowy-deps/gcc-4.8.4/bin:/usr/sbin:/sbin:/usr/bin:/bin
export LD_SEARCH_PATH=/home/travis/snowy-deps/libedit-3.1/lib:/home/travis/snowy-deps/glib-2.43.2/lib:/home/travis/snowy-deps/glib-2.43.2/lib:/home/travis/snowy-deps/bison-3.0.2/lib:/home/travis/snowy-deps/flex-2.5.39/lib:/home/travis/snowy-deps/llvm-3.5.0/lib:/home/travis/snowy-deps/gcc-4.8.4/lib:/home/travis/snowy-deps/gcc-4.8.4/lib64
export PKG_CONFIG_PATH=/home/travis/snowy-deps/libedit-3.1/lib/pkgconfig:/home/travis/snowy-deps/glib-2.43.2/lib/pkgconfig:/home/travis/snowy-deps/glib-2.43.2/bin:/home/travis/snowy-deps/bison-3.0.2/bin:/home/travis/snowy-deps/flex-2.5.39/bin:/home/travis/snowy-deps/llvm-3.5.0/bin:/home/travis/snowy-deps/gcc-4.8.4/bin:/usr/bin:/bin

echo Installed libraries
ldconfig -p |sort

export CXXFLAGS=''

mkdir m4 && ./autogen.sh

./configure CXXFLAGS='-Wl,--rpath=/home/travis/snowy-deps/gcc-4.8.4/lib64 -Wl,--rpath=/home/travis/snowy-deps/glib-2.43.2/lib -I/home/travis/snowy-deps/flex-2.5.39/include -L/home/travis/snowy-deps/libedit-3.1/lib' && make -j && make check
