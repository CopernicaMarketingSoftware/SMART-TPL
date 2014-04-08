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
class ToStringCallback
{
private:
    /**
     *  The signature
     *  @var    jit_type_t
     */
    jit_type_t _signature;
    
public:
    /**
     *  Constructor
     */
    ToStringCallback()
    {
        // parameters that are supported
        jit_type_t params[2] = {
            jit_type_void_ptr,
            jit_type_void_ptr
        };
    
        // create the signature
        _signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void_ptr, params, 2, 1);
    }
    
    /**
     *  Destructor
     */
    virtual ~ToStringCallback() {}
    
    /**
     *  Retrieve the signature
     *  @return signature
     */
    const jit_type_t &signature() const
    {
        return _signature;
    }
};

/**
 *  End namespace
 */
}

