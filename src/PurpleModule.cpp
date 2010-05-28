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

using namespace purple;

int PurpleModule::process(request_rec* r) {
    ap_rprintf(r, "Kikoo =), c'est purple avec le module\n");
    return OK;
} /* -----  end of method PurpleModule::process  ----- */


