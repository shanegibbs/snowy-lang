#!/bin/bash -ex

export CXXFLAGS=''

mkdir m4 && ./autogen.sh

./configure && make && make check
