/**
 *  VariantValue.cpp
 *
 *  Implementation of the VariantValue class
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */
#include "includes.h"

/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Create a new iterator that allows you to iterate over the subvalues
 *  feel free to return nullptr from here in case memberCount returns 0
 *  as this method won't ever get called in that case anyway.
 *
 *  @return Newly allocated Iterator
 */
Iterator *VariantValue::iterator() const
{
    // In case we're a vector we'll return a vector iterator
    if (_value->type() == Variant::ValueType::ValueVectorType) return new Internal::VectorIterator(*_value);

    // In case we're a map we'll return a map iterator
    if (_value->type() == Variant::ValueType::ValueMapType) return new Internal::MapIterator(*_value);

    // In case we're neither a map or a vector we'll just not return a iterator..
    return nullptr;
}

/**
 *  End namespace
 */
}