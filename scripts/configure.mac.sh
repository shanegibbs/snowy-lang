#!/bin/sh

`dirname "$(readlink -f $0)"`/../configure \
  CXX=clang++ \
  CXXFLAGS='-g -std=c++11 -Wno-deprecated-register' \
  LDFLAGS='-L/usr/local/lib' \
  CFLAGS='-I/usr/local/include' \
  --enable-debug
