FROM ubuntu:15.10

RUN apt-get update && apt-get install -y \
	  git \
	  build-essential \
    make \
    gcc \
    libcurl4-openssl-dev \
    libjson0-dev \
    libmysqlclient-dev \
    libpq-dev \
    libsqlite3-dev \
    lcov \
    valgrind \
    openssl \
    uuid-dev \
    liburiparser-dev \
    cmake \
    cmake-data

COPY . libarg3

WORKDIR libarg3

RUN mkdir -p build && cd build && \
    cmake .. && make && make test
    