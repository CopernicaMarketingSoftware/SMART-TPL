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
SignatureCallback Callbacks::_write({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_ulonglong });
SignatureCallback Callbacks::_output({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_ulonglong });
SignatureCallback Callbacks::_output_numeric({ jit_type_void_ptr, jit_type_sys_longlong });
SignatureCallback Callbacks::_member({ jit_type_void_ptr, jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_longlong }, jit_type_void_ptr);
SignatureCallback Callbacks::_member_at({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_ulonglong }, jit_type_void_ptr);
SignatureCallback Callbacks::_create_iterator({ jit_type_void_ptr, jit_type_void_ptr }, jit_type_void_ptr);
SignatureCallback Callbacks::_delete_iterator({ jit_type_void_ptr, jit_type_void_ptr });
SignatureCallback Callbacks::_valid_iterator({ jit_type_void_ptr, jit_type_void_ptr }, jit_type_sys_bool);
SignatureCallback Callbacks::_iterator_key({ jit_type_void_ptr, jit_type_void_ptr }, jit_type_void_ptr);
SignatureCallback Callbacks::_iterator_value({ jit_type_void_ptr, jit_type_void_ptr }, jit_type_void_ptr);
SignatureCallback Callbacks::_iterator_next({ jit_type_void_ptr, jit_type_void_ptr });
SignatureCallback Callbacks::_variable({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_ulonglong }, jit_type_void_ptr);
SignatureCallback Callbacks::_toString({ jit_type_void_ptr, jit_type_void_ptr }, jit_type_void_ptr);
SignatureCallback Callbacks::_toNumeric({ jit_type_void_ptr, jit_type_void_ptr }, jit_type_sys_longlong);
SignatureCallback Callbacks::_toDouble({ jit_type_void_ptr, jit_type_void_ptr }, jit_type_float64);
SignatureCallback Callbacks::_toBoolean({ jit_type_void_ptr, jit_type_void_ptr }, jit_type_sys_bool);
SignatureCallback Callbacks::_size({ jit_type_void_ptr, jit_type_void_ptr }, jit_type_sys_ulonglong);
SignatureCallback Callbacks::_modifier({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_ulonglong }, jit_type_void_ptr);
SignatureCallback Callbacks::_modify_variable({ jit_type_void_ptr, jit_type_void_ptr, jit_type_void_ptr, jit_type_void_ptr }, jit_type_void_ptr);
SignatureCallback Callbacks::_create_params({ jit_type_void_ptr, jit_type_sys_ulonglong }, jit_type_void_ptr);
SignatureCallback Callbacks::_params_append_numeric({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_longlong });
SignatureCallback Callbacks::_params_append_double({ jit_type_void_ptr, jit_type_void_ptr, jit_type_float64 });
SignatureCallback Callbacks::_params_append_string({ jit_type_void_ptr, jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_ulonglong });
SignatureCallback Callbacks::_params_append_boolean({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_bool });
SignatureCallback Callbacks::_delete_params({ jit_type_void_ptr, jit_type_void_ptr });
SignatureCallback Callbacks::_strcmp({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_ulonglong, jit_type_void_ptr, jit_type_sys_ulonglong }, jit_type_sys_bool);
SignatureCallback Callbacks::_assign({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_ulonglong, jit_type_void_ptr });
SignatureCallback Callbacks::_assign_boolean({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_ulonglong, jit_type_sys_bool });
SignatureCallback Callbacks::_assign_numeric({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_ulonglong, jit_type_sys_longlong });
SignatureCallback Callbacks::_assign_double({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_ulonglong, jit_type_float64 });
SignatureCallback Callbacks::_assign_string({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_ulonglong, jit_type_void_ptr, jit_type_sys_ulonglong });
SignatureCallback Callbacks::_mark_failed({ jit_type_void_ptr });

/**
 *  A static empty value
 */
VariantValue                _empty;

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
 *  @param  escape          Whether we should be escaping or not
 */
void smart_tpl_output(void *userdata, const void *variable, int escape)
{
    // convert the userdata to a handler object
    auto *handler = (Handler *)userdata;

    // convert the variable to a variable object
    auto *var = (const Value *)variable;

    // output the variable
    handler->output(var, escape != 0);
}

/**
 *  Function to output a numeric value
 *  @param  userdata       pointer to user-supplied data
 *  @param  number         the number to output
 */
void smart_tpl_output_numeric(void *userdata, numeric_t number)
{
    // Convert the userdata to our handler object
    auto *handler = (Handler*) userdata;

    // Call the output numeric method on the handler with our number
    handler->outputNumeric(number);
}

/**
 *  Retrieve a pointer to a member
 *  @param  userdata        pointer to user-supplied data
 *  @param  variable        pointer to variable
 *  @param  name            name of the variable
 *  @param  size            size of the variable
 *  @return                 pointer to a new variable
 */
const void *smart_tpl_member(void *userdata, const void *variable, const char *name, size_t size)
{
    // convert the variable to a variable object
    auto *var = (const Value *)variable;

    // fetch the member
    auto member = var->member(name, size);

    // Allocate it on the heap so we can return the pointer to it
    auto *output = new VariantValue(member);

    // Give the pointer to our handler so he can manage the Variant pointer
    auto *handler = (Handler *) userdata;
    handler->manageValue(output);

    // return the output
    return output;
}

/**
 *  Retrieve a pointer to a member at a certain position
 *  @param  userdata        pointer to user-supplied data
 *  @param  variable        pointer to variable
 *  @param  position        what position would we like
 *  @return                 pointer to a new variable
 */
const void* smart_tpl_member_at(void* userdata, const void* variable, size_t position)
{
    // convert the variable to a value object
    auto *var = (const Value *)variable;

    // fetch the member
    auto member = var->member(position);

    // Allocate it on the heap so we can return the pointer to it
    auto *output = new VariantValue(member);

    // Give the pointer to our handler so he can manage the Variant pointer
    auto *handler = (Handler *) userdata;
    handler->manageValue(output);

    // return the output
    return output;
}

/**
 *  Tell the handler that we are starting a new loop
 *  @param  userdata        pointer to user-supplied data
 *  @param  variable        pointer to the variable that is being iterated
 */
void *smart_tpl_create_iterator(void *userdata, const void *variable)
{
    // cast to actual value object
    auto *var = (const Value *)variable;

    // construct a new iterator
    auto *iter = new Iterator(var);

    // cast userdata to our handler
    auto *handler = (Handler *)userdata;

    // make our newly allocated iterator managed
    handler->manageIterator(iter);

    // return our iterator
    return iter;
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
    //delete iter; // @todo as we're making these things managed now using std::unique_ptrs we should just get rid of these callbacks
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
const void *smart_tpl_iterator_key(void *userdata, void *iterator)
{
    // cast to iterator
    auto *iter = (Iterator *)iterator;

    // Ask the iterator
    auto key = iter->key();

    // Allocate it on the heap so we can return the pointer to it
    auto *output = new VariantValue(key);

    // Return the pointer
    return output;
}

/**
 *  Retrieve the iterator value
 *  @param  userdata        pointer to user-supplied data
 *  @param  iterator        pointer to the iterator returned by smart_tpl_create_iterator
 *  @return                 pointer to the current value object
 */
const void *smart_tpl_iterator_value(void *userdata, void *iterator)
{
    // cast to iterator
    auto *iter = (Iterator *)iterator;

    // fetch the value from the iterator
    auto value = iter->value();

    // Allocate it on the heap so we can return the pointer to it
    auto *output = new VariantValue(value);

    // return the output
    return output;
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
const void *smart_tpl_variable(void *userdata, const char *name, size_t size)
{
    // convert the userdata to a handler object
    auto *handler = (Handler *)userdata;

    // convert to a variable
    auto *result = handler->variable(name, size);

    // ensure that we always return an object
    return result ? result : &_empty;
}

/**
 *  Retrieve the string representation of a variable
 *  @param  userdata        pointer to user-supplied data
 *  @param  variable        pointer to variable
 *  @return                 string buffer
 */
const char *smart_tpl_to_string(void *userdata, const void *variable)
{
    // convert the variable to a value object
    auto *var = (const Value *) variable;

    // convert to string
    auto result = var->toString();

    // return the string
    return result.c_str();
}

/**
 *  Retrieve the numeric representation of a variable
 *  @param  userdata        pointer to user-supplied data
 *  @param  variable        pointer to variable
 *  @return                 numeric value
 */
numeric_t smart_tpl_to_numeric(void *userdata, const void *variable)
{
    // convert the variable to a value object
    auto *var = (const Value *)variable;

    // convert to numeric
    return var->toNumeric();
}

/**
 *  Retrieve the floating point representation of a variable
 *  @param  userdata       pointer to user-supplied data
 *  @param  variable       pointer to a variable
 *  @return                floating point value
 */
double smart_tpl_to_double(void *userdata, const void *variable)
{
    // convert the variable to a value object
    auto *var = (const Value *)variable;

    // convert to floating point
    return var->toDouble();
}

/**
 *  Retrieve the boolean representation of a variable
 *  @param  userdata        pointer to user-supplied data
 *  @param  variable        pointer to variable
 *  @return                 numeric value
 */
int smart_tpl_to_boolean(void *userdata, const void *variable)
{
    // convert the variable to a value object
    auto *var = (const Value *)variable;

    // convert to bool
    return var->toBoolean();
}

/**
 *  Retrieve the length of the string representation of a variable
 *  @param  userdata        pointer to user-supplied data
 *  @param  variable        pointer to variable
 *  @return                 string length
 */
size_t smart_tpl_size(void *userdata, const void *variable)
{
    // convert the variable to a value object
    auto *var = (const Value *)variable;

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
    auto *handler = (Handler *) userdata;

    // Lookup and return the modifier in the Handler
    return handler->modifier(name, size);
}

/**
 *  Apply a modifier from smart_tpl_modifier on a value
 *  @param userdata       pointer to user-supplied data
 *  @param variable       pointer to a value that we should apply the modifier on
 *  @param modifier_ptr   pointer to the modifier that should be applied
 *  @param parameters     pointer to a Parameters object
 */
const void* smart_tpl_modify_variable(void *userdata, const void *variable, void *modifier_ptr, void *parameters)
{
    // In case the modifier or the input is a nullptr just return the original value
    if (modifier_ptr == nullptr || variable == nullptr) return variable;

    // convert to the Modifier
    auto *modifier = (Modifier *) modifier_ptr;

    // convert to the Variant object
    auto *value = (const VariantValue *) variable;

    // convert to Parameters object
    auto *params_ptr = (SmartTpl::Parameters *) parameters;

    // If params_ptr is valid use that one, create an empty one of the stack otherwise
    SmartTpl::Parameters params = (params_ptr) ? *params_ptr : SmartTpl::Parameters();

    // Actually modify the value
    auto variant = modifier->modify(*value, params);

    // If we both have the same shared pointer to modifier probably just returned the input
    // Returning the input value is faster and safer from this point on
    if (variant == *value) return value;

    // Convert the variant to a pointer so we can actually return it from C
    auto *output = new VariantValue(variant);

    // Give it to our handler so he can manage the Variant pointer
    auto *handler = (Handler *) userdata;
    handler->manageValue(output);

    return output;
}

/**
 *  Assign a numeric value to a local variable
 *  @param userdata        pointer to user-supplied data
 *  @param key             the key we would like to assign it to
 *  @param keysize         the size of key
 *  @param value           the numeric value we would like to assign
 */
void smart_tpl_assign_numeric(void *userdata, const char *key, size_t keysize, numeric_t value)
{
    // Convert userdata to our Handler
    auto handler = (Handler *) userdata;

    // Assign numeric value to key
    handler->assign(key, keysize, value);
}

/**
 *  Assign a floating point value to a local variable
 *  @param userdata        pointer to user-supplied data
 *  @param key             the key we would like to assign it to
 *  @param keysize         the size of key
 *  @param value           the floating point value we would like to assign
 */
void smart_tpl_assign_double(void *userdata, const char *key, size_t keysize, double value)
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
void smart_tpl_assign(void *userdata, const char *key, size_t keysize, const void *variable)
{
    // Convert userdata to our Handler
    auto handler = (Handler *) userdata;

    // Convert value to type Variant
    auto *variant = (const VariantValue *) variable;

    // Assign value to key
    handler->assign(key, keysize, variant);
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
 *  Create a Parameters object
 *  @param  userdata         Pointer to user-supplied data
 *  @param  parameters_count The amount of parameters to reserve ahead of time
 *  @return Pointer to a new SmartTpl::Parameters object
 */
void *smart_tpl_create_params(void *userdata, size_t parameters_count)
{
    // Important that we create the public Parameters here and not the internal one
    auto *params = new SmartTpl::Parameters();

    // We reserve the parameters_count as this is known on compile time
    params->reserve(parameters_count);

    // cast userdata to our handler
    auto *handler = (Handler *)userdata;

    // make our newly allocated iterator managed
    handler->manageParameters(params);

    // Return the pointer to the parameters
    return params;
}

/**
 *  Append a numeric value to the parameters
 *  @param  userdata       Pointer to user-supplied data
 *  @param  parameters     Pointer to a SmartTpl::Parameters object
 *  @param  value          The numeric value to append
 */
void smart_tpl_params_append_numeric(void *userdata, void *parameters, numeric_t value)
{
    // Convert to a Parameters object
    auto *params = (SmartTpl::Parameters *) parameters;

    // Add the numeric value
    params->emplace_back(value);
}

/**
 *  Append a floating point value to the parameters
 *  @param  userdata        Pointer to user-supplied data
 *  @param  parameters      Pointer to a SmartTpl::Parameters object
 *  @param  value           The floating point value to append
 */
void smart_tpl_params_append_double(void *userdata, void *parameters, double value)
{
    // Convert to a Parameters object
    auto *params = (SmartTpl::Parameters *) parameters;

    // Add the numeric value
    params->emplace_back(value);
}

/**
 *  Append a string value to the parameters
 *  @param  userdata      Pointer to user-supplied data
 *  @param  parameters    Pointer to a SmartTpl::Parameters object
 *  @param  buf           String we would like to append
 *  @param  len           Size of buf
 */
void smart_tpl_params_append_string(void *userdata, void *parameters, const char *buf, size_t len)
{
    // Convert to a Parameters object
    auto *params = (SmartTpl::Parameters *) parameters;

    // Add the string value
    params->emplace_back(buf, len);
}

/**
 *  Append a boolean value to the parameters
 *  @param  userdata       Pointer to user-supplied data
 *  @param  parameters     Pointer to a SmartTpl::Parameters object
 *  @param  boolean        A 'boolean' value, 0 is false, everything else is true (C-style)
 */
void smart_tpl_params_append_boolean(void *userdata, void *parameters, int boolean)
{
    // Convert to a Parameters object
    auto *params = (SmartTpl::Parameters *) parameters;

    // Add the boolean value to the parameters
    params->emplace_back(boolean != 0);
}

/**
 *  Used to deconstruct the Parameters object
 *  @param  userdata        Pointer to user-supplied data
 *  @param  parameters      Pointer to a SmartTpl::Parameters object
 */
void smart_tpl_delete_params(void *userdata, void *parameters)
{
    // Convert to a Parameters object
    auto *params = (SmartTpl::Parameters *) parameters;

    // Deconstruct the Parameters
    //delete params;
}

/**
 *  Used to set the handler into failed mode so we know we have to throw a runtime error
 *  @param  userdata        Pointer to user-supplied data
 */
void smart_tpl_mark_failed(void *userdata)
{
    // Convert userdata to our Handler
    auto *handler = (Handler *) userdata;

    // Set the handler into failed mode
    handler->markFailed();
}

/**
 *  Used to throw an actual C++ exception from the runtime, don't do this from the jitted code
 *  as you won't be able to actually catch it from there. This only has the return type int so
 *  we can include it inside if statements etc
 *  @param  userdata        Pointer to user-supplied data
 */
int smart_tpl_throw_exception(void* userdata)
{
    throw std::runtime_error("A runtime error occured :(");
}

/**
 *  End namespace
 */
}}