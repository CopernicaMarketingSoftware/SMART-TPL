/**
 *  MapValue.cpp
 *
 *  A SmartTpl::Value which represents a map with VariantValues
 *  this is only a cpp file because the map iterator is an internal class
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */
#include "includes.h"

/**
 *  Set up namespace
 */
namespace SmartTpl {

Iterator *MapValue::iterator() const
{
    return new Internal::MapIterator(_value);
}

/**
 *  End namespace
 */
}