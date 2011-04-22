EXTRA_DIST = \
    tests/xpath.test \
    tests/keywords.out \
    tests/nobelprice.out \
    tests/scientists.out \
    tests/run-dlvhex-tests.sh \
    answerset_compare.py

# global preprocessor flags
AM_CPPFLAGS = \
    -I$(top_srcdir)/include \
    $(BOOST_CPPFLAGS) \
    $(LIBXML2_CFLAGS) \
    @LIBCURL_CPPFLAGS@

# global linker flags
AM_LDFLAGS = $(BOOST_UNIT_TEST_FRAMEWORK_LDFLAGS)

# global libs
LIBS = $(BOOST_UNIT_TEST_FRAMEWORK_LIBS) $(LIBXML2_LIBS) @LIBCURL@ $(DLVHEX_LIBS)

TESTS = xpath-unittest \
        tests/run-dlvhex-tests.sh

TESTS_ENVIRONMENT = TOPSRCDIR=$(top_srcdir) TOPBUILDDIR=$(top_builddir) BOOST_TEST_LOG_LEVEL=all BOOST_TEST_SHOW_PROGRESS=yes

check_PROGRAMS = xpath-unittest

xpath_unittest_SOURCES = xpath-unittest.cpp
xpath_unittest_LDADD = $(top_builddir)/src/libxpath-test.la
