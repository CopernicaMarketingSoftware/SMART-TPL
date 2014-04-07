/**
 *  Bytecode.cpp
 *
 *  Implementation file of the LLVM code generator.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */
#include "includes.h"

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Constructor
 *  @param  name        Name of the template (this will also be the module identifier)
 *  @param  tree        The syntax tree that is turned into LLVM
 */
Bytecode::Bytecode(const char *name, const SyntaxTree &tree) : _function(_context), _callbacks(&_function)
{
    // start building the function
    _function.build_start();
    
    // the function gets one parameter, a non-specified void* that will also be
    // passed to all callbacks
    jit_type_t params[1];
    
    // set the parameter
    params[0] = jit_type_void_ptr;
    
    // create the function with the appropriate signature
    _function.create(jit_type_create_signature(jit_abi_cdecl, jit_type_void, params, 1, 1));
    
    // read in the one and only parameter into _userdata
    _userdata = _function.get_param(0);
    
    // generate the LLVM code
    tree.generate(this);
    
    // compile the function
    _function.compile();
    
    // done building
    _function.build_end();
}

/**
 *  Destructor
 */
Bytecode::~Bytecode()
{
}

/**
 *  Generate code to output raw data
 *  @param  data                data to output
 */
void Bytecode::raw(const std::string &data)
{
    // we need a constant of the buffer, and the buffer size
    jit_value buffer = _function.new_constant((void *)data.c_str(), jit_type_void_ptr);
    jit_value size = _function.new_constant(data.size(), jit_type_int);
    
    // call the write function
    _callbacks.write(_userdata, buffer, size);
}

/**
 *  Generate the code to output a variable
 *  @param  variable            the variable to output
 */
void Bytecode::output(const Variable *variable)
{
//    // we need a temporary constant for the variable pointer
//    jit_value pointer = _function.new_constant(variable, jit_type_pointer);
//    
//    // call the output function
//    _callbacks.output(_function, _userdata, pointer);
}

/**
 *  Generate a conditional statement
 *  @param  expression          the expression to evaluate
 *  @param  ifstatements        the statements in the 'if' part
 *  @param  elsestatements      the statements in the 'else' part
 */
void Bytecode::condition(const Expression *expression, const Statements *ifstatements, const Statements *elsestatements)
{
}

/**
 *  Generate the code to get a pointer to a variable
 *  There are three formats, to get a pointer to a literal variable by name,
 *  to get a pointer to a variable inside a table with a literal name, and
 *  to get a pointer to a variable with variable name
 *  @param  parent              parent variable from which the var is retrieved
 *  @param  name                name of the variable
 */
void Bytecode::varPointer(const Variable *parent, const std::string &name)
{
}

/**
 *  Generate the code to get a pointer to a variable
 *  There are three formats, to get a pointer to a literal variable by name,
 *  to get a pointer to a variable inside a table with a literal name, and
 *  to get a pointer to a variable with variable name
 *  @param  parent              parent variable from which the var is retrieved
 *  @param  expression          Expression that evaluates to a var name
 */
void Bytecode::varPointer(const Variable *parent, const Expression *expression)
{
}

/**
 *  Generate the code to get a pointer to a variable
 *  There are three formats, to get a pointer to a literal variable by name,
 *  to get a pointer to a variable inside a table with a literal name, and
 *  to get a pointer to a variable with variable name
 *  @param  name                name of the variable
 */
void Bytecode::varPointer(const std::string &name)
{
}

/**
 *  Create a string or numeric literal
 *  @param  value
 */
void Bytecode::string(const std::string &value)
{
}

/**
 *  Create a string or numeric literal
 *  @param  value
 */
void Bytecode::numeric(int value)
{
}

/**
 *  Create a string or numeric constant for a variable
 *  @param  variable
 */
void Bytecode::string(const Variable *variable)
{
}

/**
 *  Create a string or numeric constant for a variable
 *  @param  variable
 */
void Bytecode::numeric(const Variable *variable)
{
}

/**
 *  Create a string literal from an expression that is known to return a numeric value,
 *  and a method to do this in the other direction
 *  @param  expression
 */
void Bytecode::numericToString(const Expression *expression)
{
}

/**
 *  Create a string literal from an expression that is known to return a numeric value,
 *  and a method to do this in the other direction
 *  @param  expression
 */
void Bytecode::stringToNumeric(const Expression *expression)
{
}

/**
 *  Arithmetric operations
 *  @param  left
 *  @param  right
 */
void Bytecode::plus(const Expression *left, const Expression *right) {}
void Bytecode::minus(const Expression *left, const Expression *right) {}
void Bytecode::divide(const Expression *left, const Expression *right) {}
void Bytecode::multiply(const Expression *left, const Expression *right) {}

/**
 *  Comparison operators
 *  @param  left
 *  @param  right
 */
void Bytecode::equals(const Expression *left, const Expression *right) {}
void Bytecode::notEquals(const Expression *left, const Expression *right) {}
void Bytecode::greater(const Expression *left, const Expression *right) {}
void Bytecode::greaterEquals(const Expression *left, const Expression *right) {}
void Bytecode::lesser(const Expression *left, const Expression *right) {}
void Bytecode::lesserEquals(const Expression *left, const Expression *right) {}

/**
 *  Boolean operators
 *  @param  left
 *  @param  right
 */
void Bytecode::booleanAnd(const Expression *left, const Expression *right) {}
void Bytecode::booleanOr(const Expression *left, const Expression *right) {}

/**
 *  End namespace
 */
}

