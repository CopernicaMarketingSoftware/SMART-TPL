/**
 *  Write.h
 *
 *  Signature of the write callback. This is a callback that will call back
 *  to the native function smart_tpl_write(void *, const char *data, uint64_t size);
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
class WriteCallback : public BaseCallback
{
public:
    /**
     *  Constructor
     */
    WriteCallback()
    : BaseCallback({ jit_type_void_ptr, jit_type_void_ptr, jit_type_ulong })
    {
    }

    /**
     *  Destructor
     */
    virtual ~WriteCallback() {}
};

/**
 *  End namespace
 */
}}