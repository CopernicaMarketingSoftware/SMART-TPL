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
namespace SmartTpl {

/**
 *  Class definition
 */
class DeleteIteratorCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    DeleteIteratorCallback()
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
    virtual ~DeleteIteratorCallback() {}
};

/**
 *  End namespace
 */
}

