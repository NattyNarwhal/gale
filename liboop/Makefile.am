## Process this file with automake to generate Makefile.in

# Makefile.am, liboop, copyright 1999 Dan Egnor
#
# This is free software; you can redistribute it and/or modify it under the
# terms of the GNU Lesser General Public License, version 2.1 or later.
# See the file COPYING for details.

ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = foreign 1.7
lib_LTLIBRARIES = liboop.la @LIBOOP_LIBS@
EXTRA_LTLIBRARIES = liboop-adns.la

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = liboop.pc

# versions updated as of 1.0
liboop_la_LDFLAGS = -version-info 4:1:0 # version:revision:age
liboop_la_SOURCES = sys.c select.c signal.c alloc.c read.c read-fd.c read-mem.c

liboop_adns_la_LDFLAGS = -version-info 3:0:0 -rpath '$(libdir)'
liboop_adns_la_LIBADD = $(ADNS_LIBS)
liboop_adns_la_SOURCES = adns.c

include_HEADERS = oop.h oop-adns.h oop-read.h

noinst_PROGRAMS = test-oop

test_oop_SOURCES = test-oop.c
test_oop_CFLAGS =
test_oop_LDADD = liboop-adns.la liboop.la $(ADNS_LIBS)

release: dist
	gzip -dc $(PACKAGE)-$(VERSION).tar.gz | bzip2 -9 \
	> $(PACKAGE)-$(VERSION).tar.bz2
	if test -d /ofb/www/download/liboop ; then \
	cd /ofb/www/download/liboop && \
	mv "$(shell pwd)/$(PACKAGE)-$(VERSION)".* . && \
	ln -sf $(PACKAGE)-$(VERSION).tar.gz $(PACKAGE).tar.gz && \
	ln -sf $(PACKAGE)-$(VERSION).tar.bz2 $(PACKAGE).tar.bz2 ; \
	fi
	@echo '** NOW TAG THE CVS REPOSITORY! **'

install-exec-local:
	$(PROG_LDCONFIG) || true
