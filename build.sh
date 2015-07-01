#!/bin/zsh

SRC="$HOME/src"
BUILD="$HOME/build"

if [ ! -d "$BUILD" ]; then
  mkdir "$BUILD" && cd $BUILD
  $SRC/configure CXXFLAGS='-Wno-deprecated-register -fsanitize=address -fcolor-diagnostics' --enable-debug
fi

cd $BUILD
make -j check
