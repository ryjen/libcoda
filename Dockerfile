FROM ryjen/cpp-coveralls

ARG CMAKE_DEFINES

RUN apt-get install -y \	  
    libcurl4-openssl-dev \
    libjson-c-dev \
    libmysqlclient-dev \
    libpq-dev \
    libsqlite3-dev \
    uuid-dev \
    liburiparser-dev

COPY . /usr/src

RUN mkdir -p /usr/src/build

WORKDIR /usr/src/build

RUN cmake ${CMAKE_DEFINES} ..

RUN make

CMD "make", "test", "ARGS=-V"
