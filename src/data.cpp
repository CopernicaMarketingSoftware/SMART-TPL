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
Data &Data::assign(const char *name, int value)
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
    _variables[name] = std::unique_ptr<Value>(value);

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
    // look up variable
    auto iter = _variables.find(name);
    if (iter == _variables.end()) return nullptr;
    
    // get the pointer
    return iter->second.get();
}

/**
 *  End namespace
 */
}

