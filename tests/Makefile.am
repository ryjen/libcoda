
noinst_PROGRAMS = arg3_test

arg3_test_SOURCES = arg3.test.cpp argument.test.cpp collections.test.cpp log.test.cpp string.test.cpp

AM_CPPFLAGS = -std=c++11 -stdlib=libc++ -Ivendor -Wall -Werror

arg3_test_LDADD =  ../src/format/src/libarg3fmt-0.2.la ../src/string/libarg3str-0.1.la ../src/log/libarg3log-0.1.la
