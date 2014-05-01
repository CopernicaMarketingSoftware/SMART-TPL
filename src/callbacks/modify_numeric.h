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
class ModifyNumericCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    ModifyNumericCallback()
    {
        // parameters that are supported
        jit_type_t params[] = {
            jit_type_void_ptr,
            jit_type_void_ptr,
            jit_type_long
        };

        // create the signature
        _signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void_ptr, params, sizeof(params)/sizeof(jit_type_t), 1);
    }

    /**
     *  Destructor
     */
    virtual ~ModifyNumericCallback() {}
};

/**
 *  End namespace
 */
}

