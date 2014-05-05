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
    {
        // parameters that are supported
        jit_type_t params[] = {
            jit_type_void_ptr,
            jit_type_void_ptr
        };

        // create the signature
        _signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void, params, sizeof(params)/sizeof(jit_type_t), 1);
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