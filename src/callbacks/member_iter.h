/**
 *  Member_Iter.h
 *
 *  Signature of the member callback. This is a callback that will call back
 *  to the native function smart_tpl_member_iter(void *, void *, const char *, size_t);
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
class MemberIterCallback
{
private:
    /**
     *  The signature
     *  @var    jit_type_t
     */
    jit_type_t _signature;

public:
    /**
     *  Constructor
     */
    MemberIterCallback()
    {
        // parameters that are supported
        jit_type_t params[4] = {
            jit_type_void_ptr,
            jit_type_void_ptr,
            jit_type_void_ptr,
            jit_type_sys_int,
        };

        // create the signature
        _signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void_ptr, params, 4, 1);
    }

    /**
     *  Destructor
     */
    virtual ~MemberIterCallback() {}

    /**
     *  Retrieve the signature
     *  @return signature
     */
    const jit_type_t &signature() const
    {
        return _signature;
    }
};

/**
 *  End namespace
 */
}

