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
    _out << "#include <smarttpl/callbacks.h>" << std::endl;

    // create function header
    _out << "void show_template(struct smart_tpl_callbacks *callbacks, void *userdata) {" << std::endl;
    
    // generate the statements
    tree.generate(this);
    
    // end of the function
    _out << "}" << std::endl;
}

/**
 *  Generate the code to output raw data
 *  @param  data        buffer to output
 */
void CCode::raw(const std::string &data) 
{
    // quote newlines, null characters, etc in the string so that it can
    // be picked up by the compiler
    QuotedString quoted(data);
    
    // output the data
    _out << "callbacks->write(userdata,\"" << quoted << "\"," << data.size() << ");" << std::endl;
}

/**
 *  Generate the code to output an expression
 *  @param  expression  expression to output
 */
void CCode::output(const Expression *expression)
{
    const Variable* variable = dynamic_cast<const Variable*>(expression);
    if (variable)
    {
        _out << "callbacks->output(userdata,";
        variable->pointer(this);
        _out << ");" << std::endl;
    }
    else
    {
        // we're going to call the write function
        _out << "callbacks->write(userdata,";

        // convert the expression to a string
        expression->string(this);

        // end of the function
        _out << ");" << std::endl;
    }
}

/**
 *  Generate a conditional statement
 *  @param  expression          the expression to evaluate
 *  @param  ifstatements        the statements in the 'if' part
 *  @param  elsestatements      the statements in the 'else' part
 */
void CCode::condition(const Expression *expression, const Statements *ifstatements, const  Statements *elsestatements)
{
    // this is going to be a regular C "if" statement
    _out << "if (";
    
    // and now we generate the code that turns the expression into a boolean
    expression->boolean(this);
    
    // close the if condition and open a curly brace to start a new code block
    _out << "){" << std::endl;
    
    // now we generate all statements
    ifstatements->generate(this);
    
    // do we have an else block?
    if (elsestatements)
    {
        // close the if block and open the else block
        _out << "}else{" << std::endl;
        
        // generate the else statements
        elsestatements->generate(this);
    }
    
    // and of the block
    _out << "}" << std::endl;
}

/**
 *  Generate the code to get a pointer to a variable
 *  @param  name                name of the variable
 */
void CCode::varPointer(const std::string &name)
{
    // call the callback to get the variable
    _out << "callbacks->variable(userdata,\"" << name << "\"," << name.size() << ")";
}

/**
 *  Generate the code to get a pointer to a variable
 *  @param  parent              parent variable from which the var is retrieved
 *  @param  name                name of the variable
 */
void CCode::varPointer(const Variable *parent, const std::string &name)
{
    // call the member() function
    _out << "callbacks->member(userdata,";
    
    // generate a var pointer for the variable
    parent->pointer(this);
    
    // and append a call to retrieve the member
    _out << ",\"" << name << "\"," << name.size() << ")";
}

/**
 *  Generate the code to get a pointer to a variable
 *  @param  parent              parent variable from which the var is retrieved
 *  @param  expression          Expression that evaluates to a var name
 */
void CCode::varPointer(const Variable *parent, const Expression *expression)
{
    // call the member() function
    _out << "callbacks->member(userdata,";

    // generate a var pointer for the variable
    parent->pointer(this);
    
    // and append a call to retrieve the member
    _out << ",";
    
    // and now we should generate a string value for the expression
    expression->string(this);
    
    // end expression
    _out << ")";
}

/**
 *  Create a string literal
 *  @param  value
 */
void CCode::string(const std::string &value)
{
    // quote newlines, null characters, etc in the string so that it can
    // be picked up by the compiler
    QuotedString quoted(value);

    // output string
    _out << "\"" << quoted << "\"," << value.size();
}

/**
 *  Create a numeric literal
 *  @param  value
 */
void CCode::numeric(int value)
{
    // output number
    _out << value;
}

/**
 *  Create a string constant for a variable
 *  @param  variable
 */
void CCode::string(const Variable *variable)
{
    // call the to_string method
    _out << "callbacks->to_string(userdata,";
    
    // generate pointer to the variable
    variable->pointer(this);
    
    // ask the size of the variable
    _out << "), callbacks->size(userdata,";
    
    // generate another pointer to the variable
    variable->pointer(this);
    
    // that was it
    _out << ")";
    
    
}

/**
 *  Create a string or numeric constant for a variable
 *  @param  variable
 */
void CCode::numeric(const Variable *variable)
{
    // call the to_numeric method
    _out << "callbacks->to_numeric(userdata,";
    
    // generate pointer to the variable
    variable->pointer(this);

    // that was it
    _out << ")";
}

/**
 *  Create a boolean constant for a variable
 *  @param  variable
 */
void CCode::boolean(const Variable *variable)
{
    // call the to_numeric method
    _out << "callbacks->to_boolean(userdata,";
    
    // generate pointer to the variable
    variable->pointer(this);

    // that was it
    _out << ")";
}

/**
 *  Create a string value from an expression that is known to return a numeric value
 *  @param  expression
 */
void CCode::numericToString(const Expression *expression)
{
    // we have a special function for this
    _out << "numeric_to_string(";
    
    // output the expression to numeric
    expression->numeric(this);
    
    // end of function
    _out << ")";
}

/**
 *  Create a numeric value from an expression that is known to return a string
 *  @param  expression
 */
void CCode::stringToNumeric(const Expression *expression)
{
    // we have a special function for this
    _out << "string_to_numeric(";
    
    // output the expression
    expression->string(this);
    
    // end of function
    _out << ")";
}

/**
 *  Arithmetric operations
 *  @param  left
 *  @param  right
 */
void CCode::plus(const Expression *left, const Expression *right)       { left->numeric(this); _out << "+"; right->numeric(this); }
void CCode::minus(const Expression *left, const Expression *right)      { left->numeric(this); _out << "-"; right->numeric(this); }
void CCode::divide(const Expression *left, const Expression *right)     { left->numeric(this); _out << "/"; right->numeric(this); }
void CCode::multiply(const Expression *left, const Expression *right)   { left->numeric(this); _out << "*"; right->numeric(this); }

/**
 *  Comparison operators
 *  @param  left
 *  @param  right
 */
void CCode::equals(const Expression *left, const Expression *right)         { left->numeric(this); _out << "=="; right->numeric(this); }
void CCode::notEquals(const Expression *left, const Expression *right)      { left->numeric(this); _out << "!="; right->numeric(this); }
void CCode::greater(const Expression *left, const Expression *right)        { left->numeric(this); _out << ">" ; right->numeric(this); }
void CCode::greaterEquals(const Expression *left, const Expression *right)  { left->numeric(this); _out << ">="; right->numeric(this); }
void CCode::lesser(const Expression *left, const Expression *right)         { left->numeric(this); _out << "<";  right->numeric(this); }
void CCode::lesserEquals(const Expression *left, const Expression *right)   { left->numeric(this); _out << "<="; right->numeric(this); }

/**
 *  Boolean operators
 *  @param  left
 *  @param  right
 */
void CCode::booleanAnd(const Expression *left, const Expression *right) { left->boolean(this); _out << "&&"; right->boolean(this); }
void CCode::booleanOr(const Expression *left, const Expression *right)  { left->boolean(this); _out << "||"; right->boolean(this); }

/**
 *  End of namespace
 */
}

