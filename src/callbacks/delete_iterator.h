/**
 *  DeleteIterator.h
 *
 *  Signature of the delete_iterator callback. This is a callback that will call back
 *  to the native function smart_tpl_delete_iterator(void*,void*);
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Our signature matches with the IteratorBaseCallback, so we're just a typedef
 */
using DeleteIteratorCallback = IteratorBaseCallback;

/**
 *  End namespace
 */
}}