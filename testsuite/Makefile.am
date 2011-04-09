EXTRA_DIST = \
    tests/xpath.test \
    tests/keywords.out \
    tests/nobelprice.out \
    tests/scientists.out \
    tests/run-dlvhex-tests.sh

# global preprocessor flags
AM_CPPFLAGS = \
    -I$(top_srcdir)/include \
    $(BOOST_CPPFLAGS) \
    $(LIBXML2_CFLAGS)

# global linker flags
AM_LDFLAGS = $(BOOST_UNIT_TEST_FRAMEWORK_LDFLAGS)

#TESTS = tests/run-dlvhex-tests.sh
#TESTS_ENVIRONMENT = DLVHEX=dlvhex TESTDIR=$(top_srcdir)/testsuite/tests PARAMETERS="-s --plugindir=$(top_builddir)/src/.libs <-- !!! NOT WORKING, WHY !!!"

# global libs
LIBS = $(BOOST_UNIT_TEST_FRAMEWORK_LIBS) $(LIBXML2_LIBS) $(DLVHEX_LIBS)

TESTS = xpath-unittest \
        tests/run-dlvhex-tests.sh
        
TESTS_ENVIRONMENT = EXAMPLESDIR=$(top_builddir)/examples BOOST_TEST_LOG_LEVEL=all BOOST_TEST_SHOW_PROGRESS=yes DLVHEX=dlvhex TESTDIR=$(top_srcdir)/testsuite/tests PARAMETERS="-s"

check_PROGRAMS = xpath-unittest

xpath_unittest_SOURCES = xpath-unittest.cpp
xpath_unittest_LDADD = $(top_builddir)/src/libdlvhexxpath-test.la
