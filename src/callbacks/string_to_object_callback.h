/**
 *  String_to_object_callback.h
 *
 *  Callback that accepts a string and outputs a void pointer, which is not too
 *  uncommon. Instead of subclassing this purely for a new name, typedef it.
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
class StringToObjectCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    StringToObjectCallback()
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr, jit_type_sys_ulonglong }, jit_type_void_ptr) {}

    /**
     *  Destructor
     */
    virtual ~StringToObjectCallback()
    {
    }
};

/**
 *  End namespace
 */
}}