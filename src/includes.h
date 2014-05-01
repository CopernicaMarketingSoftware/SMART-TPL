/**
 *  Includes.h
 * 
 *  Header file that includes all header files of the SmartTpl library
 * 
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  C++ dependencies
 */

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

/**
 *  Public includes
 */

#include "include/source.h"
#include "include/file.h"
#include "include/buffer.h"

#include "include/value.h"
#include "include/string.h"
#include "include/numeric.h"
#include "include/empty.h"
#include "include/map.h"
#include "include/list.h"
#include "include/boolean.h"
#include "include/datevalue.h"

#include "include/callbacks.h"
#include "include/variant.h"
#include "include/modifier.h"
#include "include/data.h"
#include "include/template.h"

/**
 *  Library only dependencies
 */
#include <jit/jit-plus.h>

/**
 *  Implementation-only header files
 */
#include "token.h"
#include "quotedstring.h"
#include "generator.h"
#include "builtin/tolower.h"
#include "builtin/toupper.h"
#include "modifiers/parameters.h"
#include "modifiers/modifierexpression.h"
#include "modifiers/modifiers.h"
#include "expressions/expression.h"
#include "expressions/variable.h"
#include "expressions/literalvariable.h"
#include "expressions/arrayaccess.h"
#include "expressions/literalarrayaccess.h"
#include "expressions/variablearrayaccess.h"
#include "expressions/literal.h"
#include "expressions/literalboolean.h"
#include "expressions/literalinteger.h"
#include "expressions/literalstring.h"
#include "expressions/filter.h"
#include "statements/statement.h"
#include "statements/statements.h"
#include "statements/raw.h"
#include "statements/var.h"
#include "statements/if.h"
#include "statements/foreach.h"
#include "statements/assign.h"
#include "operators/operator.h"
#include "operators/binary.h"
#include "operators/binaryarithmetric.h"
#include "operators/binaryplus.h"
#include "operators/binaryminus.h"
#include "operators/binarydivide.h"
#include "operators/binarymultiply.h"
#include "operators/binarycompare.h"
#include "operators/binaryequals.h"
#include "operators/binarynotequals.h"
#include "operators/binarylesser.h"
#include "operators/binarylesserequals.h"
#include "operators/binarygreater.h"
#include "operators/binarygreaterequals.h"
#include "operators/binaryboolean.h"
#include "operators/binaryand.h"
#include "operators/binaryor.h"
#include "callbacks/callback.h"
#include "callbacks/write.h"
#include "callbacks/output.h"
#include "callbacks/member.h"
#include "callbacks/member_at.h"
#include "callbacks/member_iter.h"
#include "callbacks/loop_start.h"
#include "callbacks/variable.h"
#include "callbacks/tostring.h"
#include "callbacks/tonumeric.h"
#include "callbacks/toboolean.h"
#include "callbacks/modifier.h"
#include "callbacks/modify_variable.h"
#include "callbacks/modify_numeric.h"
#include "callbacks/modify_string.h"
#include "callbacks/size.h"
#include "callbacks/strcmp.h"
#include "callbacks/assign.h"
#include "callbacks/assign_boolean.h"
#include "callbacks/assign_numeric.h"
#include "callbacks/assign_string.h"
#include "tokenprocessor.h"
#include "parser.h"
#include "tokenizer.h"
#include "syntaxtree.h"
#include "ccode.h"
#include "callbacks.h"
#include "handler.h"
#include "executor.h"
#include "bytecode.h"
#include "library.h"
