/**
 *  Output.h
 *
 *  Signature of the output callback. This is a callback that will call back
 *  to the native function smart_tpl_output(void *, void *);
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
class OutputCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    OutputCallback()
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_int })
    {
    }

    /**
     *  Destructor
     */
    virtual ~OutputCallback() {}
};

/**
 *  End namespace
 */
}}