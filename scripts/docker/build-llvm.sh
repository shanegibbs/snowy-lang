#!/bin/zsh

VERSION=3.5.0

source ~/.zshrc
set -eu

cd $HOME
export BUILD="$HOME/build"
export SRC="$HOME/llvm-$VERSION.src"

curl "http://llvm.org/releases/$VERSION/llvm-$VERSION.src.tar.xz" |tar xJ

cd $SRC/tools
curl "http://llvm.org/releases/$VERSION/cfe-$VERSION.src.tar.xz" |tar xJ
mv cfe-$VERSION.src clang

cd $SRC/tools/clang/tools
curl "http://llvm.org/releases/$VERSION/clang-tools-extra-$VERSION.src.tar.xz" |tar xJ
mv clang-tools-extra-$VERSION.src extra

cd $SRC/projects
curl "http://llvm.org/releases/$VERSION/compiler-rt-$VERSION.src.tar.xz" |tar xJ
mv compiler-rt-$VERSION.src compiler-rt

unset CC
unset CXX
#export CC="$PREFIX/bin/gcc"
#export CXX="$PREFIX/bin/g++"
export CFLAGS="-O3"
export CXXFLAGS=$CFLAGS

mkdir $HOME/build && cd $HOME/build

$SRC/configure CFLAGS="$CFLAGS" CXXFLAGS="$CXXFLAGS" --prefix=$PREFIX --enable-optimized --enable-targets=x86_64 --disable-terminfo --disable-libedit
make -j$PROC_COUNT
make install

rm -rf $SRC $BUILD
