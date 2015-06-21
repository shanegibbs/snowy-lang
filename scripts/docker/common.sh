#!/bin/bash -eu

export PREFIX=$HOME
export PROC_COUNT=`expr $(grep -c ^processor /proc/cpuinfo) + 1 `

echo PREFIX is $PREFIX

export PATH=$PREFIX/bin:$PATH
export LD_SEARCH_PATH=$PREFIX/lib:$PREFIX/lib64
export PKG_CONFIG_PATH=$PREFIX/lib/pkgconfig
