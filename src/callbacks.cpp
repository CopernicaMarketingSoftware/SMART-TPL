/**
 *  Callbacks.cpp
 *
 *  Implementation of the callbacks
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
 *  We always have a empty variable in place
 */
static EmptyValue empty;

/**
 *  Signature of the write callback
 *  @var    WriteCallback
 */
WriteCallback Callbacks::_write;

/**
 *  Signature of the output callback
 *  @var    OutputCallback
 */
OutputCallback Callbacks::_output;

/**
 *  Signature of the member callback
 *  @var    MemberCallback
 */
MemberCallback Callbacks::_member;

/**
 *  Signature of the variable callback
 *  @var    MemberCallback
 */
VariableCallback Callbacks::_variable;

/**
 *  Signature of the function to convert a variable to a string
 *  @var    ToStringCallback
 */
ToStringCallback Callbacks::_toString;

/**
 *  Signature of the function to convert a variable to a numeric value
 *  @var    ToNumericCallback
 */
ToNumericCallback Callbacks::_toNumeric;

/**
 *  Signature of the function to convert a variable to a boolean value
 *  @var    ToBooleanCallback
 */
ToBooleanCallback Callbacks::_toBoolean;

/**
 *  Signature of the function to retrieve the size/strlen of a variable
 *  @var    SizeCallback
 */
SizeCallback Callbacks::_size;

/**
 *  Signature of the function to retrieve the modifier
 *  @var    ModifierCallback
 */
ModifierCallback Callbacks::_modifier;

/**
 *  Signature of the function to apply a modifier
 *  @var    ApplyCallback
 */
ApplyCallback Callbacks::_apply;


/**
 *  Function to write raw data
 *  @param  userdata        pointer user-supplied data
 *  @param  data            pointer to the buffer
 *  @param  size            size of the data to write
 */
void smart_tpl_write(void *userdata, const char *data, size_t size)
{
    // convert the userdata to a handler object
    auto *handler = (Handler *)userdata;
    
    // call the handler
    handler->write(data, size);
}

/**
 *  Function to output a variable
 *  @param  userdata        pointer to user-supplied data
 *  @param  variable        pointer to the variable
 */
void smart_tpl_output(void *userdata, void *variable)
{
    // convert the userdata to a handler object
    auto *handler = (Handler *)userdata;

    // convert the variable to a variable object
    auto *var = (Value *)variable;
    
    // output the variable
    handler->write(var->toString(), var->size());
}

/**
 *  Retrieve a pointer to a member
 *  @param  userdata        pointer to user-supplied data
 *  @param  variable        pointer to variable
 *  @param  name            name of the variable
 *  @param  size            size of the variable
 *  @return                 pointer to a new variable
 */
void *smart_tpl_member(void *userdata, void *variable, const char *name, size_t size)
{
    // convert the variable to a variable object
    auto *var = (Value *)variable;
    
    // fetch the member
    auto *result = var->member(name, size);
    
    // ensure that we always return an object
    return result ? result : &empty;
}
    
/**
 *  Retrieve a pointer to a variable
 *  @param  userdata        pointer to user-supplied data
 *  @param  name            name of the variable
 *  @param  size            size of the variable
 *  @return                 pointer to a new variable
 */
void *smart_tpl_variable(void *userdata, const char *name, size_t size)
{
    // convert the userdata to a handler object
    auto *handler = (Handler *)userdata;
    
    // convert to a variable
    auto *result = handler->variable(name, size);

    // ensure that we always return an object
    return result ? result : &empty;
}

/**
 *  Retrieve the string representation of a variable
 *  @param  userdata        pointer to user-supplied data
 *  @param  variable        pointer to variable
 *  @return                 string buffer
 */
const char *smart_tpl_to_string(void *userdata, void *variable)
{
    // convert the variable to a value object
    auto *var = (Value *)variable;
    
    // convert to string
    auto *result = var->toString();
    
    // ensure that a string is always returned
    return result ? result : empty.toString();
}

/**
 *  Retrieve the numeric representation of a variable
 *  @param  userdata        pointer to user-supplied data
 *  @param  variable        pointer to variable
 *  @return                 numeric value
 */
size_t smart_tpl_to_numeric(void *userdata, void *variable)
{
    // convert the variable to a value object
    auto *var = (Value *)variable;
    
    // convert to numeric
    return var->toNumeric();
}

/**
 *  Retrieve the boolean representation of a variable
 *  @param  userdata        pointer to user-supplied data
 *  @param  variable        pointer to variable
 *  @return                 numeric value
 */
size_t smart_tpl_to_boolean(void *userdata, void *variable)
{
    // convert the variable to a value object
    auto *var = (Value *)variable;
    
    // convert to bool
    return var->toBoolean();
}
    
/**
 *  Retrieve the length of the string representation of a variable
 *  @param  userdata        pointer to user-supplied data
 *  @param  variable        pointer to variable
 *  @return                 string length
 */
size_t smart_tpl_size(void *userdata, void *variable)
{
    // convert the variable to a value object
    auto *var = (Value *)variable;
    
    // return the size
    return var->size();
}

void* smart_tpl_modifier(void *userdata, const char *name, size_t size)
{
    // convert to Handler
    auto *handler = (Handler *)userdata;

    // Lookup and return the modifier in the Handler
    return handler->modifier(name, size);
}

void* smart_tpl_apply(void *userdata, void *variable, void *modifier_ptr)
{
    // In case the modifier is a nullptr just return the original value
    if (modifier_ptr == nullptr || variable == nullptr)
        return variable;
    // convert to the Modifier
    auto *modifier = (Modifier*) modifier_ptr;
    // convert to the Value object
    auto *value = (Value*) variable;

    auto *output = modifier->modify(value);
    if (output != value)
    {  // As our output value is different from our input value we mark it as destroy later
        auto *handler = (Handler *)userdata;
        handler->destroyValue(output);
    }
    return output;
}

/**
 *  End namespace
 */
}

