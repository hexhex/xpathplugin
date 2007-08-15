AUTOMAKE_OPTIONS = gnu

EXTRA_DIST = \
    xpath.test \
    keywords.hex \
    keywords.out \
    nobelprice.hex \
    nobelprice.out \
    scientists.hex \
    scientists.out \
    scientists.xml \
	 run-dlvhex-tests.sh

TESTS = run-dlvhex-tests.sh

TESTS_ENVIRONMENT = TESTDIR=$(top_srcdir)/testsuite DLVHEX=dlvhex PARAMETERS="-s --plugindir=$(top_builddir)/src/.libs"

DISTCLEANFILES = $(top_builddir)/testsuite/scientists.xml
