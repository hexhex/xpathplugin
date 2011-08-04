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
 * @file   xpath-unittest.cpp
 * @brief  Plugin to evaluate XPath queries.
 * @author <A HREF="mailto:gamsta@gmx.net">Juergen Weinberger</A>
 * @date   Thu Sep 2 00:00:00 GMT 2010
 * 
 * 
 */

#include "xpathatom.hpp"
#include "xpathplugin.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "xpath-unittest"
#include <boost/test/unit_test.hpp>

#include <fstream>
#include <iostream>

using namespace dlvhex;
using namespace dlvhex::xpath;

// Test loading of a not existing xml file
BOOST_AUTO_TEST_CASE( XPathAtomTest_LoadNoneExistingXML )
{
  const char* ex = getenv("TOP_SRCDIR");
  assert (ex != 0);
  
  std::string xmlfile(ex);
  xmlfile += "/examples/notexisting.xml";
  
  XPathAtom* xa = new XPathAtom;
  BOOST_CHECK(xa != 0);
  
  std::vector<Tuple> out;
  BOOST_CHECK_THROW(xa->parseXMLFile( xmlfile, "//keyword/child::node()", out), PluginError);
 
  delete xa;
}

// Test loading and evaluating an invalid xml file
BOOST_AUTO_TEST_CASE( XPathAtomTest_LoadInvalidXML )
{
  const char* ex = getenv("TOP_SRCDIR");
  assert (ex != 0);
  
  std::string xmlfile(ex);
  xmlfile += "/examples/scientists_err.xml";
  
  XPathAtom* xa = new XPathAtom;
  BOOST_CHECK(xa != 0);
  
  std::vector<Tuple> out;
  BOOST_CHECK_THROW(xa->parseXMLFile( xmlfile, "//keyword/child::node()", out), PluginError);
 
  delete xa;
}

// Test evaluating an invalid query
BOOST_AUTO_TEST_CASE( XPathAtomTest_EvaluateInvalidQuery )
{
  const char* ex = getenv("TOP_SRCDIR");
  assert (ex != 0);
  
  std::string xmlfile(ex);
  xmlfile += "/examples/scientists.xml";
  
  XPathAtom* xa = new XPathAtom;
  BOOST_CHECK(xa != 0);
  
  std::vector<Tuple> out;
  BOOST_CHECK_THROW(xa->parseXMLFile( xmlfile, "---", out), PluginError);
 
  delete xa;
}

// Test evaluating an empty query
BOOST_AUTO_TEST_CASE( XPathAtomTest_EmptyQuery )
{
  const char* ex = getenv("TOP_SRCDIR");
  assert (ex != 0);
  
  std::string xmlfile(ex);
  xmlfile += "/examples/scientists.xml";
  
  XPathAtom* xa = new XPathAtom;
  BOOST_CHECK(xa != 0);
  
  std::vector<Tuple> out;
  BOOST_CHECK_NO_THROW(xa->parseXMLFile( xmlfile, "//birth/child::node()", out));
 
  BOOST_CHECK(out.size() == 0);				    
  delete xa;
}

// Test evaluating a none atomic query
BOOST_AUTO_TEST_CASE( XPathAtomTest_NotAtomicOnlyQuery )
{
  const char* ex = getenv("TOP_SRCDIR");
  assert (ex != 0);
  
  std::string xmlfile(ex);
  xmlfile += "/examples/scientists.xml";
  
  XPathAtom* xa = new XPathAtom;
  BOOST_CHECK(xa != 0);
  
  std::vector<Tuple> out;
  BOOST_CHECK_THROW(xa->parseXMLFile( xmlfile, "//comment()", out), PluginError);
 
  BOOST_CHECK(out.size() == 0);				    
  delete xa;
}

// Tests loading and evaluating of a valid xml file and query
BOOST_AUTO_TEST_CASE( XPathAtomTest_AllValid )
{
  const char* ex = getenv("TOP_SRCDIR");
  assert (ex != 0);
  
  std::string xmlfile(ex);
  xmlfile += "/examples/scientists.xml";
  
  XPathAtom* xa = new XPathAtom;
  BOOST_CHECK(xa != 0);
  
  std::vector<Tuple> out;
  BOOST_CHECK_NO_THROW(xa->parseXMLFile( xmlfile, "//keyword/child::node()", out));
 
  BOOST_CHECK(out.size() == 18);				    
  delete xa;
}
