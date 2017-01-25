FROM ryjen/cpp-coveralls

ARG CMAKE_DEFINES

ENV POSTGRES_VERS 9.3

RUN apt-get install -y \
    libcurl4-openssl-dev \
    libjson-c-dev \
    libmysqlclient-dev \
    libpq-dev \
    libsqlite3-dev \
    uuid-dev \
    liburiparser-dev \
    postgresql-server-dev-all \
    libssl-dev libcurl4-openssl-dev \
    libboost-dev

COPY . /usr/src

RUN mkdir -p /usr/src/build

WORKDIR /usr/src/build

RUN cmake ${CMAKE_DEFINES} -DPostgreSQL_TYPE_INCLUDE_DIR=/usr/include/postgresql/${POSTGRES_VERS}/server ..

RUN make

CMD "make", "test", "ARGS=-V"
