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

namespace purple {
    class BlueProcessor :public Processor {
	public:
	    BlueProcessor(std::string filename, v8::Handle<v8::Value> data, v8::Handle<v8::Object> global);
	    std::string getResult();
	protected:
	    virtual void initializeGlobalObjectTemplate(v8::Handle<v8::ObjectTemplate>);
	    virtual void initializeGlobalObject(v8::Handle<v8::Object>);
	    virtual PScript* getScript() ;
	    virtual std::string getCwd() ;
	    virtual void handleExceptions(v8::Handle<v8::Value> e);
	    virtual int returnValue(v8::Handle<v8::Value> jsReturnValue) ;
	    virtual void clean() ;

	    std::string include(std::string filename);
	    void print(std::string str);

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
	    std::string _buffer;
	    std::stack<std::string> _bufferized;


	    static v8::Handle<v8::Value> includeCallback(const v8::Arguments& args);
	    static v8::Handle<v8::Value> printCallback(const v8::Arguments& args);
    };
};


#endif /* BLUE_HPP */
