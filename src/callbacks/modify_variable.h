/**
 *  Modify_Variable.h
 *
 *  Signature of the modify variable callback. This is a callback that will call back
 *  to the native function smart_tpl_modify_variable(void *, void *, void *);
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
class ModifyVariableCallback
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
    ModifyVariableCallback()
    {
        // parameters that are supported
        jit_type_t params[3] = {
            jit_type_void_ptr,
            jit_type_void_ptr,
            jit_type_void_ptr
        };

        // create the signature
        _signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void_ptr, params, 3, 1);
    }

    /**
     *  Destructor
     */
    virtual ~ModifyVariableCallback() {}

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

