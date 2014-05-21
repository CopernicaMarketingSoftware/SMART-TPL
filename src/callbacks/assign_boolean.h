/**
 *  AssignBoolean.h
 *
 *  Signature of the assign_boolean callback. This is a callback that will call back
 *  to the native function smart_tpl_assign_boolean(void*, const char*, size_t, int);
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
class AssignBooleanCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    AssignBooleanCallback()
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr, jit_type_ulong, jit_type_sys_int })
    {
    }

    /**
     *  Destructor
     */
    virtual ~AssignBooleanCallback() {}
};

/**
 *  End namespace
 */
}}