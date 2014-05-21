/**
 *  Variable_callback.h
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
class VariableBaseCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    VariableBaseCallback(jit_type_t return_type)
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr }, return_type) {}

    /**
     *  Destructor
     */
    virtual ~VariableBaseCallback()
    {
    }
};

/**
 *  End namespace
 */
}}