/*
 * =====================================================================================
 *
 *       Filename:  utils.hpp
 *
 *    Description:  y
 *
 *        Version:  1.0
 *        Created:  07/06/2010 21:37:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Florent Jaby (FJ), florent.jaby@gmail.com
 *        Company:  Florent Jaby
 *
 * =====================================================================================
 */
#ifndef UTILS_HPP
#define UTILS_HPP

#include	<list>
#include	<string>
#include	<iostream>
#include	"httpd.h"
#include	"http_config.h"
namespace purple {
    std::string canon_path(const std::string& path) ;
    std::vector<std::string> apr_table_elements(apr_table_t* t);


    v8::Handle<v8::Value> getFromTable(v8::Local<v8::String> key, const v8::AccessorInfo& info);
    v8::Handle<v8::Value> setInTable (v8::Local<v8::String> key, v8::Local<v8::Value> value, const v8::AccessorInfo& info);
    v8::Handle<v8::Boolean> removeFromTable(v8::Local<v8::String> key, const v8::AccessorInfo& info);
    v8::Handle<v8::Array> listTable(const v8::AccessorInfo& info);
    v8::Handle<v8::Value> addToTable(const v8::Arguments& args);
    /*
     */
};

#endif /* UTILS_HPP */
