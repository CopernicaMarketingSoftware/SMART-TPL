/**
 *  Value.cpp
 * 
 *  Default functions for Value objects. Classes that build on the Value object
 *  will default to these functions when they do not overwrite the implementations
 *  defined here.
 * 
 *  @author         David van Erkelens <david.vanerkelens@copernica.com>
 *  @copyright      2019 Copernica BV
 */

/**
 *  Dependencies
 */
#include "includes.h"

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  If this type was used in an arithmetric operation, should it then be
 *  treated as a floating point number, or as a regular integer?
 *  @return bool
 */
bool Value::arithmeticFloat() const
{
    // by default, values can not be treated as floats
    return false;
}

/**
 *  Convert the value to a string
 *  @return std::string
 */
std::string Value::toString() const 
{
    // return empty string
    return _empty;
}

/**
 *  Convert the variable to a numeric value (this is a deprecated method)
 *  @return numeric_t
 */
numeric_t Value::toNumeric() const 
{
    // zero
    return 0; 
}

/**
 *  Convert the variable to an integer value
 *  @return integer_t
 */
integer_t Value::toInteger() const 
{
    // this is an alias to toNumeric()
    return toNumeric();
}

/**
 *  Convert the variable to a boolean value
 *  @return bool
 */
bool Value::toBoolean() const 
{
    // an empty value is false
    return false;
}

/**
 *  Convert the variable to a floating point value
 *  @return double
 */
double Value::toDouble() const 
{
    // zero
    return 0.0;
}

/**
 *  Get access to the amount of members this value has
 *  @return size_t
 */
size_t Value::memberCount() const 
{
    // no members
    return 0;
}

/**
 *  Get access to a member value
 *  @param  name        name of the member
 *  @param  size        size of the name
 *  @return VariantValue
 */
VariantValue Value::member(const char *name, size_t size) const
{
    // not supported by default
    return nullptr;
}

/**
 *  Get access to a member at a certain position
 *  @param  position    Position of the item we want to retrieve
 *  @return VariantValue
 */
VariantValue Value::member(size_t position) const
{
    // not supported by default
    return nullptr;
}

/**
 *  Get access to a member at a certain position
 *  @param  position    Position of the item we want to retrieve
 *  @return VariantValue
 */
VariantValue Value::member(const Value &position) const
{
    // pass on to the position value, that value knows what to do
    return position.lookupIn(*this);
}

/**
 *  Use this value as index of another parent value
 *  @param  value       the value in which to look for this key
 *  @return VariantValue
 */
VariantValue Value::lookupIn(const Value &value) const
{
    // convert to string 
    auto key = this->toString();

    // pass on to member call
    return value.member(key.data(), key.size());
}

 /**
 *  Create a new iterator that allows you to iterate over the subvalues
 *  feel free to return nullptr if you don't want to be able to iterate
 *  over your type
 *
 *  @return Newly allocated Iterator
 */
Iterator *Value::iterator() const
{
    // no iterator
    return nullptr;
}

/**
 *  End of namespace
 */
}