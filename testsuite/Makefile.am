# global preprocessor flags
AM_CPPFLAGS = \
    -I$(top_srcdir)/include \
    $(BOOST_CPPFLAGS) \
    $(LIBXML2_CFLAGS)

# global linker flags
AM_LDFLAGS = $(BOOST_UNIT_TEST_FRAMEWORK_LDFLAGS)

# global libs
LIBS = $(BOOST_UNIT_TEST_FRAMEWORK_LIBS) $(LIBXML2_LIBS) $(DLVHEX_LIBS)

TESTS = xpath-unittest

TESTS_ENVIRONMENT = EXAMPLESDIR=$(top_srcdir)/examples BOOST_TEST_LOG_LEVEL=all BOOST_TEST_SHOW_PROGRESS=yes

check_PROGRAMS = xpath-unittest

xpath_unittest_SOURCES = xpath-unittest.cpp
xpath_unittest_LDADD = $(top_builddir)/src/libdlvhexxpath-test.la
