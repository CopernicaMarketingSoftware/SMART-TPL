/**
 *  Modifier.h
 *
 *  Signature of the modifier callback. This is a callback that will call back
 *  to the native function smart_tpl_modifier(void *, const char *, size_t);
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
using ModifierCallback = StringToObjectCallback;

/**
 *  End namespace
 */
}}