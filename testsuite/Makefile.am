#
# replace 'plugin' on the right side by your plugin's name
#
plugin_LTLIBRARIES = libdlvhexxpath.la

#
# replace 'plugin' on the left side as above and
# add all sources of your plugin
#
libdlvhexxpath_la_SOURCES =	xpathplugin.cpp \
				xpathatom.cpp

#
# extend compiler flags by CFLAGS of other needed libraries
#
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	$(DLVHEX_CFLAGS) \
	$(LIBXML2_CFLAGS)

#
# replace 'plugin' on the left side as above and
# add other needed libs to linker flags if necessary
#

libdlvhexxpath_la_LDFLAGS = -avoid-version -module \
			$(LIBXML2_LIBS) 


