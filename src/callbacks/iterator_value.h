/**
 *  IteratorValue.h
 *
 *  Signature of the iterator_value callback. This is a callback that will call back
 *  to the native function smart_tpl_iterator_value(void*,void*);
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
class IteratorValueCallback : public IteratorBaseCallback
{
public:
    /**
     *  Constructor
     */
    IteratorValueCallback()
    : IteratorBaseCallback(jit_type_void_ptr)
    {
    }

    /**
     *  Destructor
     */
    virtual ~IteratorValueCallback() {}
};

/**
 *  End namespace
 */
}}