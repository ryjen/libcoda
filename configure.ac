#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([arg3], [0.5], [c0der78@gmail.com])
AC_CONFIG_SRCDIR([src/config.h.in])
AC_CONFIG_HEADERS([src/config.h])
AM_INIT_AUTOMAKE([silent-rules check-news])
LT_INIT

: ${CXXFLAGS=""}

AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX([clang++ g++])
AC_PROG_CC

if test "x$CXX" = "xclang++"; then
  AC_SUBST([AM_CPPFLAGS], ["-std=c++11 -stdlib=libc++ -Wall -Werror"])
else
  AC_SUBST([AM_CPPFLAGS], ["-std=c++0x -Wall -Werror"])
fi

# Checks for libraries.
AC_CHECK_PROG(GIT_CHECK,git,yes)
if test x"$GIT_CHECK" != x"yes" ; then
    AC_MSG_ERROR([Required program 'git' not found.])
fi

#coverage

m4_include([m4/gcov.m4])
AC_TDD_GCOV
AC_SUBST(COVERAGE_CFLAGS)
AC_SUBST(COVERAGE_CXXFLAGS)
AC_SUBST(COVERAGE_LDFLAGS)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_MKTIME
AC_FUNC_REALLOC
AC_CHECK_FUNCS([strchr])

AC_CONFIG_FILES([Makefile arg3.pc
                 src/Makefile
                 src/collections/Makefile
                 src/log/Makefile
                 src/math/Makefile
                 src/string/Makefile
                 src/terminal/Makefile
                 tests/Makefile])

AC_CONFIG_SUBDIRS([src/db
                   src/dice
                   src/format
                   src/json
                   src/net])

AC_OUTPUT
