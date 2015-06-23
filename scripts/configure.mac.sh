#!/bin/bash

DIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd)

$DIR/../configure \
  CXX=clang++ \
  CXXFLAGS='-g -std=c++11 -Wno-deprecated-register' \
  LDFLAGS='-L/usr/local/lib' \
  CFLAGS='-I/usr/local/include' \
  --enable-debug
