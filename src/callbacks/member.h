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
namespace SmartTpl { namespace Internal {

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
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_int }, jit_type_void_ptr)
    {
    }

    /**
     *  Destructor
     */
    virtual ~MemberCallback() {}
};

/**
 *  End namespace
 */
}}