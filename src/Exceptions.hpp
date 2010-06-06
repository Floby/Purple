/*
 * =====================================================================================
 *
 *       Filename:  Exeptions.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  29/05/2010 18:36:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */

#ifndef EXEPTIONS_HPP
#define EXEPTIONS_HPP


#include	<string>
#include	<stdexcept>

namespace purple {
    class FileNotFound :public std::exception {
	public:
	    FileNotFound(std::string filename) : _filename(filename) {
	    }
	    virtual ~FileNotFound() throw() {
	    }
	    virtual const char* what() const throw() {
		return (std::string("couldn't locate ") + _filename).c_str();
	    }
	    const std::string& file() {
		return _filename;
	    }
	private:
	    std::string _filename; 
    };
    class ModuleLoadError :public std::exception {
	public:
	    ModuleLoadError(std::string filename, std::string error) : _filename(filename), _error(error) {
	    }
	    virtual ~ModuleLoadError() throw() {
	    }
	    const std::string& file() {
		return _filename;
	    }

	    virtual const char* what() const throw(){
		return _error.c_str();
	    }
	private:
	    std::string _filename; 
	    std::string _error;
    };


    class CompilingError :public std::exception {
	public:
	    CompilingError(std::string reason) : _reason(reason) {
	    }
	    virtual ~CompilingError() throw() {
	    }
	    const std::string& reason() {
		return _reason;
	    }
	private:
	    std::string _reason; 
    };

};

#endif /* EXEPTIONS_HPP */
