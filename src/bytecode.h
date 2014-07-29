/**
 *  Bytecode.h
 *
 *  A generator class that creates a LLVM representation of a template.
 *
 *  This class overrides from the Generator class to generate the code that
 *  can be passed to a LLVM machine.
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
class Bytecode : private Generator, public Executor
{
private:
    /**
     *  The syntax tree
     *  @var    SyntaxTree
     */
    SyntaxTree _tree;

    /**
     *  The jit context
     *  @var    jit_context
     */
    jit_context _context;

    /**
     *  The function to generate the template
     *  @var    Function
     */
    jit_function _function;

    /**
     *  The signature for _function
     *  @var    jit_type_t
     */
    static jit_type_t _function_signature;

    /**
     *  Signature of the ShowTemplate function
     */
    using ShowTemplate = void(const void *userdata);

    /**
     *  Jit closure function that is directly callable from C
     *  @var    ShowTemplate
     */
    ShowTemplate *_closure = nullptr;

    /**
     *  Signature of all callbacks methods
     *  @var    Callbacks
     */
    Callbacks _callbacks;

    /**
     *  The user-data that is passed to the function
     *  @var    jit_value
     */
    jit_value _userdata;

    /**
     *  A jit value constant of 1 which is just here so we can reuse it over and over again
     *  @var    jit_value
     */
    jit_value _true;

    /**
     *  A jit value constant of 0 which is just here so we can reuse it over and over again
     *  @var    jit_value
     */
    jit_value _false;

    /**
     *  Stack with temporary values
     *  @var    std::stack
     */
    std::stack<jit_value> _stack;

    /**
     *  The exception handler for libjit
     */
    static void *jit_exception_handler(int exception_type);

    /**
     *  Helper method to pop a value from the stack
     *  @return jit_value
     */
    jit_value pop();

    /**
     *  Construct a poiner to a variable
     *  @param  variable
     *  @return jit_value
     */
    jit_value pointer(const Variable *variable);

    /**
     *  Retrieve the numeric representation of an expression
     *  @param  expression
     *  @return jit_value
     */
    jit_value numericExpression(const Expression *expression);

    /**
     *  Retrieve the boolean representation of an expression
     *  @param  expression
     *  @return jit_value
     */
    jit_value booleanExpression(const Expression *expression);

    /**
     *  Generate code to output raw data
     *  @param  data                data to output
     */
    void raw(const std::string &data) override;

    /**
     *  Generate the code to output a variable
     *  @param  variable           The variable to output
     */
    void output(const Variable *variable) override;

    /**
     *  Generate the code to output the output of a filter
     *  @param  filter             The filter to eventually output
     */
    void output(const Filter *filter) override;

    /**
     *  Generate the code to write an expression as a string
     *  @param  expression          the expression to write as a string
     */
    void write(const Expression *expression) override;

    /**
     *  Generate a conditional statement
     *  @param  expression          the expression to evaluate
     *  @param  ifstatements        the statements in the 'if' part
     *  @param  elsestatements      the statements in the 'else' part
     */
    void condition(const Expression *expression, const Statements *ifstatements, const Statements *elsestatements) override;

    /**
     *  Generate the code to get a pointer to a variable
     *  There are three formats, to get a pointer to a literal variable by name,
     *  to get a pointer to a variable inside a table with a literal name, and
     *  to get a pointer to a variable with variable name
     *  @param  parent              parent variable from which the var is retrieved
     *  @param  name                name of the variable
     *  @param  expression          Expression that evaluates to a var name
     */
    void varPointer(const Variable *parent, const std::string &name) override;
    void varPointer(const Variable *parent, const Expression *expression) override;
    void varPointer(const std::string &name) override;

    /**
     *  Create a string or numeric literal
     *  @param  value
     */
    void string(const std::string &value) override;
    void numeric(numeric_t value) override;

    /**
     *  Create a string or numeric constant for a variable
     *  @param  variable
     */
    void stringVariable(const Variable *variable) override;
    void numericVariable(const Variable *variable) override;
    void booleanVariable(const Variable *variable) override;
    void variable(const Variable *variable) override;

    /**
     *  Arithmetric operations
     *  @param  left
     *  @param  right
     */
    void plus(const Expression *left, const Expression *right) override;
    void minus(const Expression *left, const Expression *right) override;
    void divide(const Expression *left, const Expression *right) override;
    void multiply(const Expression *left, const Expression *right) override;
    void modulo(const Expression *left, const Expression *right) override;

    /**
     *  Comparison operators
     *  @param  left
     *  @param  right
     */
    void equals(const Expression *left, const Expression *right) override;
    void notEquals(const Expression *left, const Expression *right) override;
    void greater(const Expression *left, const Expression *right) override;
    void greaterEquals(const Expression *left, const Expression *right) override;
    void lesser(const Expression *left, const Expression *right) override;
    void lesserEquals(const Expression *left, const Expression *right) override;

    /**
     *  Boolean operators
     *  @param  left
     *  @param  right
     */
    void booleanAnd(const Expression *left, const Expression *right) override;
    void booleanOr(const Expression *left, const Expression *right) override;

    /**
     *  Generate the code to apply a set of modifiers on an expression
     *  @param  modifiers          The set of modifiers to apply
     *  @param  expression         The expression to apply to modifiers on
     */
    void modifiers(const Modifiers *modifiers, const Variable *variable) override;

    /**
     *  Generate the code to construct the following parameters
     *  @param  parameters         The parameters to construct
     *  @note Construct as in, generate the code so the runtime can construct them
     */
    void parameters(const Parameters *parameters) override;

    /**
     *  Generate the code to do a foreach loop over variable
     *  @param variable         The variable object to iterate over
     *  @param key              The magic variable name for the keys
     *  @param value            The magic variable name for the values
     *  @param statements       The statements to execute on each iteration
     *  @param else_statements  The statements to execute if there was nothing to loop through
     */
    void foreach(const Variable *variable, const std::string &key, const std::string &value, const Statements *statements, const Statements *else_statements) override;

    /**
     *  Generate the code to assign the output of an expression to a key
     *  @param key                  The key to assign the output to
     *  @param expression           The expression to evaluate
     */
    void assign(const std::string &key, const Expression *expression) override;

public:
    /**
     *  Constructor
     *  @param  source The source that holds the template
     *  @throws std::runtime_error If something went wrong while compiling the jit code
     */
    Bytecode(const Source& source);

    /**
     *  Destructor
     */
    virtual ~Bytecode() {};

    /**
     *  Execute the template given a certain handler
     *  @param  handler
     */
    void process(Handler &handler) override;

    /**
     *  Compile the template into C code
     *  @return std::string
     */
    std::string compile() override
    {
        // convert the syntax tree into C code
        return CCode(_tree).asString();
    }

    /**
     *  Retrieve what encoding the 'template' has natively
     *  @return std::string
     */
    std::string encoding() override
    {
        return _tree.mode();
    }
};

/**
 *  End namespace
 */
}}