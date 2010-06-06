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
#include	<fstream>


namespace v8 { namespace juice { namespace cw {
    template<>
    struct InternalFields<std::ifstream> : InternalFields_Base<std::ifstream, 1, 0> {};

    template<>
    struct ToNative_SearchPrototypesForNative<std::ifstream> : Opt_Bool<true>
    {};

    template<>
    struct AllowCtorWithoutNew<std::ifstream> : Opt_Bool<false>
    {};

    template<>
    struct Extract<std::ifstream> : TwoWayBind_Extract<std::ifstream>
    {};
    /*

     */
    template<>
    struct Factory<std::ifstream> 
	: Factory_CtorForwarder1<std::ifstream, char*>
    {};

    template<>
    struct ToNative<std::ifstream> : ToNative_Base<std::ifstream>
    {};

    template<>
    struct ToJS<std::ifstream> :  TwoWayBind_ToJS<std::ifstream>
    {};

    template<> 
    struct ClassName<std::ifstream> {
	static char const * Value() {
	    return "InputFile";
	}
    };
    
    /*
    template<>
    struct WeakWrap<std::ifstream> {
	typedef std::ifstream Type;
	typedef std::ifstream * NativeHandle
	typedef TwoWayBind_WeakWrap<std::ifstream> WB;
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
    struct JSToNative<std::ifstream> 
	: v8::juice::cw::JSToNativeImpl<std::ifstream>
    {};

    template<>
    struct NativeToJS<std::ifstream>
	: v8::juice::cw::NativeToJSImpl<std::ifstream>
    {};

}}};
/*
*/
