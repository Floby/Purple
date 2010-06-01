/*
 * =====================================================================================
 *
 *       Filename:  FsModule.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/06/2010 14:57:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */

#ifndef FSMODULE_HPP
#define FSMODULE_HPP


#include	<BinaryModule.hpp>

namespace purple {
    class FsModule :public BinaryModule {
	public:
	    virtual v8::Handle<v8::Object> getJsModuleObject();
    };
};

#endif /* FSMODULE_HPP */
