/**
 *  CreateIterator.h
 *
 *  Signature of the create_iterator callback. This is a callback that will call back
 *  to the native function smart_tpl_create_iterator(void*,void*);
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
class CreateIteratorCallback : public IteratorBaseCallback
{
public:
    /**
     *  Constructor
     */
    CreateIteratorCallback()
    : IteratorBaseCallback(jit_type_void_ptr)
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