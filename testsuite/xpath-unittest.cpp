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
