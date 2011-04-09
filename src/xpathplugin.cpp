/** 
 * @file   xpathplugin.cpp
 * @brief  Plugin to evaluate XPath queries.
 * @author <A HREF="mailto:gamsta@gmx.net">Juergen Weinberger</A>
 * @date 2.9.2010  
 * 
 * 
 */
#include "xpathplugin.hpp"

#include <iostream>

namespace dlvhex {
  namespace xpath {

void 
XPathPlugin::getAtoms(AtomFunctionMap& a) 
{
	a["xpath"] = boost::shared_ptr<PluginAtom>(new XPathAtom);
}
    
void 
XPathPlugin::setOptions(bool doHelp, std::vector<std::string>& argv, std::ostream& out) 
{
	if (doHelp)
    {
		out << "some-plugin: " << std::endl << std::endl;
		out << " --myswitch=FOO       Use FOO as bar." << std::endl;
		out << " --anotherone         Turn off light." << std::endl;
		return;
    }

    std::vector<std::vector<std::string>::iterator> found;

    // go through options that were left from dlvhex-main()
    for (std::vector<std::string>::iterator it = argv.begin();
         it != argv.end();
         it++)
    {
        std::string::size_type o;
        o = it->find("--myswitch=");
    
        if (o != std::string::npos)
        {
            std::string option = it->substr(o + 11); // length of parameter = 11
            // do something with this option
            // remember to delete it from list:
            found.push_back(it);
        }
        o = it->find("--anotherone");
        // process second switch...
    }

    // delete all found options, dlvhex would complain about them!
    for (std::vector<std::vector<std::string>::iterator>::const_iterator it = found.begin();
         it != found.end(); 
         ++it)
    {
        argv.erase(*it);
    }
}


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

  } // namespace xpath
} // namespace dlvhex

