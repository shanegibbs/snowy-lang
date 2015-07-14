#!/bin/sh -ex

ld \
    -dynamic-linker /lib64/ld-linux-x86-64.so.2 \
    -o main \
    /usr/lib/x86_64-linux-gnu/crt1.o \
    /usr/lib/x86_64-linux-gnu/crti.o \
    /usr/lib/gcc/x86_64-linux-gnu/4.8/crtbegin.o \
    main.o \
    -lc \
    /usr/lib/gcc/x86_64-linux-gnu/4.8/crtend.o \
    /usr/lib/x86_64-linux-gnu/crtn.o
