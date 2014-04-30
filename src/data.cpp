/**
 *  Data.cpp
 *
 *  Implementation file for the Data class
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */
#include "includes.h"

/**
 *  Namespace
 */
namespace SmartTpl {

static ToUpperModifier toupper;
static ToLowerModifier tolower;

/**
 *  Constructor
 */
Data::Data()
{
    // register two built-in modifiers
    modifier("toupper", &toupper);
    modifier("tolower", &tolower);
}

/**
 *  Assign data
 *  @param  name        Name of the variable
 *  @param  value       Value of the variable
 *  @return Data        Same object for chaining
 */
Data &Data::assign(const char *name, const std::string &value)
{
    // append variable
    _variables[name] = std::unique_ptr<Value>(new StringValue(value));

    // allow chaining
    return *this;
}

/**
 *  Assign data
 *  @param  name        Name of the variable
 *  @param  value       Value of the variable
 *  @return Data        Same object for chaining
 */
Data &Data::assign(const char *name, numeric_t value)
{
    // append variable
    _variables[name] = std::unique_ptr<Value>(new NumericValue(value));

    // allow chaining
    return *this;
}

/**
 * Assign data
 * @param  name         Name of the variable
 * @param  value        Value of the variable
 * @return Data         Same object for chaining
 */
Data &Data::assign(const char *name, Value* value)
{
    // append variable
    _custom_variables[name] = value;

    // allow chaining
    return *this;
}

Data &Data::callback(const char *name, const std::function<Variant()> &lambda)
{
    _callbacks[name] = lambda;
    // allow chaining
    return *this;
}

/**
 *  Assign a modifier
 *  @param  name        Name of the modifier
 *  @param  modifier    Pointer to the modifier object
 *  @return Data
 */
Data &Data::modifier(const char *name, Modifier* modifier)
{
    // assign variable
    _modifiers[name] = modifier;

    // allow chaining
    return *this;
}

/**
 *  Retrieve a variable pointer by name
 *  @param  name        the name
 *  @param  size        size of the name
 *  @return Value*
 */
Value *Data::value(const char *name, size_t size) const
{
    // first look through the 'custom' variables
    auto c_iter = _custom_variables.find(name);
    if (c_iter != _custom_variables.end()) return c_iter->second;

    // if we didn't find it yet let's look in _variables
    auto iter = _variables.find(name);
    if (iter != _variables.end()) return iter->second.get();

    // return nullptr if we found nothing
    return nullptr;
}

/**
 *  Retrieve a pointer to a modifier
 *  @param  name        Name of the modifier
 *  @param  size        Length of the name
 *  @return Modifier*
 */
Modifier *Data::modifier(const char* name, size_t size) const
{
    // check if the modifier is listed
    auto iter = _modifiers.find(name);
    if (iter == _modifiers.end()) return nullptr;

    // get the pointer
    return iter->second;
}

const std::function<Variant()> *Data::callback(const char *name, size_t size) const
{
    auto iter = _callbacks.find(name);
    if (iter != _callbacks.end()) return &iter->second;
    return nullptr;
}

/**
 *  End namespace
 */
}

