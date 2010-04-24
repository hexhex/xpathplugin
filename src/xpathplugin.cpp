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
 * @author <A HREF="mailto:daniel.scheikl@student.tuwien.ac.at">Daniel Scheikl</A>
 */


/** 
 * @file   xpathplugin.cpp
 * @brief  Plugin to evaluate XPath queries.
 * @author <A HREF="mailto:daniel.scheikl@student.tuwien.ac.at">Daniel Scheikl</A>
 * @date   
 * 
 * 
 */

/*********************************************************************/
/*********************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#if defined(XALAN_CLASSIC_IOSTREAMS)
#include <iostream.h>
#else
#include <iostream>
#endif

#include <exception>
#include <string>
#include <locale.h>

#include "dlvhex/PluginInterface.h"

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

#include "myerrorhandler.cpp"


/*********************************************************************/
/*********************************************************************/

using namespace xalanc;
using namespace std;
XERCES_CPP_NAMESPACE_USE 

/*********************************************************************/
/*********************************************************************/
/*********************************************************************/

static const XMLCh ls_id[] = {chLatin_L, chLatin_S, chNull};

/** This class is used to implement the XPath atom.
 * As usual, this class inherits from PluginAtom. All class members are automatically called while
 * the XPath atom is processed.
 * 
 * 
 */
class XPathAtom : public PluginAtom
{
	
	private:
	
	/*********************************************************************/
	/*********************************************************************/

	//Constructors and Deconstructors:		
	
	/** The constructor.
	 * The constructor sets the input and output arity of the XPath plugin and 
	 * intializes Xerces and Xalan. If an error occurs,
	 * an apropriate error message is thrown.
	 * 
	 * @throws PluginError.
	 * 
	 */
	public:

    	XPathAtom() throw (PluginError)
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
       	    try 
       	    {	
       	    	XMLPlatformUtils::Initialize();	
       	    	
       	    	XALAN_USING_XERCES(XMLPlatformUtils)
				XALAN_USING_XALAN(XPathEvaluator)
				
				XPathEvaluator::initialize();	
       	    }
  			catch (const XMLException& e) 
  			{	
  				throw PluginError("Xerces/XML exception: " + (std::string)XMLString::transcode(e.getMessage()));
  			}
  			catch(const XSLException& e)
        	{	
        		throw PluginError("XSL Exception: " + (std::string)transcode(e.getMessage()));
        	}
    	}
   		
   		/*********************************************************************/
   		 
   		 /** The destructor.
   		  * Releases some Xerces and Xalan resources.
   		  * 
   		  */	
    	~XPathAtom()
    	{	XMLPlatformUtils::Terminate();	}

	/*********************************************************************/
	/*********************************************************************/
	
	/** Processes the plugin input parameters and returns a (set of) literals.
	 * This function is automatically called by dlvhex. It is used process the input
	 * parameters of the plugin and return an answer. 
	 * 
	 * @param query set of plugin-input parameters. The XPath plugin has only a binary input. The first
	 * element of this vector is the URI of an XML file, while the second element is the XPath query.
	 * @param answer set of plugin-output parameters.
	 * 
	 */
	public:
	
   		virtual void retrieve(const Query& query, Answer& answer) throw (PluginError)
    	{
    		std::vector<Tuple> out;
    					
	    	parseXMLFile(XMLString::transcode((query.getInputTuple()[0].getUnquotedString()).c_str()), 
	    				XMLString::transcode((query.getInputTuple()[1].getUnquotedString()).c_str()), out); 
	     
	   
	        answer.addTuples(out);
	    }

    /*********************************************************************/
    
    /** Parses the given XML file an evaluates the given XPath query.
     * This method parses the XML file where the URI points to and evaluates the
     * query given by the second parameter of the plugin. The useable results of the query are saven in a vector.
     * 
     * @param uri The URI of the XML file (first parameter of the XPath atom).
     * @param query The XPath query (second parameter of the XPath atom).
     * @param out This vector is used to store useable answers of the query.
     * 
     * @throws PluginError Xerces and Xalan error messages that can occur.
     * 
	 */
    	void parseXMLFile(const XMLCh* uri, const XMLCh* query, std::vector<Tuple> &out) throw (PluginError)
    	{
    		try
    		{
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
    		catch(const DOMException& e)
    		{
    			throw PluginError("XML error: " + (std::string)XMLString::transcode(e.getMessage()));
    		}
    		catch(const XPathParserException& e)
    		{
    			throw PluginError("XPath error: " + (std::string)transcode(e.getMessage()));
    		}
    		catch(const exception& e)  //debug
    		{
    			throw PluginError((std::string)e.what());
    		}
    	}
    
	/*********************************************************************/
	/*********************************************************************/


	private:
	 
		 /** Transcodes a XalanDOMString to a char array.
	     * 
	     * @param xStr The XalanDOMString to convert.
	     * 
	     * @return The convertet char array.
	     * 
		 */
		char* transcode(const XalanDOMString xStr)
		{	return XMLString::transcode(xStr.c_str());	}
		
		
		////////this method is used for debug purposes only//////////
		void printNodeNumbers()
		{
    			printf("\n\n");
    			printf("UNKNOWN_NODE: %d\n",XalanNode::UNKNOWN_NODE);
    			printf("ELEMENT_NODE: %d\n",XalanNode::ELEMENT_NODE);
    			printf("ATTRIBUTE_NODE: %d\n",XalanNode::ATTRIBUTE_NODE);
    			printf("TEXT_NODE: %d\n",XalanNode::TEXT_NODE);
    			printf("CDATA_SECTION_NODE: %d\n",XalanNode::CDATA_SECTION_NODE);
    			printf("ENTITY_REFERENCE_NODE: %d\n",XalanNode::ENTITY_REFERENCE_NODE);
    			printf("PROCESING_INSTRUCTION_NODE: %d\n",XalanNode::PROCESSING_INSTRUCTION_NODE);
    			printf("COMMENT_NODE: %d\n",XalanNode::COMMENT_NODE);
    			printf("DOCUMENT_NODE: %d\n",XalanNode::DOCUMENT_NODE);
    			printf("DOCUMENT_TYPE_NODE: %d\n",XalanNode::DOCUMENT_TYPE_NODE);
    			printf("DOCUMENT_FRAGMENT_NODE: %d\n",XalanNode::DOCUMENT_FRAGMENT_NODE);
    			printf("NOTATION_NODE: %d\n",XalanNode::NOTATION_NODE);
    			printf("\n\n");
		}
		
};



/*********************************************************************/
/*********************************************************************/
/*********************************************************************/

class XPathPlugin : public PluginInterface
{
public:

   
   /*********************************************************************/

    // register all atoms of this plugin:
    virtual void getAtoms(AtomFunctionMap& a)
    {
        a["xpath"] = new XPathAtom;
    }
    
    /*********************************************************************/

    // process options that were given to dlvhex
    void setOptions(bool doHelp, std::vector<std::string>& argv, std::ostream& out)
    {
        if (doHelp)
        {
            out << "some-plugin: " << std::endl << std::endl;
            out << " --myswitch=FOO       Use FOO as bar." << std::endl;
            out << " --anotherone         Turn off light." << std::endl;
            return;
        }

        std::vector<std::vector<std::string>::iterator> found;

        //
        // go through options that were left from dlvhex-main()
        //
        for (std::vector<std::string>::iterator it = argv.begin();
                it != argv.end();
                it++)
        {
            std::string::size_type o;

            o = it->find("--myswitch=");

            if (o != std::string::npos)
            {
                std::string option = it->substr(o + 11); // length of parameter = 11

                //
                // do something with this option
                //

                // remember to delete it from list:
                found.push_back(it);
            }

            o = it->find("--anotherone");

            //
            // process second switch...
            //
        }

        //
        // delete all found options, dlvhex would complain about them!
        // 
        for (std::vector<std::vector<std::string>::iterator>::const_iterator it = found.begin();
            it != found.end(); ++it)
        {
            argv.erase(*it);
        }
    }

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


