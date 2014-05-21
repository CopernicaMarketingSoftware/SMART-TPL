/**
 *  ToString.h
 *
 *  Signature of the to_string callback. This is a callback that will call back
 *  to the native function smart_tpl_to_string(void *, void *);
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class ToStringCallback : public VariableBaseCallback
{
public:
    /**
     *  Constructor
     */
    ToStringCallback()
    : VariableBaseCallback(jit_type_void_ptr)
    {
    }

    /**
     *  Destructor
     */
    virtual ~ToStringCallback() {}
};

/**
 *  End namespace
 */
}}