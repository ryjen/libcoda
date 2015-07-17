
check_PROGRAMS = arg3_test

arg3_test_SOURCES = arg3.test.cpp argument.test.cpp collections.test.cpp log.test.cpp string.test.cpp buffer.test.cpp terminal.test.cpp

AM_CPPFLAGS = @AM_CPPFLAGS@ -Ivendor/bandit

arg3_test_LDADD =  ../src/format/src/libarg3fmt.la ../src/string/libarg3str.la ../src/log/libarg3log.la ../src/terminal/libarg3term.la

check: arg3_test
	./arg3_test

