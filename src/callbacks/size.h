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
 *  @todo Should the return type of this really be jit_type_sys_int?
 */
class SizeCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    SizeCallback()
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr }, jit_type_sys_int)
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