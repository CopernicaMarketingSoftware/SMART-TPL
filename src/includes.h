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
#include <boost/regex.hpp>
#include <iomanip>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

/**
 *  Public includes
 */

#include "include/source.h"
#include "include/file.h"
#include "include/buffer.h"

#include "include/iterator.h"

#include "include/value.h"
#include "include/variantvalue.h"
#include "include/nullvalue.h"
#include "include/boolvalue.h"
#include "include/numericvalue.h"
#include "include/doublevalue.h"
#include "include/stringvalue.h"
#include "include/vectorvalue.h"
#include "include/mapvalue.h"
#include "include/callback.h"
#include "include/datevalue.h"

#include "include/callbacks.h"
#include "include/parameters.h"
#include "include/modifier.h"
#include "include/data.h"
#include "include/template.h"
#include "include/compileerror.h"

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
#include "escaper.h"
#include "callbackvalue.h"
#include "escapers/null.h"
#include "escapers/html.h"
#include "escapers/url.h"
#include "escapers/base64.h"
#include "builtin/tolower.h"
#include "builtin/toupper.h"
#include "builtin/cat.h"
#include "builtin/strlen.h"
#include "builtin/empty.h"
#include "builtin/count.h"
#include "builtin/count_words.h"
#include "builtin/count_characters.h"
#include "builtin/count_paragraphs.h"
#include "builtin/default.h"
#include "builtin/escape.h"
#include "builtin/indent.h"
#include "builtin/replace.h"
#include "builtin/nl2br.h"
#include "builtin/spacify.h"
#include "builtin/truncate.h"
#include "builtin/ucfirst.h"
#include "builtin/trim.h"
#include "builtin/regex_replace.h"
#include "builtin/substr.h"
#include "builtin/strstr.h"
#include "builtin/urlencode.h"
#include "builtin/urldecode.h"
#include "builtin/md5.h"
#include "builtin/sha1.h"
#include "builtin/sha256.h"
#include "builtin/sha512.h"
#include "builtin/base64encode.h"
#include "builtin/base64decode.h"
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
#include "expressions/literalnumeric.h"
#include "expressions/literaldouble.h"
#include "expressions/literalstring.h"
#include "expressions/filter.h"
#include "statements/statement.h"
#include "statements/statements.h"
#include "statements/raw.h"
#include "statements/expression.h"
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
#include "operators/binarymodulo.h"
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
#include "signature_callback.h"
#include "tokenprocessor.h"
#include "parser.h"
#include "tokenizer.h"
#include "syntaxtree.h"
#include "ccode.h"
#include "callbacks.h"
#include "iterator.h"
#include "handler.h"
#include "executor.h"
#include "jit_exception.h"
#include "bytecode.h"
#include "library.h"
#include "vector_iterator.h"
#include "map_iterator.h"