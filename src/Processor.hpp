/*
 * =====================================================================================
 *
 *       Filename:  Processor.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25/05/2010 15:41:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */

#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include "PScript.hpp"
#include	<v8/v8-debug.h>
#include	<string>

namespace purple {
    class Processor {
	public:
	    Processor();
	    virtual ~Processor();

	    int process();
	    virtual v8::Handle<v8::Context> getContext();
	protected:
	    //virtual void createContext();
	    void initializeContext();
	    virtual void initializeGlobalObjectTemplate(v8::Handle<v8::ObjectTemplate>);
	    virtual void initializeGlobalObject(v8::Handle<v8::Object>);
	    virtual PScript* getScript() =0;
	    virtual std::string getCwd() =0;
	    virtual void handleExceptions(v8::Handle<v8::Value> e);
	    virtual int returnValue(v8::Handle<v8::Value> jsReturnValue) =0;
	    virtual void clean() ;

	    static std::string reachScript(std::string filename);

	    static Processor* retrieveInternalPointer();
	    v8::Handle<v8::Value> getModule(const std::string& name);

	    PScript* _script;

	private:
	    v8::Persistent<v8::Context> _context; 

	    static v8::Handle<v8::Value> requireCallback(const v8::Arguments& args);
	    v8::Handle<v8::Value> getJsModule(const std::string& name);
	    v8::Handle<v8::Value> getSoModule(const std::string& name);
    };
};

#endif /* PROCESSOR_HPP */

