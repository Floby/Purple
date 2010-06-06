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

Node::Node(string id) : _id(id) {}
Node::~Node() {
}
std::string Node::getId() {
    return _id;
}

void Node::setId(string id) {
    _id = id;
}

std::string Node::toString() {
    return string("node-> id:") + _id;
}
