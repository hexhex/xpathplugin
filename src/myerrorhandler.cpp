/* -*- C++ -*- */

/** 
 * @file   MyErrorHandler.cpp
 * @brief  A modified error handler for Xerces error handling.
 * @author <A HREF="mailto:gamsta@gmx.net">Juergen Weinberger</A>
 * @date 2.9.2010 
 * 
 */

#include "myerrorhandler.hpp"
#include <dlvhex/Error.h>

bool MyErrorHandler::handleError(const DOMError &dError)
{
	throw dlvhex::PluginError("DOM error: " + (std::string)XMLString::transcode(dError.getMessage()));
	return true;
}

