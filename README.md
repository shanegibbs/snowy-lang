![Build Status]
(https://travis-ci.org/shanegibbs/snowy-lang.svg?branch=master)

# Snowy Lang

## Getting Started

### Generating the configure script

```
# ./autogen.sh
```

### Run configure script

Create a build directory:

```
# mkdir build
# cd build
```

There are some pre setup scripts you can use. For ubuntu, run `../scripts/configure.ubuntu.sh`. For mac, run `../scripts/configure.mac.sh`. Or you can run configure with your own options:

```
# ../configure CXX=clang++ CXXFLAGS='-g' LDFLAGS=-L/usr/local/lib CFLAGS=-I/usr/local/include --enable-debug
```

## Dependencies

* bison (GNU Bison) 3.0.2
* flex 2.5.35 Apple(flex-31)
* llvm 3.5.0

### Ubuntu

```
sudo apt-get install build-essential autoconf clang-3.5 llvm-3.5 llvm-3.5-dev libedit-dev libglib2.0-0 libglib2.0-dev bison flex
```
