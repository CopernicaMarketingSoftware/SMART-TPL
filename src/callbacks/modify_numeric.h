/**
 *  Modify_Numeric.h
 *
 *  Signature of the modify numeric callback. This is a callback that will call back
 *  to the native function smart_tpl_modify_numeric(void *, void *, long);
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
class ModifyNumericCallback
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
    ModifyNumericCallback()
    {
        // parameters that are supported
        jit_type_t params[3] = {
            jit_type_void_ptr,
            jit_type_void_ptr,
            jit_type_long
        };

        // create the signature
        _signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void_ptr, params, 3, 1);
    }

    /**
     *  Destructor
     */
    virtual ~ModifyNumericCallback() {}

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

