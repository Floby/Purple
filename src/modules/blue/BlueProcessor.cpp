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


#include	<sstream>
#include	<v8/juice/convert.h>
#include	<ModuleManager.hpp>
#include	<utils.hpp>
#include	<Exceptions.hpp>
#include	"BlueProcessor.hpp"

using namespace purple;
using namespace std;
using namespace v8;

BlueProcessor::BlueProcessor(string filename, Handle<Value> data, Handle<Object> global) {
    _filenames.push(filename);
    cerr << "data = " << juice::convert::CastFromJS<string>(data) << endl;
    _data = Persistent<Value>::New(data->IsUndefined() ? Object::New() : data );
    _global = Persistent<Object>::New(global->IsUndefined() ? Object::New() : global);
}


void BlueProcessor::initializeGlobalObjectTemplate(v8::Handle<v8::ObjectTemplate> gt) {
    Processor::initializeGlobalObjectTemplate(gt);
    gt->Set(String::New("__include"), FunctionTemplate::New(includeCallback));
    gt->Set(String::New("__print"), FunctionTemplate::New(printCallback));
    gt->Set(String::New("__report__error"), FunctionTemplate::New(reportErrorCallback));
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
    g->Set(String::New("data"), _data);
}
    
PScript* BlueProcessor::getScript() {
    return BScript::get(_filenames.top());
}
std::string BlueProcessor::getCwd() {
   string dir = _filenames.top();
   dir = dir.substr(0, dir.find_last_of('/')+1);
   return dir;
}
void BlueProcessor::handleExceptions(v8::Handle<v8::Value> e) {
    Processor::handleExceptions(e);
    _buffer += "\n\n" + juice::convert::CastFromJS<string>(e)+"\n";
}
int BlueProcessor::returnValue(v8::Handle<v8::Value> jsReturnValue) {
    return 0;
}
void BlueProcessor::clean() {
    Processor::clean();
    if(_errors.size() == 0) return;
    stringstream ss;
    ss << "\n<br /><br />\n\n";
    for(unsigned int i=0 ; i<_errors.size() ; ++i) {
	ss <<  "error #" << (i+1) << " : "
	    << _errors[i] << "<br />\n\n";
    }
    _buffer += ss.str();
}

std::string BlueProcessor::include(std::string filename) {
    cerr << "called include with "<<filename<<endl;
    HandleScope hs;
    if(filename.find_first_of('/') != 0) {
	//it's a relative path	
	filename = getCwd() + '/' + filename;
    }
    filename = canon_path(filename);
    cerr << "loading " << filename << endl;
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

string BlueProcessor::getResult() {
    return _buffer;
}

v8::Handle<v8::Value> BlueProcessor::includeCallback(const v8::Arguments& args) {
    string filename = v8::juice::convert::CastFromJS<string>(args[0]);
    BlueProcessor* p = (BlueProcessor*) Processor::retrieveInternalPointer();
    try {
	return v8::juice::convert::CastToJS<string>(p->include(filename));
    } catch(const FileNotFound& e) {
	return ThrowException(Exception::Error(String::New(e.what())));
    }
}
v8::Handle<v8::Value> BlueProcessor::printCallback(const v8::Arguments& args) {
    string str = v8::juice::convert::CastFromJS<string>(args[0]);
    BlueProcessor* p = (BlueProcessor*) retrieveInternalPointer();
    p->print(str);
    return v8::Undefined(); 
}
Handle<Value> BlueProcessor::reportErrorCallback(const Arguments& args) {
    string str = v8::juice::convert::CastFromJS<string>(args[0]);
    BlueProcessor* p = (BlueProcessor*) retrieveInternalPointer();
    return p->reportError(str);
}

Handle<Value> BlueProcessor::reportError(string e) {
    _errors.push_back(e);
    stringstream ss;
    ss << "[err #" << _errors.size() << "]";
    return juice::convert::CastToJS<string>(ss.str());
}

BlueProcessor::BScript::BScript(const string& filename) : PScript(filename) {
    Handle<Function> bidon = Handle<Function>::Cast(Object::New());
    Handle<Function> parser = Handle<Function>::Cast(module_manager.getJsModule(bidon, "/usr/lib/purple/js/BlueParser.js"));
    Handle<Value> args[] = {
	v8::juice::convert::CastToJS(_src)
    };    
    Handle<Value> result = parser->Call(Object::New(), 1, args);
    _src = v8::juice::convert::CastFromJS<string>(result);
    //cerr << _src << endl;
}

BlueProcessor::BScript* BlueProcessor::BScript::get(const string& filename) {
    PScript* c = PScript::getFromCache(filename);
    if(c) return (BScript*)c;
    return new BScript(filename);
}


Handle<Object> BlueProcessor::getFunction() {
    HandleScope hs;
    Handle<FunctionTemplate> ft = FunctionTemplate::New(jsFunction);
    return hs.Close(ft->GetFunction());
}

v8::Handle<v8::Value> BlueProcessor::jsFunction(const v8::Arguments& args) {
    HandleScope hs;
    Processor* processor = (Processor*) Processor::retrieveInternalPointer();
    string filename = v8::juice::convert::CastFromJS<string>(args[0]);
    if(filename[0] != '/') {
	filename = processor->getCwd()+"/"+filename;
    }

    //creating processor
    BlueProcessor bp(canon_path(filename), args[1], Handle<Object>::Cast(args[2]));
    bp.process();
    string result = bp.getResult();
    return hs.Close(juice::convert::CastToJS<string>(result));
}
