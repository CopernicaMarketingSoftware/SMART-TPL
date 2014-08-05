/**
 *  Size.h
 *
 *  Signature of the size callback. This is a callback that will call back
 *  to the native function smart_tpl_size(void *, void *);
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
class SizeCallback : public VariableBaseCallback
{
public:
    /**
     *  Constructor
     */
    SizeCallback()
    : VariableBaseCallback(jit_type_sys_ulonglong)
    {
    }

    /**
     *  Destructor
     */
    virtual ~SizeCallback() {}
};

/**
 *  End namespace
 */
}}