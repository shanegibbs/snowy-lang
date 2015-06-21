#!/bin/zsh

source ~/.zshrc
set -eu

# dup from zshrc-local for now
export PREFIX=$HOME/usr
export PROC_COUNT=`expr $(grep -c ^processor /proc/cpuinfo) + 1 `
# end dup

cd $HOME
curl "http://mirrors.concertpass.com/gcc/releases/gcc-4.8.4/gcc-4.8.4.tar.bz2"| tar xj
export BUILD="$HOME/build"
export SRC="$HOME/gcc-4.8.4"

cd $SRC
./contrib/download_prerequisites

unset CC
unset CXX
export CFLAGS='-O3'
export CXXFLAGS=$CFLAGS

mkdir $BUILD && cd $BUILD
$SRC/configure CFLAGS="$CFLAGS" CXXFLAGS="$CXXFLAGS" --prefix=$PREFIX --enable-languages=c,c++
make -j$PROC_COUNT
make install

rm -rf $SRC $BUILD
