dnl Process this file with autoconf to produce a configure script.
AC_INIT([liboop],[1.0])
AC_CONFIG_SRCDIR(INSTALL)
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE
AC_CANONICAL_HOST
LT_INIT
AC_PROG_CC
AC_PROG_INSTALL
PROG_LDCONFIG=:

AC_ARG_WITH(adns, AS_HELP_STRING([--without-adns],[disable ADNS adapter]))

dnl System type checks.
case "$host" in
  *-linux-*)
    AC_PATH_PROG(PROG_LDCONFIG, ldconfig, :, $PATH:/usr/sbin:/sbin)
    no_wacky_libs=yes
    ;;
  *-sgi-irix6*)
    if test -n "$LPATH" ; then
      LDFLAGS="-Wl,-rpath,$LPATH $LDFLAGS"
    fi
    no_wacky_libs=yes
    ;;
esac

AC_CHECK_HEADERS(poll.h sys/select.h sys/socket.h string.h strings.h)

if test xno != x$with_adns; then
  AC_CHECK_LIB(adns,adns_init,[
    LIBOOP_LIBS="liboop-adns.la $LIBOOP_LIBS"
    ADNS_LIBS="-ladns"
    AC_DEFINE(HAVE_ADNS)
  ])
fi

if test -z "$no_wacky_libs" ; then
  AC_CHECK_LIB(resolv,res_query)
  AC_SEARCH_LIBS(gethostbyname,nsl)
  AC_SEARCH_LIBS(socket,socket)
fi

test yes = "$GCC" && 
CFLAGS="-Wall -Wno-comment -Wmissing-prototypes -Wstrict-prototypes -Wpointer-arith -Wwrite-strings $CFLAGS"' $(EXTRA_CFLAGS)'

AC_SUBST(PROG_LDCONFIG)
AC_SUBST(ADNS_LIBS)
AC_SUBST(LIBOOP_LIBS)
AC_CONFIG_FILES([Makefile liboop.pc])
AC_OUTPUT
