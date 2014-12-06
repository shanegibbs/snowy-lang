#!/bin/sh

echo sudo apt-get install build-essential autoconf clang-3.5 llvm-3.5 llvm-3.5-dev libedit-dev libglib2.0-0 libglib2.0-dev \
  bison

`dirname "$(readlink -f $0)"`/../configure CXX=clang++ CXXFLAGS='-g -std=c++11 -Wno-deprecated-register' --enable-debug
