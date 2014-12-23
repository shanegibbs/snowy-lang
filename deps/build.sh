#!/bin/bash -ex

if [ ! -e /etc/lsb-release ]; then
  echo lsb-release not found
  exit 1
fi

. /etc/lsb-release

if [ "$DISTRIB_RELEASE" == "14.04" ]; then
  sudo apt-get install -y libc6-dev-i386 m4 libffi-dev gettext wget build-essential libncurses5-dev zlib1g-dev pkg-config
elif [ "$DISTRIB_RELEASE" == "12.04" ]; then
  sudo apt-get install -y libc6-dev-i386 m4 libffi-dev gettext wget build-essential libncurses5-dev zlib1g-dev pkg-config
else
  echo Unsupported OS
  exit 1
fi

PROC_COUNT=$(grep -c ^processor /proc/cpuinfo)
WORKSPACE=$PWD/build
mkdir -p $WORKSPACE

INSTALL=$HOME/snowy-deps

export SNOWY_GCC=$INSTALL/gcc-4.8.4
if [ ! -e "$INSTALL/gcc-4.8.4/bin/gcc" ]; then
  export CFLAGS='-O3 -I/usr/include/x86_64-linux-gnu'
  export CXXFLAGS=$CFLAGS

  cd $WORKSPACE
  if [ ! -e gcc-4.8.4.tar.bz2 ]; then curl -O 'http://mirrors.concertpass.com/gcc/releases/gcc-4.8.4/gcc-4.8.4.tar.bz2'; fi
  rm -rf gcc-4.8.4
  tar -xjf gcc-4.8.4.tar.bz2
  cd gcc-4.8.4
  ./contrib/download_prerequisites
  mkdir build && cd build
  ../configure --enable-languages=c,c++ --prefix=$INSTALL/gcc-4.8.4
  make -j$PROC_COUNT
  make install
  cd $WORKSPACE
  rm -rf gcc-4.8.4
fi

# add gcc to path
#export PATH=$INSTALL/gcc-4.8.4/bin:$PATH
export CC="$SNOWY_GCC/bin/gcc"
export CFLAGS='-O3'
export CXX="$SNOWY_GCC/bin/g++"
export CXXFLAGS=$CFLAGS

function build() {
LIB_NAME=$1
TAR_NAME=$2
DIR_NAME=$3
URL=$4
TEST_FILE=$5
CONF=$6
if [ ! -e "$INSTALL/$LIB_NAME/$TEST_FILE" ]; then
  cd $WORKSPACE
  if [ ! -e "$TAR_NAME" ]; then curl -O "$URL"; fi
  rm -rf $DIR_NAME
  tar -xf $TAR_NAME
  mkdir -p $DIR_NAME/snowy-build && cd $DIR_NAME/snowy-build
  ../configure --prefix=$INSTALL/$LIB_NAME $CONF
  make -j$PROC_COUNT
  make install
  cd $WORKSPACE
  rm -rf $LIB_NAME
fi
}

LIB_NAME=llvm-3.5.0
export SNOWY_LLVM=$INSTALL/$LIB_NAME
if [ ! -e "$INSTALL/$LIB_NAME/bin/llvm-config" ]; then
  cd $WORKSPACE
  if [ ! -e "$LIB_NAME.src.tar.xz" ]; then curl -O "http://llvm.org/releases/3.5.0/llvm-3.5.0.src.tar.xz"; fi
  rm -rf $LIB_NAME.src
  tar -xf $LIB_NAME.src.tar.xz
  mkdir -p $LIB_NAME.src/build && cd $LIB_NAME.src/build
  ../configure --prefix=$INSTALL/$LIB_NAME --enable-optimized
  make -j$PROC_COUNT
  make install
  cd $WORKSPACE
  rm -rf $LIB_NAME.src
fi

build "flex-2.5.39" "flex-2.5.39.tar.bz2" "flex-2.5.39" \
  "http://hivelocity.dl.sourceforge.net/project/flex/flex-2.5.39.tar.bz2" "bin/flex" \
  ""

build "bison-3.0.2" "bison-3.0.2.tar.gz" "bison-3.0.2" \
  "http://ftp.gnu.org/gnu/bison/bison-3.0.2.tar.gz" "bin/bison" \
  ""

build "libedit-3.1" "libedit-20141030-3.1.tar.gz" "libedit-20141029-3.1" \
  "http://thrysoee.dk/editline/libedit-20141030-3.1.tar.gz" "lib/libedit.a" \
  ""

build "glib-2.43.2" "glib-2.43.2.tar.xz" "glib-2.43.2" \
  "http://ftp.gnome.org/pub/gnome/sources/glib/2.43/glib-2.43.2.tar.xz" "lib/libedit.a" \
  ""

#LIB_NAME=glib-2.43.2
#export SNOWY_GLIB=$INSTALL/$LIB_NAME
#if [ ! -e "$INSTALL/$LIB_NAME/bin/llvm-config" ]; then
#  cd $WORKSPACE
#  if [ ! -e "$LIB_NAME.tar.xz" ]; then curl -O "http://ftp.gnome.org/pub/gnome/sources/glib/2.43/glib-2.43.2.tar.xz"; fi
#  rm -rf $LIB_NAME
#  tar -xf $LIB_NAME.tar.xz
#  mkdir -p $LIB_NAME/build-dir && cd $LIB_NAME/build-dir
#  ../configure --prefix=$INSTALL/$LIB_NAME
#  make -j$PROC_COUNT
#  make install
#  cd $WORKSPACE
#  rm -rf $LIB_NAME
#fi
