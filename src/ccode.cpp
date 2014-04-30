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
    _out << ");" << std::endl;
}

/**
 *  Generate the code to output the output of a filter
 *  @param  filter             The filter to eventually output
 */
void CCode::output(const Filter *filter)
{
    // We're going to call the output callback function
    _out << "callbacks->output(userdata,";

    // call the string method on our filter, which writes all the filtering code for us
    filter->string(this);

    // and let's properly end the C statement
    _out << ");" << std::endl;
}

/**
 *  Generate the code to write an expression as a string
 *  @param  expression          the expression to write as a string
 */
void CCode::write(const Expression *expression)
{
    // we're going to call the write function
    _out << "callbacks->write(userdata,";

    // convert the expression to a string
    expression->string(this);

    // end of the function
    _out << ");" << std::endl;
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
    if (expression->type() == Expression::Type::Numeric)
    {
        // call the member_at() function
        _out << "callbacks->member_at(userdata,";

        // generate a var pointer for the variable
        parent->pointer(this);
        _out << ",";

        // generate the expression as a numeric value
        expression->numeric(this);

        // end the member_at call
        _out << ")";
    }
    else
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
}

/**
 *  Create a string literal
 *  @param  value
 */
void CCode::string(const std::string &value)
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
        _out << "\"" << quoted << "\"," << value.size();
    }
}

/**
 *  Create a numeric literal
 *  @param  value
 */
void CCode::numeric(numeric_t value)
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
 *  @todo Maybe don't actually compile in the comparison if it's a comparison between literals
 *        it seems kind of pointless to evaluate something like (true == true) everytime.
 */
void CCode::equals(const Expression *left, const Expression *right)
{
    if (left->type() == Expression::Type::Numeric && right->type() == Expression::Type::Numeric)
    {
        left->numeric(this); _out << "=="; right->numeric(this);
    }
    else if (left->type() == Expression::Type::String && right->type() == Expression::Type::String)
    {
        _out << "callbacks->strcmp(userdata,"; left->string(this); _out << ","; right->string(this); _out << ")";
    }
    else if (left->type() == Expression::Type::Boolean && right->type() == Expression::Type::Boolean)
    {
        left->boolean(this); _out << "=="; right->boolean(this);
    }
    else
    {
        throw std::runtime_error("Comparison between different types is currently not supported.");
    }
}
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
 *  Apply one modifier to the expression
 *  @param  expression
 *  @param  modifier
 *  @todo Actually implement it using the ideas described in the comments here
 */
/*void CCode::modifier(const Expression *expression, const Modifier *modifier)
{
    // check the expression type, because we are going to call a different
    // apply_to_*** function depending on the expression type
    switch (expression->type()) {
        case Type::Numeric:
            // call the apply_to_numeric function
            _out << "callbacks->apply_to_numeric(userdata,";

            // convert the expression into a literal numeric value
            expression->numeric(this);

            // fetch the modifier
            _out << "callbacks->modifier(" << modifier->name() << "," << modifier->size() << ")";
            break;

}*/


/**
 *  Generate the code to apply a set of modifiers on an expression
 *  @param  modifiers          The set of modifiers to apply
 *  @param  expression         The expression to apply to modifiers on
 */
void CCode::modifiers(const Modifiers* modifiers, const Expression *expression)
{
    // @todo This call currently only supports Expressions of the type Variable
    const Variable* variable = dynamic_cast<const Variable*>(expression);
    if (variable)
    {
        for (auto &modifier : *modifiers)
        {
            _out << "callbacks->modify_variable(userdata,callbacks->modifier(userdata,";
            string(modifier.get()->token());
            _out << "),";
        }
        variable->pointer(this);
        for (auto &modifier : *modifiers)
        {
            (void) modifier; // Yeah yeah compiler I get it, I'm not using modifier..
            _out << ")";
        }
    }
}

/**
 *  Generate the code to do a foreach loop over variable
 *  @param key                The magic variable name that should be used
 *  @param variable           The variable object to iterate over
 *  @param statements         The statements to execute on each iteration
 *  @param keyvar             The magic variable name that should contain the key, ignore if it is empty
 */
void CCode::foreach(const std::string& key, const Variable *variable, const Statements *statements, const std::string &keyvar)
{
    // Instruct our callbacks that we want to start a new loop
    _out << "callbacks->loop_start(userdata);" << std::endl;

    // Start the actual loop
    _out << "while (callbacks->member_iter(userdata,";

    // write out a pointer to the variable we're iterating over
    variable->pointer(this); _out << ",";

    // write the magic key
    string(key); _out << ",";

    // write the magic key for the key
    string(keyvar); _out << ")) {" << std::endl;

    // generate the actual statements
    statements->generate(this);

    // end the while loop
    _out << "}" << std::endl;

    // Instruct our callbacks that we're done looping
    _out << "callbacks->loop_stop(userdata);" << std::endl;
}

/**
 *  Generate the code to assign the output of an expression to a key
 *  @param key                  The key to assign the output to
 *  @param expression           The expression to evaluate
 */
void CCode::assign(const std::string &key, const Expression *expression)
{
    switch (expression->type()) {
    case Expression::Type::Numeric:
        // Convert to a numeric type and use the assign_numeric callback
        _out << "callbacks->assign_numeric(userdata,";
        expression->numeric(this);
        break;
    case Expression::Type::String:
        // Convert to a string and use the assign_string callback
        _out << "callbacks->assign_string(userdata,";
        expression->string(this);
        break;
    case Expression::Type::Boolean:
        // Convert to a boolean and use the assign_boolean callback
        _out << "callbacks->assign_boolean(userdata,";
        expression->boolean(this);
        break;
    case Expression::Type::Value: {
        const Variable *variable = dynamic_cast<const Variable*>(expression);
        if (variable)
        {
            // If we are a variable just convert it to a pointer and pass that to the assign callback
            _out << "callbacks->assign(userdata,";
            variable->pointer(this);
            break;
        }
        throw std::runtime_error("Unsupported assign.");
    }
    }
    _out << ",";

    // write the key we want to assign our value to
    string(key); _out << ");" << std::endl;
}

/**
 *  End of namespace
 */
}

