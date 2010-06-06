/*
 * =====================================================================================
 *
 *       Filename:  InputFileModule.cpp
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
#include	"InputFileModule.hpp"
#include	<fstream>
#include	"bindings.hpp"

using namespace purple;
using namespace ::v8;
using namespace ::v8::juice;
using namespace std;

InputFileModule::InputFileModule() {
    
}

Handle<Object> InputFileModule::getJsModuleObject() {
    Handle<Object> exports = Object::New();

    typedef v8::juice::cw::ClassWrap<std::ifstream> CW;
    CW& b(CW::Instance());
/*
    typedef convert::MemFuncInvocationCallbackCreator<Node> ICM;
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
    b.Set("close", CW::DestroyObject);
*/
    b.Seal();
    b.AddClassTo(exports);

    return exports;
}
