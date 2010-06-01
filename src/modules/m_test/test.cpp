/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  31/05/2010 16:16:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */


#include	<v8/v8-debug.h>
#include	<BinaryModule.hpp>
#include	<string>
#include	<iostream>
#include	<cstdlib>

using namespace v8;
using namespace std;

namespace purple {
    class TestModule :public BinaryModule {
	virtual Handle<Object> getJsModuleObject();
	static Handle<Value> systemCallback(const Arguments& args);
    };

    Handle<Object> TestModule::getJsModuleObject() {
	/*
	HandleScope hs;
	Persistent<Object> chose = Persistent<Object>::New(Object::New());
	return hs.Close(chose);
	*/
	HandleScope hs;
	cerr << "creating new object" << endl;
	Persistent<Object> exports = Persistent<Object>::New(Object::New());
	cerr << "adding new string" << endl;
	exports->Set(String::New("param"), Boolean::New(true));
	Handle<FunctionTemplate> systemTemplate = FunctionTemplate::New(systemCallback);
	exports->Set(String::New("system"), systemTemplate->GetFunction());
	cerr << "returning value" << endl;
	return hs.Close(exports);
    }

    Handle<Value> TestModule::systemCallback(const Arguments& args) {
	string cmd = *(String::Utf8Value(args[0]));
	int res = system(cmd.c_str());
	cerr << "system returned "<<res<<endl;
	return Number::New(res);
    }
};



extern "C" purple::TestModule purple_module_test;
purple::TestModule purple_module_test = purple::TestModule();
