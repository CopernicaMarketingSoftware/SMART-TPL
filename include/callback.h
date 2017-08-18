/**
 *  Callback.h
 *
 *  Specific implementation of the Value class, in which the implementation
 *  is done by a callback
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Include guard
 */
#pragma once

/**
 *  Dependencies
 */
#include <functional>

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Definition of the callback
 */
using Callback = std::function<VariantValue()>;


/**
 *  End of namespace
 */
}
