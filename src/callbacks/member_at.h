/**
 *  Member_At.h
 *
 *  Signature of the member_at callback. This is a callback that will call back
 *  to the native function smart_tpl_member_at(void *, void *, uint64_t);
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
class MemberAtCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    MemberAtCallback()
    {
        // parameters that are supported
        jit_type_t params[] = {
            jit_type_void_ptr,
            jit_type_void_ptr,
            jit_type_sys_int,
        };

        // create the signature
        _signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void_ptr, params, sizeof(params)/sizeof(jit_type_t), 1);
    }

    /**
     *  Destructor
     */
    virtual ~MemberAtCallback() {}
};

/**
 *  End namespace
 */
}

