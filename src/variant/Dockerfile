
FROM ryjen/cpp-coveralls

ARG CMAKE_DEFINES

RUN mkdir -p /usr/src/build

ADD . /usr/src

WORKDIR /usr/src/build

RUN cmake ${CMAKE_DEFINES} ..

RUN make

CMD "make", "test", "ARGS=-V"
