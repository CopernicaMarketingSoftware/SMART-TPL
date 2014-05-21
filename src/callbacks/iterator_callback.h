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
class IteratorBaseCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    IteratorBaseCallback(jit_type_t return_type = jit_type_void)
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr }, return_type) {}

    /**
     *  Destructor
     */
    virtual ~IteratorBaseCallback()
    {
    }
};

/**
 *  End namespace
 */
}}