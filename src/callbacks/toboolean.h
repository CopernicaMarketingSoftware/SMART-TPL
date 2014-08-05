/**
 *  ToBoolean.h
 *
 *  Signature of the to_boolean callback. This is a callback that will call back
 *  to the native function smart_tpl_to_boolean(void *, void *);
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
class ToBooleanCallback : public VariableBaseCallback
{
public:
    /**
     *  Constructor
     */
    ToBooleanCallback()
    : VariableBaseCallback(jit_type_int)
    {
    }

    /**
     *  Destructor
     */
    virtual ~ToBooleanCallback() {}
};

/**
 *  End namespace
 */
}}