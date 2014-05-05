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
void        smart_tpl_write(void *userdata, const char *data, size_t size);
void        smart_tpl_output(void *userdata, void *variable);
void       *smart_tpl_member(void *userdata, void *variable, const char *name, size_t size);
void       *smart_tpl_member_at(void *userdata, void *variable, long position);
void       *smart_tpl_create_iterator(void *userdata, void *variable);
void        smart_tpl_delete_iterator(void *userdata, void *iterator);
int         smart_tpl_valid_iterator(void *userdata, void *iterator);
void       *smart_tpl_iterator_key(void *userdata, void *iterator);
void       *smart_tpl_iterator_value(void *userdata, void *iterator);
void        smart_tpl_iterator_next(void *userdata, void *iterator);
void       *smart_tpl_variable(void *userdata, const char *name, size_t size);
const char *smart_tpl_to_string(void *userdata, void *variable);
size_t      smart_tpl_to_numeric(void *userdata, void *variable);
int         smart_tpl_to_boolean(void *userdata, void *variable);
size_t      smart_tpl_size(void *userdata, void *variable);
void*       smart_tpl_modifier(void *userdata, const char *name, size_t size);
void*       smart_tpl_modify_variable(void *userdata, void *modifier, void *variable);
void*       smart_tpl_modify_numeric(void *userdata, void *modifier, long value);
void*       smart_tpl_modify_string(void *userdata, void *modifier, const char *value, size_t size);
void        smart_tpl_assign_numeric(void *userdata, const char *key, size_t keysize, long value);
void        smart_tpl_assign_boolean(void *userdata, const char *key, size_t keysize, int boolean);
void        smart_tpl_assign_string(void *userdata, const char *key, size_t keysize, const char *buf, size_t buf_size);
void        smart_tpl_assign(void *userdata, const char *key, size_t keysize, void *variable);
int         smart_tpl_strcmp(void *userdata, const char *a, size_t a_len, const char *b, size_t b_len);

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
     *  Signature of the member_at callback
     *  @var    MemberAtCallback
     */
    static MemberAtCallback _member_at;

    /**
     *  Signature of the create-iterator callback
     *  @var CreateItereratorCallback
     */
    static CreateIteratorCallback _create_iterator;

    /**
     *  Signature of the delete-iterator callback
     *  @var DeleteItereratorCallback
     */
    static DeleteIteratorCallback _delete_iterator;

    /**
     *  Signature of the valid-iterator callback
     *  @var ValidItereratorCallback
     */
    static ValidIteratorCallback _valid_iterator;
    
    /**
     *  Signature of the iterator-key callback
     *  @var ItereratorKeyCallback
     */
    static IteratorKeyCallback _iterator_key;

    /**
     *  Signature of the iterator-value callback
     *  @var ItereratorValueCallback
     */
    static IteratorValueCallback _iterator_value;
    
    /**
     *  Signature of the iterator-next callback
     *  @var IteratorNextCallback
     */
    static IteratorNextCallback _iterator_next;

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

    /**
     *  Signature of the function to retrieve the modifier
     *  @var    ModifierCallback
     */
    static ModifierCallback _modifier;

    /**
     *  Signature of the function to modify a variable
     *  @var    ModifyVariableCallback
     */
    static ModifyVariableCallback _modify_variable;

    /**
     *  Signature of the function to modify a numeric variable
     *  @var ModifyNumericCallback
     */
    static ModifyNumericCallback _modify_numeric;

    /**
     *  Signature of the function to modify a string variable
     *  @var ModifyStringCallback
     */
    static ModifyStringCallback _modify_string;

    /**
     *  Signature of the function to compare 2 strings
     *  @var StrCmpCallback
     */
    static StrCmpCallback _strcmp;

    /**
     *  Signature of the function to assign a variable to a local variable
     *  @var AssignCallback
     */
    static AssignCallback _assign;

    /**
     *  Signature of the function to assign a boolean to a local variable
     *  @var AssignBooleanCallback
     */
    static AssignBooleanCallback _assign_boolean;

    /**
     *  Signature of the function to assign a numeric value to a local variable
     *  @var AssignNumericCallback
     */
    static AssignNumericCallback _assign_numeric;

    /**
     *  Signature of the function to assign a string to a local variable
     *  @var AssignStringCallback
     */
    static AssignStringCallback _assign_string;

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
     *  @see    smart_tpl_write
     */
    void write(const jit_value &userdata, const jit_value &buffer, const jit_value size)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(), 
            buffer.raw(), 
            size.raw() 
        };

        // create the instruction
        _function->insn_call_native("smart_tpl_write", (void *)smart_tpl_write, _write.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the output function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  variable        Pointer to the variable
     *  @see    smart_tpl_output
     */
    void output(const jit_value &userdata, const jit_value &variable)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(), 
            variable.raw()
        };

        // create the instruction
        _function->insn_call_native("smart_tpl_output", (void *)smart_tpl_output, _output.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the member function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  variable        Pointer to the variable
     *  @param  name            Name of the member
     *  @param  size            Size of the name
     *  @return jit_value       The new variable pointer
     *  @see    smart_tpl_member
     */
    jit_value member(const jit_value &userdata, const jit_value &variable, const jit_value &name, const jit_value &size)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(), 
            variable.raw(),
            name.raw(),
            size.raw()
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_member", (void *)smart_tpl_member, _member.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the member_at function
     *  @param  userdata    Pointer to user-supplied data
     *  @param  variable    Pointer to the variable
     *  @param  position    Position of the member value
     *  @return jit_value   The new variable pointer
     *  @see    smart_tpl_member_at
     */
    jit_value member_at(const jit_value &userdata, const jit_value &variable, const jit_value &position)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            variable.raw(),
            position.raw()
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_member_at", (void *)smart_tpl_member_at, _member_at.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the create_iterator function
     *  @param  userdata    Pointer to user supplied data
     *  @param  variable    Variable over which we're iterating
     *  @return jit_value   The new iterator pointer
     *  @see    smart_tpl_create_iterator
     */
    jit_value create_iterator(const jit_value &userdata, const jit_value &variable)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            variable.raw()
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_create_iterator", (void *)smart_tpl_create_iterator, _create_iterator.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the valid_iterator function
     *  @param  userdata    Pointer to user supplied data
     *  @param  iterator    Iterator that is in use
     *  @return jit_value   Boolean value
     *  @see    smart_tpl_valid_iterator
     */
    jit_value valid_iterator(const jit_value &userdata, const jit_value &iterator)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            iterator.raw()
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_valid_iterator", (void *)smart_tpl_valid_iterator, _valid_iterator.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the iterator_key function
     *  @param  userdata    Pointer to user supplied data
     *  @param  iterator    Iterator that is in use
     *  @return jit_value   Current key pointer
     *  @see    smart_tpl_iterator_key
     */
    jit_value iterator_key(const jit_value &userdata, const jit_value &iterator)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            iterator.raw()
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_iterator_key", (void *)smart_tpl_iterator_key, _iterator_key.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the iterator_value function
     *  @param  userdata    Pointer to user supplied data
     *  @param  iterator    Iterator that is in use
     *  @return jit_value   Current value pointer
     *  @see    smart_tpl_iterator_value
     */
    jit_value iterator_value(const jit_value &userdata, const jit_value &iterator)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            iterator.raw()
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_iterator_value", (void *)smart_tpl_iterator_value, _iterator_value.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the iterator_next function
     *  @param  userdata    Pointer to user supplied data
     *  @param  iterator    Iterator that is in use
     *  @see    smart_tpl_iterator_next
     */
    void iterator_next(const jit_value &userdata, const jit_value &iterator)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            iterator.raw()
        };

        // create the instruction
        _function->insn_call_native("smart_tpl_iterator_next", (void *)smart_tpl_iterator_next, _iterator_next.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the variable function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  name            Name of the variable
     *  @param  size            Size of the name
     *  @return jit_value       The new variable pointer
     *  @see    smart_tpl_variable
     */
    jit_value variable(const jit_value &userdata, const jit_value &name, const jit_value &size)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(), 
            name.raw(),
            size.raw()
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_variable", (void *)smart_tpl_variable, _variable.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the to_numeric function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  variable        Pointer to the variable
     *  @return jit_value       Numeric representation
     *  @see    smart_tpl_to_numeric
     */
    jit_value to_numeric(const jit_value &userdata, const jit_value &variable)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(), 
            variable.raw()
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_to_numeric", (void *)smart_tpl_to_numeric, _toNumeric.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the to_boolean function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  variable        Pointer to the variable
     *  @return jit_value       Boolean representation
     *  @see    smart_tpl_to_boolean
     */
    jit_value to_boolean(const jit_value &userdata, const jit_value &variable)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(), 
            variable.raw()
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_to_boolean", (void *)smart_tpl_to_boolean, _toBoolean.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the to_string function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  variable        Pointer to the variable
     *  @return jit_value       String representation
     *  @see    smart_tpl_to_string
     */
    jit_value to_string(const jit_value &userdata, const jit_value &variable)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(), 
            variable.raw()
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_to_string", (void *)smart_tpl_to_string, _toString.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the size function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  variable        Pointer to the variable
     *  @return jit_value       String length
     *  @see    smart_tpl_size
     */
    jit_value size(const jit_value &userdata, const jit_value &variable)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(), 
            variable.raw()
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_size", (void *)smart_tpl_size, _size.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the modifier function
     *  @param  userdata      Pointer to user-supplied data
     *  @param  name          Name of the modifier we want to retrieve
     *  @param  size          Length of name
     *  @return jit_value     Pointer to the modifier object
     *  @see    smart_tpl_modifier
     */
    jit_value modifier(const jit_value &userdata, const jit_value &name, const jit_value &size)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            name.raw(),
            size.raw()
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_modifier", (void *)smart_tpl_modifier, _modifier.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the modify_variable function
     *  @param  userdata    Pointer to user-supplied data
     *  @param  modifier    The modifier to apply @see modifier()
     *  @param  variable    The variable to modify
     *  @return jit_value   A new modified variable pointer
     *  @see    smart_tpl_modify_variable
     */
    jit_value modify_variable(const jit_value &userdata, const jit_value &modifier, const jit_value &variable)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            modifier.raw(),
            variable.raw()
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_modify_variable", (void *) smart_tpl_modify_variable, _modify_variable.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the modify_numeric function
     *  @param  userdata    Pointer to user-supplied data
     *  @param  modifier    The modifier to apply @see modifier()
     *  @param  value       The numeric value to modify
     *  @return jit_value   A new modified variable pointer
     *  @see smart_tpl_modify_numeric
     *  @todo   Start actually using these methods
     */
    jit_value modify_numeric(const jit_value &userdata, const jit_value &modifier, const jit_value &value)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            modifier.raw(),
            value.raw()
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_modify_numeric", (void *) smart_tpl_modify_numeric, _modify_numeric.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the modify_string function
     *  @param  userdata    Pointer to user-supplied data
     *  @param  modifier    The modifier to apply @see modifier()
     *  @param  data        The string to modify
     *  @param  size        The length of the string to modify
     *  @return jit_value   A new modified variable pointer
     *  @see    smart_tpl_modify_string
     *  @todo   Start actually using these methods
     */
    jit_value modify_string(const jit_value &userdata, const jit_value &modifier, const jit_value &data, const jit_value &size)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            modifier.raw(),
            data.raw(),
            size.raw()
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_modify_string", (void *) smart_tpl_modify_string, _modify_string.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the strcmp function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  a               One of the strings to compare
     *  @param  a_len           The length of a
     *  @param  b               The other string to compare
     *  @param  b_len           The length of b
     *  @return jit_value       0 if equal, non-zero otherwise
     *  @see    smart_tpl_strcmp
     */
    jit_value strcmp(const jit_value &userdata, const jit_value &a, const jit_value &a_len, const jit_value &b, const jit_value &b_len)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            a.raw(),
            a_len.raw(),
            b.raw(),
            b_len.raw(),
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_strcmp", (void *) smart_tpl_strcmp, _strcmp.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the assign function
     *  @param  userdata     Pointer to user-supplied data
     *  @param  variable     The variable to assign
     *  @param  key          The key to assign variable to
     *  @param  key_size     The length of key
     *  @see    smart_tpl_assign
     */
    void assign(const jit_value &userdata, const jit_value &variable, const jit_value &key, const jit_value &key_size)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            variable.raw(),
            key.raw(),
            key_size.raw(),
        };

        // create the instruction
        _function->insn_call_native("smart_tpl_assign", (void *) smart_tpl_assign, _assign.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the assign_numeric function
     *  @param  userdata       Pointer to user-supplied data
     *  @param  value          The numeric value to assign
     *  @param  key            The key to assign value to
     *  @param  key_size       The length of key
     *  @see    smart_tpl_assign_numeric
     */
    void assign_numeric(const jit_value &userdata, const jit_value &value, const jit_value &key, const jit_value &key_size)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            value.raw(),
            key.raw(),
            key_size.raw(),
        };

        // create the instruction
        _function->insn_call_native("smart_tpl_assign_numeric", (void *) smart_tpl_assign_numeric, _assign_numeric.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the assign_boolean function
     *  @param  userdata      Pointer to user-supplied data
     *  @param  boolean       The boolean value to assign
     *  @param  key           The key to assign boolean to
     *  @param  key_size      The length of key
     *  @see    smart_tpl_assign_boolean
     */
    void assign_boolean(const jit_value &userdata, const jit_value &boolean, const jit_value &key, const jit_value &key_size)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            boolean.raw(),
            key.raw(),
            key_size.raw(),
        };

        // create the instruction
        _function->insn_call_native("smart_tpl_assign_boolean", (void *) smart_tpl_assign_boolean, _assign_boolean.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the assign_string function
     *  @param  userdata      Pointer to user-supplied data
     *  @param  str           The string to assign
     *  @param  str_size      The length of str
     *  @param  key           The key to assign str to
     *  @param  key_size      The length of key
     *  @see    smart_tpl_assign_string
     */
    void assign_string(const jit_value &userdata, const jit_value &str, const jit_value str_size, const jit_value &key, const jit_value &key_size)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            str.raw(),
            str_size.raw(),
            key.raw(),
            key_size.raw(),
        };

        // create the instruction
        _function->insn_call_native("smart_tpl_assign_string", (void *) smart_tpl_assign_string, _assign_string.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }
};

/**
 *  End of namespace
 */
}

