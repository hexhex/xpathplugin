
AC_PREREQ([2.59])

#
#
AC_INIT([dlvhex-xpathplugin],[0.2.0],[daniel.scheikl@student.tuwien.ac.at])

# this refers to one of the sources, change it if you renamed the file
AC_CONFIG_SRCDIR([src/xpathplugin.cpp])

AC_CONFIG_HEADER([src/config.h])

MAJOR=`echo $PACKAGE_VERSION | sed "s/^\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/"`
MINOR=`echo $PACKAGE_VERSION | sed "s/^\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/"`
MICRO=`echo $PACKAGE_VERSION | sed "s/^\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/"`

# user corresponding names and texts here
AC_DEFINE_UNQUOTED([XPATH_MAJOR], [$MAJOR], [Major version number of the XPath-plugin])
AC_DEFINE_UNQUOTED([XPATH_MINOR], [$MINOR], [Minor version number of the XPath-plugin])
AC_DEFINE_UNQUOTED([XPATH_MICRO], [$MICRO], [Micro version number of the XPath-plugin])


AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for header files.
AC_HEADER_DIRENT
AC_CHECK_HEADERS([sys/param.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_LIBTOOL_DLOPEN
AC_DISABLE_STATIC # we don't need a static library
AC_PROG_LIBTOOL

#
# check for other libraries here
#

#check for XERCES
AC_CHECK_HEADERS([xercesc/util/XercesVersion.hpp],,AC_MSG_ERROR([can't find Xerces for C++ header files]))
AC_CHECK_LIB([xerces-c],[main],,AC_MSG_ERROR([can't find Xerces for C++ library]))

#check for XALAN
AC_CHECK_HEADERS([xalanc/Include/XalanVersion.hpp],,AC_MSG_ERROR([can't find Xalan for C++ header files]))
AC_CHECK_LIB([xalan-c],[main],,AC_MSG_ERROR([can't find Xalan for C++ library]))

#
# of course we need dlvhex itself!
#
PKG_CHECK_MODULES([DLVHEX], [dlvhex >= 1.4])

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
# all needed makefiles
#
AC_CONFIG_FILES([
           Makefile 
           src/Makefile
           testsuite/Makefile
])

AC_OUTPUT

