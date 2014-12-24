#!/bin/bash -e

INSTALL=$HOME/snowy-deps

PATH=/usr/bin:/bin
LD_SEARCH_PATH=""
PKG_CONFIG_PATH=""

deps=( gcc-4.8.4 llvm-3.5.0 flex-2.5.39 bison-3.0.2 glib-2.43.2 )
for i in "${deps[@]}"
do
  PATH=$INSTALL/$i/bin:$PATH
  LD_SEARCH_PATH=$INSTALL/$i/lib:$PATH
  PKG_CONFIG_PATH=$INSTALL/$i/lib/pkgconfig:$PATH
done

echo export PATH=$PATH
echo export LD_SEARCH_PATH=$LD_SEARCH_PATH
echo export PKG_CONFIG_PATH=$PKG_CONFIG_PATH
