/*
 * =====================================================================================
 *
 *       Filename:  ModuleManager.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  30/05/2010 17:27:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */


#include	"ModuleManager.hpp"
#include	"ModuleProcessor.hpp"
#include	"Exceptions.hpp"
#include	"BinaryModule.hpp"
#include	<iostream>
#include	<dlfcn.h>
#include	<cstdio>
using namespace purple;
using namespace v8;
using namespace std;

static bool do_cache = false;

Handle<Value> ModuleManager::getJsModule(v8::Handle<v8::Function> require, std::string name) {
    if(_loaded_modules.find(name) != _loaded_modules.end()) {
	return _loaded_modules[name];
    }

    cerr << "ModuleManager::getJsModule(" << name << ")\n";
    vector<string> paths = listPossiblePaths(require, name);
    for(unsigned int i=0 ; i<paths.size() ; ++i) {
	try {
	    return loadJsModule(paths[i]);
	} catch(const exception& e) {}
    }
   
    throw(FileNotFound("name"));
}

Handle<Value> ModuleManager::loadJsModule(string path) {
    if(_loaded_modules.find(path) != _loaded_modules.end()) {
	cerr << "USING CACHE FOR " << path << endl;
	return _loaded_modules[path];
    }
    
    ModuleProcessor processor(path);
    processor.process();
    Handle<Value> exports = processor.getContext()->Global()->Get(String::New("exports"));
    cerr << "processed "<< path << endl;
    //sets in the cache
    if(do_cache) _loaded_modules[path] = Persistent<Object>::New(Handle<Object>::Cast(exports));
    return exports;
}

Handle<Value> ModuleManager::loadSoModule(std::string path) {
    //HandleScope hs;
    void* lib_handle;
    char* error;

    lib_handle = dlopen(path.c_str(), RTLD_NOW); // error if unresolved symbols
    if(!lib_handle) {
	cerr << "couldn't load " << path << ": " << dlerror() << endl;
	throw(FileNotFound(path));
    }
    string symname = "";
    unsigned int slashpos, extpos;
    slashpos = path.find_last_of('/')+1;
    extpos = path.rfind(".so");
    cerr << "position of .so "<< path.rfind(".so")<<endl;
    symname += "purple_module_" + path.substr(slashpos, extpos - slashpos);
    cerr << "loading symbol: " << symname << endl;
    BinaryModule* bm = static_cast<BinaryModule*>(dlsym(lib_handle, symname.c_str()));
    if((error = dlerror()) != NULL) {
	cerr << "couldn't get symbol: " << symname << endl;
	throw(FileNotFound(path));
    }
    cerr << "got symbol" << endl;
    // maybe create a context for the created objects
    Handle<Object> module = bm->getJsModuleObject();
    cerr << "got js object " << endl;
    //if(do_cache) _loaded_modules[path] = Persistent<Object>::New(module);
    cerr << "returning module" << endl;
    //return hs.Close(module);
    return module;
}

ModuleManager::envInfo ModuleManager::getEnvInformations(Handle<Function> require) {
    HandleScope hs;
    Handle<Object> paths = Handle<Object>::Cast(require->Get(String::New("paths")));
    unsigned int length = paths->Get(String::New("length"))->Uint32Value();
    cerr << "paths.length = " << length << endl;
    vector<string> res;
    for(unsigned int i=0; i<length ; ++i) {
	String::Utf8Value v(paths->Get(i));
	cerr << "found " << *v << " in paths[" << i << "]\n";
	res.push_back(string(*v));
    }
    Handle<Object> env = Handle<Object>::Cast(Context::GetCalling()->Global()->Get(String::New("_env")));
    String::Utf8Value cwd (env->Get(String::New("cwd")));
    cerr << "found cwd = " << *cwd << endl;
    envInfo result = make_pair(string(*cwd), res);

    return result;

}

vector<string> ModuleManager::listPossiblePaths(Handle<Function> require, string name) {
    vector<string> res;
    if(name[0] == '/') {
	res.push_back(name);
	return res;
    }

    envInfo paths = getEnvInformations(require);
    if(name.find("./") <= 1) { //if begins with ./ or ../
	//on cherche dans le meme répertoire
	cerr << "loading in the same directory " << name << endl;
	res.push_back(paths.first + '/' + name);
	return res;
    }

    for(unsigned int i=0 ; i<paths.second.size() ; ++i) {
	string path = paths.second[i] + '/' + name; 
	//cerr << "trying " << path << endl;
	res.push_back(path);
    }
    return res;
}

Handle<Value> ModuleManager::getSoModule(v8::Handle<v8::Function> require, std::string name) {
    if(_loaded_modules.find(name) != _loaded_modules.end()) {
	return _loaded_modules[name];
    }

    //HandleScope hs;

    cerr << "ModuleManager::getSoModule(" << name << ")\n";
    vector<string> paths = listPossiblePaths(require, name);
    for(unsigned int i=0 ; i<paths.size() ; ++i) {
	try {
	    Handle<Value> res = loadSoModule(paths[i]); //change to SO
	    cerr << "got module (getSoModule)" << endl;
	    //return hs.Close(res);
	    return res;
	} catch(const exception& e) {}
    }
   
    throw(FileNotFound("name"));
}
