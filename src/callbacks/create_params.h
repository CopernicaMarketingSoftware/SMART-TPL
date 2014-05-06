/**
 *  Create_Params.h
 *
 *  Signature of the create_params callback. This is a callback that will call back
 *  to the native function smart_tpl_create_params(void*)
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
class CreateParamsCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    CreateParamsCallback()
    {
        // parameters that are supported
        jit_type_t params[] = {
            jit_type_void_ptr,
        };

        // create the signature
        _signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void_ptr, params, sizeof(params)/sizeof(jit_type_t), 1);
    }

    /**
     *  Destructor
     */
    virtual ~CreateParamsCallback() {}
};

/**
 *  End namespace
 */
}}