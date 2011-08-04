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
 * @file   xpathplugin.hpp
 * @brief  Plugin to evaluate XPath queries.
 * @author <A HREF="mailto:gamsta@gmx.net">Juergen Weinberger</A>
 * @date   Thu Sep 2 00:00:00 GMT 2010
 * 
 * 
 */

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
 * <VAR>Please note:</VAR> This plugin requires <A HREF="http://xmlsoft.org">libxml2</A>.
 *
 */

#ifndef XPATH_PLUGIN_HPP_
#define XPATH_PLUGIN_HPP_

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

  } // namespace xpath
} // namespace dlvhex

#endif // XPATH_PLUGIN_HPP_

// Local Variables:
// mode: C++
// End:
