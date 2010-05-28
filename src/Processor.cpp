/*
 * =====================================================================================
 *
 *       Filename:  Processor.cpp
 *
 *    Description:  :
 *
 *        Version:  1.0
 *        Created:  25/05/2010 15:41:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */


#include	"Processor.hpp"

using namespace purple;
using namespace v8;

void Processor::initializeContext() {
    this->_context = Context::New(); 
} /* -----  end of method Processor::initializeContext  ----- */


Handle<Context> Processor::getContext() {
    return this->_context;
}
