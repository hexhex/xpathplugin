AUTOMAKE_OPTIONS = gnu 1.10

ACLOCAL_AMFLAGS = -I m4
include doxygen.am

SUBDIRS = \
	src \
	testsuite \
        examples \
	include

EXTRA_DIST = \
	doxygen.am \
	doxygen.cfg

MOSTLYCLEANFILES = $(DX_CLEANFILES)
