#!/bin/bash -ex

if [ ! -e /etc/lsb-release ]; then
  echo lsb-release not found
  exit 1
fi

. /etc/lsb-release

if [ "$DISTRIB_RELEASE" == "14.04" ]; then
  sudo apt-get install -y libc6-dev-i386 m4 libffi-dev gettext wget build-essential libncurses5-dev zlib1g-dev pkg-config groff
elif [ "$DISTRIB_RELEASE" == "12.04" ]; then
  sudo apt-get install -y libc6-dev-i386 m4 libffi-dev gettext wget build-essential libncurses5-dev zlib1g-dev pkg-config groff
else
  echo Unsupported OS
  exit 1
fi

PROC_COUNT=`expr $(grep -c ^processor /proc/cpuinfo) + 1 `
echo Using PROC_COUNT $PROC_COUNT

WORKSPACE=$PWD/build
mkdir -p $WORKSPACE

INSTALL=$HOME/snowy-deps

function build() {
LIB_NAME=$1
TAR_NAME=$2
DIR_NAME=$3
URL=$4
TEST_FILE=$5
CONF=$6
if [ ! -e "$INSTALL/$TEST_FILE" ]; then
  cd $WORKSPACE
  if [ ! -e "$TAR_NAME" ]; then curl -O "$URL"; fi
  rm -rf $DIR_NAME

  tar -xf $TAR_NAME

  if [ "$TEST_FILE" == "bin/llvm-config" ]; then
    curl -O "http://llvm.org/releases/3.5.0/cfe-3.5.0.src.tar.xz"
    tar -xf cfe-3.5.0.src.tar.xz
    mv cfe-3.5.0.src $DIR_NAME/tools/clang
  fi

  cd $DIR_NAME

  # for gcc
  if [ -f "contrib/download_prerequisites" ]; then
    ./contrib/download_prerequisites
  fi

  mkdir snowy-build && cd snowy-build
  ../configure CC="$CC" CXX="$CXX" CFLAGS="$CFLAGS" CXXFLAGS="$CXXFLAGS" --prefix=$INSTALL $CONF
  make -j$PROC_COUNT 2>&1
  make install

  cd $WORKSPACE
  rm -rf $DIR_NAME
fi
}

export CFLAGS='-O3 -I/usr/include/x86_64-linux-gnu'
export CXXFLAGS=$CFLAGS

build "gcc-4.8.4" "gcc-4.8.4.tar.bz2" "gcc-4.8.4" \
  "http://mirrors.concertpass.com/gcc/releases/gcc-4.8.4/gcc-4.8.4.tar.bz2" "bin/gcc" \
  "--enable-languages=c,c++"

# add gcc to path
export PATH=$INSTALL/bin:$PATH
export CC="$INSTALL/bin/gcc"
export CFLAGS="-O3 -Wl,--rpath=$INSTALL/lib64 -Wl,--rpath=$INSTALL/lib -L$INSTALL/lib64 -L$INSTALL/lib -I$INSTALL/include"
export CXX="$INSTALL/bin/g++"
export CXXFLAGS=$CFLAGS
export LD_SEARCH_PATH=$INSTALL/lib:$INSTALL/lib64
export PKG_CONFIG_PATH=$INSTALL/lib/pkgconfig

build "llvm-3.5.0" "llvm-3.5.0.src.tar.xz" "llvm-3.5.0.src" \
  "http://llvm.org/releases/3.5.0/llvm-3.5.0.src.tar.xz" "bin/llvm-config" \
  "--enable-optimized --enable-targets=x86_64 --disable-terminfo --disable-libedit"

export CC="$INSTALL/bin/clang"
export CXX="$INSTALL/bin/clang++"

build "flex-2.5.39" "flex-2.5.39.tar.bz2" "flex-2.5.39" \
  "http://hivelocity.dl.sourceforge.net/project/flex/flex-2.5.39.tar.bz2" "bin/flex" \
  ""

build "bison-3.0.2" "bison-3.0.2.tar.gz" "bison-3.0.2" \
  "http://ftp.gnu.org/gnu/bison/bison-3.0.2.tar.gz" "bin/bison" \
  ""

# build "libedit-3.1" "libedit-20141030-3.1.tar.gz" "libedit-20141029-3.1" \
#   "http://thrysoee.dk/editline/libedit-20141030-3.1.tar.gz" "lib/libedit.a" \
#   ""

build "glib-2.43.2" "glib-2.43.2.tar.xz" "glib-2.43.2" \
  "http://ftp.gnome.org/pub/gnome/sources/glib/2.43/glib-2.43.2.tar.xz" "lib/libedit.a" \
  ""
