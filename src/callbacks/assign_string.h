/**
 *  AssignString.h
 *
 *  Signature of the assign_string callback. This is a callback that will call back
 *  to the native function smart_tpl_assign_string(void*, const char*, size_t, const char*, size_t);
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
class AssignStringCallback : public AssignBaseCallback
{
public:
    /**
     *  Constructor
     */
    AssignStringCallback()
    : AssignBaseCallback(jit_type_void_ptr, jit_type_ulong)
    {
    }

    /**
     *  Destructor
     */
    virtual ~AssignStringCallback() {}
};

/**
 *  End namespace
 */
}}