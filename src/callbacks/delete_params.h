/**
 *  Delete_params.h
 *
 *  Signature of the delete_params callback. This is a callback that will call back
 *  to the native function smart_tpl_delete_params(void *, void *);
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
class DeleteParamsCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    DeleteParamsCallback()
    {
        // parameters that are supported
        jit_type_t params[] = {
            jit_type_void_ptr,
            jit_type_void_ptr,
        };

        // create the signature
        _signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void, params, sizeof(params)/sizeof(jit_type_t), 1);
    }

    /**
     *  Destructor
     */
    virtual ~DeleteParamsCallback() {}
};

/**
 *  End namespace
 */
}}