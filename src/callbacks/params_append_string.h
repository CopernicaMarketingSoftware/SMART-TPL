/**
 *  Params_append_string.h
 *
 *  Signature of the params_append_string callback. This is a callback that will call back
 *  to the native function smart_tpl_params_append_string(void *, void *, char *, size_t);
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
class ParamsAppendStringCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    ParamsAppendStringCallback()
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr, jit_type_void_ptr, jit_type_ulong })
    {
    }

    /**
     *  Destructor
     */
    virtual ~ParamsAppendStringCallback() {}
};

/**
 *  End namespace
 */
}}