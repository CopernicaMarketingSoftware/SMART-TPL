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
 *  Signature of the function to retrieve the size/strlen of a variable
 *  @var    SizeCallback
 */
SizeCallback Callbacks::_size;


/**
 *  Function to write raw data
 *  @param  userdata        pointer user-supplied data
 *  @param  data            pointer to the buffer
 *  @param  size            size of the data to write
 */
void smart_tpl_write(void *userdata, const char *data, int size)
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
 void *smart_tpl_member(void *userdata, void *variable, const char *name, int size)
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
void *smart_tpl_variable(void *userdata, const char *name, int size)
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
    // convert the variable to a variable object
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
int smart_tpl_to_numeric(void *userdata, void *variable)
{
    // convert the variable to a variable object
    auto *var = (Value *)variable;
    
    // convert to numeric
    return var->toNumeric();
}
    
/**
 *  Retrieve the length of the string representation of a variable
 *  @param  userdata        pointer to user-supplied data
 *  @param  variable        pointer to variable
 *  @return                 string length
 */
int smart_tpl_size(void *userdata, void *variable)
{
    // convert the variable to a variable object
    auto *var = (Value *)variable;
    
    // convert to numeric
    return var->size();
}

/**
 *  End namespace
 */
}

