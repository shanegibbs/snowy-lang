#!/bin/bash -eu

export PREFIX=$HOME
export PROC_COUNT=`expr $(grep -c ^processor /proc/cpuinfo) + 1 `

echo PREFIX is $PREFIX
