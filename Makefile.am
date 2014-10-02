EXTRA_DIST = update_dependencies.sh

SUBDIRS = src tests

include $(top_srcdir)/Makefile.am.coverage

pkgconfigdir = $(libdir)/pkgconfig
nodist_pkgconfig_DATA = arg3.pc

test: check

