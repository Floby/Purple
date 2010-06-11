/*
 * =====================================================================================
 *
 *       Filename:  utils.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/06/2010 22:17:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */


#include	<v8/juice/convert.h>
#include	"utils.hpp"

using namespace purple;
using namespace std;
using namespace v8;

std::string purple::canon_path(const std::string& path) {
    std::list<std::string> names;
    std::string name;

    for(unsigned int i=0 ; i<path.length() ; ++i) {
	if(path[i] == '/') {
	    names.push_back(name);
	    name = "";
	}
	else {
	    name += path[i];
	}
    }
    names.push_back(name);

    names.remove(".");
    std::list<std::string>::iterator it = names.begin(), tmp;
    while(it != names.end()) {
	if(*it == std::string("..")) {
	    --it;
	    it = names.erase(it);
	    it = names.erase(it);
	}
	else if(*it == std::string("")) {
	    it = names.erase(it);
	}
	else ++it;
    }
    std::string result = "";
    for(it = names.begin() ; it != names.end() ; ++it) {
	result += "/" + *it;
    }
    return result;
}

int report_key(void* vector, const char* key, const char* value) {
    std::cerr << "found in table: " << key << " " << value << std::endl;
    std::vector<std::string> *v = (std::vector<std::string>*) vector;
    v->push_back(key);
    return 1;
}

std::vector<std::string> purple::apr_table_elements(apr_table_t* t) {
    cerr << "apr_table_elements using " << t << endl;
    std::vector<std::string> result;
    apr_table_do(&report_key, &result, t, NULL);
    return result;
}

v8::Handle<v8::Value> purple::getFromTable(v8::Local<v8::String> key, const AccessorInfo& info) {
    cerr << "called getFromTable with " << *String::AsciiValue(key) << endl;
    apr_table_t* t = (apr_table_t*) Handle<Object>::Cast(info.This())->GetPointerFromInternalField(0); 
    const char* result = apr_table_get(t, *(String::AsciiValue(key)));
    if(!result) return Handle<Value>();
    return juice::convert::CastToJS<string>(result);
}

v8::Handle<v8::Value> purple::setInTable (v8::Local<v8::String> key, v8::Local<v8::Value> value, const AccessorInfo& info) {
    if(value->IsUndefined()) return Handle<Value>();
    apr_table_t* t = (apr_table_t*) Handle<Object>::Cast(info.This())->GetPointerFromInternalField(0);
    apr_table_set(t, *String::Utf8Value(key), *String::Utf8Value(value));
    return value;
}
v8::Handle<v8::Value> purple::addToTable(const v8::Arguments& args) {
    apr_table_t* t = (apr_table_t*) Handle<Object>::Cast(args.This())->GetPointerFromInternalField(0);
    apr_table_add(t, *String::Utf8Value(args[0]), *String::Utf8Value(args[1])); 
    return args[1];
}
v8::Handle<v8::Boolean> purple::removeFromTable(v8::Local<v8::String> key, const v8::AccessorInfo& info) {
    apr_table_t* t = (apr_table_t*) Handle<Object>::Cast(info.This())->GetPointerFromInternalField(0);
    apr_table_unset(t, *String::Utf8Value(key)); 
    return v8::True();
}
v8::Handle<v8::Array> purple::listTable(const v8::AccessorInfo& info) {
    cerr << "listTable" << endl;
    apr_table_t* t = (apr_table_t*) Handle<Object>::Cast(info.This())->GetPointerFromInternalField(0);
    cerr << "using table at " << t << endl;
    vector<string> result = purple::apr_table_elements(t);
    return Handle<Array>::Cast(juice::convert::CastToJS<vector<string> >(result));    
}
