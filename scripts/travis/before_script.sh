#!/bin/bash -ex

curl -O 'https://s3-us-west-2.amazonaws.com/snowy-lang/deps/travis/snowy-deps.tar.bz'
tar -xf snowy-deps.tar.bz -C $HOME
