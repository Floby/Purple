/*
 * =====================================================================================
 *
 *       Filename:  mod_purple.cpp
 *
 *    Description:  Main apache module file
 *
 *        Version:  1.0
 *        Created:  25/05/2010 13:31:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */


#include	"httpd.h"
#include	"http_config.h"
#include	"http_protocol.h"

#include	<string>
#include	"PurpleModule.hpp"
#include	"ModuleManager.hpp"
#include	"Exceptions.hpp"

extern "C" module AP_MODULE_DECLARE_DATA purple_module; // C-style external symbol
namespace purple {
    ModuleManager module_manager;
};
purple::PurpleModule PurpleInstance;

/*
 * Fonction appelée pour chaque requête. retourne le code HTTP
 */
static int mod_purple_method_handler(request_rec* r) {
    fprintf(stderr, "purple: %s was requested (mapped to %s), handled by %s\n", r->uri, r->filename, r->handler);
    fflush(stderr);
    if(std::string("purple") == r->handler) {
	r->content_type = "text/html";
	r->content_type = "text/plain";
	try {
	    PurpleInstance.process(r);
	}
	catch(const char* error) {
	    return 500;
	}
	catch (const purple::FileNotFound& e) {
	    return 404;
	}
	catch(const std::exception& e) {
	    return 500;
	}
	return OK;
    }
    return DECLINED; //we don't process this request
}

/*
 * une fonction callback qui inscrit d'autres callbacks pour gérer les requetes
 */
static void mod_purple_register_hooks(apr_pool_t* p) {
    ap_hook_handler(mod_purple_method_handler, NULL, NULL, APR_HOOK_LAST);
    ap_add_version_component(p, "Purple(nightly alpha masonic)");
}

/*
 * Une structure pour déclarer tous les éléments du module
 */
module AP_MODULE_DECLARE_DATA purple_module = {
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    mod_purple_register_hooks
};
