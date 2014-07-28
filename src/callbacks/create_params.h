/**
 *  Create_Params.h
 *
 *  Signature of the create_params callback. This is a callback that will call back
 *  to the native function smart_tpl_create_params(void*)
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
class CreateParamsCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    CreateParamsCallback()
    : BaseCallback({ jit_type_void_ptr, jit_type_ulong }, jit_type_void_ptr)
    {
    }

    /**
     *  Destructor
     */
    virtual ~CreateParamsCallback() {}
};

/**
 *  End namespace
 */
}}