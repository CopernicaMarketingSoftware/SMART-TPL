/**
 *  SmartTpl.h
 *
 *  This is the startup header file for the SmartTpl library.
 *
 *  SmartTpl is a lightweight template library that is loosely based on the
 *  "Smarty" template language that is implemented in PHP. SmartTpl is fully
 *  implemented in C++, and thus much faster.
 *  
 *  The SmartTpl language is - although much faster, also not as powerful as 
 *  Smarty. This is on purpose: SmartTpl is a template language, and does not
 *  want to be a programming language. It can only be used for displaying 
 *  variables in a template, and for simple "if" statements and simple
 *  loops that iterate over variables.
 * 
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */
#ifndef __SMART_TPL_H__
#define __SMART_TPL_H__

/**
 *  Dependencies
 */
#include <string>
#include <map>
#include <memory>
#include <cstring>

/**
 *  All header files of the SmartTpl library
 */
#include <smarttpl/value.h>
#include <smarttpl/data.h>
#include <smarttpl/template.h>

/**
 *  End of the include guard
 */
#endif // __SMART_TPL_H__

