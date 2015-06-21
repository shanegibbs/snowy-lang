#!/bin/zsh

VERSION=2.5.39

source ~/.zshrc
set -eu

cd $HOME
export BUILD="$HOME/build"
export SRC="$HOME/flex-$VERSION"
export CFLAGS="-O3"
export CXXFLAGS=$CFLAGS

curl "http://hivelocity.dl.sourceforge.net/project/flex/flex-$VERSION.tar.bz2" |tar xj

mkdir $HOME/build && cd $HOME/build

$SRC/configure CFLAGS="$CFLAGS" CXXFLAGS="$CXXFLAGS" --prefix=$PREFIX
make -j$PROC_COUNT
make install

rm -rf $SRC $BUILD
