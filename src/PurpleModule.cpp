/*
 * =====================================================================================
 *
 *       Filename:  PurpleModule.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25/05/2010 15:27:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */


#include	"http_protocol.h"
#include	"PurpleModule.hpp"
#include	"RequestProcessor.hpp"

using namespace purple;

int PurpleModule::process(request_rec* r) {
    RequestProcessor rp(r);
    return rp.process();
} /* -----  end of method PurpleModule::process  ----- */


