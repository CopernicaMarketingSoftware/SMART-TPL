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
    _out << "}" << std::endl;

    // Write a second function that returns what mode we are in
    _out << "const char *mode = ";

    // Quote the string from mode() just in case
    QuotedString quoted(tree.mode());

    // And write the string from mode() after the const char *mode declaration
    _out << "\"" << quoted << "\";" << std::endl;
}

CCode::CCode(const Source& source)
: CCode(SyntaxTree(source.data(), source.size()))
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
    // Start a new block
    _out << "{" << std::endl;

    // Let's first of all declare our output variable
    _out << "const void *o = NULL;" << std::endl;

    // call the string method on our filter, which writes all the filtering code for us
    filter->string(this);

    // Now let's actually call the output callback
    _out << "callbacks->output(userdata,o,";

    // Let's write the escape flag
    _out << (filter->escape() ? 1 : 0);

    // And end the output statement
    _out << ");" << std::endl;

    // End our block
    _out << "}" << std::endl;
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
    if (left->type() == Expression::Type::Numeric || right->type() == Expression::Type::Numeric)
    {
        left->numeric(this); _out << "=="; right->numeric(this);
    }
    else if (left->type() == Expression::Type::Boolean || right->type() == Expression::Type::Boolean)
    {
        left->boolean(this); _out << "=="; right->boolean(this);
    }
    else
    {
        _out << "callbacks->strcmp(userdata,"; left->string(this); _out << ","; right->string(this); _out << ") == 0";
    }
}

void CCode::notEquals(const Expression *left, const Expression *right)
{
    if (left->type() == Expression::Type::Numeric || right->type() == Expression::Type::Numeric)
    {
        left->numeric(this); _out << "!="; right->numeric(this);
    }
    else if (left->type() == Expression::Type::Boolean || right->type() == Expression::Type::Boolean)
    {
        left->boolean(this); _out << "!="; right->boolean(this);
    }
    else
    {
        _out << "callbacks->strcmp(userdata,"; left->string(this); _out << ","; right->string(this); _out << ") != 0";
    }
}
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
        for (auto iter = modifiers->begin(); iter != modifiers->end(); ++iter)
        {
            // Retrieve the parameters
            const Parameters *params = (*iter)->parameters();
            // Start our own private block if we have parameters
            if (params)
            {
                _out << "{" << std::endl;

                // Generate the parameters
                params->generate(this);
            }

            // Call the modify_variable callback
            _out << "o = callbacks->modify_variable(userdata,";
            if (iter == modifiers->begin())
            {
                variable->pointer(this);
                _out << ",";
            }
            else
            {
                _out << "o,";
            }

            // Write the get modifier callback
            _out << "callbacks->modifier(userdata,";
            string((*iter)->token());
            _out << "),";

            // If there are parameters write our local variable here, NULL otherwise
            if (params) _out << "p";
            else _out << "NULL";
            _out << ");" << std::endl;

            if (params)
            {
                // Deconstruct our parameters
                _out << "callbacks->delete_params(userdata,p);" << std::endl;

                // End our private block
                _out << "}" << std::endl;
            }
        }
    }
}

/**
 *  Generate the code to construct the following parameters
 *  @param  parameters         The parameters to construct
 *  @note Construct as in, generate the code so the runtime can construct them
 */
void CCode::parameters(const Parameters *parameters)
{
    _out << "void *p = callbacks->create_params(userdata);" << std::endl;
    for (auto &param : *parameters)
    {
        switch (param->type()) {
        case Expression::Type::Boolean:
            // This expression in the parameters is a boolean value, so we use params_append_boolean
            _out << "callbacks->params_append_boolean(userdata,p,";
            param->boolean(this);
            _out << ");";
            break;
        case Expression::Type::Numeric:
            // This expression in the parameters is a numeric value, so we use params_append_numeric
            _out << "callbacks->params_append_numeric(userdata,p,";
            param->numeric(this);
            _out << ");";
            break;
        case Expression::Type::String:
            // This expression in the parameters is a string value, so we use params_append_string
            _out << "callbacks->params_append_string(userdata,p,";
            param->string(this);
            _out << ");";
            break;
        default:
            throw std::runtime_error("Unsupported operation for now");
        }
        _out << std::endl;
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
    _out << "{" << std::endl;

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
    if (!key.empty()) { _out << "callbacks->assign(userdata,"; string(key); _out << ",callbacks->iterator_key(userdata,iterator));" << std::endl; }
    if (!value.empty()) { _out << "callbacks->assign(userdata,"; string(value); _out << ",callbacks->iterator_value(userdata,iterator));" << std::endl; }

    // generate the actual statements
    statements->generate(this);

    // proceed the iterator
    _out << "callbacks->iterator_next(userdata,iterator);" << std::endl;

    // end of the while loop
    _out << "}" << std::endl;

    // End our else block if we have an else block that is
    if (else_statements) _out << "}" << std::endl;

    // clean up the iterator
    _out << "callbacks->delete_iterator(userdata,iterator);" << std::endl;

    // end of the block
    _out << "}" << std::endl;

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
        string(key); _out << ",";
        expression->numeric(this);
        break;
    case Expression::Type::String:
        // Convert to a string and use the assign_string callback
        _out << "callbacks->assign_string(userdata,";
        string(key); _out << ",";
        expression->string(this);
        break;
    case Expression::Type::Boolean:
        // Convert to a boolean and use the assign_boolean callback
        _out << "callbacks->assign_boolean(userdata,";
        string(key); _out << ",";
        expression->boolean(this);
        break;
    case Expression::Type::Value: {
        const Variable *variable = dynamic_cast<const Variable*>(expression);
        if (variable)
        {
            // If we are a variable just convert it to a pointer and pass that to the assign callback
            _out << "callbacks->assign(userdata,";
            string(key); _out << ",";
            variable->pointer(this);
            break;
        }
        throw std::runtime_error("Unsupported assign.");
    }
    }
    // Finish this statement
    _out << ");" << std::endl;
}

/**
 *  End of namespace
 */
}}
