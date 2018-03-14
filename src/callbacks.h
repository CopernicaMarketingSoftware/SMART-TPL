/**
 *  Callbacks.h
 *
 *  Class that is used by the JIT compiler and that represents all functions
 *  in the main SMART-TPL library that can be called from outside a template
 *  function.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 - 2018 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Signatures of the global callback functions
 */
void        smart_tpl_write                 (void *userdata, const char *data, size_t size);
void        smart_tpl_output                (void *userdata, const void *variable, int escape);
void        smart_tpl_output_numeric        (void *userdata, numeric_t number);
void        smart_tpl_output_boolean        (void *userdata, bool value);
const void *smart_tpl_member                (void *userdata, const void *variable, const char *name, size_t size);
const void *smart_tpl_member_at             (void *userdata, const void *variable, size_t position);
void       *smart_tpl_create_iterator       (void *userdata, const void *variable);
int         smart_tpl_valid_iterator        (void *userdata, void *iterator);
const void *smart_tpl_iterator_key          (void *userdata, void *iterator);
const void *smart_tpl_iterator_value        (void *userdata, void *iterator);
void        smart_tpl_iterator_next         (void *userdata, void *iterator);
const void *smart_tpl_variable              (void *userdata, const char *name, size_t size);
const char *smart_tpl_to_string             (void *userdata, const void *variable);
numeric_t   smart_tpl_to_numeric            (void *userdata, const void *variable);
double      smart_tpl_to_double             (void *userdata, const void *variable);
int         smart_tpl_to_boolean            (void *userdata, const void *variable);
size_t      smart_tpl_size                  (void *userdata, const void *variable);
void       *smart_tpl_modifier              (void *userdata, const char *name, size_t size);
const void *smart_tpl_modify_variable       (void *userdata, const void *variable, void *modifier, const void *parameters);
void        smart_tpl_assign_numeric        (void *userdata, const char *key, size_t keysize, numeric_t value);
void        smart_tpl_assign_boolean        (void *userdata, const char *key, size_t keysize, int boolean);
void        smart_tpl_assign_string         (void *userdata, const char *key, size_t keysize, const char *buf, size_t buf_size);
void        smart_tpl_assign_double         (void *userdata, const char *key, size_t keysize, double value);
void        smart_tpl_assign                (void *userdata, const char *key, size_t keysize, const void *variable);
int         smart_tpl_strcmp                (void *userdata, const char *a, size_t a_len, const char *b, size_t b_len);
void       *smart_tpl_regex_compile         (void *userdata, const char *regex, size_t size);
int         smart_tpl_regex_match           (void *userdata, void *handle, const char *message, size_t size);
void        smart_tpl_regex_release         (void *userdata, void *handle);
const void *smart_tpl_create_params         (void *userdata, size_t parameters_count);
const void *smart_tpl_params_append_numeric (void *userdata, const void *parameters, numeric_t value);
const void *smart_tpl_params_append_double  (void *userdata, const void *parameters, double value);
const void *smart_tpl_params_append_string  (void *userdata, const void *parameters, const char *buf, size_t len);
const void *smart_tpl_params_append_boolean (void *userdata, const void *parameters, int boolean);
void        smart_tpl_mark_failed           (void *userdata, const char *error);
int         smart_tpl_throw_exception       (void *userdata, const char *error);

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
     */
    static SignatureCallback _write;

    /**
     *  Signature of the output callback
     */
    static SignatureCallback _output;

    /**
     *  Signature fo the output numeric callback
     */
    static SignatureCallback _output_numeric;

    /**
     *  Signature fo the output boolean callback
     */
    static SignatureCallback _output_boolean;

    /**
     *  Signature of the member callback
     */
    static SignatureCallback _member;

    /**
     *  Signature of the member_at callback
     */
    static SignatureCallback _member_at;

    /**
     *  Signature of the create-iterator callback
     */
    static SignatureCallback _create_iterator;

    /**
     *  Signature of the valid-iterator callback
     */
    static SignatureCallback _valid_iterator;

    /**
     *  Signature of the iterator-key callback
     */
    static SignatureCallback _iterator_key;

    /**
     *  Signature of the iterator-value callback
     */
    static SignatureCallback _iterator_value;

    /**
     *  Signature of the iterator-next callback
     */
    static SignatureCallback _iterator_next;

    /**
     *  Signature of the variable callback
     */
    static SignatureCallback _variable;

    /**
     *  Signature of the function to convert a variable to a string
     */
    static SignatureCallback _toString;

    /**
     *  Signature of the function to convert a variable to a numeric value
     */
    static SignatureCallback _toNumeric;

    /**
     *  Signature of the function to convert a variable to a floating point value
     */
    static SignatureCallback _toDouble;

    /**
     *  Signature of the function to convert a variable to a boolean value
     */
    static SignatureCallback _toBoolean;

    /**
     *  Signature of the function to retrieve the size/strlen of a variable
     */
    static SignatureCallback _size;

    /**
     *  Signature of the function to retrieve the modifier
     */
    static SignatureCallback _modifier;

    /**
     *  Signature of the function to modify a variable
     */
    static SignatureCallback _modify_variable;

    /**
     *  Signature of the function to create a new parameters object
     */
    static SignatureCallback _create_params;

    /**
     *  Signature of the function to append a numeric value to parameters
     */
    static SignatureCallback _params_append_numeric;

    /**
     *  Signature of the function to append a floating point value to parameters
     */
    static SignatureCallback _params_append_double;

    /**
     *  Signature of the function to append a string value to parameters
     */
    static SignatureCallback _params_append_string;

    /**
     *  Signature of the function to append a boolean value to parameters
     */
    static SignatureCallback _params_append_boolean;

    /**
     *  Signature of the function to compare 2 strings
     */
    static SignatureCallback _strcmp;

    /**
     *  Signature of the functions to check if a string matches with a regex
     */
    static SignatureCallback _regex_compile;
    static SignatureCallback _regex_match;
    static SignatureCallback _regex_release;

    /**
     *  Signature of the function to assign a variable to a local variable
     */
    static SignatureCallback _assign;

    /**
     *  Signature of the function to assign a boolean to a local variable
     */
    static SignatureCallback _assign_boolean;

    /**
     *  Signature of the function to assign a numeric value to a local variable
     */
    static SignatureCallback _assign_numeric;

    /**
     *  Signature of the function to assign a double value to a local variable
     */
    static SignatureCallback _assign_double;

    /**
     *  Signature of the function to assign a string to a local variable
     */
    static SignatureCallback _assign_string;

    /**
     *  Signature of the function to set our handler in failed mode
     */
    static SignatureCallback _mark_failed;

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
     *  @param  escape          Boolean whether we should escape the output or not
     *  @see    smart_tpl_output
     */
    void output(const jit_value &userdata, const jit_value &variable, const jit_value &escape)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            variable.raw(),
            escape.raw(),
        };

        // create the instruction
        _function->insn_call_native("smart_tpl_output", (void *)smart_tpl_output, _output.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the output numeric function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  number          Number to output
     *  @see    smart_tpl_output_numeric
     */
    void output_numeric(const jit_value &userdata, const jit_value &number)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            number.raw(),
        };

        // create the instruction
        _function->insn_call_native("smart_tpl_output_numeric", (void *)smart_tpl_output_numeric, _output_numeric.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the output boolean function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  value           Value to output
     *  @see    smart_tpl_output_numeric
     */
    void output_boolean(const jit_value &userdata, const jit_value &value)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            value.raw(),
        };

        // create the instruction
        _function->insn_call_native("smart_tpl_output_boolean", (void *)smart_tpl_output_boolean, _output_boolean.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
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
     *  Call the to_double function
     *  @param  userdata        Pointer to user-supplied data
     *  @param  variable        Pointer to the variable
     *  @return jit_value       Floating point representation
     *  @see    smart_tpl_to_double
     */
    jit_value to_double(const jit_value &userdata, const jit_value &variable)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            variable.raw()
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_to_double", (void *)smart_tpl_to_double, _toDouble.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
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
     *  Call the create_params function
     *  @param  userdata       Pointer to user-supplied data
     *  @return jit_value      Pointer to a new SmartTpl::Parameters object
     *  @see    smart_tpl_create_params
     */
    jit_value create_params(const jit_value &userdata, const jit_value &parameters_count)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            parameters_count.raw(),
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_create_params", (void *) smart_tpl_create_params, _create_params.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the params_append_boolean function
     *  @param  userdata       Pointer to user-supplied data
     *  @param  parameters     Pointer to the parameters we would like to append to
     *  @param  value          The boolean value we would like to append
     *  @see    smart_tpl_params_append_boolean
     */
    void params_append_boolean(const jit_value &userdata, const jit_value &parameters, const jit_value &value)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            parameters.raw(),
            value.raw(),
        };

        // create the instruction
        _function->insn_call_native("smart_tpl_params_append_boolean", (void *) smart_tpl_params_append_boolean, _params_append_boolean.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the params_append_numeric function
     *  @param  userdata       Pointer to user-supplied data
     *  @param  parameters     Pointer to the parameters we would like to append to
     *  @param  value          The numeric value we would like to append
     *  @see    smart_tpl_params_append_numeric
     */
    void params_append_numeric(const jit_value &userdata, const jit_value &parameters, const jit_value &value)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            parameters.raw(),
            value.raw(),
        };

        // create the instruction
        _function->insn_call_native("smart_tpl_params_append_numeric", (void *) smart_tpl_params_append_numeric, _params_append_numeric.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the params_append_double function
     *  @param  userdata       Pointer to user-supplied data
     *  @param  parameters     Pointer to the parameters we would like to append to
     *  @param  value          The double value we would like to append
     *  @see    smart_tpl_params_append_double
     */
    void params_append_double(const jit_value &userdata, const jit_value &parameters, const jit_value &value)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            parameters.raw(),
            value.raw(),
        };

        // create the instruction
        _function->insn_call_native("smart_tpl_params_append_double", (void *) smart_tpl_params_append_double, _params_append_double.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the params_append_string function
     *  @param  userdata       Pointer to user-supplied data
     *  @param  parameters     Pointer to the parameters we would like to append to
     *  @param  buf            The string we would like to append
     *  @param  len            The length of the string we would like to append
     *  @see    smart_tpl_params_append_string
     */
    void params_append_string(const jit_value &userdata, const jit_value &parameters, const jit_value &buf, const jit_value &len)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            parameters.raw(),
            buf.raw(),
            len.raw(),
        };

        // create the instruction
        _function->insn_call_native("smart_tpl_params_append_string", (void *) smart_tpl_params_append_string, _params_append_string.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
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
     *  @param  variable    The variable to modify
     *  @param  modifier    The modifier to apply @see modifier()
     *  @param  parameters  The parameters for this modifier
     *  @return jit_value   A new modified variable pointer
     *  @see    smart_tpl_modify_variable
     */
    jit_value modify_variable(const jit_value &userdata, const jit_value &variable, const jit_value &modifier, const jit_value &parameters)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            variable.raw(),
            modifier.raw(),
            parameters.raw(),
        };

        // create the instruction
        return _function->insn_call_native("smart_tpl_modify_variable", (void *) smart_tpl_modify_variable, _modify_variable.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
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
     *  Compile a regular expression
     *  @param  userdata        Pointer to user-supplied data
     *  @param  regex           The regular expression to compile
     *  @param  size            Size of the regular expression
     *  @return jit_value
     */
    jit_value regex_compile(const jit_value &userdata, const jit_value &regex, const jit_value &size)
    {
        // arguments to compile the the regular expression
        jit_value_t args[] = {
            userdata.raw(),
            regex.raw(),
            size.raw()
        };
        
        // create the instruction
        return _function->insn_call_native("smart_tpl_regex_compile", (void *) smart_tpl_regex_compile, _regex_compile.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Match a regular expression
     *  @param  userdata        Pointer to user-supplied 
     *  @param  regex           The regular expression (return value of earlier call to regex_compile())
     *  @param  string          The message
     *  @param  size            Size of the regular expression
     *  @return jit_value
     */
    jit_value regex_match(const jit_value &userdata, const jit_value &regex, const jit_value &string, const jit_value &size)
    {
        // arguments to compile the the regular expression
        jit_value_t args[] = {
            userdata.raw(),
            regex.raw(),
            string.raw(),
            size.raw()
        };
        
        // create the instruction
        return _function->insn_call_native("smart_tpl_regex_match", (void *) smart_tpl_regex_match, _regex_match.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }
    
    /**
     *  Release a regular expression that was earlier compiled with regex_compile()
     *  @param  userdata        Pointer to user-supplied 
     *  @param  regex           The regular expression (return value of earlier call to regex_compile())
     */
    void regex_release(const jit_value &userdata, const jit_value &regex)
    {
        // arguments to compile the the regular expression
        jit_value_t args[] = {
            userdata.raw(),
            regex.raw()
        };
        
        // create the instruction
        _function->insn_call_native("smart_tpl_regex_release", (void *) smart_tpl_regex_release, _regex_release.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the assign function
     *  @param  userdata     Pointer to user-supplied data
     *  @param  variable     The variable to assign
     *  @param  key          The key to assign variable to
     *  @param  key_size     The length of key
     *  @see    smart_tpl_assign
     */
    void assign(const jit_value &userdata, const jit_value &key, const jit_value &key_size, const jit_value &variable)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            key.raw(),
            key_size.raw(),
            variable.raw(),
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
    void assign_numeric(const jit_value &userdata, const jit_value &key, const jit_value &key_size, const jit_value &value)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            key.raw(),
            key_size.raw(),
            value.raw(),
        };

        // create the instruction
        _function->insn_call_native("smart_tpl_assign_numeric", (void *) smart_tpl_assign_numeric, _assign_numeric.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the assign_double function
     *  @param  userdata       Pointer to user-supplied data
     *  @param  value          The floating point value to assign
     *  @param  key            The key to assign value to
     *  @param  key_size       The length of key
     *  @see    smart_tpl_assign_double
     */
    void assign_double(const jit_value &userdata, const jit_value &value, const jit_value &key, const jit_value &key_size)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            value.raw(),
            key.raw(),
            key_size.raw(),
        };

        // create the instruction
        _function->insn_call_native("smart_tpl_assign_double", (void *) smart_tpl_assign_double, _assign_double.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the assign_boolean function
     *  @param  userdata      Pointer to user-supplied data
     *  @param  boolean       The boolean value to assign
     *  @param  key           The key to assign boolean to
     *  @param  key_size      The length of key
     *  @see    smart_tpl_assign_boolean
     */
    void assign_boolean(const jit_value &userdata, const jit_value &key, const jit_value &key_size, const jit_value &boolean)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            key.raw(),
            key_size.raw(),
            boolean.raw(),
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
    void assign_string(const jit_value &userdata, const jit_value &key, const jit_value &key_size, const jit_value &str, const jit_value str_size)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            key.raw(),
            key_size.raw(),
            str.raw(),
            str_size.raw(),
        };

        // create the instruction
        _function->insn_call_native("smart_tpl_assign_string", (void *) smart_tpl_assign_string, _assign_string.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }

    /**
     *  Call the mark_failed function
     *  @param   userdata        Pointer to user-supplied data
     *  @param   error           Error message
     *  @see     smart_tpl_mark_failed
     */
    void mark_failed(const jit_value &userdata, const jit_value &error)
    {
        // construct the arguments
        jit_value_t args[] = {
            userdata.raw(),
            error.raw()
        };

        // create the instruction
        _function->insn_call_native("smart_tpl_mark_failed", (void *) smart_tpl_mark_failed, _mark_failed.signature(), args, sizeof(args)/sizeof(jit_value_t), 0);
    }
};

/**
 *  End of namespace
 */
}}
