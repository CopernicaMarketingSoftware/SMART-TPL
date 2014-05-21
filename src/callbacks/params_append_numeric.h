/**
 *  Params_append_numeric.h
 *
 *  Signature of the params_append_numeric callback. This is a callback that will call back
 *  to the native function smart_tpl_params_append_numeric(void *, void *, long);
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
class ParamsAppendNumericCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    ParamsAppendNumericCallback()
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr, jit_type_long })
    {
    }

    /**
     *  Destructor
     */
    virtual ~ParamsAppendNumericCallback() {}
};

/**
 *  End namespace
 */
}}