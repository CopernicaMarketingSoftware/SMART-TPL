/**
 *  ToString.h
 *
 *  Signature of the to_string callback. This is a callback that will call back
 *  to the native function smart_tpl_to_string(void *, void *);
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class ToStringCallback : public Callback
{
public:
    /**
     *  Constructor
     */
    ToStringCallback()
    {
        // parameters that are supported
        jit_type_t params[] = {
            jit_type_void_ptr,
            jit_type_void_ptr
        };

        // create the signature
        _signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void_ptr, params, sizeof(params)/sizeof(jit_type_t), 1);
    }

    /**
     *  Destructor
     */
    virtual ~ToStringCallback() {}
};

/**
 *  End namespace
 */
}

