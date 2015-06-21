FROM ubuntu:14.04

ADD build-packages.sh /tmp/build/
RUN /tmp/build/build-packages.sh

RUN useradd -m -s /bin/zsh snowy
USER snowy
WORKDIR /home/snowy
ENV HOME /home/snowy
RUN git clone --recursive https://github.com/shanegibbs/shanegibbs-dots.git /home/snowy/.shanegibbs-dots
RUN /home/snowy/.shanegibbs-dots/setup.sh

ENV SRCDIR /home/snowy/src

#ADD build-gcc.sh /tmp/build/
#RUN /tmp/build/build-gcc.sh

ADD zshrc-local /home/snowy/.zshrc-local

ADD build-llvm.sh /tmp/build/
RUN /tmp/build/build-llvm.sh

ADD build-flex.sh /tmp/build/
RUN /tmp/build/build-flex.sh

ADD build-bison.sh /tmp/build/
RUN /tmp/build/build-bison.sh

USER root
RUN echo snowy ALL=NOPASSWD: ALL > /etc/sudoers.d/snowy

USER snowy
CMD /bin/zsh -l
