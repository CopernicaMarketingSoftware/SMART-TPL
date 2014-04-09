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
void        smart_tpl_write(void *userdata, const char *data, int size);
void        smart_tpl_output(void *userdata, void *variable);
void       *smart_tpl_member(void *userdata, void *variable, const char *name, int size);
void       *smart_tpl_variable(void *userdata, const char *name, int size);
const char *smart_tpl_to_string(void *userdata, void *variable);
int         smart_tpl_to_numeric(void *userdata, void *variable);
int         smart_tpl_to_boolean(void *userdata, void *variable);
int         smart_tpl_size(void *userdata, void *variable);

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
    static WriteCallback _write;
    
    /**
     *  Signature of the output callback
     *  @var    OutputCallback
     */
    static OutputCallback _output;
    
    /**
     *  Signature of the member callback
     *  @var    MemberCallback
     */
    static MemberCallback _member;

    /**
     *  Signature of the variable callback
     *  @var    MemberCallback
     */
    static VariableCallback _variable;
    
    /**
     *  Signature of the function to convert a variable to a string
     *  @var    ToStringCallback
     */
    static ToStringCallback _toString;
    
    /**
     *  Signature of the function to convert a variable to a numeric value
     *  @var    ToNumericCallback
     */
    static ToNumericCallback _toNumeric;

    /**
     *  Signature of the function to convert a variable to a boolean value
     *  @var    ToBooleanCallback
     */
    static ToBooleanCallback _toBoolean;
    
    /**
     *  Signature of the function to retrieve the size/strlen of a variable
     *  @var    SizeCallback
     */
    static SizeCallback _size;
    
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
    
    /**
     *  Call the member function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  variable        Pointer to the variable
     *  @param  name            Name of the member
     *  @param  size            Size of the name
     *  @return jit_value       The new variable pointer
     */
    jit_value member(const jit_value &userdata, const jit_value &variable, const jit_value &name, const jit_value &size)
    {
        // construct the arguments
        jit_value_t args[4] = { 
            userdata.raw(), 
            variable.raw(),
            name.raw(),
            size.raw()
        };
        
        // create the instruction
        return _function->insn_call_native("smart_tpl_member", (void *)smart_tpl_member, _member.signature(), args, 4, 0);
    }

    /**
     *  Call the variable function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  name            Name of the variable
     *  @param  size            Size of the name
     *  @return jit_value       The new variable pointer
     */
    jit_value variable(const jit_value &userdata, const jit_value &name, const jit_value &size)
    {
        // construct the arguments
        jit_value_t args[3] = { 
            userdata.raw(), 
            name.raw(),
            size.raw()
        };
        
        // create the instruction
        return _function->insn_call_native("smart_tpl_variable", (void *)smart_tpl_variable, _variable.signature(), args, 3, 0);
    }
    
    /**
     *  Call the to_numeric function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  variable        Pointer to the variable
     *  @return jit_value       Numeric representation
     */
    jit_value to_numeric(const jit_value &userdata, const jit_value &variable)
    {
        // construct the arguments
        jit_value_t args[3] = { 
            userdata.raw(), 
            variable.raw()
        };
        
        // create the instruction
        return _function->insn_call_native("smart_tpl_to_numeric", (void *)smart_tpl_to_numeric, _toNumeric.signature(), args, 2, 0);
    }

    /**
     *  Call the to_boolean function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  variable        Pointer to the variable
     *  @return jit_value       Boolean representation
     */
    jit_value to_boolean(const jit_value &userdata, const jit_value &variable)
    {
        // construct the arguments
        jit_value_t args[3] = { 
            userdata.raw(), 
            variable.raw()
        };
        
        // create the instruction
        return _function->insn_call_native("smart_tpl_to_boolean", (void *)smart_tpl_to_boolean, _toBoolean.signature(), args, 2, 0);
    }

    /**
     *  Call the to_string function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  variable        Pointer to the variable
     *  @return jit_value       String representation
     */
    jit_value to_string(const jit_value &userdata, const jit_value &variable)
    {
        // construct the arguments
        jit_value_t args[3] = { 
            userdata.raw(), 
            variable.raw()
        };
        
        // create the instruction
        return _function->insn_call_native("smart_tpl_to_string", (void *)smart_tpl_to_string, _toString.signature(), args, 2, 0);
    }

    /**
     *  Call the size function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  variable        Pointer to the variable
     *  @return jit_value       String length
     */
    jit_value size(const jit_value &userdata, const jit_value &variable)
    {
        // construct the arguments
        jit_value_t args[3] = { 
            userdata.raw(), 
            variable.raw()
        };
        
        // create the instruction
        return _function->insn_call_native("smart_tpl_size", (void *)smart_tpl_size, _size.signature(), args, 2, 0);
    }
};
    
/**
 *  End of namespace
 */
}

