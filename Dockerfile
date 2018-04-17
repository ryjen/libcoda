FROM ryjen/cpp-coveralls

ARG CMAKE_DEFINES

ENV POSTGRES_VERS 9.5

RUN apt-get install -y \
    libjson-c-dev \
    libmysqlclient-dev \
    libpq-dev \
    libsqlite3-dev \
    uuid-dev \
    postgresql-server-dev-all \
    libboost-dev \
    libssl-dev libcurl4-openssl-dev liburiparser-dev

COPY . /usr/src

RUN mkdir -p /usr/src/build

WORKDIR /usr/src/build

RUN cmake ${CMAKE_DEFINES} -DPostgreSQL_TYPE_INCLUDE_DIR=/usr/include/postgresql/${POSTGRES_VERS}/server ..

RUN make

CMD "make", "test", "ARGS=-V"
