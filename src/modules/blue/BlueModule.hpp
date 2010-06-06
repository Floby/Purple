/*
 * =====================================================================================
 *
 *       Filename:  BlueModule.hpp
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
#ifndef NODEMODULE_HPP
#define NODEMODULE_HPP


#include	<BinaryModule.hpp>
#include	"Blue.hpp"

namespace purple {
    class BlueModule :public BinaryModule {
	public:
	    BlueModule();
	    virtual v8::Handle<v8::Object> getJsModuleObject();
	private:
    };
};

#endif /* NODEMODULE_HPP */
