/*
 * =====================================================================================
 *
 *       Filename:  bindings.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/06/2010 15:43:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */


#include	<ClassWrap.h>
#include	<ClassWrap_TwoWay.h>
#include	<convert.h>
#include	"Node.hpp"


namespace v8 { namespace juice { namespace cw {
    template<>
    struct InternalFields<purple::Node> : InternalFields_Base<purple::Node, 1, 0> {};

    template<>
    struct ToNative_SearchPrototypesForNative<purple::Node> : Opt_Bool<true>
    {};

    template<>
    struct AllowCtorWithoutNew<purple::Node> : Opt_Bool<false>
    {};

    template<>
    struct Extract<purple::Node> : TwoWayBind_Extract<purple::Node>
    {};
    /*

     */
    template<>
    struct Factory<purple::Node> 
	: Factory_CtorForwarder1<purple::Node, std::string>
    {};

    template<>
    struct ToNative<purple::Node> : ToNative_Base<purple::Node>
    {};

    template<>
    struct ToJS<purple::Node> :  TwoWayBind_ToJS<purple::Node>
    {};

    template<> 
    struct ClassName<purple::Node> {
	static char const * Value() {
	    return "Node";
	}
    };
    
    /*
    template<>
    struct WeakWrap<purple::Node> {
	typedef purple::Node Type;
	typedef purple::Node * NativeHandle
	typedef TwoWayBind_WeakWrap<purple::Node> WB;
	static void Wrap(v8::Persistent<v8::Object> const & jsSelf, NativeHandle nativeSelf) {
	    WB::Wrap(jsSelf, nativeSelf);
	    return;
	}
	static void Unwrap(v8::Persistent<v8::Object> const & jsSelf, NativeHandle nativeSelf) {
	    WB::Unwrap(jsSelf, nativeSelf);
	    return;
	}
    };
     */

}}};

namespace v8 { namespace juice { namespace convert {
    template<>
    struct JSToNative<purple::Node> 
	: v8::juice::cw::JSToNativeImpl<purple::Node>
    {};

    template<>
    struct NativeToJS<purple::Node>
	: v8::juice::cw::NativeToJSImpl<purple::Node>
    {};

}}};
/*
*/
