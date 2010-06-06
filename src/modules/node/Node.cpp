/*
 * =====================================================================================
 *
 *       Filename:  Node.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/06/2010 15:23:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */

#include	<sstream>
#include	"Node.hpp"

using namespace purple;
using namespace std;
/*
static unsigned int next_id=0;
Node::Node() {
    _id = next_id++;
}
 */

Node::Node(string id) : _id(id) {}

std::string Node::getId() {
    return _id;
}

string Node::toString() {
    stringstream res;
    res << getId();
    return (res.str());
}

Node::NodeList Node::getChildren() {
    if(isLeaf()) return NodeList();  
    list<Node*>::iterator it;
    NodeList res;
    for(it = _children.begin() ; it != _children.end() ; ++it) {
	res.push_back(*it);
    }
    return res;
}

bool Node::isLeaf() {
    return !(_children.empty());
}

void Node::addChild(Node* n) {
    _children.push_back(n);
}

