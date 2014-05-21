/**
 *  Parameter_append_callback.h
 *
 *  Base class of most of the variable related methods that simply accept 2 void
 *  pointers and return some other type. This return type can be overriden, the
 *  parameters cannot.
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
class ParameterAppendBaseCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    ParameterAppendBaseCallback(jit_type_t assign_type)
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr, assign_type }, jit_type_void) {}

    // This one is only required because strings require 2 parameters..
    ParameterAppendBaseCallback(jit_type_t assign_type, jit_type_t assign_type1)
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr, assign_type , assign_type1 }, jit_type_void) {}

    /**
     *  Destructor
     */
    virtual ~ParameterAppendBaseCallback()
    {
    }
};

/**
 *  End namespace
 */
}}