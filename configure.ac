dnl Process this file with autoconf to produce a configure script.

AC_PREREQ([2.72])
AC_INIT([gale],[1.1happy])
AC_CONFIG_SRCDIR(INSTALL)
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS(include/gale/config.h:config.h.in)
AC_CANONICAL_HOST
AC_PROG_CC
LT_INIT
AM_MAINTAINER_MODE

AC_ARG_ENABLE(adns,
[  --enable-adns           use asynchronous DNS resolver],
[case "${enableval}" in
  yes) use_adns=true ;;
  no)  use_adns=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-adns]) ;;
esac],[use_adns=true])
if $use_adns ; then
  AC_DEFINE(HAVE_ADNS, 1, [The ADNS resolver library is available.])
fi

dnl Configure subpackages
AC_CONFIG_SUBDIRS(liboop)

no_wacky_libs=""
GALE_LIBS="\${top_builddir}/libgale/libgale.la"

dnl Checks for programs.
AC_PROG_INSTALL
AC_PROG_YACC
PROG_LDCONFIG=:

dnl Add special GCC warnings, but don't enable them yet.
warning_flags="$CFLAGS"
error_flags="$CFLAGS"
if test yes = "$GCC" ; then
  warning_flags="-Wall -Wno-comment $CFLAGS"
  error_flags="-Werror $warning_flags"
fi

dnl System type checks.
case "$host" in
  *-linux-*)
    AC_PATH_PROG(PROG_LDCONFIG, ldconfig, :, $PATH:/usr/sbin:/sbin)
    ;;
  *-sgi-irix6*)
    if test -n "$LPATH" ; then
      LDFLAGS="-Wl,-rpath,$LPATH $LDFLAGS"
    fi
    no_wacky_libs=yes
    AC_DEFINE(OS_IRIX, 1, [This is SGI IRIX.])
    ;;
  *-hp-hpux*)
    AC_DEFINE(OS_HPUX, 1, [This is Hewlett-Packard HP-UX.])
    ;;
  *-*-solaris2*)
    AC_DEFINE(OS_SOLARIS, 1, [This is Sun Solaris.])
    ;;
  *-*-*bsd*)
    AC_DEFINE(OS_BSD, 1, [This is a BSD-based operating system.])
    ;;
esac

dnl Checks for libraries.
if test -z "$no_wacky_libs" ; then
  AC_CHECK_LIB(nsl,main)
  AC_CHECK_LIB(socket,socket)
fi

termcap_lib=""
AC_CHECK_LIB(termcap,tgetent,[termcap_lib="-ltermcap"],[
  AC_CHECK_LIB(ncurses,tgetent)])
AC_CHECK_LIB(resolv,res_query)
AC_CHECK_FUNCS([wcwidth wcswidth])

PKG_CHECK_MODULES([SSL], [libcrypto libssl], [GALE_LIBS="$GALE_LIBS $SSL_LIBS"])

AM_ICONV
GALE_LIBS="$GALE_LIBS $LTLIBICONV"

AC_CHECK_LIB(dl,dlopen,[
  GALE_LIBS="$GALE_LIBS -ldl"
  AC_DEFINE(HAVE_LIBDL, 1, [The dynamic loader library is available.])])
PKG_CHECK_MODULES([READLINE], [readline], [
  AC_DEFINE(HAVE_LIBREADLINE, 1, [The GNU readline library is available.])],
  []);

PKG_CHECK_MODULES([GC], [bdw-gc], [GALE_LIBS="$GALE_LIBS $GC_LIBS"])

AC_MSG_CHECKING([for local copy of liboop])
if test -f "${srcdir}/liboop/oop.h"; then
  AC_MSG_RESULT(yes)
  CPPFLAGS="-I\${top_srcdir}/liboop $CPPFLAGS"
  build_liboop=true
  if $use_adns; then
    AC_CHECK_LIB(adns,adns_init,[:],[
      AC_MSG_ERROR([cannot find adns library, try configure --disable-adns])
    ])
    GALE_LIBS="$GALE_LIBS \${top_builddir}/liboop/liboop-adns.la"
  fi
  GALE_LIBS="$GALE_LIBS \${top_builddir}/liboop/liboop.la"
else
  AC_MSG_RESULT(no)
  AC_CHECK_LIB(oop,oop_sys_new,[:],[
    AC_MSG_ERROR([cannot find liboop library, see INSTALL directions])
  ])
  if $use_adns; then
    AC_CHECK_LIB(oop-adns,oop_adns_new,[:],[
      AC_MSG_ERROR([cannot find liboop-adns library, was liboop built for adns?])
    ],-loop)
    AC_CHECK_LIB(adns,adns_init,[:],[
      AC_MSG_ERROR([cannot find adns library, try configure --disable-adns])
    ])
    GALE_LIBS="$GALE_LIBS -loop-adns -loop -ladns"
  else
    GALE_LIBS="$GALE_LIBS -loop"
  fi
fi

GALE_LIBS="$GALE_LIBS $termcap_lib"

dnl Checks for header files.
AC_CHECK_HEADERS(sys/select.h curses.h term.h dlfcn.h readline/readline.h rune.h wchar.h)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(short)
AC_CHECK_SIZEOF(long)

dnl Output.

CFLAGS_NOWARN="$CFLAGS"
CFLAGS="$warning_flags"
CPPFLAGS="-I\${top_srcdir}/include -I\${top_builddir}/include $CPPFLAGS"
CPPFLAGS="-DGALE_SYS_DIR=\\\"${sysconfdir}/gale\\\" $CPPFLAGS"

AC_SUBST(CFLAGS_NOWARN)
AC_SUBST(GALE_LIBS)
AC_SUBST(SSL_LIBS)
AC_SUBST(GC_LIBS)
AC_SUBST(READLINE_LIBS)
AC_SUBST(PROG_LDCONFIG)

AM_CONDITIONAL(BUILD_LIBOOP,test x$build_liboop = xtrue)

AC_CONFIG_FILES([
	gale-config
	gale-install
	Makefile 
	libgale/Makefile 
	gsub/Makefile
	gsend/Makefile
	kutils/Makefile
	server/Makefile
	gdomain/Makefile
	include/Makefile 
	include/gale/Makefile
])
AC_OUTPUT
