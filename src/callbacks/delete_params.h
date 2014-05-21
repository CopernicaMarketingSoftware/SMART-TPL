/**
 *  Delete_params.h
 *
 *  Signature of the delete_params callback. This is a callback that will call back
 *  to the native function smart_tpl_delete_params(void *, void *);
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
class DeleteParamsCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    DeleteParamsCallback()
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr })
    {
    }

    /**
     *  Destructor
     */
    virtual ~DeleteParamsCallback() {}
};

/**
 *  End namespace
 */
}}