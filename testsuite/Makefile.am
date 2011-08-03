EXTRA_DIST = \
	answerset_compare.py \
	run-dlvhex-tests.sh

# global preprocessor flags
AM_CPPFLAGS = \
    -I$(top_srcdir)/include \
    $(BOOST_CPPFLAGS) \
	  $(DLVHEX_CFLAGS) \
    $(LIBXML2_CFLAGS) \
    @LIBCURL_CPPFLAGS@

# global linker flags
AM_LDFLAGS = $(BOOST_UNIT_TEST_FRAMEWORK_LDFLAGS)

# global libs
LIBS = $(BOOST_UNIT_TEST_FRAMEWORK_LIBS) $(LIBXML2_LIBS) @LIBCURL@ $(DLVHEX_LIBS)

TESTS = \
	xpath-unittest \
	run-dlvhex-tests.sh

TESTS_ENVIRONMENT = \
  TOP_SRCDIR=$(top_srcdir) \
  EXAMPLESDIR=$(top_builddir)/examples \
  TESTDIR=$(top_srcdir)/examples/tests \
  DLVHEX="dlvhex -s --plugindir=$(top_builddir)/src/.libs" \
  BOOST_TEST_SHOW_PROGRESS=yes \
  BOOST_TEST_REPORT_LEVEL=detailed \
  BOOST_TEST_LOG_LEVEL=all

check_PROGRAMS = xpath-unittest

xpath_unittest_SOURCES = xpath-unittest.cpp
xpath_unittest_LDADD = $(top_builddir)/src/libxpath-test.la
