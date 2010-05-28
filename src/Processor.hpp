/*
 * =====================================================================================
 *
 *       Filename:  Processor.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25/05/2010 15:41:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */

#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include	<v8/v8-debug.h>

namespace purple {
    class Processor {
	public:
	    Processor();
	    virtual ~Processor();

	    virtual int process() =0;
	protected:
	    virtual void initializeContext();
	    virtual v8::Handle<v8::Context> getContext();
	private:
	    v8::Persistent<v8::Context> _context; 
    };
};

#endif /* PROCESSOR_HPP */

