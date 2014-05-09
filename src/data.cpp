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

static Internal::ToUpperModifier         toupper;
static Internal::ToLowerModifier         tolower;
static Internal::CatModifier             cat;
static Internal::CountCharactersModifier count_characters;
static Internal::CountParagraphsModifier count_paragraphs;
static Internal::DefaultModifier         _default; // Underscore is purely because default is a keyword
static Internal::EscapeModifier          escape;
static Internal::IndentModifier          indent;
static Internal::ReplaceModifier         replace;
static Internal::Nl2brModifier           nl2br;

/**
 *  Constructor
 */
Data::Data()
{
    // register built-in modifiers
    modifier("toupper", &toupper);
    modifier("upper", &toupper);
    modifier("tolower", &tolower);
    modifier("lower", &tolower);
    modifier("cat", &cat);
    modifier("count_characters", &count_characters);
    modifier("count_paragraphs", &count_paragraphs);
    modifier("default", &_default);
    modifier("escape", &escape);
    modifier("indent", &indent);
    modifier("replace", &replace);
    modifier("nl2br", &nl2br);
}

/**
 *  Assign data
 *  @param  name        Name of the variable
 *  @param  value       Value of the variable
 *  @return Data        Same object for chaining
 */
Data &Data::assign(const char *name, const std::string &value)
{
    // construct variable
    Value *v = new StringValue(value);

    // store in the list of variables
    _variables[name] = v;

    // Make our newly allocated StringValue managed
    _managed_variables.push_back(std::unique_ptr<Value>(v));

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
    // construct variable
    Value *v = new NumericValue(value);

    // store in the list of variables
    _variables[name] = v;

    // Make our newly allocated NumericValue managed
    _managed_variables.push_back(std::unique_ptr<Value>(v));

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
    _variables[name] = value;

    // allow chaining
    return *this;
}

/**
 *  Assign a callback
 *  @param  name        Name of the variable
 *  @param  callback    Callback function
 *  @param  cache       Should we cache calls to your callback?
 *  @return Data        Same object for chaining
 */
Data &Data::callback(const char *name, const Callback &callback, bool cache)
{
    // construct variable
    Value *v = new CallbackValue(callback, cache);

    // store in the list of variables
    _variables[name] = v;

    // Make our newly allocated NumericValue managed
    _managed_variables.push_back(std::unique_ptr<Value>(v));

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
    // look it up in _variables
    auto iter = _variables.find(name);
    if (iter != _variables.end()) return iter->second;

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

/**
 *  End namespace
 */
}

