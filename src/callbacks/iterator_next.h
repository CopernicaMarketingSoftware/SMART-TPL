/**
 *  IteratorNext.h
 *
 *  Signature of the iterator_next callback. This is a callback that will call back
 *  to the native function smart_tpl_iterator_next(void*,void*);
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
class IteratorNextCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    IteratorNextCallback()
    {
        // parameters that are supported
        jit_type_t params[] = {
            jit_type_void_ptr,  // userdata
            jit_type_void_ptr   // iterator
        };

        // create the signature
        _signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void, params, sizeof(params)/sizeof(jit_type_t), 1);
    }

    /**
     *  Destructor
     */
    virtual ~IteratorNextCallback() {}
};

/**
 *  End namespace
 */
}}