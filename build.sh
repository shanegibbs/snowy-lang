#!/bin/zsh

SRC="$HOME/src"
BUILD="$HOME/build"

if [ ! -d "$BUILD" ]; then
  mkdir "$BUILD" && cd $BUILD
  $SRC/configure --enable-debug
fi

cd $BUILD
make -j check
