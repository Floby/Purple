/*
 * =====================================================================================
 *
 *       Filename:  PScript.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  29/05/2010 12:49:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */

#ifndef PSCRIPT_HPP
#define PSCRIPT_HPP

#include	<v8/v8-debug.h>
#include	<string>

namespace purple {
    class PScript {
	public:
	    static PScript* get(std::string filename);
	    ~PScript();

	    v8::Handle<v8::Script> getJsScript();
	    const std::string& getSource();
	private:
	    PScript(std::string filename);
	    v8::Persistent<v8::Script> _script;
	    bool _compiled;
	    std::string _src;
	    std::string _filename;
	    int _timestamp;


	    static std::string readFile(std::string filename);
    };
};

#endif /* PSCRIPT_HPP */
