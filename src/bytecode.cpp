/**
 *  Bytecode.cpp
 *
 *  Implementation file of the LLVM code generator.
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
 *  @param  source       The source that holds the template
 *  @throws CompileError If something went wrong while compiling the jit code
 */
Bytecode::Bytecode(const Source& source) : 
    _tree(source.version(), source.data(), source.size()),
    _function_signature(jit_function::signature_helper(jit_type_void, jit_type_void_ptr, jit_function::end_params)),
    _function(_context, _function_signature),
    _callbacks(&_function),
    _userdata(_function.get_param(0)),
    _true(_function.new_constant(1)),
    _false(_function.new_constant(0)),
    _division_by_zero(_function, "Division by zero"),
    _invalid_regex(_function, "Invalid regular expression")
{
    // set our jit_exception_handler as the exception handler for jit
    auto original_handler = jit_exception_set_handler(JitException::handler);

    // start building the function
    _context.build_start();

    try
    {
        // generate the libjit code
        _tree.generate(this);

        // in case we reach this point correctly just return from our function cleanly
        _function.insn_return();

        // generate the error labels, by adding the error handlers we create 
        // the following code inside the function:
        //
        //  instruction;
        //  instruction;
        //  return;
        //  division_by_zero:
        //  instruction;
        //  return;
        //  invalid_regex:
        //  instruction;
        //  return;
        //
        // if the function runs correctly, only the normal instructions are executed
        // and then the "return" is encountered and the function exits normally. If an
        // error occurs, the code can jump to one of the error labels, and execute that
        add(_division_by_zero);
        add(_invalid_regex);

        // compile the function
        _function.compile();
    }
    catch (const std::runtime_error &error)
    {
        // we caught a compile error while generating/compiling, cleanup libjit
        _context.build_end();

        // Set the jit_exception_handler back to the original handler
        jit_exception_set_handler(original_handler);

        // rethrow
        throw;
    }

    // done building
    _context.build_end();

    // get the closure, but only if libjit supports closures and it isn't in interpreter mode
    // in interpreter mode closures tend to just segfault while running
    if (jit_supports_closures() && !jit_uses_interpreter()) _closure = (ShowTemplate *)_function.closure();

    // Set the jit_exception_handler back to the original handler
    jit_exception_set_handler(original_handler);
}

/**
 *  Destructor
 */
Bytecode::~Bytecode()
{
    // if there is a signature, we need to free it
    if (_function_signature) jit_type_free(_function_signature);
}

/**
 *  Method to initialize an error label
 *  @param  label
 */
void Bytecode::add(ErrorLabel &label)
{
    // add the label
    _function.insn_label(label.label());
    
    // we need a constant of the message
    jit_value buffer = _function.new_constant((void *)label.message(), jit_type_void_ptr);

    // call the mark_failed function
    _callbacks.mark_failed(_userdata, buffer);

    // completely return out of the function (this is an fatal error code)
    _function.insn_return();
}

/**
 *  Helper method to pop a value from the stack
 *  @return jit_value
 *  @throws RunTimeError if the internal stack is empty
 */
jit_value Bytecode::pop()
{
    // let's check if the stack is empty and throw an error if it is instead of crashing
    // this should never ever happen, unless working on the library itself.
    if (_stack.empty()) throw RunTimeError("Internal stack is empty");

    // get the value from the stack
    jit_value& value = _stack.top();

    // remove the value from the stack
    _stack.pop();

    // done
    return value;
}

/**
 *  Generate code to output raw data
 *  @param  data                data to output
 */
void Bytecode::raw(const std::string &data)
{
    // we need a constant of the buffer, and the buffer size
    jit_value buffer = _function.new_constant((void *)data.data(), jit_type_void_ptr);
    jit_value size = _function.new_constant(data.size(), jit_type_sys_ulonglong);

    // call the write function
    _callbacks.write(_userdata, buffer, size);
}

/**
 *  Construct a pointer to a variable
 *  @param  variable
 *  @return jit_value
 */
jit_value Bytecode::pointer(const Variable *variable)
{
    // we first have to create a pointer to the variable on the stack
    variable->pointer(this);

    // return it from the stack
    return pop();
}

/**
 *  Retrieve the integer representation of an expression
 *  @param  expression
 *  @return jit_value
 */
jit_value Bytecode::integerExpression(const Expression *expression)
{
    // create on the stack
    expression->toInteger(this);

    // remove it from the stack
    return pop();
}

/**
 *  Retrieve the boolean representation (1 or 0) of an expression
 *  @param  expression
 *  @return jit_value
 */
jit_value Bytecode::booleanExpression(const Expression *expression)
{
    // create on the stack
    expression->toBoolean(this);

    // remove from the stack
    return pop();
}

/**
 *  Retrieve the floating point representation of an expression
 *  @param  expression
 *  @return jit_value
 */
jit_value Bytecode::doubleExpression(const Expression *expression)
{
    // create on the stack
    expression->toDouble(this);

    // remove from the stack
    return pop();
}

/**
 *  Retrieve the pointer to the variable that holds the result of an expression
 * 	@param	expression
 * 	@return jit_value
 */
jit_value Bytecode::pointerExpression(const Expression *expression)
{
    // create on the stack
    expression->toPointer(this);

    // remove from the stack
    return pop();
}

/**
 *  Generate the code to output a variable
 *  @param  variable           The variable to output
 */
void Bytecode::output(const Variable *variable)
{
    // output the variable using the output callback, we of course use pointer(Variable*) here
    _callbacks.output(_userdata, pointer(variable), _true);
}

/**
 *  Generate the code to output the output of a filter
 *  @param  filter             The filter to eventually output
 */
void Bytecode::output(const Filter *filter)
{
    // Call the pointer method on the filter, so that a pointer to the filtered variable will be added to the stack
    filter->pointer(this);

    // Pop the value that modifiers() left us
    auto var = pop();

    // output this value
    _callbacks.output(_userdata, var, filter->escape() ? _true : _false);
}

/**
 *  Generate the code to write an expression as a string
 *  @param  expression          the expression to write as a string
 */
void Bytecode::write(const Expression *expression)
{
    // check the type
    switch (expression->type()) {
    case Expression::Type::Integer:
        // generate the code that pushes the nummeric value to the stack, and output that
        _callbacks.output_integer(_userdata, integerExpression(expression));
        break;
    
    case Expression::Type::Boolean:
        // generate the code that pushes a boolean value to the stack, and output that
        _callbacks.output_boolean(_userdata, booleanExpression(expression));
        break;

    case Expression::Type::Double:
        // generate the code that pushes a boolean value to the stack, and output that
        _callbacks.output_double(_userdata, doubleExpression(expression));
        break;

    case Expression::Type::Value:
        // generate the code that pushes a value pointer to the stack, and output that
        _callbacks.output(_userdata, pointerExpression(expression), _true); // @todo escape?
        break;
    
    default:
        // convert the expression to a string (this pushes two values on the stack)
        expression->toString(this);

        // pop the buffer and size from the stack (in reverse order)
        auto size = pop();
        auto buffer = pop();

        // call the write function
        _callbacks.write(_userdata, buffer, size);
        break;
    }
}

/**
 *  Generate a conditional statement
 *  @param  expression          the expression to evaluate
 *  @param  ifstatements        the statements in the 'if' part
 *  @param  elsestatements      the statements in the 'else' part
 */
void Bytecode::condition(const Expression *expression, const Statements *ifstatements, const Statements *elsestatements)
{
    // In case we have an else statement we generate slightly different jit code
    if (elsestatements)
    {
        // we need a label for the 'else' part that we're going to create, and for the
        // part after the entire condition
        jit_label elselabel = _function.new_label();
        jit_label endlabel = _function.new_label();

        // branche to the label if the expression is not valid
        _function.insn_branch_if_not(booleanExpression(expression), elselabel);

        // now we should create the if statements
        ifstatements->generate(this);

        // branche to the end-position
        _function.insn_branch(endlabel);

        // the else label starts here
        _function.insn_label(elselabel);

        // generate the else instructions
        elsestatements->generate(this);

        // the end-label starts here
        _function.insn_label(endlabel);
    }
    else
    {
        // as we don't have an else statement here we just need one label to possibly jump
        // over the if statements if the expression is false
        jit_label endlabel = _function.new_label();

        // branche to the label if the expression is not valid
        _function.insn_branch_if_not(booleanExpression(expression), endlabel);

        // now we should create the if statements
        ifstatements->generate(this);

        // the end-label starts here
        _function.insn_label(endlabel);
    }
}

/**
 *  Generate the code to get a pointer to a variable, given a index by name
 *  @param  parent              parent variable from which the var is retrieved
 *  @param  name                name of the variable
 *  @note   +1 on the stack
 */
void Bytecode::varPointer(const Variable *parent, const std::string &name)
{
    // we need a constant of the name, and the name size
    jit_value namevalue = _function.new_constant((void *)name.data(), jit_type_void_ptr);
    jit_value namesize = _function.new_constant(name.size(), jit_type_sys_ulonglong);

    // call the native function to retrieve the member of a variable, and store the pointer
    // to the variable on the stack
    _stack.push(_callbacks.member(_userdata, pointer(parent), namevalue, namesize));
}

/**
 *  Generate the code to get a pointer to a variable, given by an expression
 *  @param  parent              parent variable from which the var is retrieved
 *  @param  expression          Expression that evaluates to a var name
 *  @note   +1 on the stack
 */
void Bytecode::varPointer(const Variable *parent, const Expression *expression)
{
    // If the expression if an integer, it's easy to get the member at that position
    if (expression->type() == Expression::Type::Integer)
    {
        // call the native function to retrieve the member of the variable and
        // push the variable to the stack
        _stack.push(_callbacks.member_at(_userdata, pointer(parent), integerExpression(expression)));
    }

    // If the expression is of unknown / variable type, we have to determine at
    // runtime what implementation to call
    else if (expression->type() == Expression::Type::Value)
    {
        // Get variable pointer
        expression->toPointer(this);

        // Get the pointer
        auto variable = pop();

        // Get the variable from runtime space
        _stack.push(_callbacks.member_at_value(_userdata, pointer(parent), variable));
    }

    // Otherwise, treat the expression as a string (which it might be, actually)
    else
    {
        // convert the expression to a string (this pushes two values on the stack)
        expression->toString(this);

        // pop the buffer and size from the stack (in reverse order)
        auto size = pop();
        auto buffer = pop();

        // call the native function to retrieve the member of a variable, and store the pointer
        // to the variable on the stack
        _stack.push(_callbacks.member(_userdata, pointer(parent), buffer, size));
    }
}

/**
 *  Generate the code to get a pointer to a variable given a literal name
 *  @param  name                name of the variable
 *  @note   +1 on the stack
 */
void Bytecode::varPointer(const std::string &name)
{
    // we need a constant of the name, and the name size
    jit_value namevalue = _function.new_constant((void *)name.data(), jit_type_void_ptr);
    jit_value namesize = _function.new_constant(name.size(), jit_type_sys_ulonglong);

    // push the variable on the stack
    _stack.push(_callbacks.variable(_userdata, namevalue, namesize));
}

/**
 *  Create a string literal
 *  @param  value
 *  @note   +2 on the stack
 */
void Bytecode::stringValue(const std::string &value)
{
    // push buffer and size
    _stack.push(_function.new_constant((void *)value.data(), jit_type_void_ptr));
    _stack.push(_function.new_constant(value.size(), jit_type_sys_ulonglong));
}

/**
 *  Create a integer literal
 *  @param  value
 *  @note   +1 on the stack
 */
void Bytecode::integerValue(integer_t value)
{
    // push value
    _stack.push(_function.new_constant(value, jit_type_sys_longlong));
}

/**
 *  Create a double literal
 *  @param  value
 *  @note   +1 on the stack
 */
void Bytecode::doubleValue(double value)
{
    // push value
    _stack.push(_function.new_constant(value, jit_type_float64));
}

/**
 *  Create a string or integer constant for a variable
 *  @param  variable
 *  @note   +2 on the stack
 */
void Bytecode::stringVariable(const Variable *variable)
{
    // first we need a pointer to the variable
    jit_value var = pointer(variable);

    // call the functions to retrieve the string value
    _stack.push(_callbacks.to_string(_userdata, var));
    _stack.push(_callbacks.size(_userdata, var));
}

/**
 *  Create a string or integer constant for a variable
 *  @param  variable
 *  @note   +1 on the stack
 */
void Bytecode::integerVariable(const Variable *variable)
{
    // call the function to convert a variable to a pointer address
    _stack.push(_callbacks.to_integer(_userdata, pointer(variable)));
}

/**
 *  Create a boolean constant for a variable
 *  @param  variable
 *  @note   +1 on the stack
 */
void Bytecode::booleanVariable(const Variable *variable)
{
    // call the function to convert a variable to a integer value
    _stack.push(_callbacks.to_boolean(_userdata, pointer(variable)));
}

/**
 *  Create a floating point constant for a variable
 *  @param  variable
 *  @note   +1 on the stack
 */
void Bytecode::doubleVariable(const Variable *variable)
{
    // call the function to convert a variable to a floating point value
    _stack.push(_callbacks.to_double(_userdata, pointer(variable)));
}

void Bytecode::variable(const Variable* variable)
{
    stringVariable(variable);
}

/**
 *  Move an expression to the runtime space
 *  @param  expression
 */
void Bytecode::pointerString(const Expression *expression) 
{
    // get the string representation of the expression 
    expression->toString(this);

    // get the size and buffer from the stack
    jit_value size = pop();
    jit_value buffer = pop();

    // add to runtime space and push the pointer
    _stack.push(_callbacks.transfer_string(_userdata, buffer, size));
}

/**
 *  Move an expression to the runtime space
 *  @param  expression
 */
void Bytecode::pointerInteger(const Expression *expression) 
{
    // turn the expression into a integer
    expression->toInteger(this);

    // pop the result and add its generated pointer to the stack
    _stack.push(_callbacks.transfer_integer(_userdata, pop()));
}

/**
 *  Move an expression to the runtime space
 *  @param  expression
 */
void Bytecode::pointerDouble(const Expression *expression) 
{
    // turn the expression into a boolean
    expression->toDouble(this);

    // pop the result and add its generated pointer to the stack
    _stack.push(_callbacks.transfer_double(_userdata, pop()));
}

/**
 *  Move an expression to the runtime space
 *  @param  expression
 */
void Bytecode::pointerBoolean(const Expression *expression) 
{
    // turn the expression into a boolean
    expression->toBoolean(this);

    // pop the result and add its generated pointer to the stack
    _stack.push(_callbacks.transfer_boolean(_userdata, pop()));
}

/**
 *  Negate the boolean expression
 *  @param  expression
 *  @note   +1 on the stack
 */
void Bytecode::negateBoolean(const Expression *expression)
{
    // turn the expression into a boolean
    expression->toBoolean(this);

    // pop the result, negate it and push it back to the stack
    _stack.push(_function.insn_to_not_bool(pop()));
}

/**
 *  Arithmetric operation that turns a plus operation into an integer
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::integerPlus(const Expression *left, const Expression *right)
{
    // calculate left and right values
    jit_value l = integerExpression(left);
    jit_value r = integerExpression(right);

    // calculate them, and push to stack
    _stack.emplace(l + r);
}

/**
 *  Arithmetric operation that turns a plus operation into an double
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::doublePlus(const Expression *left, const Expression *right)
{
    // calculate left and right values
    jit_value l = doubleExpression(left);
    jit_value r = doubleExpression(right);

    // calculate them, and push to stack
    _stack.emplace(l + r);
}

/**
 *  Arithmetric operation that turns a plus operation into an pointer to a variable
 * 	This is useful if the types of the operands are not yet known at compile-time
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::pointerPlus(const Expression *left, const Expression *right)
{
    // calculate left and right values
    jit_value l = pointerExpression(left);
    jit_value r = pointerExpression(right);

    // calculate them, and push to stack
    _stack.push(_callbacks.plus(_userdata, l, r));
}

/**
 *  Arithmetric operation that turns a minus operation into an integer
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::integerMinus(const Expression *left, const Expression *right)
{
    // calculate left and right values
    jit_value l = integerExpression(left);
    jit_value r = integerExpression(right);

    // calculate them, and push to stack
    _stack.emplace(l - r);
}

/**
 *  Arithmetric operation that turns a minus operation into an double
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::doubleMinus(const Expression *left, const Expression *right)
{
    // calculate left and right values
    jit_value l = doubleExpression(left);
    jit_value r = doubleExpression(right);

    // calculate them, and push to stack
    _stack.emplace(l - r);
}

/**
 *  Arithmetric operation that turns a minus operation into an pointer to a variable
 * 	This is useful if the types of the operands are not yet known at compile-time
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::pointerMinus(const Expression *left, const Expression *right)
{
    // calculate left and right values
    jit_value l = pointerExpression(left);
    jit_value r = pointerExpression(right);

    // calculate them, and push to stack
    _stack.push(_callbacks.minus(_userdata, l, r));
}

/**
 *  Arithmetric operation that turns a multiply operation into an integer
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::integerMultiply(const Expression *left, const Expression *right)
{
    // calculate left and right values
    jit_value l = integerExpression(left);
    jit_value r = integerExpression(right);

    // calculate them, and push to stack
    _stack.emplace(l * r);
}

/**
 *  Arithmetric operation that turns a multiply operation into an double
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::doubleMultiply(const Expression *left, const Expression *right)
{
    // calculate left and right values
    jit_value l = doubleExpression(left);
    jit_value r = doubleExpression(right);

    // calculate them, and push to stack
    _stack.emplace(l * r);
}

/**
 *  Arithmetric operation that turns a multiply operation into an pointer to a variable
 * 	This is useful if the types of the operands are not yet known at compile-time
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::pointerMultiply(const Expression *left, const Expression *right)
{
    // calculate left and right values
    jit_value l = pointerExpression(left);
    jit_value r = pointerExpression(right);

    // calculate them, and push to stack
    _stack.push(_callbacks.multiply(_userdata, l, r));
}

/**
 *  Arithmetric operation that turns a divide operation into an integer
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::integerDivide(const Expression *left, const Expression *right)
{
    // calculate right value
    jit_value r = integerExpression(right);

    // if it is 0 we branch off to our early exit label
    _function.insn_branch_if(r == _false, _division_by_zero.label());

    // calculate left value
    jit_value l = integerExpression(left);

    // calculate them, and push to stack
    _stack.emplace(l / r);
}

/**
 *  Arithmetric operation that turns a divide operation into an double
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::doubleDivide(const Expression *left, const Expression *right)
{
    // calculate right value
    jit_value r = doubleExpression(right);

    // if it is 0 we branch off to our early exit label
    _function.insn_branch_if(r == _false, _division_by_zero.label());

    // calculate left value
    jit_value l = doubleExpression(left);

    // calculate them, and push to stack
    _stack.emplace(l / r);
}

/**
 *  Arithmetric operation that turns a divide operation into an pointer to a variable
 * 	This is useful if the types of the operands are not yet known at compile-time
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::pointerDivide(const Expression *left, const Expression *right)
{
    // calculate left and right values
    jit_value l = pointerExpression(left);
    jit_value r = pointerExpression(right);

    // get the result
    jit_value result = _callbacks.divide(_userdata, l, r);

    // If the resulting pointer is a nullpointer, we have a division by zero error
    _function.insn_branch_if(result == _false, _division_by_zero.label());

    // calculate them, and push to stack
    _stack.push(result);
}

/**
 *  Arithmetric operation
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::integerModulo(const Expression *left, const Expression *right)
{
    // calculate left and right values
    jit_value l = integerExpression(left);
    jit_value r = integerExpression(right);

    // calculate them, and push to stack
    _stack.emplace(l % r);
}

/**
 *  Arithmetric operation
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::pointerModulo(const Expression *left, const Expression *right)
{
    // calculate the result
    integerModulo(left, right);

    // transfer result to runtime space and add pointer to stack
    _stack.push(_callbacks.transfer_integer(_userdata, pop()));
}

/**
 *  Comparison operator
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::equals(const Expression *left, const Expression *right)
{
    if (left->type() == Expression::Type::Double || right->type() == Expression::Type::Double)
    {
        // Convert both expressions to floating points
        jit_value l = doubleExpression(left);
        jit_value r = doubleExpression(right);

        // Compare them and push it to the stack
        _stack.emplace(l == r);
    }
    else if (left->type() == Expression::Type::Integer || right->type() == Expression::Type::Integer)
    {
        // Convert both expressions to integer values
        jit_value l = integerExpression(left);
        jit_value r = integerExpression(right);

        // Compare them and push it to the stack
        _stack.emplace(l == r);
    }
    else if (left->type() == Expression::Type::Boolean || right->type() == Expression::Type::Boolean)
    {
        // Convert both expressions too boolean values
        jit_value l = booleanExpression(left);
        jit_value r = booleanExpression(right);

        // Compare them and push it to the stack
        _stack.emplace(l == r);
    }
    else
    {
        // ask the left instruction to push the string to the stack
        left->toString(this);
        
        // and get the string back from the stack
        jit_value l_size = pop();
        jit_value l = pop();

        // ask the right instruction to do the same (push string to the stack)
        right->toString(this);
        
        // and get it back from the stack
        jit_value r_size = pop();
        jit_value r = pop();

        // Call the strcmp callback and push the result to the stack
        jit_value cmp = _callbacks.strcmp(_userdata, l, l_size, r, r_size);

        // Compare against the constant _false which is just a 0
        _stack.emplace(cmp == _false);
    }
}

/**
 *  Comparison operator
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::notEquals(const Expression *left, const Expression *right)
{
    if (left->type() == Expression::Type::Double || right->type() == Expression::Type::Double)
    {
        // Convert both expressions to floating points
        jit_value l = doubleExpression(left);
        jit_value r = doubleExpression(right);

        // Compare them and push it to the stack
        _stack.emplace(l != r);
    }
    else if (left->type() == Expression::Type::Integer || right->type() == Expression::Type::Integer)
    {
        // Convert both expressions to integer values
        jit_value l = integerExpression(left);
        jit_value r = integerExpression(right);

        // Compare them and push it to the stack
        _stack.emplace(l != r);
    }
    else if (left->type() == Expression::Type::Boolean || right->type() == Expression::Type::Boolean)
    {
        // Convert both expressions too boolean values
        jit_value l = booleanExpression(left);
        jit_value r = booleanExpression(right);

        // Compare them and push it to the stack
        _stack.emplace(l != r);
    }
    else
    {
        // Convert both expressions to strings
        left->toString(this);
        jit_value l_size = pop();
        jit_value l = pop();

        // Right expression is also turned into a string
        right->toString(this);
        jit_value r_size = pop();
        jit_value r = pop();

        // Call the strcmp callback and push the result to the stack
        jit_value cmp = _callbacks.strcmp(_userdata, l, l_size, r, r_size);
        _stack.emplace(cmp != _false);
    }
}

/**
 *  Comparison operator
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::greater(const Expression *left, const Expression *right)
{
    // calculate left and right values
    jit_value l = (left->type() == Expression::Type::Double || left->type() == Expression::Type::Value) ? doubleExpression(left) : integerExpression(left);
    jit_value r = (right->type() == Expression::Type::Double || right->type() == Expression::Type::Value) ? doubleExpression(right) : integerExpression(right);

    // calculate them, and push to stack
    _stack.emplace(l > r);
}

/**
 *  Comparison operator
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::greaterEquals(const Expression *left, const Expression *right)
{
    // calculate left and right values
    jit_value l = (left->type() == Expression::Type::Double || left->type() == Expression::Type::Value) ? doubleExpression(left) : integerExpression(left);
    jit_value r = (right->type() == Expression::Type::Double || right->type() == Expression::Type::Value) ? doubleExpression(right) : integerExpression(right);

    // calculate them, and push to stack
    _stack.emplace(l >= r);
}

/**
 *  Comparison operator
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::lesser(const Expression *left, const Expression *right)
{
    // calculate left and right values
    jit_value l = (left->type() == Expression::Type::Double || left->type() == Expression::Type::Value) ? doubleExpression(left) : integerExpression(left);
    jit_value r = (right->type() == Expression::Type::Double || right->type() == Expression::Type::Value) ? doubleExpression(right) : integerExpression(right);

    // calculate them, and push to stack
    _stack.emplace(l < r);
}

/**
 *  Comparison operator
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::lesserEquals(const Expression *left, const Expression *right)
{
    // calculate left and right values
    jit_value l = (left->type() == Expression::Type::Double || left->type() == Expression::Type::Value) ? doubleExpression(left) : integerExpression(left);
    jit_value r = (right->type() == Expression::Type::Double || right->type() == Expression::Type::Value) ? doubleExpression(right) : integerExpression(right);

    // calculate them, and push to stack
    _stack.emplace(l <= r);
}

/**
 *  Regular expression operator
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::regex(const Expression *left, const Expression *right)
{
    // generate the code to turn the expression on the right hand size into a string (this pushes two instructions to the stack)
    right->toString(this);
    
    // pop the last two elements from the stack (the string representation of the expression plus its size)
    jit_value expressionsize = pop();
    jit_value expression = pop();

    // now we are going to call the function to turn this into an expression
    jit_value handle = _callbacks.regex_compile(_userdata, expression, expressionsize);

    // we insert a jump to go to the error handler if the regex compilation fails
    _function.insn_branch_if_not(handle, _invalid_regex.label());

    // right hand side indeed contains a valid regex, now create the code that turns the left hand size in a string
    left->toString(this);

    // pop the last two instructions from the stack (this is now the string on the left hand side)
    jit_value messagesize = pop();
    jit_value message = pop();

    // call the regex match function and push the result to the stack
    jit_value result = _callbacks.regex_match(_userdata, handle, message, messagesize);

    // and finally we call a method to destruct regex resources
    _callbacks.regex_release(_userdata, handle);
    
    // push the result to the stack
    _stack.emplace(result != _false);
}

/**
 *  Boolean operator
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::booleanAnd(const Expression *left, const Expression *right)
{
    // calculate the values
    jit_value l = booleanExpression(left);
    jit_value r = booleanExpression(right);

    // insert a boolean and on the left and right expression
    _stack.push(_function.insn_and(l, r));
}

/**
 *  Boolean operator
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::booleanOr(const Expression *left, const Expression *right)
{
    // calculate the values
    jit_value l = booleanExpression(left);
    jit_value r = booleanExpression(right);

    // insert a boolean or on the left and right expression
    _stack.push(_function.insn_or(l, r));
}

/**
 *  Generate the code to apply a set of modifiers on an expression
 *  @param  modifiers          The set of modifiers to apply
 *  @param  expression         The expression to apply to modifiers on
 *  @note   +1 on the stack    (pointer to the latest variable)
 */
void Bytecode::modifiers(const Modifiers *modifiers, const Variable *variable)
{
    // we will need a pointer to the variable on the stack that we can pop off later on to modify it
    variable->pointer(this);

    // loop through all the modifiers
    for (const auto &modifier : *modifiers)
    {
        // Push the token of the modifier (so the name of it) to the stack
        stringValue(modifier.get()->token());

        // the stack currently contains { size, buffer, variable }

        // pop the buffer and size from the stack (in reverse order) to get the modifier name
        auto size = pop();
        auto buffer = pop();

        // call the native function to save the modifier to the variable on the stack
        _stack.push(_callbacks.modifier(_userdata, buffer, size));

        // the stack currently contains { modifier, variable }

        // pop the modifier
        auto mod = pop();

        // pop the variable from the stack
        auto var = pop();

        // Let's retrieve our parameters and if we have them generate them
        const Parameters *params = modifier->parameters();
        if (params) parameters(params);

        // Turn our possibly just created parameters into a jit_value
        // We're using _false here for a nullptr
        jit_value jitparams = (params) ? pop() : _false;

        // let's apply the modifier and push the new result of it to the stack
        _stack.push(_callbacks.modify_variable(_userdata, var, mod, jitparams));
    }
}

/**
 *  Generate the code to apply a set of modifiers on an expression and turn it into a string
 *  @param  modifiers          The set of modifiers to apply
 *  @param  variable           The variable to apply to modifers to
 */
void Bytecode::modifiersString(const Modifiers *modifiers, const Variable *variable)
{
    // first generate the modifiers and all, which adds the output to the stack
    this->modifiers(modifiers, variable);
    
    // get the pointer to the variable from the stack
    auto lastvar = pop();

    // push the result that is on the stack through to_boolean
    _stack.push(_callbacks.to_string(_userdata, lastvar));
    _stack.push(_callbacks.size(_userdata, lastvar));
}

/**
 *  Generate the code to apply a set of modifiers on an expression and turn it into a boolean
 *  @param  modifiers          The set of modifiers to apply
 *  @param  variable           The variable to apply to modifers to
 */
void Bytecode::modifiersBoolean(const Modifiers *modifiers, const Variable *variable)
{
    // first generate the modifiers and all, which adds the output to the stack
    this->modifiers(modifiers, variable);

    // push the result that is on the stack through to_boolean
    _stack.push(_callbacks.to_boolean(_userdata, pop()));
}

/**
 *  Generate the code to apply a set of modifiers on an expression and turn it into a double
 *  @param  modifiers          The set of modifiers to apply
 *  @param  variable           The variable to apply the modifiers to
 */
void Bytecode::modifiersDouble(const Modifiers *modifiers, const Variable *variable)
{
    // first generate the modifiers and all, which adds the output to the stack
    this->modifiers(modifiers, variable);

    // push the result that is on the stack through to_double
    _stack.push(_callbacks.to_double(_userdata, pop()));
}

/**
 *  Generate the code to construct the following parameters
 *  @param  parameters         The parameters to construct
 *  @note   Construct as in, generate the code so the runtime can construct them
 *  @note   +1 on the stack
 */
void Bytecode::parameters(const Parameters *parameters)
{
    // Construct the parameters through our callback
    auto params = _callbacks.create_params(_userdata, _function.new_constant(parameters->size()));

    // loop through all the parameters and add them to our params object one by one
    for (auto &param : *parameters)
    {
        switch (param->type()) {
        case Expression::Type::Boolean:
            // Convert the expression to a boolean value and append it using params_append_boolean
            _callbacks.params_append_boolean(_userdata, params, booleanExpression(param.get()));
            break;
        case Expression::Type::Integer:
            // Convert the expression to a integer value and append it using params_append_integer
            _callbacks.params_append_integer(_userdata, params, integerExpression(param.get()));
            break;
        case Expression::Type::String: {
            // Convert the expression to a string value and append it using params_append_string
            param->toString(this);

            // pop the buffer and size from the stack (in reverse order) to get output of the expression
            auto size = pop();
            auto buffer = pop();

            // actually append the string
            _callbacks.params_append_string(_userdata, params, buffer, size);
            break;
        }
        case Expression::Type::Double:
            // Convert the expression to a floating point value and append it using params_append_integer
            _callbacks.params_append_double(_userdata, params, doubleExpression(param.get()));
            break;
        default:
            throw CompileError("Unknown typed values are currently unsupported");
        }
    }

    // Push the parameters to the stack
    _stack.push(std::move(params));
}

/**
 *  Generate the code to do a foreach loop over variable
 *  @param variable         The variable object to iterate over
 *  @param key              The magic variable name for the keys
 *  @param value            The magic variable name for the values
 *  @param statements       The statements to execute on each iteration
 *  @param else_statements  The statements to execute if there was nothing to loop through
 */
void Bytecode::foreach(const Variable *variable, const std::string &key, const std::string &value, const Statements *statements, const Statements *else_statements)
{
    // tell the callbacks that we're creating an iterator
    auto iterator = _callbacks.create_iterator(_userdata, pointer(variable));

    // we create a label just before our loop so we can actually loop
    // and we create a label just outside of it, so we can jump out of it
    jit_label label_while = _function.new_label();
    jit_label label_after_while = _function.new_label();

    if (else_statements)
    {
        // Call the valid_iterator callback to begin with
        auto valid = _callbacks.valid_iterator(_userdata, iterator);

        // Jump to the start of the actual while loop if we are valid
        _function.insn_branch_if(valid, label_while);

        // Otherwise just fall through and call the else_statements
        else_statements->generate(this);

        // Then just jump over the while loop entirely
        _function.insn_branch(label_after_while);
    }

    // we insert our label_while at the start
    _function.insn_label(label_while);

    // make the valid_iterator callback
    auto valid = _callbacks.valid_iterator(_userdata, iterator);

    // if the output of the callback is 0 (false) we jump to label_after_while
    _function.insn_branch_if_not(valid, label_after_while);

    // do we have a key?
    if (!key.empty())
    {
        // construct jit values for the key name
        stringValue(key);
        auto key_size = pop();
        auto key_buf = pop();

        // ask for the key
        auto current_key = _callbacks.iterator_key(_userdata, iterator);

        // assign the key
        _callbacks.assign(_userdata, key_buf, key_size, current_key);
    }

    // do we have a value?
    if (!value.empty())
    {
        // convert our magic key to jit_values for the callback
        stringValue(value);
        auto value_size = pop();
        auto value_buf = pop();

        // ask for the value
        auto current_value = _callbacks.iterator_value(_userdata, iterator);

        // assign the value
        _callbacks.assign(_userdata, value_buf, value_size, current_value);
    }

    // generate the actual statements
    statements->generate(this);

    // proceed with iterator
    _callbacks.iterator_next(_userdata, iterator);

    // jump back to label_while
    _function.insn_branch(label_while);

    // insert our label_after_while at the end
    _function.insn_label(label_after_while);
}

/**
 *  Generate the code to assign the output of an expression to a key
 *  @param key                  The key to assign the output to
 *  @param expression           The expression to evaluate
 */
void Bytecode::assign(const std::string &key, const Expression *expression)
{
    // Convert the key to jit_values
    stringValue(key);
    auto key_size = pop();
    auto key_str = pop();

    switch (expression->type()) {
    case Expression::Type::Integer: {
        // Convert to a integer type and use the assign_integer callback
        _callbacks.assign_integer(_userdata, key_str, key_size, integerExpression(expression));
        break;
    }
    case Expression::Type::String: {
        // Convert to a string and use the assign_string callback
        expression->toString(this);
        auto size = pop();
        auto str = pop();
        _callbacks.assign_string(_userdata, key_str, key_size, str, size);
        break;
    }
    case Expression::Type::Boolean: {
        // Convert to a boolean and use the assign_boolean callback
        _callbacks.assign_boolean(_userdata, key_str, key_size, booleanExpression(expression));
        break;
    }
    case Expression::Type::Value: {
        // If we are a variable just convert it to a pointer and pass that to the assign callback
        _callbacks.assign(_userdata, key_str, key_size, pointerExpression(expression));
        break;
    }
    case Expression::Type::Double:
        // Convert to a floating point and use the assign_double callback
        _callbacks.assign_double(_userdata, key_str, key_size, doubleExpression(expression));
        break;
    }
}

/**
 *  Execute the template given a certain handler
 *  @param  handler
 */
void Bytecode::process(Handler &handler)
{
    // do we have a C function?
    if (_closure)
    {
        // call the C function directly
        _closure(&handler);
    }
    else
    {
        // the is one argument, a pointer to the handler
        void *arg = &handler;

        // arguments should be passed as pointers
        void *args[1] = { &arg };

        // call the function
        _function.apply(args, nullptr);
    }
}

/**
 *  End namespace
 */
}}
