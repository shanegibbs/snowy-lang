FROM ubuntu:14.04

WORKDIR /tmp/build
ENV WORKDIR /tmp/build

ADD build-packages.sh /tmp/build/
RUN ./build-packages.sh

ADD build-download.sh /tmp/build/
RUN ./build-download.sh

RUN useradd -m -s /bin/zsh snowy
ADD common.sh /tmp/build/

ADD build-gcc.sh /tmp/build/
RUN su -l snowy -c "env WORKDIR=${WORKDIR} /tmp/build/build-gcc.sh"
