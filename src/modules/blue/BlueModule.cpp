/*
 * =====================================================================================
 *
 *       Filename:  BlueModule.cpp
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
#include	"BlueModule.hpp"
#include	"BlueProcessor.hpp"
//#include	"bindings.hpp"

using namespace purple;
using namespace ::v8;
using namespace ::v8::juice;
using namespace std;

BlueModule::BlueModule() {
    
}

Handle<Object> BlueModule::getJsModuleObject() {
    Handle<Object> exports = BlueProcessor::getFunction();
    //Handle<Object> exports = Object::New();
    //exports->Set(String::New("chose"), String::New("bidule"));

    /*
    typedef v8::juice::cw::ClassWrap<Blue> CW;
    CW& b(CW::Instance());

    typedef convert::MemFuncInvocationCallbackCreator<Blue> ICM;
    b.BindGetterSetter<std::string, &Blue::getId,
			void, std::string, &Blue::setId>("id");
    b.Set("toString",
	    ICM::M0::Invocable<string, &Blue::toString>);
    b.Set("getId",
	    ICM::M0::Invocable<string, &Blue::getId>);
    b.Set("setId",
	    ICM::M1::Invocable<void, string, &Blue::setId>);
    
    b.Set("toString",
	    ICM::M0::Invocable<string, &Blue::toString>);
    b.Set("getId",
	    ICM::M0::Invocable<string, &Blue::getId>);
    b.Set("isLeaf",
	    ICM::M0::Invocable<bool, &Blue::isLeaf>);
    //b.Set("addChild",
	    //ICM::M1::Invocable<void, Blue*, &Blue::isLeaf>);
    //b.Set("getChildren",
	    //ICM::M0::Invocable<Blue::BlueList, &Blue::getChildren>);
    b.Set("destroy", CW::DestroyObject);

    b.Seal();
    b.AddClassTo(exports);
     */
    //exports->Set(String::New("Blue"), b.CtorTemplate()->GetFunction());
    cerr << exports->IsFunction() << endl;
    return exports;
}
