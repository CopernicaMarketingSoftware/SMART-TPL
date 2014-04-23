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
 *  The signature for _function
 *  @var    jit_type_t
 */
jit_type_t Bytecode::_function_signature = jit_function::signature_helper(jit_type_void, jit_type_void_ptr, jit_function::end_params);

/**
 *  Constructor
 *  @param  source The source that holds the template
 *  @throws std::runtime_error If something went wrong while compiling the jit code
 */
Bytecode::Bytecode(const Source& source) : _tree(source.data(), source.size()),
    _function(_context, _function_signature),
    _callbacks(&_function)
{
    // start building the function
    _context.build_start();
    
    // read in the one and only parameter into _userdata
    _userdata = _function.get_param(0);
    
    // generate the LLVM code
    _tree.generate(this);
    
    // compile the function
    _function.compile();
    
    // done building
    _context.build_end();
    
    // get the closure
    _closure = (ShowTemplate *)_function.closure();
}

/**
 *  Destructor
 */
Bytecode::~Bytecode() {}

/**
 *  Helper method to pop a value from the stack
 *  @return jit_value
 *  @throws std::runtime_error if the internal stack is empty
 */
jit_value Bytecode::pop()
{
    // let's check if the stack is empty and throw an error if it is instead of crashing
    if (_stack.empty())
        throw std::runtime_error("_stack is empty");
    // get the value from the stack
    jit_value value = _stack.top();
    
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
    jit_value buffer = _function.new_constant((void *)data.c_str(), jit_type_void_ptr);
    jit_value size = _function.new_constant(data.size(), jit_type_sys_int);
    
    // call the write function
    _callbacks.write(_userdata, buffer, size);
}

/**
 *  Construct a poiner to a variable
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
 *  Retrieve the numeric representation of an expression
 *  @param  expression
 *  @return jit_value
 */
jit_value Bytecode::numeric(const Expression *expression)
{
    // create on the stack
    expression->numeric(this);
    
    // remove it from the stack
    return pop();
}

/**
 *  Retrieve the boolean representation (1 or 0) of an expression
 *  @param  expression
 *  @return jit_value
 */
jit_value Bytecode::boolean(const Expression *expression)
{
    // create on the stack
    expression->boolean(this);
    
    // remove from the stack
    return pop();
}

/**
 *  Generate the code to output a variable
 *  @param  variable           The variable to output
 */
void Bytecode::output(const Variable *variable)
{
    variable->pointer(this);

    auto var = pop();

    _callbacks.output(_userdata, var);
}

/**
 *  Generate the code to output the output of a filter
 *  @param  filter             The filter to eventually output
 */
void Bytecode::output(const Filter *filter)
{
    // Call the string method on the filter which will call the modifiers() on our generator
    filter->string(this);

    // Pop the value that modifiers() left us
    auto var = pop();

    // output this value
    _callbacks.output(_userdata, var);
}

/**
 *  Generate the code to write an expression as a string
 *  @param  expression          the expression to write as a string
 */
void Bytecode::write(const Expression *expression)
{
    // convert the expression to a string (this pushes two values on the stack
    expression->string(this);
    
    // pop the buffer and size from the stack (in reverse order)
    auto size = pop();
    auto buffer = pop();

    // call the write function
    _callbacks.write(_userdata, buffer, size);
}

/**
 *  Generate a conditional statement
 *  @param  expression          the expression to evaluate
 *  @param  ifstatements        the statements in the 'if' part
 *  @param  elsestatements      the statements in the 'else' part
 */
void Bytecode::condition(const Expression *expression, const Statements *ifstatements, const Statements *elsestatements)
{
    // we need a label for the 'else' part that we're going to create, and for the
    // part after the entire condition
    jit_label elselabel = _function.new_label();
    jit_label endlabel = _function.new_label();
    
    // branche to the label if the expression is not valid
    _function.insn_branch_if_not(boolean(expression), elselabel);
    
    // now we should create the if statements
    ifstatements->generate(this);
    
    // branche to the end-position
    _function.insn_branch(endlabel);
    
    // the else label starts here
    _function.insn_label(elselabel);
    
    // generate the else instructions
    if (elsestatements) elsestatements->generate(this);
    
    // the end-label starts here
    _function.insn_label(endlabel);
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
    jit_value namevalue = _function.new_constant((void *)name.c_str(), jit_type_void_ptr);
    jit_value namesize = _function.new_constant(name.size(), jit_type_sys_int);
    
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
    // convert the expression to a string (this pushes two values on the stack
    expression->string(this);
    
    // pop the buffer and size from the stack (in reverse order)
    auto size = pop();
    auto buffer = pop();
    
    // call the native function to retrieve the member of a variable, and store the pointer
    // to the variable on the stack
    _stack.push(_callbacks.member(_userdata, pointer(parent), buffer, size));
}

/**
 *  Generate the code to get a pointer to a variable given a literal name
 *  @param  name                name of the variable
 *  @note   +1 on the stack
 */
void Bytecode::varPointer(const std::string &name)
{
    // we need a constant of the name, and the name size
    jit_value namevalue = _function.new_constant((void *)name.c_str(), jit_type_void_ptr);
    jit_value namesize = _function.new_constant(name.size(), jit_type_sys_int);

    // push the variable on the stack
    _stack.push(_callbacks.variable(_userdata, namevalue, namesize));
}

/**
 *  Create a string or numeric literal
 *  @param  value
 *  @note   +2 on the stack
 */
void Bytecode::string(const std::string &value)
{
    // push buffer and size
    _stack.push(_function.new_constant((void *)value.c_str(), jit_type_void_ptr));
    _stack.push(_function.new_constant(value.size(), jit_type_sys_int));
}

/**
 *  Create a string or numeric literal
 *  @param  value
 *  @note   +1 on the stack
 */
void Bytecode::numeric(int value)
{
    // push value
    _stack.push(_function.new_constant(value, jit_type_sys_int));
}

/**
 *  Create a string or numeric constant for a variable
 *  @param  variable
 *  @note   +2 on the stack
 */
void Bytecode::string(const Variable *variable)
{
    // first we need a pointer to the variable
    jit_value var = pointer(variable);
    
    // call the functions to retrieve the string value
    _stack.push(_callbacks.to_string(_userdata, var));
    _stack.push(_callbacks.size(_userdata, var));
}

/**
 *  Create a string or numeric constant for a variable
 *  @param  variable
 *  @note   +1 on the stack
 */
void Bytecode::numeric(const Variable *variable)
{
    // call the function to convert a variable to a numeric value
    _stack.push(_callbacks.to_numeric(_userdata, pointer(variable)));
}

/**
 *  Create a boolean constant for a variable
 *  @param  variable
 *  @note   +1 on the stack
 */
void Bytecode::boolean(const Variable *variable)
{
    // call the function to convert a variable to a numeric value
    _stack.push(_callbacks.to_boolean(_userdata, pointer(variable)));
}

void Bytecode::variable(const Variable* variable)
{
    // @todo
    string(variable);
}

/**
 *  Create a string literal from an expression that is known to return a numeric value,
 *  and a method to do this in the other direction
 *  @param  expression
 */
void Bytecode::numericToString(const Expression *expression)
{
    // @todo implementation
}

/**
 *  Create a string literal from an expression that is known to return a numeric value,
 *  and a method to do this in the other direction
 *  @param  expression
 */
void Bytecode::stringToNumeric(const Expression *expression)
{
    // @todo implementation
}

/**
 *  Arithmetric operation
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::plus(const Expression *left, const Expression *right) 
{
    // calculate left and right values
    jit_value l = numeric(left);
    jit_value r = numeric(right);
    
    // calculate them, and push to stack
    _stack.push(l + r);
}

/**
 *  Arithmetric operation
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::minus(const Expression *left, const Expression *right) 
{
    // calculate left and right values
    jit_value l = numeric(left);
    jit_value r = numeric(right);
    
    // calculate them, and push to stack
    _stack.push(l - r);
}

/**
 *  Arithmetric operation
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::divide(const Expression *left, const Expression *right) 
{
    // calculate left and right values
    jit_value l = numeric(left);
    jit_value r = numeric(right);
    
    // calculate them, and push to stack
    _stack.push(l / r);
}

/**
 *  Arithmetric operation
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::multiply(const Expression *left, const Expression *right) 
{
    // calculate left and right values
    jit_value l = numeric(left);
    jit_value r = numeric(right);
    
    // calculate them, and push to stack
    _stack.push(l * r);
}

/**
 *  Comparison operator
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::equals(const Expression *left, const Expression *right) 
{
    // @todo alternative for string comparison
    
    // calculate left and right values
    jit_value l = numeric(left);
    jit_value r = numeric(right);
    
    // calculate them, and push to stack
    _stack.push(l == r);
}

/**
 *  Comparison operator
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::notEquals(const Expression *left, const Expression *right) 
{
    // @todo alternative for string comparison
    
    // calculate left and right values
    jit_value l = numeric(left);
    jit_value r = numeric(right);
    
    // calculate them, and push to stack
    _stack.push(l != r);
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
    jit_value l = numeric(left);
    jit_value r = numeric(right);
    
    // calculate them, and push to stack
    _stack.push(l > r);
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
    jit_value l = numeric(left);
    jit_value r = numeric(right);
    
    // calculate them, and push to stack
    _stack.push(l >= r);
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
    jit_value l = numeric(left);
    jit_value r = numeric(right);
    
    // calculate them, and push to stack
    _stack.push(l < r);
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
    jit_value l = numeric(left);
    jit_value r = numeric(right);
    
    // calculate them, and push to stack
    _stack.push(l <= r);
}

/**
 *  Boolean operator
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::booleanAnd(const Expression *left, const Expression *right) 
{
    // construct the result value
    jit_value result = _function.new_value(jit_type_sys_int);
    
    // we need a label for the right part that only has to be evaluated if
    // the left part is true (otherwise the result is false anyway)
    jit_label rightlabel = _function.new_label();
    jit_label endlabel = _function.new_label();
    
    // calculate the left value
    jit_value l = boolean(left);
    
    // branche to the right label if the expression is true
    _function.insn_branch_if(l, rightlabel);
    
    // left part already evaluates to false, store false in the result
    _function.store(result, l);
    
    // go to the end label
    _function.insn_branch(endlabel);
    
    // the right label starts here
    _function.insn_label(rightlabel);
    
    // calculate the right value
    jit_value r = boolean(right);
    
    // left part already evaluates to true, store r result in the result
    _function.store(result, r);
    
    // the end-label starts here
    _function.insn_label(endlabel);

    // push the result on the stack
    _stack.push(result);
}

/**
 *  Boolean operator
 *  @param  left
 *  @param  right
 *  @note   +1 on the stack
 */
void Bytecode::booleanOr(const Expression *left, const Expression *right) 
{
    // construct the result value
    jit_value result = _function.new_value(jit_type_sys_int);
    
    // we need a label for the right part that only has to be evaluated if
    // the left part is false (otherwise the result is true anyway)
    jit_label rightlabel = _function.new_label();
    jit_label endlabel = _function.new_label();
    
    // calculate the left value
    jit_value l = boolean(left);
    
    // branche to the right label if the expression is not valid
    _function.insn_branch_if_not(l, rightlabel);
    
    // left part already evaluates to true, store a 1 in the result
    _function.store(result, l);
    
    // go to the end label
    _function.insn_branch(endlabel);
    
    // the right label starts here
    _function.insn_label(rightlabel);
    
    // calculate the right value
    jit_value r = boolean(right);
    
    // left part evaluated to false, store right result in the result
    _function.store(result, r);
    
    // the end-label starts here
    _function.insn_label(endlabel);

    // push the result on the stack
    _stack.push(result);
}

/**
 *  Generate the code to apply a set of modifiers on an expression
 *  @param  modifiers          The set of modifiers to apply
 *  @param  expression         The expression to apply to modifiers on
 *  @note   +1 on the stack
 */
void Bytecode::modifiers(const Modifiers* modifiers, const Expression *expression)
{
    // @todo This call currently only supports Expressions of the type Variable
    const Variable* variable = dynamic_cast<const Variable*>(expression);
    if (variable)
    {
        variable->pointer(this);
        for (auto &modifier : *modifiers)
        {
            string(modifier.get()->token());

            // pop the buffer and size from the stack (in reverse order) to get the modifier name
            auto size = pop();
            auto buffer = pop();

            // call the native function to save the modifier
            // to the variable on the stack
            _stack.push(_callbacks.modifier(_userdata, buffer, size));

            // pop the modifier
            auto mod = pop();
            // pop the latest value from the stack
            auto var = pop();
            // let's apply the modifier and push the new result of it to the stack
            _stack.push(_callbacks.modify_variable(_userdata, var, mod));
        }
    }
}

/**
 *  Execute the template given a certain data source
 *  @param  data
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
        
        // result variable (not used)
        int result;

        // call the function
        _function.apply(args, &result);
    }
}

/**
 *  End namespace
 */
}

