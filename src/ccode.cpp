/**
 *  Ccode.cpp
 *
 *  Implementation file for the Ccode class
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 - 2019 Copernica BV
 */
#include "includes.h"

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

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
    _out << '}' << std::endl;

    // the function to check whether a template uses personalization data
    _out << "int personalized = " << (tree.personalized() ? "1" : "0") << ";" << std::endl;

    // Write a second function that returns what mode we are in
    _out << "const char *mode = ";

    // Quote the string from mode() just in case
    QuotedString quoted(tree.mode());

    // And write the string from mode() after the const char *mode declaration
    _out << '\"' << quoted << "\";" << std::endl;
}

CCode::CCode(const Source &source) : 
    CCode(SyntaxTree(source.version(), source.data(), source.size()))
{
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
 *  Generate the code to output a variable
 *  @param  variable           The variable to output
 */
void CCode::output(const Variable* variable)
{
    // we're going to call the output function
    _out << "callbacks->output(userdata,";

    // convert the variable to the pointer of it
    variable->pointer(this);

    // end of the function
    _out << ",1);" << std::endl;
}

/**
 *  Generate the code to output the output of a filter
 *  @param  filter             The filter to eventually output
 */
void CCode::output(const Filter *filter)
{
    // Now let's actually call the output callback
    _out << "callbacks->output(userdata,";

    // call the pointer method on our filter, which writes all the filtering code for us
    filter->pointer(this);

    // Let's write the escape flag
    _out << ',' << (filter->escape() ? 1 : 0);

    // And end the output statement
    _out << ");" << std::endl;
}

/**
 *  Generate the code to write an expression as a string
 *  @param  expression          the expression to write as a string
 */
void CCode::write(const Expression *expression)
{
    if (expression->type() == Expression::Type::Integer)
    {
        _out << "callbacks->output_integer(userdata,";

        expression->toInteger(this);

        _out << ");" << std::endl;
    }
    else if (expression->type() == Expression::Type::Boolean)
    {
        _out << "callbacks->output_boolean(userdata,";

        expression->toBoolean(this);

        _out << ");" << std::endl;
    }
    else if (expression->type() == Expression::Type::Double)
    {
        _out << "callbacks->output_double(userdata,";

        expression->toDouble(this);

        _out << ");" << std::endl;
    }
    else if (expression->type() == Expression::Type::Value)
    {
        _out << "callbacks->output(userdata,";

        expression->toPointer(this);

        _out << ",1);" << std::endl;
    }
    else
    {
        // we're going to call the write function
        _out << "callbacks->write(userdata,";

        // convert the expression to a string
        expression->toString(this);

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
    expression->toBoolean(this);

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
    _out << '}' << std::endl;
}

/**
 *  Generate the code to get a pointer to a variable
 *  @param  name                name of the variable
 */
void CCode::varPointer(const std::string &name)
{
    // quote newlines, null characters, etc in the string so that it can
    // be picked up by the compiler
    QuotedString quoted(name);

    // call the callback to get the variable
    _out << "callbacks->variable(userdata,\"" << quoted << "\"," << name.size() << ')';
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

    // quote newlines, null characters, etc in the string so that it can
    // be picked up by the compiler
    QuotedString quoted(name);

    // and append a call to retrieve the member
    _out << ",\"" << quoted << "\"," << name.size() << ')';
}

/**
 *  Generate the code to get a pointer to a variable
 *  @param  parent              parent variable from which the var is retrieved
 *  @param  expression          Expression that evaluates to a var name
 */
void CCode::varPointer(const Variable *parent, const Expression *expression)
{
    if (expression->type() == Expression::Type::Integer)
    {
        // call the member_at() function
        _out << "callbacks->member_at(userdata,";

        // generate a var pointer for the variable
        parent->pointer(this);
        _out << ',';

        // generate the expression as a integer value
        expression->toInteger(this);

        // end the member_at call
        _out << ')';
    }
    else if (expression->type() == Expression::Type::Value)
    {
        // call the member_at_variable() function
        _out << "callbacks->member_at_variable(userdata,";

        // generate var pointer to the array
        parent->pointer(this);
        _out << ",";

        // generate a pointer to the index variable
        expression->toPointer(this);

        // end the member_at_variable call
        _out << ')';

    }
    else
    {
        // call the member() function
        _out << "callbacks->member(userdata,";

        // generate a var pointer for the variable
        parent->pointer(this);

        // and append a call to retrieve the member
        _out << ',';

        // and now we should generate a string value for the expression
        expression->toString(this);

        // end expression
        _out << ')';
    }
}

/**
 *  Create a string literal
 *  @param  value
 */
void CCode::stringValue(const std::string &value)
{
    if (value.empty())
    {
        // If we're empty it is just more efficient to use NULL instead of ""
        _out << "NULL,0";
    }
    else
    {
        // quote newlines, null characters, etc in the string so that it can
        // be picked up by the compiler
        QuotedString quoted(value);

        // output string
        _out << '\"' << quoted << "\"," << value.size();
    }
}

/**
 *  Create a integer literal
 *  @param  value
 */
void CCode::integerValue(integer_t value)
{
    // output number
    _out << value;
}

/**
 *  Create a double literal
 *  @param  value
 */
void CCode::doubleValue(double value)
{
    // output number
    _out.precision(std::numeric_limits<double>::digits10);
    _out << std::fixed << value;
}

/**
 *  Create a string constant for a variable
 *  @param  variable
 */
void CCode::stringVariable(const Variable *variable)
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
    _out << ')';
}

/**
 *  Create a string or integer constant for a variable
 *  @param  variable
 */
void CCode::integerVariable(const Variable *variable)
{
    // call the to_integer method
    _out << "callbacks->to_integer(userdata,";

    // generate pointer to the variable
    variable->pointer(this);

    // that was it
    _out << ')';
}

/**
 *  Create a boolean constant for a variable
 *  @param  variable
 */
void CCode::booleanVariable(const Variable *variable)
{
    // call the to_boolean method
    _out << "callbacks->to_boolean(userdata,";

    // generate pointer to the variable
    variable->pointer(this);

    // that was it
    _out << ')';
}

/**
 *  Create a floating point constant for a variable
 *  @param  variable
 */
void CCode::doubleVariable(const Variable *variable)
{
    // call the to_double method
    _out << "callbacks->to_double(userdata,";

    // generate pointer to the variable
    variable->pointer(this);

    // that was it
    _out << ')';
}

/**
 *  Get a variable
 *  @param variable
 */
void CCode::variable(const Variable* variable)
{
    // call the variable callback
    _out << "callbacks->variable(userdata,";

    // generate pointer to the variable
    variable->pointer(this);

    // that was it
    _out << ')';
}

/**
 *  Move a constant to runtime space
 *  @param  expression
 */
void CCode::pointerString(const Expression *expression) 
{
    // open command
    _out << "callbacks->transfer_string(userdata,";

    // turn the expression into a string
    expression->toString(this);    
    
    // finalize command
    _out << ")";
}

/**
 *  Move a constant to runtime space
 *  @param  expression
 */
void CCode::pointerInteger(const Expression *expression) 
{
    // open command
    _out << "callbacks->transfer_integer(userdata,";

    // turn the expression into an integer
    expression->toInteger(this);    
    
    // finalize command
    _out << ")";
}

/**
 *  Move a constant to runtime space
 *  @param  expression
 */
void CCode::pointerDouble(const Expression *expression) 
{
    // open command
    _out << "callbacks->transfer_double(userdata,";

    // turn the expression into a double
    expression->toDouble(this);    
    
    // finalize command
    _out << ")";
}

/**
 *  Move a constant to runtime space
 *  @param  expression
 */
void CCode::pointerBoolean(const Expression *expression) 
{
    // open command
    _out << "callbacks->transfer_boolean(userdata,";

    // turn the expression into a boolean
    expression->toBoolean(this);    
    
    // finalize command
    _out << ")";
}

/**
 *  Negate the boolean expression
 *  @param  expression
 */
void CCode::negateBoolean(const Expression *expression)
{
    // output a ! to negate the boolean
    _out << "!";

    // then actually start printing the boolean expression
    expression->toBoolean(this);
}

/**
 *  Arithmetic operations
 *  @param  left
 *  @param  right
 */
void CCode::integerPlus(const Expression *left, const Expression *right) 
{
    // open a parenthese
    _out << '(';

    // print the left integer
    left->toInteger(this);

    // print the operator
    _out << '+';

    // print the right integer
    right->toInteger(this);

    // close the parenthese
    _out << ')';
}

/**
 *  Arithmetic operations
 *  @param  left
 *  @param  right
 */
void CCode::doublePlus(const Expression *left, const Expression *right) 
{
    // open a parenthese
    _out << '(';

    // print the left integer
    left->toDouble(this);

    // print the operator
    _out << '+';

    // print the right integer
    right->toDouble(this);

    // close the parenthese
    _out << ')';
}

/**
 *  Arithmetic operations
 *  @param  left
 *  @param  right
 */
void CCode::pointerPlus(const Expression *left, const Expression *right) 
{
    // start the command
    _out << "callbacks->plus(userdata,";

    // add left expression
    left->toPointer(this);

    // comma
    _out << ",";

    // add right expression
    right->toPointer(this);

    // finalize command
    _out << ")";
}

/**
 *  Arithmetic operations
 *  @param  left
 *  @param  right
 */
void CCode::integerMinus(const Expression *left, const Expression *right) 
{
    // open a parenthese
    _out << '(';

    // print the left integer
    left->toInteger(this);

    // print the operator
    _out << '-';

    // print the right integer
    right->toInteger(this);

    // close the parenthese
    _out << ')';
}

/**
 *  Arithmetic operations
 *  @param  left
 *  @param  right
 */
void CCode::doubleMinus(const Expression *left, const Expression *right) 
{
    // open a parenthese
    _out << '(';

    // print the left integer
    left->toDouble(this);

    // print the operator
    _out << '-';

    // print the right integer
    right->toDouble(this);

    // close the parenthese
    _out << ')';
}

/**
 *  Arithmetic operations
 *  @param  left
 *  @param  right
 */
void CCode::pointerMinus(const Expression *left, const Expression *right) 
{
    // start the command
    _out << "callbacks->minus(userdata,";

    // add left expression
    left->toPointer(this);

    // comma
    _out << ",";

    // add right expression
    right->toPointer(this);

    // finalize command
    _out << ")";
}

/**
 *  Arithmetic operations
 *  @param  left
 *  @param  right
 */
void CCode::integerMultiply(const Expression *left, const Expression *right) 
{
    // open a parenthese
    _out << '(';

    // print the left integer
    left->toInteger(this);

    // print the operator
    _out << '*';

    // print the right integer
    right->toInteger(this);

    // close the parenthese
    _out << ')';
}

/**
 *  Arithmetic operations
 *  @param  left
 *  @param  right
 */
void CCode::doubleMultiply(const Expression *left, const Expression *right) 
{
    // open a parenthese
    _out << '(';

    // print the left integer
    left->toDouble(this);

    // print the operator
    _out << '*';

    // print the right integer
    right->toDouble(this);

    // close the parenthese
    _out << ')';
}

/**
 *  Arithmetic operations
 *  @param  left
 *  @param  right
 */
void CCode::pointerMultiply(const Expression *left, const Expression *right) 
{
    // start the command
    _out << "callbacks->multiply(userdata,";

    // add left expression
    left->toPointer(this);

    // comma
    _out << ",";

    // add right expression
    right->toPointer(this);

    // finalize command
    _out << ")";
}

/**
 *  Arithmetic operations
 *  @param  left
 *  @param  right
 */
void CCode::integerDivide(const Expression *left, const Expression *right) 
{    
    // open a parenthese
    _out << '(';

    // print the left integer
    left->toInteger(this);

    // print the operator and start a new block for our zero division check
    _out << "/((";

    // print the right integer
    right->toInteger(this);

    // compare it to 0 using an inline if statement. If this is true we will call throw_exception
    // which will throw a C++ exception out of everything
    _out << ") == 0 ? callbacks->throw_exception(userdata, \"Zero division error\") : (";

    // but if we are false we'll need the original value of course, so we print that expression yet again
    // this seems inefficient, although it probably doesn't mattter as C compiler are 'smart' ;)
    right->toInteger(this);

    // And end the actual blocks for the inline if statement
    _out << ")))";
}

/**
 *  Arithmetic operations
 *  @param  left
 *  @param  right
 */
void CCode::doubleDivide(const Expression *left, const Expression *right) 
{
    // open a parenthese
    _out << '(';

    // print the left integer
    left->toInteger(this);

    // print the operator and start a new block for our zero division check
    _out << "/((";

    // print the right integer
    right->toInteger(this);

    // compare it to 0 using an inline if statement. If this is true we will call throw_exception
    // which will throw a C++ exception out of everything
    _out << ") == 0 ? callbacks->throw_exception(userdata, \"Zero division error\") : (";

    // but if we are false we'll need the original value of course, so we print that expression yet again
    // this seems inefficient, although it probably doesn't mattter as C compiler are 'smart' ;)
    right->toInteger(this);

    // And end the actual blocks for the inline if statement
    _out << ")))";
}

/**
 *  Arithmetic operations
 *  @param  left
 *  @param  right
 */
void CCode::pointerDivide(const Expression *left, const Expression *right) 
{
    // start the command
    _out << "(callbacks->divide(userdata,";

    // add left expression
    left->toPointer(this);

    // comma
    _out << ",";

    // add right expression
    right->toPointer(this);

    // finalize command
    _out << ") == NULL ? callbacks->transfer_integer(userdata, callbacks->throw_exception(userdata, \"Zero division error\")) : " ;

    // start the command
    _out << "callbacks->divide(userdata,";

    // add left expression
    left->toPointer(this);

    // comma
    _out << ",";

    // add right expression
    right->toPointer(this);

    // finalize command
    _out << "))";
}

/**
 *  Arithmetic operations
 *  @param  left
 *  @param  right
 */
void CCode::integerModulo(const Expression *left, const Expression *right) 
{
    // open a parenthese
    _out << '(';

    // print the left integer
    left->toInteger(this);

    // print the operator
    _out << '%';

    // print the right integer
    right->toInteger(this);

    // close the parenthese
    _out << ')';
}

/**
 *  Arithmetic operations
 *  @param  left
 *  @param  right
 */
void CCode::pointerModulo(const Expression *left, const Expression *right) 
{
    // start the command
    _out << "callbacks->modulo(userdata,";

    // add left expression
    left->toPointer(this);

    // comma
    _out << ",";

    // add right expression
    right->toPointer(this);

    // finalize command
    _out << ")";
}


/**
 *  Comparison operators
 *  @param  left
 *  @param  right
 *  @note   Literal comparisons are possible with this, although that shouldn't matter.
 *          We're assuming gcc as the compiler for this after all, which will optimize it out
 *          anyway, even if you compile it with -O0 (aka don't optimize). Only thing it probably
 *          can't optimize away are our strcmp calls, but that's mostly because we have our own
 *          function for that.
 */
void CCode::equals(const Expression *left, const Expression *right)
{
    if (left->type() == Expression::Type::Double || right->type() == Expression::Type::Double)
    {
        left->toDouble(this); _out << "=="; right->toDouble(this);
    }
    else if (left->type() == Expression::Type::Integer || right->type() == Expression::Type::Integer)
    {
        left->toInteger(this); _out << "=="; right->toInteger(this);
    }
    else if (left->type() == Expression::Type::Boolean || right->type() == Expression::Type::Boolean)
    {
        left->toBoolean(this); _out << "=="; right->toBoolean(this);
    }
    else
    {
        _out << "callbacks->strcmp(userdata,"; left->toString(this); _out << ','; right->toString(this); _out << ") == 0";
    }
}

void CCode::notEquals(const Expression *left, const Expression *right)
{
    if (left->type() == Expression::Type::Double || right->type() == Expression::Type::Double)
    {
        left->toDouble(this); _out << "!="; right->toDouble(this);
    }
    else if (left->type() == Expression::Type::Integer || right->type() == Expression::Type::Integer)
    {
        left->toInteger(this); _out << "!="; right->toInteger(this);
    }
    else if (left->type() == Expression::Type::Boolean || right->type() == Expression::Type::Boolean)
    {
        left->toBoolean(this); _out << "!="; right->toBoolean(this);
    }
    else
    {
        _out << "callbacks->strcmp(userdata,"; left->toString(this); _out << ','; right->toString(this); _out << ") != 0";
    }
}

void CCode::greater(const Expression *left, const Expression *right)
{
    // Print as a double if it's a double, print as a regular numer otherwise
    if (left->type() == Expression::Type::Double || left->type() == Expression::Type::Value) left->toDouble(this);
    else left->toInteger(this);

    // Print the actual operator
    _out << '>';

    // Print as a double if it's a double, print as a regular numer otherwise
    if (right->type() == Expression::Type::Double || right->type() == Expression::Type::Value) right->toDouble(this);
    else right->toInteger(this);
}

void CCode::greaterEquals(const Expression *left, const Expression *right)
{
    // Print as a double if it's a double, print as a regular numer otherwise
    if (left->type() == Expression::Type::Double || left->type() == Expression::Type::Value) left->toDouble(this);
    else left->toInteger(this);

    // Print the actual operator
    _out << ">=";

    // Print as a double if it's a double, print as a regular numer otherwise
    if (right->type() == Expression::Type::Double || right->type() == Expression::Type::Value) right->toDouble(this);
    else right->toInteger(this);
}

void CCode::lesser(const Expression *left, const Expression *right)
{
    // Print as a double if it's a double, print as a regular numer otherwise
    if (left->type() == Expression::Type::Double || left->type() == Expression::Type::Value) left->toDouble(this);
    else left->toInteger(this);

    // Print the actual operator
    _out << '<';

    // Print as a double if it's a double, print as a regular numer otherwise
    if (right->type() == Expression::Type::Double || right->type() == Expression::Type::Value) right->toDouble(this);
    else right->toInteger(this);
}

void CCode::lesserEquals(const Expression *left, const Expression *right)
{
    // Print as a double if it's a double, print as a regular numer otherwise
    if (left->type() == Expression::Type::Double || left->type() == Expression::Type::Value) left->toDouble(this);
    else left->toInteger(this);

    // Print the actual operator
    _out << "<=";

    // Print as a double if it's a double, print as a regular numer otherwise
    if (right->type() == Expression::Type::Double || right->type() == Expression::Type::Value) right->toDouble(this);
    else right->toInteger(this);
}

/**
 *  Regular expression parsing
 *  @param  left
 *  @param  right
 */
void CCode::regex(const Expression *left, const Expression *right)
{
    _out << "callbacks->regex(userdata,"; left->toString(this); _out << ','; right->toString(this); _out << ") == 0";
}

/**
 *  Boolean operators
 *  @param  left
 *  @param  right
 */
void CCode::booleanAnd(const Expression *left, const Expression *right) { left->toBoolean(this); _out << "&&"; right->toBoolean(this); }
void CCode::booleanOr(const Expression *left, const Expression *right)  { left->toBoolean(this); _out << "||"; right->toBoolean(this); }

/**
 *  Generate the code to apply a set of modifiers on an expression
 *  @param  modifiers          The set of modifiers to apply
 *  @param  expression         The expression to apply to modifiers on
 */
void CCode::modifiers(const Modifiers *modifiers, const Variable *variable)
{
    // get some iterators
    const auto begin = modifiers->begin();
    const auto end = modifiers->end();
    const auto last = --(modifiers->end());

    // write out all the modify_variable calls first
    for (std::size_t i = 0; i < modifiers->size(); ++i) _out << "callbacks->modify_variable(userdata,";

    // then write the pointer to the variable
    variable->pointer(this);
    _out << ',';

    // finish writing the actual statements by retrieving all the actual modifiers
    for (auto iter = begin; iter != end; ++iter)
    {
        const auto &modifier = *iter;
        _out << "callbacks->modifier(userdata,";
        stringValue(modifier->token());
        _out << "),";

        const Parameters *params = modifier->parameters();

        // in case we have no parameters we can simply write NULL here
        if (!params) _out << "NULL";
        // otherwise we generate the parameters inline
        else params->generate(this);

        _out << ')';

        // all of them need this comma, except for the last one
        if (iter != last) _out << ',';
    }
}

/**
 *  Generate the code to apply a set of modifiers on an expression and turn it into a string
 *  @param  modifiers          The set of modifiers to apply
 *  @param  variable           The variable to apply to modifers to
 */
void CCode::modifiersString(const Modifiers *modifiers, const Variable *variable)
{
    // write out the to_string function
    _out << "callbacks->to_string(userdata,";

    // write the modifiers, which return a variable pointer
    this->modifiers(modifiers, variable);

    // close the function
    _out << ')';
}

/**
 *  Generate the code to apply a set of modifiers on an expression and turn it into a boolean
 *  @param  modifiers          The set of modifiers to apply
 *  @param  variable           The variable to apply to modifers to
 */
void CCode::modifiersBoolean(const Modifiers *modifiers, const Variable *variable)
{
    // write out the to_boolean function
    _out << "callbacks->to_boolean(userdata,";

    // write the modifiers, which return a variable pointer
    this->modifiers(modifiers, variable);

    // close the function
    _out << ')';
}

/**
 *  Generate the code to apply a set of modifiers on an expression and turn it into a double
 *  @param  modifiers          The set of modifiers to apply
 *  @param  variable           The variable to apply the modifiers to
 */
void CCode::modifiersDouble(const Modifiers *modifiers, const Variable *variable)
{
    // write the to_double function
    _out << "callbacks->to_double(userdata,";

    // write out the modifiers as the variable pointer
    this->modifiers(modifiers, variable);

    // close the function
    _out << ')';
}

/**
 *  Generate the code to construct the following parameters
 *  @param  parameters         The parameters to construct
 *  @note Construct as in, generate the code so the runtime can construct them
 */
void CCode::parameters(const Parameters *parameters)
{
    // write out all the param_append function names at least, as you can see
    // we are doing this is reverse order. This is simply done so at runtime the
    // push_back methods are actually called in the correct order
    for (auto iter = parameters->rbegin(); iter != parameters->rend(); ++iter)
    {
        const auto &param = *iter;

        switch (param->type()) {
        case Expression::Type::Boolean:
            _out << "callbacks->params_append_boolean(userdata,";
            break;
        case Expression::Type::Integer:
            _out << "callbacks->params_append_integer(userdata,";
            break;
        case Expression::Type::String:
            _out << "callbacks->params_append_string(userdata,";
            break;
        case Expression::Type::Double:
            _out << "callbacks->params_append_double(userdata,";
            break;
        default:
            throw CompileError("Unknown typed values are currently unsupported");
        }
    }

    // in the middle we create the parameters object
    _out << "callbacks->create_params(userdata," << parameters->size() << ")";

    // and add the actual parameters, as you can see here we are not going in
    // reverse order, we are simply executing from the inside to the outside and all
    for (auto iter = parameters->begin(); iter != parameters->end(); ++iter)
    {
        const auto &param = *iter;

        _out << ',';
        switch (param->type()) {
        case Expression::Type::Boolean:
            param->toBoolean(this);
            break;
        case Expression::Type::Integer:
            param->toInteger(this);
            break;
        case Expression::Type::String:
            param->toString(this);
            break;
        case Expression::Type::Double:
            param->toDouble(this);
            break;
        default:
            // should not be reachable as we probably already threw at this point
            throw CompileError("Unknown typed values are currently unsupported");
        }
        _out << ')';
    }
}

/**
 *  Generate the code to do a foreach loop over variable
 *  @param variable         The variable object to iterate over
 *  @param key              The magic variable name for the keys
 *  @param value            The magic variable name for the values
 *  @param statements       The statements to execute on each iteration
 *  @param else_statements  The statements to execute if there was nothing to loop through
 */
void CCode::foreach(const Variable *variable, const std::string &key, const std::string &value, const Statements *statements, const Statements *else_statements)
{
    // foreach loops are implemented inside a seperate block to create
    // a local variable scope
    _out << '{' << std::endl;

    // create the code to create the iterator
    _out << "void *iterator = callbacks->create_iterator(userdata,";

    // pointer to the variable
    variable->pointer(this); _out << ");" << std::endl;

    // In case we have else statements write the code to execute them if needed
    if (else_statements)
    {
        // Check if our iterator is invalid (no data) before the actual loop
        _out << "if (!callbacks->valid_iterator(userdata,iterator)) {" << std::endl;

        // If it indeed is invalid execute the else statements
        else_statements->generate(this);

        // Turns out it was valid, guess we'll just loop then
        _out << "} else {" << std::endl;
    }

    // construct the loop
    _out << "while (callbacks->valid_iterator(userdata,iterator)) {" << std::endl;

    // assign the key and value
    if (!key.empty()) { _out << "callbacks->assign(userdata,"; stringValue(key); _out << ",callbacks->iterator_key(userdata,iterator));" << std::endl; }
    if (!value.empty()) { _out << "callbacks->assign(userdata,"; stringValue(value); _out << ",callbacks->iterator_value(userdata,iterator));" << std::endl; }

    // generate the actual statements
    statements->generate(this);

    // proceed the iterator
    _out << "callbacks->iterator_next(userdata,iterator);" << std::endl;

    // end of the while loop
    _out << '}' << std::endl;

    // End our else block if we have an else block that is
    if (else_statements) _out << '}' << std::endl;

    // end of the block
    _out << '}' << std::endl;
}

/**
 *  Generate the code to assign the output of an expression to a key
 *  @param key                  The key to assign the output to
 *  @param expression           The expression to evaluate
 */
void CCode::assign(const std::string &key, const Expression *expression)
{
    switch (expression->type()) {
    case Expression::Type::Integer:
        // Convert to a integer type and use the assign_integer callback
        _out << "callbacks->assign_integer(userdata,";
        stringValue(key); _out << ',';
        expression->toInteger(this);
        break;
    case Expression::Type::String:
        // Convert to a string and use the assign_string callback
        _out << "callbacks->assign_string(userdata,";
        stringValue(key); _out << ',';
        expression->toString(this);
        break;
    case Expression::Type::Boolean:
        // Convert to a boolean and use the assign_boolean callback
        _out << "callbacks->assign_boolean(userdata,";
        stringValue(key); _out << ',';
        expression->toBoolean(this);
        break;
    case Expression::Type::Value: {
        // If we are a value just convert it to a pointer and pass that to the assign callback
        _out << "callbacks->assign(userdata,";
        stringValue(key); _out << ',';
        expression->toPointer(this);
        break;
    }
    case Expression::Type::Double:
        // Convert to a floating point value and use the assign_double callback
        _out << "callbacks->assign_double(userdata,";
        stringValue(key); _out << ',';
        expression->toDouble(this);
        break;
    }
    // Finish this statement
    _out << ");" << std::endl;
}

/**
 *  End of namespace
 */
}}
