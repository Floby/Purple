/*
 * =====================================================================================
 *
 *       Filename:  ModuleManager.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  30/05/2010 17:08:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */

#ifndef MODULEMANAGER_HPP
#define MODULEMANAGER_HPP


#include	<string>
#include	<list>
#include	<vector>
#include	<map>
#include	<iostream>

#include	<v8/v8-debug.h>

namespace purple {
    class ModuleManager {
	public:
	    v8::Handle<v8::Value> getJsModule(v8::Handle<v8::Function>, std::string name);
	    v8::Handle<v8::Value> getSoModule(v8::Handle<v8::Function>, std::string name);

	private:
	    std::map<std::string, v8::Persistent<v8::Object> > _loaded_modules;

	    typedef std::pair<std::string, std::vector<std::string> > envInfo;
	    static envInfo getEnvInformations(v8::Handle<v8::Function> require);
	
	    v8::Handle<v8::Value> loadJsModule(std::string path);
	    v8::Handle<v8::Value> loadSoModule(std::string path);
	    static std::vector<std::string> listPossiblePaths(v8::Handle<v8::Function> require, std::string name);
    };
    extern ModuleManager module_manager;
};



#endif /* MODULEMANAGER_HPP */
