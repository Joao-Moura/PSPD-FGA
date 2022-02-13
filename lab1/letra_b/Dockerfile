FROM ubuntu:latest
RUN apt-get update && \
    apt-get install -y\
    libc-dev-bin \
    rpcbind \
    build-essential

WORKDIR /server

COPY lab1_b*.c lab1_b.h lab1_b.x Makefile.docker ./
RUN mv Makefile.docker Makefile

COPY run_server .
