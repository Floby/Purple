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

	    typedef std::vector<Node*> NodeList;
	    NodeList getChildren();
	    std::string getId();
	    void addChild(Node*);
	    bool isLeaf();
	    std::string toString();
	private:
	    std::string _id;
	    std::list<Node*> _children;
    };
};

#endif /* NODE_HPP */
