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
static Internal::CountWordsModifier      count_words;
static Internal::CountCharactersModifier count_characters;
static Internal::CountParagraphsModifier count_paragraphs;
static Internal::DefaultModifier         _default; // Underscore is purely because default is a keyword
static Internal::EscapeModifier          escape;
static Internal::IndentModifier          indent;
static Internal::ReplaceModifier         replace;
static Internal::Nl2brModifier           nl2br;
static Internal::SpacifyModifier         spacify;
static Internal::TruncateModifier        truncate;
static Internal::CountModifier           count;
static Internal::EmptyModifier           empty;
static Internal::StrlenModifier          strlen;
static Internal::UcFirstModifier         ucfirst;
static Internal::TrimModifier            trim;
static Internal::RegexReplaceModifier    regex_replace;
static Internal::SubStrModifier          substr;
static Internal::StrStrModifier          strstr;
static Internal::UrlencodeModifier       urlencode;
static Internal::UrldecodeModifier       urldecode;
static Internal::Md5Modifier             md5;
static Internal::Sha1Modifier            sha1;
static Internal::Sha256Modifier          sha256;
static Internal::Sha512Modifier          sha512;
static Internal::Base64EncodeModifier    base64_encode;
static Internal::Base64DecodeModifier    base64_decode;

/**
 *  Constructor
 */
Data::Data()
: _modifiers({{"toupper",          &toupper},
              {"upper",            &toupper},
              {"tolower",          &tolower},
              {"lower",            &tolower},
              {"cat",              &cat},
              {"count_words",      &count_words},
              {"count_characters", &count_characters},
              {"count_paragraphs", &count_paragraphs},
              {"default",          &_default},
              {"escape",           &escape},
              {"indent",           &indent},
              {"replace",          &replace},
              {"nl2br",            &nl2br},
              {"spacify",          &spacify},
              {"truncate",         &truncate},
              {"count",            &count},
              {"strlen",           &strlen},
              {"empty",            &empty},
              {"ucfirst",          &ucfirst},
              {"trim",             &trim},
              {"regex_replace",    &regex_replace},
              {"substr",           &substr},
              {"strstr",           &strstr},
              {"urlencode",        &urlencode},
              {"urldecode",        &urldecode},
              {"md5",              &md5},
              {"sha1",             &sha1},
              {"sha256",           &sha256},
              {"sha512",           &sha512},
              {"base64_encode",    &base64_encode},
              {"base64_decode",    &base64_decode}}) // register built-in modifiers
{
}

/**
 *  Move constructor
 */
Data::Data(Data&& that)
: _variables(std::move(that._variables)),
  _managed_values(std::move(that._managed_values)),
  _modifiers(std::move(that._modifiers))
{
}

/**
 * Assign data
 * @param  name         Name of the variable
 * @param  value        Value of the variable
 * @return Data         Same object for chaining
 */
Data &Data::assign(const std::string &name, const VariantValue &value)
{
    // Create a copy of value and make it managed using assignManaged
    return assignManaged(name, new VariantValue(value));
}

/**
 * Assign data
 * @param  name         Name of the variable
 * @param  value        Value of the variable
 * @return Data         Same object for chaining
 */
Data &Data::assign(const std::string &name, VariantValue &&value)
{
    // Create a copy of value and make it managed using assignManaged
    return assignManaged(name, new VariantValue(std::move(value)));
}

/**
 *  Assign custom values
 *  @param  name       Name of the variable
 *  @param  value      Pointer to your custom value object
 *  @return Data       Same object for chaining
 */
Data &Data::assignValue(const std::string &name, Value *value)
{
    // append value
    _variables[name] = value;

    // allow chaining
    return *this;
}

/**
 *  Assign data that is managed by a unique pointer and keep managing it
 *  @param  name        Name of the variable
 *  @param  value       A unique pointer to a VariantValue
 *  @return Data        Same object for chaining
 */
Data &Data::assignManaged(const std::string &name, Value *value)
{
    // assigning nullptr's doesn't make sense..
    if (!value) return *this;

    // append variable
    _variables[name] = value;

    // make it managed
    _managed_values.emplace_back(value);

    // allow chaining
    return *this;
}

/**
 *  Assign data that is managed by a unique pointer and keep managing it
 *  @param  name        Name of the variable
 *  @param  value       A unique pointer to a VariantValue
 *  @return Data        Same object for chaining
 */
Data &Data::assignManaged(const std::string &name, std::shared_ptr<Value> &value)
{
    // assigning empty shared pointer doesn't make sense
    if (!value) return *this;

    // append variable
    _variables[name] = value.get();

    // make it managed
    _managed_values.emplace_back(value);

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
Data &Data::callback(const std::string &name, const Callback &callback, bool cache)
{
    // construct variable
    Value *v = new Internal::CallbackValue(callback, cache);

    // make our Value managed
    _managed_values.emplace_back(v);

    // and store in the list of variables
    _variables[name] = v;

    // allow chaining
    return *this;
}

/**
 *  Assign a modifier
 *  @param  name        Name of the modifier
 *  @param  modifier    Pointer to the modifier object
 *  @return Data
 */
Data &Data::modifier(const std::string &name, Modifier* modifier)
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
 *  @return Variant
 */
const Value *Data::value(const char *name, size_t size) const
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

