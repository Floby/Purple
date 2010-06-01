/*
 * =====================================================================================
 *
 *       Filename:  FsModule.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/06/2010 15:03:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */


#include	"FsModule.hpp"
#include	"InputStreamWrapper.hpp"

using namespace purple;
using namespace v8;
using namespace std;

Handle<Object> FsModule::getJsModuleObject() {
    Handle<Object> exports = Object::New();
    exports->Set(String::New("desc"), String::New("Kikoo, je vais vous aider à lire des fichiers trop cool!"));
    return exports;
}

