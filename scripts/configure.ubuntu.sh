#!/bin/sh

CLANG=$(which clang++)
if [ -z $CLANG ]; then
    CLANG=$(which clang++-3.5)
fi
if [ -z $CLANG ]; then
    echo clang++ and clang++-3.5 not found
    exit 1
fi

`dirname "$(readlink -f $0)"`/../configure \
  CXX=$CLANG \
  CXXFLAGS='-g -std=c++11 -Wno-deprecated-register'\
  --enable-debug
