/**
 *  Includes.h
 * 
 *  Header file that includes all public header files of the SmartTpl library
 * 
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Dependencies
 */
#include <string>
#include <iostream>
#include <memory>
#include <list>
#include <sstream>
#include <stack>
#include <jit/jit-plus.h>
#include <string.h>

/**
 *  All public header files of the SmartTpl library
 */
#include "../include/value.h"
#include "../include/data.h"
#include "../include/template.h"

/**
 *  Implementation-only header files
 */
#include "token.h"
#include "quotedstring.h"
#include "generator.h"
#include "expressions/expression.h"
#include "expressions/variable.h"
#include "expressions/literalvariable.h"
#include "expressions/arrayaccess.h"
#include "expressions/literalarrayaccess.h"
#include "expressions/variablearrayaccess.h"
#include "expressions/literal.h"
#include "expressions/literalboolean.h"
#include "expressions/literalinteger.h"
#include "statements/statement.h"
#include "statements/statements.h"
#include "statements/raw.h"
#include "statements/var.h"
#include "statements/if.h"
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
#include "callbacks/write.h"
#include "callbacks/output.h"
#include "callbacks/member.h"
#include "callbacks/variable.h"
#include "callbacks/tostring.h"
#include "callbacks/tonumeric.h"
#include "callbacks/size.h"
#include "tokenprocessor.h"
#include "parser.h"
#include "tokenizer.h"
#include "syntaxtree.h"
#include "ccode.h"
#include "callbacks.h"
#include "handler.h"
#include "executor.h"
#include "bytecode.h"
