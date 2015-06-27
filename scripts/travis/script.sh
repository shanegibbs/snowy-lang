#!/bin/bash -e

if [ "x$CXX" == "x" ]; then
  echo Environment variable CXX not set
  exit 1
fi

export PATH=/home/travis/usr/bin:/usr/sbin:/sbin:/usr/bin:/bin
export LD_SEARCH_PATH=/home/travis/usr/lib:/home/travis/usr/lib64
export PKG_CONFIG_PATH=/home/travis/usr/lib/pkgconfig

export LDFLAGS="$LDFLAGS -Wl,--rpath=/home/travis/usr/lib64"
export LDFLAGS="$LDFLAGS -Wl,--rpath=/home/travis/usr/lib"

# CXXFLAGS="$CXXFLAGS -v"
CXXFLAGS="$CXXFLAGS -I/home/travis/usr/include"
# CXXFLAGS="$CXXFLAGS -L/home/travis/usr/lib"

if [ "$CXX" == "clang++" ]; then
  echo 'Setting clang++ flags'
  #CXXFLAGS="$CXXFLAGS -Qunused-arguments"
  CXXFLAGS="$CXXFLAGS -Wno-deprecated-register"
fi

if [ "$CXX" == "g++" ]; then
  echo 'Setting g++ flags'
fi

SCRIPT=$(readlink -f $0)
SCRIPT_PATH=`dirname $SCRIPT`

BUILD_ROOT=$(pwd)
PROJECT_ROOT="$SCRIPT_PATH/../.."
CONFIGURE="$SCRIPT_PATH/../../configure"

if [ ! -e $CONFIGURE ]; then
  cd $PROJECT_ROOT
  mkdir -p m4 && ./autogen.sh
fi

cd $BUILD_ROOT
rm -rf build
mkdir build && cd build

set -x
$CONFIGURE CXX="$CXX" CXXFLAGS="$CXXFLAGS" LDFLAGS="$LDFLAGS" --enable-debug || cat config.log
make check
