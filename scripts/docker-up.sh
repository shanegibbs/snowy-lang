#!/bin/bash -u

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
source $DIR/docker-common.sh

if ! sudo docker inspect --format="{{ .State.Running }}" snowy-dev; then
    sudo docker run --detach --name snowy-dev --hostname snowy-dev -v "$DIR/..":/home/snowy/src --user root --entrypoint /usr/sbin/sshd -p 127.0.0.1:2222:22 --net bridge $IMAGE -D
fi

# sudo docker start snowy-dev
ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -i scripts/docker-ssh.key -p 2222 -l snowy localhost
