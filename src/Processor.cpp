/*
 * =====================================================================================
 *
 *       Filename:  Processor.cpp
 *
 *    Description:  :
 *
 *        Version:  1.0
 *        Created:  25/05/2010 15:41:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */


#include	"Processor.hpp"
#include	"Exceptions.hpp"
#include	"ModuleManager.hpp"
#include	<iostream>
#include	<fstream>
#include	<sstream>

using namespace purple;
using namespace v8;
using namespace std;

void Processor::initializeContext() {
    //create global template
    Handle<ObjectTemplate> global_template = ObjectTemplate::New();
    global_template->SetInternalFieldCount(1);
    //fill global template
    initializeGlobalObjectTemplate(global_template);
    //create context
    _context = Context::New(NULL, global_template);
} /* -----  end of method Processor::initializeContext  ----- */


void Processor::initializeGlobalObjectTemplate(Handle<ObjectTemplate> gt) {
    gt->Set(String::New("require"), FunctionTemplate::New(requireCallback)); 
    //gt->SetAccessor(String::New("_env"), _envCallback); //ugly
}

void Processor::initializeGlobalObject(Handle<Object> g) {
    g->Set(String::New("global"), g);
    Handle<Object> paths = Array::New();
    paths->Set(0, String::New("/usr/lib/purple/modules")); //TODO: move this to config
    Handle<Object>::Cast(g->Get(String::New("require")))->Set(String::New("paths"), paths);
    Handle<Object> env = Object::New();
    env->Set(String::New("cwd"), String::New(getCwd().c_str())); 
    g->Set(String::New("_env"), env);
}

Handle<Context> Processor::getContext() {
    return this->_context;
}

int Processor::process() {
    HandleScope handle_scope;
    //the process is the same for every kind of processor


    // create context
    // fill context with custom object
    cerr << "init context\n";
    this->initializeContext();
    Context::Scope context_scope(_context);
    _context->Enter();
    cerr << "entered context\n";
    cerr << "global fieldcount: " <<  Handle<Object>::Cast(_context->Global())->InternalFieldCount() << endl;
    cerr << "global proto fieldcount: " <<  Handle<Object>::Cast(_context->Global()->GetPrototype())->InternalFieldCount() << endl;
    Handle<Object>::Cast(_context->Global()->GetPrototype())->SetPointerInInternalField(0, this);
    cerr << "initializing global object\n";
    initializeGlobalObject(_context->Global());
    
    v8::TryCatch try_catch;
    // get the script
    PScript* script = this->getScript();
    _script = script;
    bool do_not_run = false;
    if(try_catch.HasCaught()) {
	Handle<Value> e = try_catch.Exception();
	this->handleExceptions(e);
	do_not_run = true;
    }

    // execute the script (this doesn't need to be handled by subclasses)
    Handle<Value> jsvalue = script->getJsScript()->Run();
    // catch exceptions
    if(jsvalue.IsEmpty() && try_catch.HasCaught()) {
	Handle<Value> exception = try_catch.Exception();
	this->handleExceptions(exception);
    }
    // determine the return value (integer)
    int result = this->returnValue(jsvalue);
    // clean up
    this->clean();
    // return value
    return result;
}

void Processor::handleExceptions(Handle<Value> e) {
    String::Utf8Value str(e);
    cerr << "uncaught exception: " << *str << endl; 
}

Processor* Processor::retrieveInternalPointer() {
    //cerr << "retrieving internal pointer\n";
    Handle<Object> proto = Handle<Object>::Cast(Context::GetCalling()->Global()->GetPrototype());
    //cerr << "internal fieldcount: " << proto->InternalFieldCount() << endl;
    return (Processor*)Handle<Object>::Cast(Context::GetCalling()->Global()->GetPrototype())->GetPointerFromInternalField(0);
}
/*
void Processor::createContext() {
    this->_context = Context::New();
}
*/

std::string reachScript(std::string filename) {
    std::ifstream file(filename.c_str());
    std::string line;
    std::stringstream res;
    if(!file.good()) throw ("cannot open file");
    while(!std::getline(file, line).eof()) {
	res << (line + '\n');
    }
    return res.str();
}


void Processor::clean() {
    _context->Exit();
}

Processor::Processor() {
}
Processor::~Processor() {
}



v8::Handle<v8::Value> Processor::requireCallback(const v8::Arguments& args) {
    Processor* processor = retrieveInternalPointer();
    string arg(*String::Utf8Value(args[0]));
    cerr << "loading module " << arg << endl;
    try {
	return  processor->getModule(arg);
    } catch(const exception& e) {
	cerr << arg << " could not be loaded\n";
	cerr << e.what() << endl;
	return ThrowException(Exception::Error(String::New(e.what())));
    }
}


Handle<Value> Processor::getModule(const string& name) {
    // does the name has an extension
    unsigned int hasjs, hasso;
    hasjs = name.rfind(".js");
    hasso = name.rfind(".so");
    if(hasjs != string::npos) {
	return getJsModule(name);
    }
    else if(hasso != string::npos) {
	return getSoModule(name);
    }

    //the name has no extension
    try {
	return getJsModule(name+".js");
    }
    catch(const FileNotFound& e) {
	cerr << "trying " << name << ".so" << endl;
	return getSoModule(name+".so");
	try {
	    return getSoModule(name+".so");
	}
	catch(const exception& e) {
	    cerr << "throwing FileNotFound (getModule)\n";
	    throw(FileNotFound(name));
	}
    }
}


Handle<Value> Processor::getJsModule(const string& name) {
    cerr << "attempting to load " << name << endl;
    Handle<Value> require = Context::GetCalling()->Global()->Get(String::New("require"));
    return module_manager.getJsModule(Handle<Function>::Cast(require), name);
}

Handle<Value> Processor::getSoModule(const string& name) {
    cerr << "attempting to load " << name << endl;
    Handle<Value> require = Context::GetCalling()->Global()->Get(String::New("require"));
    return module_manager.getSoModule(Handle<Function>::Cast(require), name);
}

