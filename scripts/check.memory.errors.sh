#!/bin/sh
valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind.log --num-callers=50 --error-exitcode=1 ./tests/SnowyTestSuite
