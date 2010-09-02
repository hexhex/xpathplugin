/* -*- C++ -*- */
/** 
 * @mainpage XPath Plugin Documentation
 * The XPath plugin is developed for <A HREF="http://www.kr.tuwien.ac.at/research/systems/dlvhex/">dlvhex</A>. It allows dlvhex programs
 * to read atomic values from XML files using <A HREF="http://www.w3.org/TR/xpath">XPath</A> queries.
 * 
 * @section using_xpath Using the XPath atom
 * Like every other external dlvhex atom the XPath atom has to start with the ampersand sign '&'. It takes to
 * constant input parameters (an URI to a XML file and the XPath query) and has one output variable for the result set
 * of the XPath query: <BR><BR>
 * <CENTER>
 * <B>&xpath[uri,xpath_query](X)</B>.
 * </CENTER>
 * 
 * @section example_sec Example
 * <CENTER>
 * female_scientists(X) :- &xpath["/path/to/XMLfile/scientists.xml","//scientist[@gender='female']/@name"](X).
 * </CENTER>
 * <BR><BR>
 * <HR>
 * <VAR>Please note:</VAR> This plugin requires <A HREF="http://xml.apache.org/xerces-c/">Xerces-C++ v2.7.0</A>
 * and <A HREF="http://xml.apache.org/xalan-c/">Xalan-C++ v1.10</A>.
 * 
 * @author <A HREF="mailto:gamsta@gmx.net">Juergen Weinberger</A>
 * @date 2.9.2010  
 */


/** 
 * @file   xpathplugin.hpp
 * @brief  Plugin to evaluate XPath queries.
 * @author <A HREF="mailto:gamsta@gmx.net">Juergen Weinberger</A>
 * @date 2.9.2010  
 * 
 * 
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <string>
#include <locale.h>

#include "dlvhex/PluginInterface.h"

#include "xpathatom.hpp"

namespace dlvhex {
	namespace xpath {

class XPathPlugin : public PluginInterface {
public:
	virtual void getAtoms(AtomFunctionMap& a);
   
    	// process options that were given to dlvhex
    	void setOptions(bool doHelp, std::vector<std::string>& argv, std::ostream& out);
};

// Plugin-Instance
XPathPlugin theXPathPlugin;

// loads the Plugin to dlvhex:
extern "C" XPathPlugin* PLUGINIMPORTFUNCTION()
{
    //
    // set version - is shown when plugin is loaded
    // remember to change the macro names to the ones you used in configure.ac!
    //

    theXPathPlugin.setVersion(XPATH_MAJOR,
                              XPATH_MINOR,
                              XPATH_MICRO);

    return &theXPathPlugin;
}

}}

