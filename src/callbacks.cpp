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
namespace SmartTpl { namespace Internal {

/**
 *  Create all static variables
 */
WriteCallback           Callbacks::_write;
OutputCallback          Callbacks::_output;
MemberCallback          Callbacks::_member;
MemberAtCallback        Callbacks::_member_at;
CreateIteratorCallback  Callbacks::_create_iterator;
DeleteIteratorCallback  Callbacks::_delete_iterator;
ValidIteratorCallback   Callbacks::_valid_iterator;
IteratorKeyCallback     Callbacks::_iterator_key;
IteratorValueCallback   Callbacks::_iterator_value;
IteratorNextCallback    Callbacks::_iterator_next;
VariableCallback        Callbacks::_variable;
ToStringCallback        Callbacks::_toString;
ToNumericCallback       Callbacks::_toNumeric;
ToBooleanCallback       Callbacks::_toBoolean;
SizeCallback            Callbacks::_size;
ModifierCallback        Callbacks::_modifier;
ModifyVariableCallback  Callbacks::_modify_variable;
ModifyNumericCallback   Callbacks::_modify_numeric;
ModifyStringCallback    Callbacks::_modify_string;
StrCmpCallback          Callbacks::_strcmp;
AssignCallback          Callbacks::_assign;
AssignBooleanCallback   Callbacks::_assign_boolean;
AssignNumericCallback   Callbacks::_assign_numeric;
AssignStringCallback    Callbacks::_assign_string;


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
    return result ? result : &EmptyValue::get();
}

/**
 *  Retrieve a pointer to a member at a certain position
 *  @param  userdata        pointer to user-supplied data
 *  @param  variable        pointer to variable
 *  @param  position        what position would we like
 *  @return                 pointer to a new variable
 */
void* smart_tpl_member_at(void* userdata, void* variable, long position)
{
    // convert the variable to a value object
    auto *var = (Value *)variable;

    // fetch the member
    auto *result = var->member(position);

    // ensure that we always return an object
    return result ? result : &EmptyValue::get();
}

/**
 *  Tell the handler that we are starting a new loop
 *  @param  userdata        pointer to user-supplied data
 *  @param  variable        pointer to the variable that is being iterated
 */
void *smart_tpl_create_iterator(void *userdata, void *variable)
{
    // cast to actual value object
    auto *var = (Value *)variable;

    // construct a new iterator
    //  @todo 
    //      can we allocate this on the heap instead of allocating with new?
    //      for example by using an already-allocated stack of iterator objects inside the handler object?
    //
    //  @todo
    //      because the iterators are not pushed to a stack, we will have a memory
    //      leak if the statements inside the loop crash, and the delete_itertor
    //      callback does not get called. Is this a serious possibility?
    return new Iterator(var);
}

/**
 *  Tell the handler that a loop is completed
 *  @param  userdata        pointer to user-supplied data
 *  @param  iterator        pointer to the iterator created with smart_tpl_delete_iterator
 */
void smart_tpl_delete_iterator(void *userdata, void *iterator)
{
    // cast to iterator
    auto *iter = (Iterator *)iterator;

    // destruct it
    delete iter;
}

/**
 *  Check if we can continue iterating over variable and set the magic key to the next value
 *  @param  userdata        pointer to user-supplied data
 *  @param  iterator        pointer to the iterator returned by smart_tpl_create_iterator
 *  @return                 1 if we can continue iterating, 0 otherwise
 */
int smart_tpl_valid_iterator(void *userdata, void *iterator)
{
    // cast to iterator
    auto *iter = (Iterator *)iterator;

    // check it
    return iter->valid();
}

/**
 *  Retrieve the iterator key
 *  @param  userdata        pointer to user-supplied data
 *  @param  iterator        pointer to the iterator returned by smart_tpl_create_iterator
 *  @return                 pointer to the current key object
 */
void *smart_tpl_iterator_key(void *userdata, void *iterator)
{
    // cast to iterator
    auto *iter = (Iterator *)iterator;

    // ask the iterator
    return iter->key();
}

/**
 *  Retrieve the iterator value
 *  @param  userdata        pointer to user-supplied data
 *  @param  iterator        pointer to the iterator returned by smart_tpl_create_iterator
 *  @return                 pointer to the current value object
 */
void *smart_tpl_iterator_value(void *userdata, void *iterator)
{
    // cast to iterator
    auto *iter = (Iterator *)iterator;
    
    // ask the iterator
    return iter->value();
}

/**
 *  Move to the next iterator value
 *  @param  userdata        pointer to user-supplied data
 *  @param  iterator        pointer to the iterator returned by smart_tpl_create_iterator
 */
void smart_tpl_iterator_next(void *userdata, void *iterator)
{
    // cast to iterator
    auto *iter = (Iterator *)iterator;

    // tell the iterator
    iter->next();
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
    return result ? result : &EmptyValue::get();
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
    return result ? result : EmptyValue::get().toString();
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
int smart_tpl_to_boolean(void *userdata, void *variable)
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

/**
 *  Retrieve the modifier by name
 *  @param userdata       pointer to user-supplied data
 *  @param name           name of the modifier the caller wants
 *  @param size           length of the name that the caller wants
 *  @return               A pointer to the modifier, or a nullptr if it wasn't found
 */
void* smart_tpl_modifier(void *userdata, const char *name, size_t size)
{
    // convert to Handler
    auto *handler = (Handler *)userdata;

    // Lookup and return the modifier in the Handler
    return handler->modifier(name, size);
}

/**
 *  Apply a modifier from smart_tpl_modifier on a value
 *  @param userdata       pointer to user-supplied data
 *  @param modifier_ptr   pointer to the modifier that should be applied
 *  @param variable       pointer to a value that we should apply the modifier on
 */
void* smart_tpl_modify_variable(void *userdata, void *modifier_ptr, void *variable)
{
    // In case the modifier is a nullptr just return the original value
    if (modifier_ptr == nullptr || variable == nullptr) return variable;

    // convert to the Modifier
    auto *modifier = (Modifier*) modifier_ptr;

    // convert to the Value object
    auto *value = (Value*) variable;

    // Actually modify the value
    auto variant = modifier->modify(value);

    // Convert the variant to a pointer so we can actually return it from C
    auto *output = new Variant(variant);

    // Give it to our handler so he can manage the Variant pointer
    auto *handler = (Handler *)userdata;
    handler->manageValue(output);

    return output;
}

/**
 *  Apply a modifier on a numeric type
 *  @param userdata     pointer to user-supplied data
 *  @param modifier     pointer to the modifier that should be applied
 *  @param value        the numeric type that should go through the modifier
 *  @todo Actually start using this method
 */
void* smart_tpl_modify_numeric(void *userdata, void *modifier, long value)
{
    return nullptr;
}

/**
 *  Apply a modifier on a string
 *  @param userdata     pointer to user-supplied data
 *  @param modifier     pointer to the modifier that should be applied
 *  @param value        the string that should be modified
 *  @param size         the length of value
 *  @todo Actually start using this method
 */
void* smart_tpl_modify_string(void *userdata, void *modifier, const char *value, size_t size)
{
    return nullptr;
}

/**
 *  Assign a numeric value to a local variable
 *  @param userdata        pointer to user-supplied data
 *  @param key             the key we would like to assign it to
 *  @param keysize         the size of key
 *  @param value           the numeric value we would like to assign
 */
void smart_tpl_assign_numeric(void *userdata, const char *key, size_t keysize, long value)
{
    // Convert userdata to our Handler
    auto handler = (Handler *) userdata;

    // Assign numeric value to key
    handler->assign(key, keysize, value);
}

/**
 *  Assign a boolean value to a local variable
 *  @param userdata             pointer to user-supplied data
 *  @param key                  the key we would like to assign it to
 *  @param keysize              the size of key
 *  @param boolean              the boolean value
 */
void smart_tpl_assign_boolean(void *userdata, const char *key, size_t keysize, int boolean)
{
    // Convert userdata to our Handler
    auto handler = (Handler *) userdata;

    // Assign boolean to key
    handler->assign(key, keysize, boolean != 0);
}

/**
 *  Assign a string value to a local variable
 *  @param userdata             pointer to user-supplied data
 *  @param key                  the key we would like to assign it to
 *  @param keysize              the size of key
 *  @param buf                  the string we would like to assign
 *  @param buf_size             the size of buf
 */
void smart_tpl_assign_string(void *userdata, const char *key, size_t keysize, const char *buf, size_t buf_size)
{
    // Convert userdata to our Handler
    auto handler = (Handler *) userdata;

    // Assign value to key
    handler->assign(key, keysize, std::string(buf, buf_size));
}

/**
 *  Assign a variable to a local variable
 *  @param userdata             pointer to user-supplied data
 *  @param key                  the key we would like to assign it to
 *  @param keysize              the size of key
 *  @param variable             the variable object we would like to assign
 */
void smart_tpl_assign(void *userdata, const char *key, size_t keysize, void *variable)
{
    // Convert userdata to our Handler
    auto handler = (Handler *) userdata;

    // Convert value to type Value
    auto value = (Value *) variable;

    // Assign value to key
    handler->assign(key, keysize, value);
}

/**
 *  Compares 2 c strings
 *  @param userdata           Pointer to user-supplied data
 *  @param a
 *  @param a_len              Length of a
 *  @param b
 *  @param b_len              Length of b
 *  This method is just here to avoid having to rewrite the way CCode writes strings
 *  which is "string",6. And it makes comparing strings from libjit a lot easier.
 */
int smart_tpl_strcmp(void *userdata, const char *a, size_t a_len, const char *b, size_t b_len)
{
    // If we aren't the same size to begin with we might as well just error out already
    if (a_len != b_len) return -1;

    // If we didn't return yet we are both the same length, if we're both 0 we're equal!
    else if (a_len == 0) return 0;

    // Pfft, we still don't know if we're equal, let's just ask strncmp() then
    return strncmp(a, b, a_len);
}

/**
 *  End namespace
 */
}}