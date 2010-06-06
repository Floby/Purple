/*
 * =====================================================================================
 *
    Filename:  ModuleProcessor.cpp
 *
 *    
 *
 *        Version:  1.0
 *        Created:  30/05/2010 16:15:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 * 
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */


#include	"ModuleProcessor.hpp"
using namespace purple;
using namespace v8;
using namespace std;

ModuleProcessor::ModuleProcessor(const string& filename) : _filename(filename) { 
}

void ModuleProcessor::initializeGlobalObjectTemplate(v8::Handle<v8::ObjectTemplate> gt) {
    Processor::initializeGlobalObjectTemplate(gt);
}

void ModuleProcessor::initializeGlobalObject(v8::Handle<v8::Object> g) {
    Processor::initializeGlobalObject(g);
}

PScript* ModuleProcessor::getScript() {
    return PScript::get(_filename); 
}

string ModuleProcessor::getCwd() {
    return _filename.substr(0, _filename.find_last_of('/'));
}

int ModuleProcessor::returnValue(v8::Handle<v8::Value> jsReturnValue) {
    return 0;
}


void ModuleProcessor::clean() {
   Processor::clean(); 
}
