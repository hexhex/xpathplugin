/** 
 * @file   xpathplugin.cpp
 * @brief  Plugin to evaluate XPath queries.
 * @author <A HREF="mailto:gamsta@gmx.net">Juergen Weinberger</A>
 * @date 2.9.2010  
 * 
 * 
 */

#include "xpathatom.hpp"
#include <iostream>
#include <sstream>

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

	//initialise libxml
	xmlInitParser();
}

XPathAtom::~XPathAtom()
{	
	//uninitialise libxml
	xmlCleanupParser();
}

void 
XPathAtom::retrieve(const Query& query, Answer& answer) throw (PluginError)
{
	std::vector<Tuple> out;

    	parseXMLFile(	query.getInputTuple()[0].getUnquotedString().c_str(),
			query.getInputTuple()[1].getUnquotedString().c_str(), 
			out); 
	answer.addTuples(out);
}

void 
XPathAtom::parseXMLFile(const std::string &uri, const std::string &query, std::vector<Tuple> &out)
{
	xmlDocPtr doc;
	xmlXPathContextPtr xpathCtx;
	xmlXPathObjectPtr xpathObj;

//	std::cout << "URI:\"" << uri << "\"" << std::endl;
//	std::cout << "Query:\"" << query << "\"" << std::endl;

	// Load the XML document
    	doc = xmlParseFile(uri.c_str());
	if (doc == NULL) 
		throw PluginError(std::string("Unable to parse XML-file \"")+uri+"\"");

	// Create the xpath evaluation context
	xpathCtx = xmlXPathNewContext(doc);
	if(xpathCtx == NULL) {
	        xmlFreeDoc(doc); 
		throw PluginError(std::string("Unable to create new XPath context"));
	}

	// Evaluate the xpath expression
	// BAD_CAST use when known its safe (This is a basic byte in an UTF-8 encoded string)
	xpathObj = xmlXPathEvalExpression(BAD_CAST(query.c_str()), xpathCtx);
    	if(xpathObj == NULL) {
	        xmlXPathFreeContext(xpathCtx); 
	        xmlFreeDoc(doc); 
		throw PluginError(std::string("Unable to evaluate XPath expression \"")+
						query+"\"");
    	}

	//Evaluate and convert the results
	evaluateXPathObject(xpathObj,out);	

	//Free everything
	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc); 
}

void 
XPathAtom::evaluateXPathObject(const xmlXPathObjectPtr xpathObj, std::vector<Tuple> &out)
{
	xmlNodeSetPtr nodes;
	xmlNodePtr cur;

	nodes = xpathObj->nodesetval;
    
	bool atomicOnly = true;
	for(int i = 0; i < nodes->nodeNr; ++i) {
		if(!(nodes->nodeTab[i])) 
			throw PluginError("Node doesn't exist, this shouldn't happen");
		
		cur = nodes->nodeTab[i]; 

		if(cur->type == XML_ATTRIBUTE_NODE ||
		   cur->type == XML_TEXT_NODE)
		{
			//Get the content of the node			
			xmlChar *tmp = xmlNodeGetContent(cur);			
			std::stringstream ss("");
			ss << tmp;
			xmlFree(tmp);

			//Store it in the output
			const Term t(ss.str(),true);
			Tuple singleValue;
			singleValue.push_back(t);
			out.push_back(singleValue);
		}
		else atomicOnly = false;
	}
	
	if(!atomicOnly)//XPath not only returns atomic values
		throw PluginError("The query didn't (only) select atomic values");
}

}}

