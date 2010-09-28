#
# create libtool libraries for the plugin and for local tests
#
plugin_LTLIBRARIES = libdlvhexxpath.la
noinst_LTLIBRARIES = libdlvhexxpath-test.la

#
# add all sources of xpath plugin and test library
#
libdlvhexxpath_la_SOURCES = xpathplugin.cpp xpathatom.cpp
libdlvhexxpath_test_la_SOURCES = xpathplugin.cpp xpathatom.cpp

#
# extend compiler flags by CFLAGS of other needed libraries
#
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	$(BOOST_CPPFLAGS) \
	$(DLVHEX_CFLAGS) \
	$(LIBXML2_CFLAGS)

#
# add other needed libs to linker flags if necessary
#
libdlvhexxpath_la_LDFLAGS = -avoid-version -module \
			$(LIBXML2_LIBS) 

libdlvhexxpath_test_la_LDFLAGS = $(LIBXML2_LIBS) 


