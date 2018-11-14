FROM ryjen/cpp-coveralls

ARG CMAKE_DEFINES

RUN apk update

RUN apk add \
    json-c0.12-dev \
    mariadb-connector-c-dev \
    mariadb-client \
    libpq \
    sqlite-dev \
    libuuid \
    postgresql-dev \
    curl-dev \
    uriparser-dev

COPY . /usr/src

RUN mkdir -p /usr/src/build

WORKDIR /usr/src/build

RUN cmake ${CMAKE_DEFINES} -DPostgreSQL_TYPE_INCLUDE_DIR="$(pg_config --includedir-server)" ..

RUN make

CMD "make", "test", "ARGS=-V"
