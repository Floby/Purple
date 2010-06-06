/*
 * =====================================================================================
 *
 *       Filename:  RequestProcessor.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25/05/2010 16:09:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */

#ifndef REQUESTPROCESSOR_HPP
#define REQUESTPROCESSOR_HPP

#include "httpd.h"
#include "http_config.h"
#include "Processor.hpp"

namespace purple {
    class RequestProcessor :public Processor {
	public:
	    RequestProcessor(request_rec* r);
	    virtual ~RequestProcessor();

	protected:
	    //virtual void createContext();
	    //virtual void initializeContext();
	    virtual void initializeGlobalObjectTemplate(v8::Handle<v8::ObjectTemplate>);
	    virtual void initializeGlobalObject(v8::Handle<v8::Object>);
	    virtual PScript* getScript();
	    virtual std::string getCwd();
	    virtual void handleExceptions(v8::Handle<v8::Value> e);
	    virtual int returnValue(v8::Handle<v8::Value> jsReturnValue);
	    virtual void clean();
	private:
	   request_rec* _request; 

	   static v8::Handle<v8::Value> printCallback(const v8::Arguments& args);
	   static v8::Handle<v8::Value> unwrapRequestHeaders(v8::Local<v8::String>, const v8::AccessorInfo& info);
	   v8::Handle<v8::ObjectTemplate> getRequestObjectTemplate();
	   v8::Handle<v8::ObjectTemplate> getHeadersInObjectTemplate();
    };
};

#endif /* REQUESTPROCESSOR_HPP */

