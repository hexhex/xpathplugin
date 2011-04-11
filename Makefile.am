AUTOMAKE_OPTIONS = gnu 1.10

ACLOCAL_AMFLAGS = -I m4
include doxygen.am

SUBDIRS = \
	src \
	testsuite \
	include 

EXTRA_DIST = \
	doxygen.am \
	doxygen.cfg \
    examples/keywords.hex \
    examples/nobelprice.hex \
    examples/scientists.hex \
    examples/scientists_err.xml \
    examples/scientists.xml

MOSTLYCLEANFILES = $(DX_CLEANFILES)
