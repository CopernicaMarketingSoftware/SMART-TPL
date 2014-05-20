/**
 *  Map.h
 *
 *  Class that represents a map with values
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */
#include "includes.h"

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Create a new iterator that allows you to iterate over the subvalues
 *  feel free to return nullptr from here in case memberCount returns 0
 *  as this method won't ever get called in that case anyway.
 *
 *  @return Newly allocated Iterator
 */
Iterator *MapValue::iterator() const
{
    return new Internal::MapIterator(this);
}


/**
 *  End namespace
 */
}