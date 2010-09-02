#
# replace 'plugin' on the right side by your plugin's name
#
plugin_LTLIBRARIES = libdlvhexxpath.la

#
# replace 'plugin' on the left side as above and
# add all sources of your plugin
#
libdlvhexxpath_la_SOURCES =	xpathplugin.cpp \
				myerrorhandler.cpp \
				xpathatom.cpp

#
# extend compiler flags by CFLAGS of other needed libraries
#
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	$(DLVHEX_CFLAGS) \
	-l/opt/local/include/xercesc \
   -l/opt/local/include/xalanc 


#
# replace 'plugin' on the left side as above and
# add other needed libs to linker flags if necessary
#
libdlvhexxpath_la_LDFLAGS = -avoid-version -module \
										-lxerces-c \
										-lxalan-c \
										-lxalanMsg

