/**
 *  AssignDouble.h
 *
 *  Signature of the assign_double callback. This is a callback that will call back
 *  to the native function smart_tpl_assign_double(void *, const char *data, size_t size, double);
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
class AssignDoubleCallback : public AssignBaseCallback
{
public:
    /**
     *  Constructor
     */
    AssignDoubleCallback()
    : AssignBaseCallback(jit_type_float64)
    {
    }

    /**
     *  Destructor
     */
    virtual ~AssignDoubleCallback() {}
};

/**
 *  End namespace
 */
}}