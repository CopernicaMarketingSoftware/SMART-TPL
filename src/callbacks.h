/**
 *  Callbacks.h
 *
 *  Class that is used by the JIT compiler and that represents all functions
 *  in the main SMART-TPL library that can be called from outside a template
 *  function.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Signatures of the global callback functions
 */
extern void smart_tpl_write(void *userdata, const char *data, uint64_t size);
extern void smart_tpl_output(void *userdata, void *variable);

/**
 *  Class definition
 */
class Callbacks
{
private:
    /**
     *  Pointer to the function
     *  @var    jit_function
     */
    jit_function *_function;

    /**
     *  Signature of the write callback
     *  @var    WriteCallback
     */
    WriteCallback _write;
    
    /**
     *  Signature of the output variable callback
     *  @var    OutputCallback
     */
    OutputCallback _output;
    
    
public:
    /**
     *  Constructor
     */
    Callbacks(jit_function *func) : _function(func) {}
    
    /**
     *  Destructor
     */
    virtual ~Callbacks() {}
      
    /**
     *  Call the write function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  buffer          Pointer to the buffer
     *  @param  size            Size of the buffer
     */
    void write(const jit_value &userdata, const jit_value &buffer, const jit_value size)
    {
        // construct the arguments
        jit_value_t args[3] = { 
            userdata.raw(), 
            buffer.raw(), 
            size.raw() 
        };
        
        // create the instruction
        _function->insn_call_native("smart_tpl_write", (void *)smart_tpl_write, _write.signature(), args, 3, 0);
    }
    
    /**
     *  Call the output function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  variable        Pointer to the variable
     */
    void output(const jit_value &userdata, const jit_value &variable)
    {
        // construct the arguments
        jit_value_t args[2] = { 
            userdata.raw(), 
            variable.raw()
        };
        
        // create the instruction
        _function->insn_call_native("smart_tpl_output", (void *)smart_tpl_output, _output.signature(), args, 2, 0);
    }
};
    
/**
 *  End of namespace
 */
}

