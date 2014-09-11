/**
 *  VectorValue.cpp
 *
 *  A SmartTpl::Value which represents a vector with VariantValues
 *  this is only a cpp file because the vector iterator is an internal class
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */
#include "includes.h"

/**
 *  Set up namespace
 */
namespace SmartTpl {

Iterator *VectorValue::iterator() const
{
    return new Internal::VectorIterator(_value);
}

/**
 *  End namespace
 */
}