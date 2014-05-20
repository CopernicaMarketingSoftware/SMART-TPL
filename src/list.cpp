/**
 *  List.h
 *
 *  Class that represents a list with values
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
Iterator *ListValue::iterator() const
{
    return new Internal::ListIterator(this);
}


/**
 *  End namespace
 */
}