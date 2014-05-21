/**
 *  Variable.h
 *
 *  Signature of the variable callback. This is a callback that will call back
 *  to the native function smart_tpl_variable(void *, const char *, uint64_t);
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
using VariableCallback = StringToObjectCallback;

/**
 *  End namespace
 */
}}