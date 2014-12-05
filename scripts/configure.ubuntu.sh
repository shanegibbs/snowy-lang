#!/bin/sh

echo sudo apt-get install build-essential autoconf clang-3.5 llvm-3.5 llvm-3.5-dev libedit-dev libglib2.0-0 libglib2.0-dev \
  bison

../configure CXX=clang++ --enable-debug
