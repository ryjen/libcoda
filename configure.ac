#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([arg3], [0.5], [c0der78@gmail.com])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE
LT_INIT

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
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

AC_CONFIG_FILES([Makefile
                 arg3/Makefile
                 arg3/collections/Makefile
                 arg3/log/Makefile
                 arg3/math/Makefile
                 arg3/string/Makefile
                 arg3/terminal/Makefile
                 tests/Makefile])
AC_CONFIG_SUBDIRS([arg3/db
                   arg3/dice
                   arg3/format
                   arg3/json
                   arg3/net])
AC_OUTPUT
