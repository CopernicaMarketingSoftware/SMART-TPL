/**
 *  ToNumeric.h
 *
 *  Signature of the to_numeric callback. This is a callback that will call back
 *  to the native function smart_tpl_to_numeric(void *, void *);
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
class ToNumericCallback : public VariableBaseCallback
{
public:
    /**
     *  Constructor
     */
    ToNumericCallback()
    : VariableBaseCallback(jit_type_long)
    {
    }

    /**
     *  Destructor
     */
    virtual ~ToNumericCallback() {}
};

/**
 *  End namespace
 */
}}