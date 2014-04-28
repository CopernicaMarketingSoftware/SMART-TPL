/**
 *  Boolean.h
 *
 *  Implementation of the BooleanValue
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include "includes.h"

/**
 *  Set up namespace
 */
namespace SmartTpl {

BooleanValue BooleanValue::_true(true);
BooleanValue BooleanValue::_false(false);

/**
 *  End namespace
 */
}