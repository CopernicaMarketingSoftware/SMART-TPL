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
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class StrCmpCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    StrCmpCallback()
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_ulonglong, jit_type_void_ptr, jit_type_sys_ulonglong }, jit_type_sys_bool)
    {
    }

    /**
     *  Destructor
     */
    virtual ~StrCmpCallback() {}
};

/**
 *  End namespace
 */
}}