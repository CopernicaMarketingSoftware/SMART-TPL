/**
 *  ValidIterator.h
 *
 *  Signature of the valid_iterator callback. This is a callback that will call back
 *  to the native function smart_tpl_valid_iterator(void*,void*);
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
class ValidIteratorCallback : public IteratorBaseCallback
{
public:
    /**
     *  Constructor
     */
    ValidIteratorCallback()
    : IteratorBaseCallback(jit_type_sys_int)
    {
    }

    /**
     *  Destructor
     */
    virtual ~ValidIteratorCallback() {}
};

/**
 *  End namespace
 */
}}