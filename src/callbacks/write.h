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
namespace SmartTpl {

/**
 *  Class definition
 */
class WriteCallback : public Callback
{
public:
    /**
     *  Constructor
     */
    WriteCallback()
    {
        // parameters that are supported
        jit_type_t params[] = {
            jit_type_void_ptr,
            jit_type_void_ptr,
            jit_type_ulong
        };

        // create the signature
        _signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void, params, sizeof(params)/sizeof(jit_type_t), 1);
    }

    /**
     *  Destructor
     */
    virtual ~WriteCallback() {}
};

/**
 *  End namespace
 */
}

