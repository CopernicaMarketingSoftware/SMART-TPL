/**
 *  AssignString.h
 *
 *  Signature of the assign_string callback. This is a callback that will call back
 *  to the native function smart_tpl_assign_string(void*, const char*, size_t, const char*, size_t);
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
class AssignStringCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    AssignStringCallback()
    {
        // parameters that are supported
        jit_type_t params[] = {
            jit_type_void_ptr,
            jit_type_void_ptr,
            jit_type_ulong,
            jit_type_void_ptr,
            jit_type_ulong
        };

        // create the signature
        _signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void, params, sizeof(params)/sizeof(jit_type_t), 1);
    }

    /**
     *  Destructor
     */
    virtual ~AssignStringCallback() {}
};

/**
 *  End namespace
 */
}}