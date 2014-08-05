/**
 *  ToDouble.h
 *
 *  Signature of the to_double callback. This is a callback that will call back
 *  to the native function smart_tpl_to_double(void *, void *);
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
class ToDoubleCallback : public VariableBaseCallback
{
public:
    /**
     *  Constructor
     */
    ToDoubleCallback()
    : VariableBaseCallback(jit_type_float64)
    {
    }

    /**
     *  Destructor
     */
    virtual ~ToDoubleCallback() {}
};

/**
 *  End namespace
 */
}}