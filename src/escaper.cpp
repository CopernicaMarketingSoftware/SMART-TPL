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

static NullEscaper _null;
static HtmlEscaper _html;

/**
 *  Return an Escaper based on the encoding
 *  @param  encoding     The human readable name of the Escaper
 *  @return A new Escape object, which you should manage yourself
 */
const Escaper* Escaper::get(const std::string &encoding) const
{
    if (encoding == "html") return &_html;
    else if (encoding == "raw") return &_null;
    return &_null;
}

/**
 *  End namespace
 */
}}