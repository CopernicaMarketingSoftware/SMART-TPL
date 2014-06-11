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
{
    // register built-in modifiers
    modifier("toupper", &toupper);
    modifier("upper", &toupper);
    modifier("tolower", &tolower);
    modifier("lower", &tolower);
    modifier("cat", &cat);
    modifier("count_words", &count_words);
    modifier("count_characters", &count_characters);
    modifier("count_paragraphs", &count_paragraphs);
    modifier("default", &_default);
    modifier("escape", &escape);
    modifier("indent", &indent);
    modifier("replace", &replace);
    modifier("nl2br", &nl2br);
    modifier("spacify", &spacify);
    modifier("truncate", &truncate);
    modifier("count", &count);
    modifier("ucfirst", &ucfirst);
    modifier("trim", &trim);
    modifier("regex_replace", &regex_replace);
    modifier("substr", &substr);
    modifier("strstr", &strstr);
    modifier("urlencode", &urlencode);
    modifier("urldecode", &urldecode);
    modifier("md5", &md5);
    modifier("sha1", &sha1);
    modifier("sha256", &sha256);
    modifier("sha512", &sha512);
    modifier("base64_encode", &base64_encode);
    modifier("base64_decode", &base64_decode);
}

Data::Data(const ::Variant::Value &value)
: Data()
{
    std::map<std::string, ::Variant::Value> map = value;
    for (auto iter = map.begin(); iter != map.end(); ++iter)
    {
        switch (iter->second.type()) {
            case ::Variant::ValueType::ValueNullType: assign(iter->first, nullptr); break;
            case ::Variant::ValueType::ValueBoolType: assign(iter->first, (bool) iter->second); break;
            case ::Variant::ValueType::ValueIntType:  assign(iter->first, (int) iter->second); break;
            case ::Variant::ValueType::ValueLongType: assign(iter->first, (long) iter->second); break;
            case ::Variant::ValueType::ValueDoubleType: assign(iter->first, (double) iter->second); break;
            case ::Variant::ValueType::ValueStringType: assign(iter->first, (std::string) iter->second); break;
            default: break;
        }
    }
}

/**
 * Assign data
 * @param  name         Name of the variable
 * @param  value        Value of the variable
 * @return Data         Same object for chaining
 */
Data &Data::assign(const char *name, const Variant &value)
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
    _variables[name] = std::shared_ptr<Value>(v);

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
 *  @return Variant
 */
Variant Data::value(const char *name, size_t size) const
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

