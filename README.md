![Build Status](https://travis-ci.org/shanegibbs/snowy-lang.svg?branch=master)

# Snowy Lang

Example: [main.s](main.s)

Arithmetic

```
a = 1 + 2
```

String literal

```
a = "Hello World!!"
puts(a)
```

Logic

```
if (true)
end
```

Function

```
def add(a, b)
  a + b
end
```

Class

```
class MyClass do
  def one()
    1
  end
end
```

TODO:

* Operators (perhaps as functions on classes. need base Object?)

```
def int:operator+(int:lhs, int:rhs)
end
```

```
def bool:operator==(bool:lhs, bool:rhs)
end
```

## Hacking

Setup

```
git clone git@github.com:shanegibbs/snowy-lang.git && cd snowy-lang
sudo apt-get install -y docker.io
```

Enter the snowy development container. `~/src` inside the container is mounted to the project directory. Anything not stored in this directory will be lost when you leave the container.

```
./scripts/docker-console.sh
```

Run `build` to execute a standard build or rebuild after any changes. Build output goes to `~/build`.

```
build
```

The build bin path (`~/build/src/bin`) is on the default `PATH`, so to test the build simply:

```
# (due to zsh, you may need to run `rehash` after the first build)
echo 'puts("test")' |LOG_LEVEL=warn snowy
```

## Goals

* Learn C/C++ and autotools
* Get a basic language structure in place
 * Similar syntax to Ruby
 * Typing > Ruby typing
 * As powerful as C/C++ but easier to write
* Investigate questions

### Questions

* Why is dependency management so hard?
* Why are some of the most popular languages slow? (performance wise)
* Can (dynamic) memory management be easier?

### Notes

* Rust looks very interesting

#### Ruby and types

Even adding a simple type specifier to Ruby syntax breaks. Language syntax seems to be a delicate balancing act.

#### Type inference

The LLVM IR api naturally lends itself towards type inference. - Need to think of some corner cases.

### Ubuntu Quick Start

```
# Install dependencies
sudo apt-get install build-essential autoconf llvm-3.6 llvm-3.6-dev llvm-3.6-runtime clang-3.6 llvm-3.6-tools libedit-dev bison flex

# Configure
./autogen.sh
mkdir build && cd build
../scripts/configure.ubuntu.sh

# Build and test
ASAN_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer-3.5 make -j check

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

### Testing

Assuming you have run `./scripts/docker-console.sh`.

Build and run test suite.

```
build
```

Debug single test without leak detection.

```
ASAN_OPTIONS=detect_leaks=0 LOG_LEVEL=debug SnowyTestSuite /IT/if/nested/true
```
