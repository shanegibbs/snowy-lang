#!/bin/sh

`dirname "$(readlink -f $0)"`/../configure \
  CXX='clang++' \
  CXXFLAGS='-g -std=c++11 -Wno-deprecated-register'\
  --enable-debug
