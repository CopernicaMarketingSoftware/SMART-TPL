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

/**
 *  LLVM library dependencies
 */
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Type.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Attributes.h>

/**
 *  All public header files of the SmartTpl library
 */
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
#include "tokenprocessor.h"
#include "tokenizer.h"
#include "syntaxtree.h"
#include "parser.h"
#include "ccode.h"
#include "bytecode/writefunction.h"
#include "bytecode/showtemplatefunction.h"
#include "bytecode/externalfunctions.h"
#include "bytecode.h"
