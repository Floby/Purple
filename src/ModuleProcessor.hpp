/*
 * =====================================================================================
 *
 *       Filename:  ModuleProcessor.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  30/05/2010 16:14:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */

#ifndef MODULEPROCESSOR_HPP
#define MODULEPROCESSOR_HPP

#include	"Processor.hpp"

namespace purple {
    class ModuleProcessor :public Processor {
	public:
	    ModuleProcessor(const std::string& filename);

	protected:
	    virtual void initializeGlobalObjectTemplate(v8::Handle<v8::ObjectTemplate>);
	    virtual void initializeGlobalObject(v8::Handle<v8::Object>);
	    virtual PScript* getScript();
	    //virtual void handleExceptions(v8::Handle<v8::Exception> e);
	    virtual int returnValue(v8::Handle<v8::Value> jsReturnValue);
	    virtual void clean() ;

	private:
	    std::string _filename;
    };
};

#endif /* MODULEPROCESSOR_HPP */
