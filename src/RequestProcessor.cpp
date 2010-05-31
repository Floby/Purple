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
    delete _script; 
}

int RequestProcessor::returnValue(Handle<Value> jsReturnValue) {
    return OK;
}

void RequestProcessor::initializeGlobalObjectTemplate(v8::Handle<v8::ObjectTemplate> gt) {
    Processor::initializeGlobalObjectTemplate(gt);
    gt->Set(String::New("print"), FunctionTemplate::New(RequestProcessor::printCallback));   
    gt->Set(String::New("echo"), FunctionTemplate::New(RequestProcessor::printCallback));   
}
void RequestProcessor::initializeGlobalObject(v8::Handle<v8::Object> g) {
    Processor::initializeGlobalObject(g);
    g->Set(String::New("myString"), String::New("Coucou les aminches, je suis une string javascript =)\n"));
}

Handle<Value> RequestProcessor::printCallback(const v8::Arguments& args) {
    cerr << "called printCallback\n";
    //retrieve the internal pointer to the processor
    RequestProcessor* processor = (RequestProcessor*) retrieveInternalPointer();
    std::string res = "";
    res += *(String::AsciiValue(args[0]));
    ap_rprintf(processor->_request, "%s", res.c_str());
    return v8::Undefined();
}
