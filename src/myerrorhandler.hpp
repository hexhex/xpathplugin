/* -*- C++ -*- */

/** 
 * @file   myerrorhandler.cpp
 * @brief  A modified error handler for Xerces error handling.
 * @author <A HREF="mailto:gamsta@gmx.net">Juergen Weinberger</A>
 * @date 2.9.2010  
 * 
 */

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/dom/DOM.hpp>
#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif

XERCES_CPP_NAMESPACE_USE

/** This class implements a minimal error handler for Xerces DOM errors.
 * This class catches all DOM errors and throws a error-message.
 * 
 */
class MyErrorHandler : public DOMErrorHandler {
public:
	bool handleError(const DOMError &dError);
};

