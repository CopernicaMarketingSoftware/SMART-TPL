/**
 *  Params_append_boolean.h
 *
 *  Signature of the params_append_numeric callback. This is a callback that will call back
 *  to the native function smart_tpl_params_append_numeric(void *, void *, int);
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
class ParamsAppendBooleanCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    ParamsAppendBooleanCallback()
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_int })
    {
    }

    /**
     *  Destructor
     */
    virtual ~ParamsAppendBooleanCallback() {}
};

/**
 *  End namespace
 */
}}