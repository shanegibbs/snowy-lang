#!/bin/bash

find /home/snowy/src/{src,tests} -type f \( -name '*.cpp' -or -name '*.h' \) |xargs clang-format -style=google -i
