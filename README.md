![Build Status]
(https://travis-ci.org/shanegibbs/snowy-lang.svg?branch=master)

# Snowy Lang

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
