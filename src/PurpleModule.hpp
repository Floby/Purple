/*
 * =====================================================================================
 *
 *       Filename:  PurpleModule.hpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  25/05/2010 15:20:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */

#ifndef PURPLEMODULE_HPP
#define PURPLEMODULE_HPP

#include	"httpd.h"
#include	"http_config.h"
#include	<string>

namespace purple {

    class PurpleModule {
	public:
	    PurpleModule() {};

	    int process(request_rec* r);
	private:
	    
    };

};

#endif /* PURPLEMODULE_HPP */
