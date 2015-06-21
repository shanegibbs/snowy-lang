#!/bin/zsh

VERSION=3.0.2

source ~/.zshrc
set -eu

cd $HOME
export BUILD="$HOME/build"
export SRC="$HOME/bison-$VERSION"
export CFLAGS="-O3"
export CXXFLAGS=$CFLAGS

curl "http://ftp.gnu.org/gnu/bison/bison-$VERSION.tar.gz" |tar xz

mkdir $HOME/build && cd $HOME/build

$SRC/configure CFLAGS="$CFLAGS" CXXFLAGS="$CXXFLAGS" --prefix=$PREFIX
make -j$PROC_COUNT
make install

rm -rf $SRC $BUILD
