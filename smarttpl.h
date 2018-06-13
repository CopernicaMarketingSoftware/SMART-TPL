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
 *  @copyright 2014 - 2016 Copernica BV
 */
#ifndef __SMART_TPL_H__
#define __SMART_TPL_H__

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <list>
#include <sstream>
#include <stack>
#include <string.h>
#include <map>
#include <stdexcept>
#include <dlfcn.h>
#include <cstring>
#include <algorithm>
#include <set>
#include <ctime>
#include <vector>

#include "smarttpl/source.h"
#include "smarttpl/file.h"
#include "smarttpl/buffer.h"

#include "smarttpl/iterator.h"

#include "smarttpl/value.h"
#include "smarttpl/variantvalue.h"
#include "smarttpl/nullvalue.h"
#include "smarttpl/boolvalue.h"
#include "smarttpl/numericvalue.h"
#include "smarttpl/doublevalue.h"
#include "smarttpl/stringvalue.h"
#include "smarttpl/vectorvalue.h"
#include "smarttpl/mapvalue.h"
#include "smarttpl/datevalue.h"

#include "smarttpl/callbacks.h"
#include "smarttpl/parameters.h"
#include "smarttpl/modifier.h"
#include "smarttpl/callback.h"
#include "smarttpl/state.h"
#include "smarttpl/data.h"
#include "smarttpl/template.h"
#include "smarttpl/compileerror.h"
#include "smarttpl/runtimeerror.h"

/**
 *  End of the include guard
 */
#endif // __SMART_TPL_H__

