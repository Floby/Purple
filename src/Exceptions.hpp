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
	    const std::string& file() {
		return _filename;
	    }
	private:
	    std::string _filename; 
    };
};

#endif /* EXEPTIONS_HPP */