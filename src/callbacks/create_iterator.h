/**
 *  CreateIterator.h
 *
 *  Signature of the create_iterator callback. This is a callback that will call back
 *  to the native function smart_tpl_create_iterator(void*,void*);
 *
 *  @todo
 *      
 *      many callbacks are so similar, we can probably simplify and merge all these
 *      callback-signature classes into one or two common classes.
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
    {
        // parameters that are supported
        jit_type_t params[] = {
            jit_type_void_ptr,  // userdata
            jit_type_void_ptr   // variable
        };

        // create the signature
        _signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void_ptr, params, sizeof(params)/sizeof(jit_type_t), 1);
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