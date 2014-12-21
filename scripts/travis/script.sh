#!/bin/bash -ex

curl -O 'https://s3-us-west-2.amazonaws.com/snowy-lang/deps/travis/snowy-deps.tar.gz'
tar -xzf snowy-deps.tar.gz -C $HOME

export PATH=/home/travis/snowy-deps/glib-2.43.2/bin:/home/travis/snowy-deps/bison-3.0.2/bin:/home/travis/snowy-deps/flex-2.5.39/bin:/home/travis/snowy-deps/llvm-3.5.0/bin:/home/travis/snowy-deps/gcc-4.8.4/bin:/usr/bin:/bin
export LD_SEARCH_PATH=/home/travis/snowy-deps/libedit-3.1/lib:/home/travis/snowy-deps/glib-2.43.2/lib:/home/travis/snowy-deps/glib-2.43.2/bin:/home/travis/snowy-deps/bison-3.0.2/bin:/home/travis/snowy-deps/flex-2.5.39/bin:/home/travis/snowy-deps/llvm-3.5.0/bin:/home/travis/snowy-deps/gcc-4.8.4/bin:/usr/bin:/bin
export PKG_CONFIG_PATH=/home/travis/snowy-deps/libedit-3.1/lib/pkgconfig:/home/travis/snowy-deps/glib-2.43.2/lib/pkgconfig:/home/travis/snowy-deps/glib-2.43.2/bin:/home/travis/snowy-deps/bison-3.0.2/bin:/home/travis/snowy-deps/flex-2.5.39/bin:/home/travis/snowy-deps/llvm-3.5.0/bin:/home/travis/snowy-deps/gcc-4.8.4/bin:/usr/bin:/bin

export CXXFLAGS=''

mkdir m4 && ./autogen.sh

./configure && make && make check
