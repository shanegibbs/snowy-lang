#!/bin/bash -ex

TAG='unknown'

if [ ! -e /etc/lsb-release ]; then
  echo lsb-release not found
  exit 1
fi

. /etc/lsb-release

if [ "$DISTRIB_RELEASE" == "14.04" ]; then
  sudo apt-get install -y libc6-dev-i386 m4 libffi-dev gettext libedit-dev
  TAG='ubuntu-14.04'
elif [ "$DISTRIB_RELEASE" == "12.04" ]; then
  sudo apt-get install -y libc6-dev-i386 m4 libffi6-dev gettext libedit-dev
  TAG='ubuntu-12.04'
else
  echo Unsupported OS
  exit 1
fi

PROC_COUNT=8
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
  ../configure --enable-languages=c,c++ --disable-shared --enable-static --prefix=$INSTALL/gcc-4.8.4
  make -j$PROC_COUNT
  make install
  cd $WORKSPACE
  rm -rf gcc-4.8.4
fi

# add gcc to path
export PATH=$INSTALL/gcc-4.8.4/bin:$PATH

LIB_NAME=flex-2.5.39
export SNOWY_FLEX=$INSTALL/$LIB_NAME
if [ ! -e "$INSTALL/$LIB_NAME/bin/flex" ]; then
  export CFLAGS='-O3'
  export CXXFLAGS=$CFLAGS
  cd $WORKSPACE
  if [ ! -e "flex-2.5.39.tar.bz2" ]; then curl -O "http://hivelocity.dl.sourceforge.net/project/flex/flex-2.5.39.tar.bz2"; fi
  rm -rf $LIB_NAME
  tar -xf flex-2.5.39.tar.bz2
  mkdir -p $LIB_NAME/build && cd $LIB_NAME/build
  ../configure --prefix=$INSTALL/$LIB_NAME
  make -j$PROC_COUNT
  make install
  cd $WORKSPACE
  rm -rf $LIB_NAME
fi

LIB_NAME=bison-3.0.2
export SNOWY_BISON=$INSTALL/$LIB_NAME
if [ ! -e "$INSTALL/$LIB_NAME/bin/bison" ]; then
  export CFLAGS='-O3'
  export CXXFLAGS=$CFLAGS
  cd $WORKSPACE
  if [ ! -e "$LIB_NAME.tar.gz" ]; then curl -O "http://ftp.gnu.org/gnu/bison/$LIB_NAME.tar.gz"; fi
  rm -rf $LIB_NAME
  tar -xf $LIB_NAME.tar.gz
  mkdir -p $LIB_NAME/build && cd $LIB_NAME/build
  ../configure --prefix=$INSTALL/$LIB_NAME
  make -j$PROC_COUNT
  make install
  cd $WORKSPACE
  rm -rf $LIB_NAME
fi

LIB_NAME=llvm-3.5.0
export SNOWY_LLVM=$INSTALL/$LIB_NAME
if [ ! -e "$INSTALL/$LIB_NAME/bin/llvm-config" ]; then
  export CFLAGS='-O3'
  export CXXFLAGS=$CFLAGS
  cd $WORKSPACE
  if [ ! -e "$LIB_NAME.src.tar.xz" ]; then curl -O "http://llvm.org/releases/3.5.0/llvm-3.5.0.src.tar.xz"; fi
  rm -rf $LIB_NAME.src
  tar -xf $LIB_NAME.src.tar.xz
  mkdir -p $LIB_NAME.src/build && cd $LIB_NAME.src/build
  ../configure --prefix=$INSTALL/$LIB_NAME
  make -j$PROC_COUNT
  make install
  cd $WORKSPACE
  rm -rf $LIB_NAME.src
fi

LIB_NAME=glib-2.43.2
export SNOWY_GLIB=$INSTALL/$LIB_NAME
if [ ! -e "$INSTALL/$LIB_NAME/bin/llvm-config" ]; then
  export CFLAGS='-O3'
  export CXXFLAGS=$CFLAGS
  cd $WORKSPACE
  if [ ! -e "$LIB_NAME.tar.xz" ]; then curl -O "http://ftp.gnome.org/pub/gnome/sources/glib/2.43/glib-2.43.2.tar.xz"; fi
  rm -rf $LIB_NAME
  tar -xf $LIB_NAME.tar.xz
  mkdir -p $LIB_NAME/build-dir && cd $LIB_NAME/build-dir
  ../configure --prefix=$INSTALL/$LIB_NAME
  make -j$PROC_COUNT
  make install
  cd $WORKSPACE
  rm -rf $LIB_NAME
fi

export PATH=$SNOWY_GCC/bin:$SNOWY_LLVM/bin:$SNOWY_FLEX/bin:$SNOWY_BISON/bin:$SNOWY_GLIB/bin:$PATH
export PKG_CONFIG_PATH=$HOME/install/glib-2.43.2/lib/pkgconfig

exit 0
