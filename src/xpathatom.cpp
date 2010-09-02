/** 
 * @file   xpathplugin.cpp
 * @brief  Plugin to evaluate XPath queries.
 * @author <A HREF="mailto:gamsta@gmx.net">Juergen Weinberger</A>
 * @date 2.9.2010  
 * 
 * 
 */

#include "xpathatom.hpp"

namespace dlvhex {
  namespace xpath {

XPathAtom::XPathAtom()
{
	//Plugin "Parameter"-Definitions:
       	addInputConstant();    //URI (or path to a file)
       	addInputConstant();    //XPath query
	setOutputArity(1);
       	    
	//to avoid region-specific charakter problems
       	setlocale(LC_ALL,NULL);
       	setlocale(LC_NUMERIC,"C");
       	 
       	XALAN_USING_XALAN(XSLException)

       	//xerces/xalan-initialization:
	try {	
      		XMLPlatformUtils::Initialize();	
       	    	
       	    	XALAN_USING_XERCES(XMLPlatformUtils)
		XALAN_USING_XALAN(XPathEvaluator)
				
		XPathEvaluator::initialize();	
	}
  	catch (const XMLException& e) {	
  		throw PluginError("Xerces/XML exception: " + (std::string)XMLString::transcode(e.getMessage()));
  	}
  	catch(const XSLException& e)
        {	
        	throw PluginError("XSL Exception: " + (std::string)transcode(e.getMessage()));
        }
}

XPathAtom::~XPathAtom()
{	
	XMLPlatformUtils::Terminate();	
}

void 
XPathAtom::retrieve(const Query& query, Answer& answer) throw (PluginError)
{
	std::vector<Tuple> out;
    	parseXMLFile(XMLString::transcode((query.getInputTuple()[0].getUnquotedString()).c_str()), 
	     				XMLString::transcode((query.getInputTuple()[1].getUnquotedString()).c_str()), out); 
	answer.addTuples(out);
}

void 
XPathAtom::parseXMLFile(const XMLCh* uri, const XMLCh* query, std::vector<Tuple> &out)
{
	try {
		//parsing XML-file and creating DOM-document:
		DOMImplementation* impl=DOMImplementationRegistry::getDOMImplementation(ls_id);
		DOMBuilder* parser = ((DOMImplementationLS*)impl)->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS,0);
		parser->setErrorHandler((new MyErrorHandler()));  //ob das geschickt ist ohne garbage collector?
		DOMDocument* doc = parser->parseURI(uri);
			    	
		//creating Xalan document wrapping Xerces:  
		XercesDOMSupport support;
		XercesParserLiaison liaison(support);
		XercesDOMWrapperParsedSource src(doc,liaison,support);
		XalanDocument* xalanDoc = src.getDocument();
			    		
		//creating the xpath-evaluator and evaluate the query
		XPathEvaluator eval;
		XalanDocumentPrefixResolver resolver(xalanDoc);
		XObjectPtr result = eval.evaluate(support, xalanDoc, query, resolver);
		    			
		//dealing with results
		const NodeRefListBase& nodeset = result->nodeset();
		bool atomicOnly=true;
		    			
		//printNodeNumbers();
		    			
		for(unsigned int i=0; i<nodeset.getLength(); i++)
		{
			if(nodeset.item(i)->getNodeType()==XalanNode::ATTRIBUTE_NODE || 
			    nodeset.item(i)->getNodeType()==XalanNode::TEXT_NODE)
			{
				const Term t(XMLString::transcode(nodeset.item(i)->getNodeValue().c_str()),true);
				Tuple singleValue;
				singleValue.push_back(t);
				out.push_back(singleValue);
			}
			else
			{
				atomicOnly=false;
				break;
			}
		}
		    			
		if(!atomicOnly)//XPath not only returns atomic values
		{
		    cout << "Warning: The query \"" << XMLString::transcode(query) << "\" doesn't (only) select atomic values\n\n";
		    out.clear();
		}   				
		    			
		parser->release();
	}
	catch(const DOMException& e) {
		throw PluginError("XML error: " + (std::string)XMLString::transcode(e.getMessage()));
	}
	catch(const XPathParserException& e) {
		throw PluginError("XPath error: " + (std::string)transcode(e.getMessage()));
	}
	catch(const exception& e) { //debug
		throw PluginError((std::string)e.what());
	}
}

}}

