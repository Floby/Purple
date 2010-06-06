/*
 * =====================================================================================
 *
 *       Filename:  InputFileModule.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/06/2010 15:12:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */
#ifndef INPUTFILEMODULE_HPP
#define INPUTFILEMODULE_HPP


#include	<BinaryModule.hpp>
#include	<fstream>

namespace purple {
    class InputFileModule :public BinaryModule {
	public:
	    InputFileModule();
	    virtual v8::Handle<v8::Object> getJsModuleObject();
	private:
    };
};

#endif /* INPUTFILEMODULE_HPP */
