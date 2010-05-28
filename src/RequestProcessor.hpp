/*
 * =====================================================================================
 *
 *       Filename:  RequestProcessor.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25/05/2010 16:09:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */

#ifndef REQUESTPROCESSOR_HPP
#define REQUESTPROCESSOR_HPP

namespace purple {
    class RequestProcessor :public Processor {
	public:
	    RequestProcessor(request_rec* r);
	    virtual ~RequestProcessor();

	    virtual int process();
	private:
	   request_rec* _request; 
    };
};

#endif /* REQUESTPROCESSOR_HPP */

