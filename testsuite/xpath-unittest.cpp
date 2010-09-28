#include "xpathatom.hpp"
#include "xpathplugin.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "xpath-unittest"
#include <boost/test/unit_test.hpp>

#include <fstream>
#include <iostream>

using namespace dlvhex;
using namespace dlvhex::xpath;

BOOST_AUTO_TEST_CASE( XPathAtomTest )
{
  const char* ex = getenv("EXAMPLESDIR");
  assert (ex != 0);

  XPathAtom* xa = new XPathAtom;

  BOOST_CHECK(xa != 0);

  delete xa;
}


BOOST_AUTO_TEST_CASE( XPathPluginTest )
{
  const char* ex = getenv("EXAMPLESDIR");
  assert (ex != 0);

  XPathPlugin* xp = new XPathPlugin;

  BOOST_CHECK(xp != 0);

  delete xp;
}
