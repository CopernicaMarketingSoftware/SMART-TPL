/**
 *  Iterator_callback.h
 *
 *  Base class of all the iterator related callback methods, the signatures are
 *  always the same for these anyway. Only the return type is different sometimes.
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
class AssignBaseCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    AssignBaseCallback(jit_type_t assign_type)
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_ulonglong, assign_type }, jit_type_void) {}

    // This one is only required because strings require 2 parameters..
    AssignBaseCallback(jit_type_t assign_type, jit_type_t assign_type1)
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_ulonglong, assign_type, assign_type1 }, jit_type_void) {}

    /**
     *  Destructor
     */
    virtual ~AssignBaseCallback()
    {
    }
};

/**
 *  End namespace
 */
}}