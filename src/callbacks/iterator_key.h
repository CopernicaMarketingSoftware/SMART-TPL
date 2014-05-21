/**
 *  IteratorKey.h
 *
 *  Signature of the iterator_key callback. This is a callback that will call back
 *  to the native function smart_tpl_iterator_key(void*,void*);
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
class IteratorKeyCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    IteratorKeyCallback()
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr }, jit_type_void_ptr)
    {
    }

    /**
     *  Destructor
     */
    virtual ~IteratorKeyCallback() {}
};

/**
 *  End namespace
 */
}}