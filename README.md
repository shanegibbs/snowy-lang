![Build Status]
(https://travis-ci.org/shanegibbs/snowy-lang.svg?branch=master)

# Snowy Lang

## Goals

* Learn C/C++ and autotools
* Get a basic language structure in place
 * Similar syntax to Ruby
 * Typing > Ruby typing
 * As powerful as C/C++ but easier to wite
* Invistigate questions

### Questions

* Why is dependency management so hard?
* Why are some of the most popular languages so slow? (performance wise)
* Can memory management be easier?

### Notes

#### Ruby and types

Even adding a simple type specifier to Ruby syntax breaks. Language syntax seems to be a delicate balancing act.

#### Type inference

The LLVM IR api naturally lends itself towards type inference. - Need to think of some corner cases.

### Ubuntu Quick Start

```
# Install dependencies
sudo apt-get install build-essential autoconf clang-3.5 llvm-3.5 llvm-3.5-dev libedit-dev bison flex

# Configure
./autogen.sh
mkdir build && cd build
../scripts/configure.ubuntu.sh

# Build and test
make -j check

# Run
echo 'puts("Hello World!!")' | ./src/bin/snowy
```

## Dependencies

* bison (GNU Bison) 3.0.2
* flex 2.5.35
* llvm 3.5.0

## Building

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
