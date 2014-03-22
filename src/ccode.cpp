/**
 *  Ccode.cpp
 *
 *  Implementation file for the Ccode class
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
 *  @param  tree        The abstract syntax tree of the template
 */
CCode::CCode(const SyntaxTree &tree)
{
    // include headers
    _out << "#include <smarttpl/shared.h>" << std::endl;
    
    // create function header
    _out << "void show_template(smarttpl_callbacks_t *callbacks) {" << std::endl;
    
    // generate the statements
    tree.generate(this);
    
    // end of the function
    _out << "}" << std::endl;
}

/**
 *  Generate the code to output raw data
 *  @param  buffer      buffer to output
 *  @param  size        buffer size
 */
void CCode::raw(const char *data, size_t size) 
{
    // quote newlines, null characters, etc in the string so that it can
    // be picked up by the compiler
    QuotedString quoted(data, size);
    
    // output the data
    _out << "callbacks->write(\"" << quoted << "\", " << size << ");" << std::endl;
}

/**
 *  Generate the code to output a variable
 *  @param  variable    the variable to output
 */
void CCode::output(const Variable *variable)
{
    // we're going to call the output function
    _out << "callbacks->output(";
        
    // generate the code to get a pointer to the variable
    variable->generate(this);
        
    // end of the function
    _out << ");" << std::endl;
}

/**
 *  Generate a conditional statement
 *  @param  expression          the expression to evaluate
 *  @param  ifstatements        the statements in the 'if' part
 *  @param  elsestatements      the statements in the 'else' part
 */
void CCode::conditional(const Expression *expression, const Statements *ifstatements, const  Statements *elsestatements)
{
    // this is going to be a regular C "if" statement
    _out << "if (";
    
    // and now we generate the code that turns the expression into a boolean
    // (and because in C there are no boolean, we use a numeric value)
    numeric(expression);
    
    // close the if condition and open a curly brace to start a new code block
    _out << "){" << std::endl;
    
    // now we generate all statements
    ifstatements->generate(this);
    
    // do we have an else block?
    if (elsetatements)
    {
        // close the if block and open the else block
        _out << "}else{" << std::endl;
        
        // generate the else statements
        _elsestatements->generate(this);
    }
    
    // and of the block
    _out << "}" << std::endl;
}

/**
 *  End of namespace
 */
}

