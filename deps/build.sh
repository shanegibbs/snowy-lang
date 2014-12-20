#!/bin/bash -ex

# gcc
sudo apt-get install libgmp3c2 libgmp3-dev
sudo apt-get install libmpfr4 libmpfr-dev
sudo apt-get install libmpc2 libmpc-dev
sudo apt-get install libc6-dev-i386
sudo apt-get install m4

# glib
sudo apt-get install libffi6-dev
sudo apt-get install gettext

WORKSPACE=$PWD

curl -O http://mirrors.concertpass.com/gcc/releases/gcc-4.8.4/gcc-4.8.4.tar.bz2
tar -xjf gcc-4.8.4.tar.bz2
cd gcc-4.8.4
mkdir build && cd build
../configure CFLAGS='-g -O2 -I/usr/include/x86_64-linux-gnu' CXXFLAGS='-g -O2 -I/usr/include/x86_64-linux-gnu' --enable-languages=c,c++ --disable-shared --enable-static --prefix=$HOME/install/gcc-4.8.4
make -j8 install

# add gcc to path
export PATH=$HOME/install/gcc-4.8.4/bin:$PATH


cd $WORKSPACE
curl -O http://hivelocity.dl.sourceforge.net/project/flex/flex-2.5.39.tar.bz2
../configure CFLAGS='-g -O2' CXXFLAGS='-g -O2' --prefix=$HOME/install/flex-2.5.39

cd $WORKSPACE
curl -O 'http://ftp.gnu.org/gnu/bison/bison-3.0.2.tar.gz'
../configure CFLAGS='-g -O2' CXXFLAGS='-g -O2' --prefix=$HOME/install/bison-3.0.2

cd $WORKSPACE
curl -O 'http://llvm.org/releases/3.5.0/llvm-3.5.0.src.tar.xz'
../configure CFLAGS='-g -O2' CXXFLAGS='-g -O2' --prefix=$HOME/install/llvm-3.5.0

export PATH=$HOME/install/gcc-4.8.4/bin:$HOME/install/llvm-3.5.0/bin:$HOME/install/flex-2.5.39/bin:$HOME/install/bison-3.0.2/bin:$PATH

cd $WORKSPACE
curl -O 'http://ftp.gnome.org/pub/gnome/sources/glib/2.43/glib-2.43.2.tar.xz'
mkdir build-dir && cd build-dir
../configure CFLAGS='-g -O2' --prefix=$HOME/install/glib-2.43.2

export PKG_CONFIG_PATH=/home/sgibbs/install/glib-2.43.2/lib/pkgconfig

../configure
