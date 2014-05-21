/**
 *  CreateIterator.h
 *
 *  Signature of the create_iterator callback. This is a callback that will call back
 *  to the native function smart_tpl_create_iterator(void*,void*);
 *
 *  @todo many callbacks are so similar, we can probably simplify and merge all these
 *        callback-signature classes into one or two common classes.
 *
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
class CreateIteratorCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    CreateIteratorCallback()
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr }, jit_type_void_ptr)
    {
    }

    /**
     *  Destructor
     */
    virtual ~CreateIteratorCallback() {}
};

/**
 *  End namespace
 */
}}