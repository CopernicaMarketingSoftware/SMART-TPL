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

/**
 *  All public header files of the SmartTpl library
 */
#include "../include/data.h"
#include "../include/template.h"

/**
 *  Implementation-only header files
 */
#include "token.h"
#include "parser.h"
#include "tokenizer.h"
#include "syntaxtree.h"
#include "lemon.h"
#include "statements/statement.h"
#include "statements/statements.h"
#include "expressions/expression.h"
#include "expressions/variable.h"
#include "expressions/literalvariable.h"
#include "expressions/arrayaccess.h"
#include "expressions/literalarrayaccess.h"
#include "expressions/variablearrayaccess.h"
#include "expressions/literal.h"
#include "expressions/literalboolean.h"
#include "expressions/literalinteger.h"
#include "statements/echo.h"
#include "statements/if.h"
#include "operators/operator.h"
#include "operators/binary.h"
