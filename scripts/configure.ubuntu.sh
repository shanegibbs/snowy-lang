#!/bin/sh

CLANG=$(which clang++)
if [ -z $CLANG ]; then
    CLANG=$(which clang++-3.6)
fi
if [ -z $CLANG ]; then
    echo clang++ and clang++-3.6 not found
    exit 1
fi

`dirname "$(readlink -f $0)"`/../configure \
  CXX=$CLANG \
  CXXFLAGS='-Wno-deprecated-register -fsanitize=address'\
  --enable-debug
