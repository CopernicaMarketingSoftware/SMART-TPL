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
namespace SmartTpl {

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
    {
        // parameters that are supported
        jit_type_t params[] = {
            jit_type_void_ptr,  // userdata
            jit_type_void_ptr   // iterator
        };

        // create the signature
        _signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void_ptr, params, sizeof(params)/sizeof(jit_type_t), 1);
    }

    /**
     *  Destructor
     */
    virtual ~IteratorKeyCallback() {}
};

/**
 *  End namespace
 */
}

