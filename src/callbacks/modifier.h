/**
 *  Modifier.h
 *
 *  Signature of the modifier callback. This is a callback that will call back
 *  to the native function smart_tpl_modifier(void *, const char *, size_t);
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class ModifierCallback
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
    ModifierCallback()
    {
        // parameters that are supported
        jit_type_t params[3] = {
            jit_type_void_ptr,
            jit_type_void_ptr,
            jit_type_ulong
        };
    
        // create the signature
        _signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void_ptr, params, 3, 1);
    }
    
    /**
     *  Destructor
     */
    virtual ~ModifierCallback() {}
    
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

