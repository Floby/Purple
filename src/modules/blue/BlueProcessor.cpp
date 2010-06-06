/*
 * =====================================================================================
 *
 *       Filename:  BlueProcessor.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2010 23:26:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */


#include	<v8/juice/convert.h>
#include	<ModuleManager.hpp>
#include	"Blue.hpp"

using namespace purple;
using namespace std;
using namespace v8;

BlueProcessor::BlueProcessor(string filename, Handle<Value> data, Handle<Object> global) {
    _filenames.push(filename);
    _data = Persistent<Value>::New(data);
    _global = Persistent<Object>::New(global);
}


void BlueProcessor::initializeGlobalObjectTemplate(v8::Handle<v8::ObjectTemplate> gt) {
    Processor::initializeGlobalObjectTemplate(gt);
    gt->Set(String::New("__include"), FunctionTemplate::New(includeCallback));
    gt->Set(String::New("__print"), FunctionTemplate::New(printCallback));
}
void BlueProcessor::initializeGlobalObject(v8::Handle<v8::Object> g) {
    Processor::initializeGlobalObject(g);
    Handle<Array> names = _global->GetPropertyNames();
    unsigned int length = names->Get(String::New("length"))->Uint32Value();
    for(unsigned int i=0; i<length ; ++i) {
	g->Set(names->Get(i), _global->Get(names->Get(i)));	
    }
    g->Set(String::New("echo"), FunctionTemplate::New(printCallback)->GetFunction());
    g->Set(String::New("print"), FunctionTemplate::New(printCallback)->GetFunction());
}
    
PScript* BlueProcessor::getScript() {
    return BScript::get(_filenames.top());
}
std::string BlueProcessor::getCwd() {
   string dir = _filenames.top();
   dir = dir.substr(0, dir.find_last_of('/'));
   return dir.length() == 0 ? "/" : dir;
}
void BlueProcessor::handleExceptions(v8::Handle<v8::Value> e) {
    Processor::handleExceptions(e);
}
int BlueProcessor::returnValue(v8::Handle<v8::Value> jsReturnValue) {
    return 0;
}
void BlueProcessor::clean() {
    Processor::clean();
}

std::string BlueProcessor::include(std::string filename) {
    HandleScope hs;
    if(filename.find("./") <= 1) {
	//it's a relative path	
	filename = getCwd() + filename;
    }
    PScript* bscript = BScript::get(filename);
    TryCatch try_catch;
    Handle<Script> script = bscript->getJsScript();
    _bufferized.push(_buffer);
    _buffer = "";
    _filenames.push(filename);
    script->Run();
    string result = _buffer;
    _filenames.pop();
    _buffer = _bufferized.top();
    _bufferized.pop();
    return result;
}

void BlueProcessor::print(std::string str) {
    _buffer += str;
}

v8::Handle<v8::Value> BlueProcessor::includeCallback(const v8::Arguments& args) {
    string filename = v8::juice::convert::CastFromJS<string>(args[0]);
    BlueProcessor* p = (BlueProcessor*) Processor::retrieveInternalPointer();
    return v8::juice::convert::CastToJS<string>(p->include(filename));
}
v8::Handle<v8::Value> BlueProcessor::printCallback(const v8::Arguments& args) {
    string str = v8::juice::convert::CastFromJS<string>(args[0]);
    BlueProcessor* p = (BlueProcessor*) retrieveInternalPointer();
    p->print(str);
    return v8::Undefined(); 
}

BlueProcessor::BScript::BScript(const string& filename) : PScript(filename) {
    Handle<Function> bidon = Handle<Function>::Cast(Object::New());
    Handle<Function> parser = Handle<Function>::Cast(module_manager.getJsModule(bidon, "/usr/lib/purple/js/BlueParser.js"));
    Handle<Value> args[] = {v8::juice::convert::CastToJS(_src)};
    Handle<Value> result = parser->Call(Object::New(), 1, args);
    _src = v8::juice::convert::CastFromJS<string>(result);
}

BlueProcessor::BScript* BlueProcessor::BScript::get(const string& filename) {
    return new BScript(filename);
}
