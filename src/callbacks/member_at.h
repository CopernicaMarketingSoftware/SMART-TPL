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
namespace SmartTpl { namespace Internal {

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
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr, jit_type_long }, jit_type_void_ptr)
    {
    }

    /**
     *  Destructor
     */
    virtual ~MemberAtCallback() {}
};

/**
 *  End namespace
 */
}}