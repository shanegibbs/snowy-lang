#!/bin/bash -u

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
source $DIR/docker-common.sh

sudo docker run --rm -tv "$DIR/..":/home/snowy/src $IMAGE build
