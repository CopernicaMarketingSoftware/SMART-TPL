/**
 *  Modify_Variable.h
 *
 *  Signature of the modify variable callback. This is a callback that will call back
 *  to the native function smart_tpl_modify_variable(void *, void *, void *, void *);
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
class ModifyVariableCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    ModifyVariableCallback()
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr, jit_type_void_ptr, jit_type_void_ptr }, jit_type_void_ptr)
    {
    }

    /**
     *  Destructor
     */
    virtual ~ModifyVariableCallback() {}
};

/**
 *  End namespace
 */
}}