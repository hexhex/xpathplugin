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
 * @file   xpathatom.hpp
 * @brief  Plugin to evaluate XPath queries.
 * @author <A HREF="mailto:gamsta@gmx.net">Juergen Weinberger</A>
 * @date   Thu Sep 2 00:00:00 GMT 2010
 * 
 * 
 */

#ifndef XPATH_ATOM_HPP_
#define XPATH_ATOM_HPP_

#include "dlvhex/PluginInterface.h"

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include <string>

using namespace std;

namespace dlvhex {
  namespace xpath {

/** This class is used to implement the XPath atom.
 * As usual, this class inherits from PluginAtom. All class members are automatically called while
 * the XPath atom is processed.
 * 
 * 
 */
class XPathAtom : public PluginAtom {
public:
	/** The constructor.
	 * The constructor sets the input and output arity of the XPath plugin and 
	 * intializes the libxml. If an error occurs, an apropriate error message is thrown.
	 * 
	 * @throws PluginError.
	 */
    	XPathAtom();

	/** The destructor.
	 * The destructor uninitialised the plugin and the libxml
	 * 
	 */
    	~XPathAtom();

	/** Processes the plugin input parameters and returns a (set of) literals.
	 * This function is automatically called by dlvhex. It is used process the input
	 * parameters of the plugin and return an answer. 
	 * 
	 * @param query set of plugin-input parameters. The XPath plugin has only a binary input. The first
	 * element of this vector is the URI of an XML file, while the second element is the XPath query.
	 * @param answer set of plugin-output parameters.
	 */
	virtual void retrieve(const Query& query, Answer& answer) throw (PluginError);
	
	/** Parses the given XML file and evaluates the given XPath query.
	 * This method parses the XML file where the URI points to and evaluates the
	 * query given by the second parameter of the plugin. The useable results of the query are saven in a vector.
	 * 
	 * @param uri The URI of the XML file (first parameter of the XPath atom).
	 * @param query The XPath query (second parameter of the XPath atom).
	 * @param out This vector is used to store useable answers of the query.
 	 * 
	 * @throws PluginError LibXML or XPath Errors occured
	 */
	void parseXMLFile(const std::string &uri, 
				const std::string &query, 
				std::vector<Tuple> &out);

private:
	/** Evaluates the results XPath query and converts it into tuples
	 * 
	 * @param xpathObj The retrieved xpath Object
	 * @param out This vector is used to store useable answers of the query.
 	 * 
	 * @throws PluginError Parsing errors that occured.
	 */
	void evaluateXPathObject(const xmlXPathObjectPtr xpathObj, 
					std::vector<Tuple> &out);
};

  } // namespace xpath
} // namespace dlvhex

#endif // XPATH_ATOM_HPP_

// Local Variables:
// mode: C++
// End:
