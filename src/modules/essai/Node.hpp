/*
 * =====================================================================================
 *
 *       Filename:  Node.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/06/2010 15:16:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */
#ifndef NODE_HPP
#define NODE_HPP

#include	<list>
#include	<vector>
#include	<string>
namespace purple {
    class Node {
	public:
	    Node(std::string id) ;
	    ~Node();

	    std::string getId();
	    void setId(std::string);
	    std::string toString();
	private:
	    std::string _id;
    };
};

#endif /* NODE_HPP */
