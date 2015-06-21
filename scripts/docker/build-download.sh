#!/bin/bash -eu

cd $SRCDIR

download() {
    URL=$1
    ARGS=$2
    echo Downloading $URL
    curl "$URL" |tar $ARGS
}

#download "http://mirrors.concertpass.com/gcc/releases/gcc-4.8.4/gcc-4.8.4.tar.bz2" "xj"
download "http://llvm.org/releases/3.5.0/llvm-3.5.0.src.tar.xz" "xJ"
download "http://hivelocity.dl.sourceforge.net/project/flex/flex-2.5.39.tar.bz2" "xj"
download "http://ftp.gnu.org/gnu/bison/bison-3.0.2.tar.gz" "xz"

cd $SRCDIR/gcc-4.8.4
./contrib/download_prerequisites

cd $SRCDIR/llvm-3.5.0.src/tools
curl "http://llvm.org/releases/3.5.0/cfe-3.5.0.src.tar.xz" |tar xJ
mv cfe-3.5.0.src clang
