/**
 *  StrCmp.h
 *
 *  Signature of the strcmp callback. This is a callback that will call back
 *  to the native function smart_tpl_strcmp(void*,const char*,size_t,const char*,size_t);
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
class StrCmpCallback : public Callback
{
public:
    /**
     *  Constructor
     */
    StrCmpCallback()
    {
        // parameters that are supported
        jit_type_t params[] = {
            jit_type_void_ptr,
            jit_type_void_ptr,
            jit_type_sys_int,
            jit_type_void_ptr,
            jit_type_sys_int,
        };

        // create the signature
        _signature = jit_type_create_signature(jit_abi_cdecl, jit_type_sys_int, params, sizeof(params)/sizeof(jit_type_t), 1);
    }

    /**
     *  Destructor
     */
    virtual ~StrCmpCallback() {}
};

/**
 *  End namespace
 */
}

