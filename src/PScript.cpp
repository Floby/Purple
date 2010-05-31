/*
 * =====================================================================================
 *
 *       Filename:  PScript.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  29/05/2010 16:34:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */


#include	<fstream>
#include	<sstream>
#include	"PScript.hpp"
#include	"Exceptions.hpp"

using namespace purple;
using namespace std;
using namespace v8;


PScript::PScript(string filename) : _compiled(false) {
    _src = readFile(filename);
    _timestamp = 0;  //for now
}

PScript::~PScript() {
    _script.Dispose();
}

string PScript::readFile(string filename) {
    std::ifstream file(filename.c_str());
    std::string line;
    std::stringstream res;
    if(!file.good()) throw (FileNotFound(filename));
    while(!std::getline(file, line).eof()) {
	res << (line + '\n');
    }
    return res.str();
}

PScript* PScript::get(string filename) {
    return new PScript(filename);
}

Handle<Script> PScript::getJsScript() {
    if(_compiled) return _script;
    HandleScope handle_scope;
    Handle<String> source = String::New(_src.c_str());
    Handle<Script> script = Script::Compile(source);
    _script = Persistent<Script>::New(script);
    return _script;
}
