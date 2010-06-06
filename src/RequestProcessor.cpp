/*
 * =====================================================================================
 *
 *       Filename:  RequestProcessor.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  28/05/2010 16:48:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */

#include "RequestProcessor.hpp"
#include "http_protocol.h"
#include	"httpd.h"
#include	"http_config.h"
#include	<v8/juice/convert.h>
#include <iostream>

using namespace purple;
using namespace v8;
using namespace std;

RequestProcessor::RequestProcessor(request_rec* r) : _request(r) {
}

RequestProcessor::~RequestProcessor() {
}
PScript* RequestProcessor::getScript() {
    return PScript::get(_request->filename);
}

void RequestProcessor::clean() {
    Processor::clean();
    delete _script; 
}

int RequestProcessor::returnValue(Handle<Value> jsReturnValue) {
    return OK;
}

void RequestProcessor::initializeGlobalObjectTemplate(v8::Handle<v8::ObjectTemplate> gt) {
    Processor::initializeGlobalObjectTemplate(gt);
    gt->Set(String::New("print"), FunctionTemplate::New(RequestProcessor::printCallback));   
    gt->Set(String::New("echo"), FunctionTemplate::New(RequestProcessor::printCallback));   
    gt->Set(String::New("request"), getRequestObjectTemplate());
}
void RequestProcessor::initializeGlobalObject(v8::Handle<v8::Object> g) {
    Processor::initializeGlobalObject(g);
    g->Set(String::New("myString"), String::New("Coucou les aminches, je suis une string javascript =)\n"));
}

string RequestProcessor::getCwd() {
    string filename(_request->filename);
    return filename.substr(0, filename.find_last_of('/'));
}

Handle<Value> RequestProcessor::printCallback(const v8::Arguments& args) {
    //retrieve the internal pointer to the processor
    RequestProcessor* processor = (RequestProcessor*) retrieveInternalPointer();
    std::string res = "";
    res += *(String::AsciiValue(args[0]));
    ap_rprintf(processor->_request, "%s", res.c_str());
    return v8::Undefined();
}

void RequestProcessor::handleExceptions(Handle<Value> e) {
    Processor::handleExceptions(e);
    ap_rprintf(_request, "uncaught exception %s\n", *(String::Utf8Value(e)));
    //if(compiletime) ap_rpintf(_request, "while compiling\n");
}

v8::Handle<v8::Value> RequestProcessor::unwrapRequestHeaders(Local<v8::String> arg, const v8::AccessorInfo& info) {
    string name = v8::juice::convert::CastFromJS<std::string>(arg);
    RequestProcessor* processor = (RequestProcessor*) retrieveInternalPointer();
    string result = apr_table_get(processor->_request->headers_in, name.c_str());
    return v8::juice::convert::CastToJS<string>(result);
}

Handle<ObjectTemplate> RequestProcessor::getHeadersInObjectTemplate() {
    HandleScope hs;
    Handle<ObjectTemplate> ht = ObjectTemplate::New();
    ht->SetNamedPropertyHandler(unwrapRequestHeaders, NULL, NULL, NULL);
    return hs.Close(ht);
}

Handle<ObjectTemplate> RequestProcessor::getRequestObjectTemplate() {
    HandleScope hs;
    Handle<ObjectTemplate> rt = ObjectTemplate::New();
    rt->Set(String::New("headers"), getHeadersInObjectTemplate());
    rt->Set(String::New("method"), String::New(_request->method));
    rt->Set(String::New("uri"), String::New(_request->uri));
    rt->Set(String::New("filename"), String::New(_request->filename));
    rt->Set(String::New("path_info"), String::New(_request->path_info));
    rt->Set(String::New("the_request"), String::New(_request->the_request));
    return hs.Close(rt);
}
