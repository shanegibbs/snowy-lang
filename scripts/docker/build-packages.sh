#!/bin/bash -eu

if [ ! -e /etc/lsb-release ]; then
  echo lsb-release not found
  exit 1
fi

. /etc/lsb-release

apt-get update

PACKAGES="libc6-dev-i386 m4 libffi-dev gettext curl wget build-essential libncurses5-dev zlib1g-dev pkg-config groff"
PACKAGES="$PACKAGES zsh vim tmux"

if [ "$DISTRIB_RELEASE" == "14.04" ]; then
  sudo apt-get install -y $PACKAGES
elif [ "$DISTRIB_RELEASE" == "12.04" ]; then
  sudo apt-get install -y $PACKAGES
else
  echo Unsupported OS
  exit 1
fi
