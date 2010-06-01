/*
 * =====================================================================================
 *
 *       Filename:  BinaryModule.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  31/05/2010 15:10:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */

#ifndef BINARYMODULE_HPP
#define BINARYMODULE_HPP


#include	<v8/v8-debug.h>

namespace purple {
    class BinaryModule {
	public:
	    virtual ~BinaryModule();

	    virtual v8::Handle<v8::Object> getJsModuleObject() =0;
	private:
    };
};

#endif /* BINARYMODULE_HPP */
