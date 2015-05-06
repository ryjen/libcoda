#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.58])
AC_INIT([arg3], [0.5.1], [c0der78@gmail.com], [libarg3], [http://github.com/c0der78/libarg3/archive/0.5.1.tar.gz])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([silent-rules check-news])
#AM_MAINTAINER_MODE([enable])

LT_INIT

: ${CXXFLAGS=""}

AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX([clang++ g++])
AC_PROG_CC
AC_PROG_AWK
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB


if test "x$CXX" = "xclang++"; then
  AC_SUBST([AM_CPPFLAGS], ["-std=c++11 -stdlib=libc++ -Wall -Werror"])
else
  AC_SUBST([AM_CPPFLAGS], ["-std=c++11 -Wall -Werror"])
fi

# Checks for libraries.
AC_CHECK_LIB(uuid, uuid_generate_random)

# if a git enabled folder...
if test -d .git ; then
  
  # get the git program
  AC_CHECK_PROG(GIT_CHECK,git,yes)

  # require git
  if test x"$GIT_CHECK" != x"yes" ; then
      AC_MSG_ERROR([Required program 'git' not found.])
  else
      # update the submodules
      git submodule update --init --recursive
  fi
fi

# coverage
m4_include([m4/gcov.m4])
AC_TDD_GCOV
AC_SUBST(COVERAGE_CFLAGS)
AC_SUBST(COVERAGE_CXXFLAGS)
AC_SUBST(COVERAGE_LDFLAGS)

# Checks for header files.
AC_CHECK_HEADERS([string.h])
AC_CHECK_HEADERS([uuid/uuid.h])

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
AC_CHECK_FUNCS([strchr strcpy strstr])

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
                   src/net 
                   src/variant])

AC_OUTPUT
