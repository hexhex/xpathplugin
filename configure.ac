AC_PREREQ([2.61])
AC_INIT([dlvhex-xpathplugin],[1.7.0],[weinma@me.com])
AC_CONFIG_SRCDIR([src/xpathplugin.cpp])
AC_CONFIG_HEADER([src/config.h])

MAJOR=`echo $PACKAGE_VERSION | sed "s,^\([[0-9]]*\)\.\([[0-9]]*\)\.\([[0-9]]*\).*,\1,"`
MINOR=`echo $PACKAGE_VERSION | sed "s,^\([[0-9]]*\)\.\([[0-9]]*\)\.\([[0-9]]*\).*,\2,"`
MICRO=`echo $PACKAGE_VERSION | sed "s,^\([[0-9]]*\)\.\([[0-9]]*\)\.\([[0-9]]*\).*,\3,"`

# user corresponding names and texts here
AC_DEFINE_UNQUOTED([XPATH_MAJOR], [$MAJOR], [Major version number of the XPath-plugin])
AC_DEFINE_UNQUOTED([XPATH_MINOR], [$MINOR], [Minor version number of the XPath-plugin])
AC_DEFINE_UNQUOTED([XPATH_MICRO], [$MICRO], [Micro version number of the XPath-plugin])


AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_CXXCPP

# Checks for header files.
AC_HEADER_DIRENT
AC_CHECK_HEADERS([sys/param.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for libtool library functions.
AC_LIBTOOL_WIN32_DLL # enable win32 dll-building support
AC_LIBTOOL_DLOPEN # we build a module library
AC_DISABLE_STATIC # we don't need a static library
AC_PROG_LIBTOOL

#
# check for other libraries here
#

#
# of course we need dlvhex itself!
#
PKG_CHECK_MODULES([DLVHEX], [dlvhex >= 1.7])

# we want libxml2
PKG_CHECK_MODULES([LIBXML2], [libxml-2.0 >= 0.25])

# cppunit is optional -> give warning in ACTION-IF-NOT-FOUND
#PKG_CHECK_MODULES([CPPUNIT], [cppunit >= 1.12.0], [have_cppunit=true], [have_cppunit=false])
#if test x$have_cppunit = xfalse; then
#   AC_MSG_WARN([could not find cppunit >= 1.12.0, `make check' will fail. Please download it from http://cppunit.sourceforge.net/ and setup PKG_CONFIG_PATH appropriately.])
#fi


# checking for boost libs
BOOST_REQUIRE([1.41.0])

BOOST_SMART_PTR
BOOST_STRING_ALGO
BOOST_TOKENIZER
BOOST_TEST

#
# where the plugin will be installed by default.
# running configure will take sysplugindir from dlvhex.pc,
# running configure --enable-userinstall will take homeplugindir.
#

AC_ARG_ENABLE(userinstall, 
             [  --enable-userinstall    Install plugin into home directory],
             [plugindir=$HOME/`pkg-config dlvhex --variable=userplugindir`],
             [plugindir=`pkg-config dlvhex --variable=sysplugindir`]
             )
AC_SUBST([plugindir])

# doxygen stuff
#
# these are the defaults, can be overridden by --enable-doxygen-...
DX_HTML_FEATURE([ON])
DX_CHM_FEATURE([OFF])
DX_CHI_FEATURE([OFF])
DX_MAN_FEATURE([OFF])
DX_RTF_FEATURE([OFF])
DX_XML_FEATURE([OFF])
DX_PDF_FEATURE([OFF])
DX_PS_FEATURE([OFF])
DX_INIT_DOXYGEN([dlvhexxpathplugin], [doxygen.cfg], [documentation])

#
# set system-wide plugin dir
#
CPPFLAGS="$CPPFLAGS -DPLUGIN_DIR='\"\$(dlvhexlibdir)\"'"

#
# all needed makefiles
#
AC_CONFIG_FILES([
           Makefile 
           examples/Makefile
	   testsuite/Makefile
	   include/Makefile
           src/Makefile
])

AC_OUTPUT

