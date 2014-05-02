/**
 *  Member.h
 *
 *  Signature of the member callback. This is a callback that will call back
 *  to the native function smart_tpl_member(void *, void *, const char *, uint64_t);
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class MemberCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    MemberCallback()
    {
        // parameters that are supported
        jit_type_t params[] = {
            jit_type_void_ptr,
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
    virtual ~MemberCallback() {}
};

/**
 *  End namespace
 */
}

