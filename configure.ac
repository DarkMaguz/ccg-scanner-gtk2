dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(CCG_Scanner-gtk2, 1.0)


AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE()

AC_PROG_CXX

dnl ###########################################################################
dnl Dependencies
dnl ###########################################################################

PKG_CHECK_MODULES([CCGS], [
	gtkmm-2.4 >= 2.24.4
	glibmm-2.4 >= 2.42.0
	opencv >= 2.4.9.1
	uchardet >= 0.0.1
])

AC_CONFIG_FILES(Makefile src/Makefile src/examples/Makefile)
AC_OUTPUT

