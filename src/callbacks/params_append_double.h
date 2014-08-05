/**
 *  Params_append_double.h
 *
 *  Signature of the params_append_double callback. This is a callback that will call back
 *  to the native function smart_tpl_params_append_double(void *, void *, double);
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
class ParamsAppendDoubleCallback : public ParameterAppendBaseCallback
{
public:
    /**
     *  Constructor
     */
    ParamsAppendDoubleCallback()
    : ParameterAppendBaseCallback(jit_type_float64)
    {
    }

    /**
     *  Destructor
     */
    virtual ~ParamsAppendDoubleCallback() {}
};

/**
 *  End namespace
 */
}}