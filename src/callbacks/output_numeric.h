/**
 *  Output_Numeric.h
 *
 *  Signature of the output numeric callback. This is a callback that will call back
 *  to the native function smart_tpl_output_numeric(void *, int64_t);
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
class OutputNumericCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    OutputNumericCallback()
    : BaseCallback({ jit_type_void_ptr, jit_type_sys_longlong })
    {
    }

    /**
     *  Destructor
     */
    virtual ~OutputNumericCallback() {}
};

/**
 *  End namespace
 */
}}