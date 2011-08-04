/* dlvhex -- Answer-Set Programming with external interfaces.
 * Copyright (C) 2007 Roman Schindlauer
 * Copyright (C) 2007 Carmelo D'Aparo
 * Copyright (C) 2007 Daniel Scheikl
 * Copyright (C) 2011 Juergen Weinberger
 * 
 * This file is part of dlvhex.
 *
 * dlvhex is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * dlvhex is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with dlvhex; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA.
 */

/** 
 * @file   xpathplugin.cpp
 * @brief  Plugin to evaluate XPath queries.
 * @author <A HREF="mailto:gamsta@gmx.net">Juergen Weinberger</A>
 * @date   Thu Sep 2 00:00:00 GMT 2010
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
XPathPlugin::setOptions(bool /* doHelp */, std::vector<std::string>& /* argv */, std::ostream& /* out */) 
{
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

