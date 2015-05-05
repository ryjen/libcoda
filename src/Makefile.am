
SUBDIRS = collections db dice format json log math net string terminal variant

lib_LTLIBRARIES = libarg3.la

libarg3_la_SOURCES = arg3.cpp

# link with the hand library.
libarg3_la_LIBADD = db/src/libarg3db.la dice/src/libarg3dice.la format/src/libarg3fmt.la json/src/libarg3json.la net/src/libarg3net.la variant/src/libarg3variant.la log/libarg3log.la math/libarg3math.la string/libarg3str.la terminal/libarg3term.la

pkginclude_HEADERS = thread/later.h
