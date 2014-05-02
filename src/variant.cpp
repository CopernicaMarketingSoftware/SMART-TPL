/**
 *  Variant.cpp
 *
 *  Implementation of the Variant
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include "includes.h"

/**
 *  Set up namespace
 */
namespace SmartTpl {

Variant::Variant() : _value(new EmptyValue()) {};
Variant::Variant(const char *value) : _value(new StringValue(value)) {};
Variant::Variant(const char *value, size_t size) : _value(new StringValue(value, size)) {};
Variant::Variant(const std::string &value) : _value(new StringValue(value)) {};
Variant::Variant(numeric_t value) : _value(new NumericValue(value)) {};

/**
 *  End namespace
 */
}