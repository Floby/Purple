/*
 * =====================================================================================
 *
 *       Filename:  Blue.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2010 20:41:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */

#ifndef BLUE_HPP
#define BLUE_HPP

#include	<Processor.hpp>
#include	<stack>
#include	<vector>

namespace purple {
    class BlueProcessor :public Processor {
	public:
	    BlueProcessor(std::string filename, v8::Handle<v8::Value> data, v8::Handle<v8::Object> global);
	    std::string getResult();

	    static v8::Handle<v8::Object> getFunction();
	    virtual std::string getCwd() ;
	protected:
	    virtual void initializeGlobalObjectTemplate(v8::Handle<v8::ObjectTemplate>);
	    virtual void initializeGlobalObject(v8::Handle<v8::Object>);
	    virtual PScript* getScript() ;
	    virtual void handleExceptions(v8::Handle<v8::Value> e);
	    virtual int returnValue(v8::Handle<v8::Value> jsReturnValue) ;
	    virtual void clean() ;

	    std::string include(std::string filename);
	    void print(std::string str);
	    v8::Handle<v8::Value> reportError(std::string);

	    static v8::Handle<v8::Value> jsFunction(const v8::Arguments& args);

	    class BScript :public PScript {
		public:
		    static BScript* get(const std::string& filename);
		protected:
		    BScript(const std::string& filename);
	    };

	private:
	    std::stack<std::string> _filenames;
	    v8::Persistent<v8::Value> _data;
	    v8::Persistent<v8::Object> _global;
	    v8::Persistent<v8::Value> _result;
	    std::string _buffer;
	    std::stack<std::string> _bufferized;

	    std::vector<std::string> _errors;


	    static v8::Handle<v8::Value> includeCallback(const v8::Arguments& args);
	    static v8::Handle<v8::Value> printCallback(const v8::Arguments& args);
	    static v8::Handle<v8::Value> reportErrorCallback(const v8::Arguments& args);
    };
};


#endif /* BLUE_HPP */
