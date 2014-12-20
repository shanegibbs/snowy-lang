#!/bin/bash -ex

TAG='unknown'

if [ ! -e /etc/lsb-release ]; then
  echo lsb-release not found
  exit 1
fi

. /etc/lsb-release

if [ "$DISTRIB_RELEASE" == "14.04" ]; then
  sudo apt-get install -y libgmp10 libgmp3-dev libmpfr4 libmpfr-dev libmpc3 libmpc-dev libc6-dev-i386 m4 libffi-dev gettext
  TAG='ubuntu-14.04'
elif [ "$DISTRIB_RELEASE" == "12.04" ]; then
  sudo apt-get install -y libgmp3c2 libgmp3-dev libmpfr4 libmpfr-dev libmpc2 libmpc-dev libc6-dev-i386 m4 libffi6-dev gettext
  TAG='ubuntu-12.04'
else
  echo Unsupported OS
  exit 1
fi

WORKSPACE=$PWD/build
mkdir -p $WORKSPACE

INSTALL=$HOME/snowy-deps/$TAG

if [ ! -e "$INSTALL/gcc-4.8.4/bin/gcc" ]; then
  export CFLAGS='-g -O2 -I/usr/include/x86_64-linux-gnu'
  export CXXFLAGS=$CFLAGS

  cd $WORKSPACE
  if [ ! -e gcc-4.8.4.tar.bz2 ]; then curl -O 'http://mirrors.concertpass.com/gcc/releases/gcc-4.8.4/gcc-4.8.4.tar.bz2'; fi
  rm -rf gcc-4.8.4
  tar -xjf gcc-4.8.4.tar.bz2
  cd gcc-4.8.4
  mkdir build && cd build
  ../configure --enable-languages=c,c++ --disable-shared --enable-static --prefix=$INSTALL/gcc-4.8.4
  make -j8
  make install
  cd $WORKSPACE
  rm -rf gcc-4.8.4
fi

# add gcc to path
export PATH=$INSTALL/gcc-4.8.4/bin:$PATH

LIB_NAME=flex-2.5.39
if [ ! -e "$INSTALL/$LIB_NAME/bin/flex" ]; then
  export CFLAGS='-g -O2'
  export CXXFLAGS=$CFLAGS
  cd $WORKSPACE
  if [ ! -e "flex-2.5.39.tar.bz2" ]; then curl -O "http://hivelocity.dl.sourceforge.net/project/flex/flex-2.5.39.tar.bz2"; fi
  rm -rf $LIB_NAME
  tar -xf flex-2.5.39.tar.bz2
  mkdir -p $LIB_NAME/build && cd $LIB_NAME/build
  ../configure --prefix=$INSTALL/$LIB_NAME
  make -j8
  make install
  cd $WORKSPACE
  rm -rf $LIB_NAME
fi

LIB_NAME=bison-3.0.2
if [ ! -e "$INSTALL/$LIB_NAME/bin/bison" ]; then
  export CFLAGS='-g -O2'
  export CXXFLAGS=$CFLAGS
  cd $WORKSPACE
  if [ ! -e "$LIB_NAME.tar.gz" ]; then curl -O "http://ftp.gnu.org/gnu/bison/$LIB_NAME.tar.gz"; fi
  rm -rf $LIB_NAME
  tar -xf $LIB_NAME.tar.gz
  mkdir -p $LIB_NAME/build && cd $LIB_NAME/build
  ../configure --prefix=$INSTALL/$LIB_NAME
  make -j8
  make install
  cd $WORKSPACE
  rm -rf $LIB_NAME
fi

LIB_NAME=llvm-3.5.0
if [ ! -e "$INSTALL/$LIB_NAME/bin/llvm-config" ]; then
  export CFLAGS='-g -O2'
  export CXXFLAGS=$CFLAGS
  cd $WORKSPACE
  if [ ! -e "$LIB_NAME.src.tar.xz" ]; then curl -O "http://llvm.org/releases/3.5.0/llvm-3.5.0.src.tar.xz"; fi
  rm -rf $LIB_NAME.src
  tar -xf $LIB_NAME.src.tar.xz
  mkdir -p $LIB_NAME.src/build && cd $LIB_NAME.src/build
  ../configure --prefix=$INSTALL/$LIB_NAME
  make -j8
  make install
  cd $WORKSPACE
  rm -rf $LIB_NAME.src
fi

LIB_NAME=glib-2.43.2
if [ ! -e "$INSTALL/$LIB_NAME/bin/llvm-config" ]; then
  export CFLAGS='-g -O2'
  export CXXFLAGS=$CFLAGS
  cd $WORKSPACE
  if [ ! -e "$LIB_NAME.tar.xz" ]; then curl -O "http://ftp.gnome.org/pub/gnome/sources/glib/2.43/glib-2.43.2.tar.xz"; fi
  rm -rf $LIB_NAME
  tar -xf $LIB_NAME.tar.xz
  mkdir -p $LIB_NAME/build-dir && cd $LIB_NAME/build-dir
  ../configure --prefix=$INSTALL/$LIB_NAME
  make -j8
  make install
  cd $WORKSPACE
  rm -rf $LIB_NAME
fi

exit 0


cd $WORKSPACE
curl -O 'http://ftp.gnome.org/pub/gnome/sources/glib/2.43/glib-2.43.2.tar.xz'
mkdir build-dir && cd build-dir
../configure CFLAGS='-g -O2' --prefix=$HOME/install/glib-2.43.2

export PATH=$HOME/install/gcc-4.8.4/bin:$HOME/install/llvm-3.5.0/bin:$HOME/install/flex-2.5.39/bin:$HOME/install/bison-3.0.2/bin:$PATH
export PKG_CONFIG_PATH=/home/sgibbs/install/glib-2.43.2/lib/pkgconfig

../configure
