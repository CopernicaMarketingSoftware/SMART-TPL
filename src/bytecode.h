/**
 *  Bytecode.h
 * 
 *  A generator class that creates a LLVM representation of a template.
 * 
 *  This class overrides from the Generator class to generate the code that
 *  can be passed to a LLVM virtual machine.
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
     *  Signature of all callbacks methods
     *  @var    Callbacks
     */
    Callbacks _callbacks;
    
    /**
     *  The user-data that is passed to the function
     *  @var    jit_value_t
     */
    jit_value _userdata;

    /**
     *  Stack with temporary values
     *  @var    std::stack
     */
    std::stack<jit_value> _stack;

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
    jit_value numeric(const Expression *expression);

    /**
     *  Generate code to output raw data
     *  @param  data                data to output
     */
    virtual void raw(const std::string &data) override;
   
    /**
     *  Generate the code to output a variable
     *  @param  variable            the variable to output
     */
    virtual void output(const Variable *variable) override;

    /**
     *  Generate a conditional statement
     *  @param  expression          the expression to evaluate
     *  @param  ifstatements        the statements in the 'if' part
     *  @param  elsestatements      the statements in the 'else' part
     */
    virtual void condition(const Expression *expression, const Statements *ifstatements, const Statements *elsestatements) override;
    
    /**
     *  Generate the code to get a pointer to a variable
     *  There are three formats, to get a pointer to a literal variable by name,
     *  to get a pointer to a variable inside a table with a literal name, and
     *  to get a pointer to a variable with variable name
     *  @param  parent              parent variable from which the var is retrieved
     *  @param  name                name of the variable
     *  @param  expression          Expression that evaluates to a var name
     */
    virtual void varPointer(const Variable *parent, const std::string &name) override;
    virtual void varPointer(const Variable *parent, const Expression *expression) override;
    virtual void varPointer(const std::string &name) override;
    
    /**
     *  Create a string or numeric literal
     *  @param  value
     */
    virtual void string(const std::string &value) override;
    virtual void numeric(int value) override;
    
    /**
     *  Create a string or numeric constant for a variable
     *  @param  variable
     */
    virtual void string(const Variable *variable) override;
    virtual void numeric(const Variable *variable) override;
    
    /**
     *  Create a string literal from an expression that is known to return a numeric value,
     *  and a method to do this in the other direction
     *  @param  expression
     */
    virtual void numericToString(const Expression *expression) override;
    virtual void stringToNumeric(const Expression *expression) override;
    
    /**
     *  Arithmetric operations
     *  @param  left
     *  @param  right
     */
    virtual void plus(const Expression *left, const Expression *right) override;
    virtual void minus(const Expression *left, const Expression *right) override;
    virtual void divide(const Expression *left, const Expression *right) override;
    virtual void multiply(const Expression *left, const Expression *right) override;
  
    /**
     *  Comparison operators
     *  @param  left
     *  @param  right
     */
    virtual void equals(const Expression *left, const Expression *right) override;
    virtual void notEquals(const Expression *left, const Expression *right) override;
    virtual void greater(const Expression *left, const Expression *right) override;
    virtual void greaterEquals(const Expression *left, const Expression *right) override;
    virtual void lesser(const Expression *left, const Expression *right) override;
    virtual void lesserEquals(const Expression *left, const Expression *right) override;
    
    /**
     *  Boolean operators
     *  @param  left
     *  @param  right
     */
    virtual void booleanAnd(const Expression *left, const Expression *right) override;
    virtual void booleanOr(const Expression *left, const Expression *right) override;


public:
    /**
     *  Constructor
     *  @param  filename        The filename that holds the template
     */
    Bytecode(const char *filename);
    
    /**
     *  Destructor
     */
    virtual ~Bytecode();

    /**
     *  Execute the template given a certain data source
     *  @param  data
     */
    virtual void process(Handler &handler) override;
    
};
    
/**
 *  End namespace
 */
}

