#!/bin/bash -eu

. $WORKDIR/common.sh
mkdir $HOME/build && cd $HOME/build

export GCC_SRC="$WORKDIR/gcc-4.8.4"
export CFLAGS='-O3 -I/usr/include/x86_64-linux-gnu'
export CXXFLAGS=$CFLAGS

$GCC_SRC/configure CFLAGS="$CFLAGS" CXXFLAGS="$CXXFLAGS" --prefix=$PREFIX --enable-languages=c,c++
make -j$PROC_COUNT 2>&1
make install

rm -rf $HOME/build
rm -rf $GCC_SRC
