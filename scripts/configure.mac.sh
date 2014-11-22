#!/bin/sh

../configure CXX=clang++ LDFLAGS=-L/usr/local/lib CFLAGS=-I/usr/local/include --enable-debug
