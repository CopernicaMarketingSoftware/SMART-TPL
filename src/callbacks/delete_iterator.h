/**
 *  DeleteIterator.h
 *
 *  Signature of the delete_iterator callback. This is a callback that will call back
 *  to the native function smart_tpl_delete_iterator(void*,void*);
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
class DeleteIteratorCallback : public IteratorBaseCallback
{
public:
    /**
     *  Constructor
     */
    DeleteIteratorCallback()
    : IteratorBaseCallback()
    {
    }

    /**
     *  Destructor
     */
    virtual ~DeleteIteratorCallback() {}
};

/**
 *  End namespace
 */
}}