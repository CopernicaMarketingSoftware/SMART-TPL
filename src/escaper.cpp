/**
 *  Escaper.cpp
 *
 *  Implementation of the Escaper class
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include "includes.h"

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Map which maps the human readable names to the actual escapers
 */
static std::map<std::string, Escaper*> _escapers;

/**
 *  Constructor, the escaper will automatically register itself in _escapers
 *  @param  name     The human readable name it should use to register itself
 */
Escaper::Escaper(const std::string &name)
{
    _escapers[name] = this;
}

/**
 *  Create static instances of all known escapers
 */
static NullEscaper _null;
static HtmlEscaper _html;

/**
 *  Return an Escaper based on the encoding
 *  @param  encoding     The human readable name of the Escaper
 *  @return A new Escape object, which you should manage yourself
 */
Escaper* Escaper::get(const std::string &encoding)
{
    // Look for the escaper with name encoding in _escapers
    auto iter = _escapers.find(encoding);

    // Did we find it? Yes? Return it
    if (iter != _escapers.end()) return iter->second;

    // We didn't find it? That's too bad, let's return the null escaper
    return &_null;
}

/**
 *  End namespace
 */
}}