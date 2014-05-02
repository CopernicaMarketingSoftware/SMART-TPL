/**
 *  AssignBoolean.h
 *
 *  Signature of the assign_boolean callback. This is a callback that will call back
 *  to the native function smart_tpl_assign_boolean(void*, int, const char*, size_t);
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
class AssignBooleanCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    AssignBooleanCallback()
    {
        // parameters that are supported
        jit_type_t params[] = {
            jit_type_void_ptr,
            jit_type_sys_int,
            jit_type_void_ptr,
            jit_type_ulong
        };

        // create the signature
        _signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void, params, sizeof(params)/sizeof(jit_type_t), 1);
    }

    /**
     *  Destructor
     */
    virtual ~AssignBooleanCallback() {}
};

/**
 *  End namespace
 */
}

