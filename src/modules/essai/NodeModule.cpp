/*
 * =====================================================================================
 *
 *       Filename:  NodeModule.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/06/2010 15:15:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */


#include	<v8/v8-debug.h>
#include	<juice/ClassWrap.h>
#include	"NodeModule.hpp"
#include	"Node.hpp"
#include	"bindings.hpp"

using namespace purple;
using namespace ::v8;
using namespace ::v8::juice;
using namespace std;

NodeModule::NodeModule() {
    
}

Handle<Object> NodeModule::getJsModuleObject() {
    Handle<Object> exports = Object::New();

    typedef v8::juice::cw::ClassWrap<Node> CW;
    CW& b(CW::Instance());

    typedef convert::MemFuncInvocationCallbackCreator<Node> ICM;
    b.BindGetterSetter<std::string, &Node::getId,
			void, std::string, &Node::setId>("id");
    b.Set("toString",
	    ICM::M0::Invocable<string, &Node::toString>);
    b.Set("getId",
	    ICM::M0::Invocable<string, &Node::getId>);
    b.Set("setId",
	    ICM::M1::Invocable<void, string, &Node::setId>);
    
    /*
    b.Set("toString",
	    ICM::M0::Invocable<string, &Node::toString>);
    b.Set("getId",
	    ICM::M0::Invocable<string, &Node::getId>);
    b.Set("isLeaf",
	    ICM::M0::Invocable<bool, &Node::isLeaf>);
    //b.Set("addChild",
	    //ICM::M1::Invocable<void, Node*, &Node::isLeaf>);
    //b.Set("getChildren",
	    //ICM::M0::Invocable<Node::NodeList, &Node::getChildren>);
     */
    b.Set("destroy", CW::DestroyObject);

    b.Seal();
    b.AddClassTo(exports);
    //exports->Set(String::New("Node"), b.CtorTemplate()->GetFunction());

    return exports;
}
