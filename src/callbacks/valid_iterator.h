/**
 *  ValidIterator.h
 *
 *  Signature of the valid_iterator callback. This is a callback that will call back
 *  to the native function smart_tpl_valid_iterator(void*,void*);
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
class ValidIteratorCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    ValidIteratorCallback()
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr }, jit_type_sys_int)
    {
    }

    /**
     *  Destructor
     */
    virtual ~ValidIteratorCallback() {}
};

/**
 *  End namespace
 */
}}