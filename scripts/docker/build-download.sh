#!/bin/bash -eu

cd $WORKDIR

download() {
    TAR_NAME=$1
    URL=$2
    echo Downloading $URL
    if [ ! -e "$TAR_NAME" ]; then curl -O "$URL"; fi
    tar -xf $TAR_NAME
}

download "gcc-4.8.4.tar.bz2" "http://mirrors.concertpass.com/gcc/releases/gcc-4.8.4/gcc-4.8.4.tar.bz2"
cd $WORKDIR/gcc-4.8.4
./contrib/download_prerequisites

download "llvm-3.5.0.src.tar.xz" "http://llvm.org/releases/3.5.0/llvm-3.5.0.src.tar.xz"
download "flex-2.5.39.tar.bz2" "http://hivelocity.dl.sourceforge.net/project/flex/flex-2.5.39.tar.bz2"
download "bison-3.0.2.tar.gz" "http://ftp.gnu.org/gnu/bison/bison-3.0.2.tar.gz"
