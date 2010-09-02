/** 
 * @file   xpathatom.hpp
 * @brief  ToDo
 * @author <A HREF="mailto:gamsta@gmx.net">Juergen Weinberger</A>
 * @date 2.9.2010  
 */

#include "xercesc/util/PlatformUtils.hpp"
#include "xercesc/framework/LocalFileInputSource.hpp"
#include "xercesc/util/XMLString.hpp"
#include "xercesc/dom/DOM.hpp"
#include "xercesc/parsers/XercesDOMParser.hpp"

#include "xalanc/Include/PlatformDefinitions.hpp"
#include "xalanc/XPath/XObject.hpp"
#include "xalanc/XPath/XPathEvaluator.hpp"
#include "xalanc/XalanSourceTree/XalanSourceTreeDOMSupport.hpp"
#include "xalanc/XalanSourceTree/XalanSourceTreeInit.hpp"
#include "xalanc/XalanSourceTree/XalanSourceTreeParserLiaison.hpp"
#include "xalanc/PlatformSupport/XSLException.hpp"
#include "xalanc/XPath/XPathParserException.hpp"
#include "xalanc/XercesParserLiaison/XercesParserLiaison.hpp"
#include "xalanc/XercesParserLiaison/XercesDOMSupport.hpp"
#include "xalanc/XalanTransformer/XercesDOMWrapperParsedSource.hpp"
#include "xalanc/DOMSupport/XalanDocumentPrefixResolver.hpp"

#include "dlvhex/PluginInterface.h"

#include "myerrorhandler.hpp"

using namespace xalanc;
using namespace std;

XERCES_CPP_NAMESPACE_USE 

static const XMLCh ls_id[] = {chLatin_L, chLatin_S, chNull};

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
	 * intializes Xerces and Xalan. If an error occurs,
	 * an apropriate error message is thrown.
	 * 
	 * @throws PluginError.
	 */
    	XPathAtom();

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
	
	/** Parses the given XML file an evaluates the given XPath query.
	 * This method parses the XML file where the URI points to and evaluates the
	 * query given by the second parameter of the plugin. The useable results of the query are saven in a vector.
	 * 
	 * @param uri The URI of the XML file (first parameter of the XPath atom).
	 * @param query The XPath query (second parameter of the XPath atom).
	 * @param out This vector is used to store useable answers of the query.
 	 * 
	 * @throws PluginError Xerces and Xalan error messages that can occur.
	 */
	void parseXMLFile(const XMLCh* uri, const XMLCh* query, std::vector<Tuple> &out);

private:
	/** Transcodes a XalanDOMString to a char array.
	 * 
	 * @param xStr The XalanDOMString to convert.	
	 * 
	 * @return The convertet char array.
	 */
	char* transcode(const XalanDOMString xStr);
	
	////////this method is used for debug purposes only//////////
	void printNodeNumbers();
};

}
}
