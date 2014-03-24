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
class Bytecode : private Generator
{
private:
    /**
     *  The LLVM context
     *  @var    llvm::LLVMContext
     */
    llvm::LLVMContext _context;

    /**
     *  The LLVM module
     *  @var    llvm::Module
     */
    llvm::Module *_module;


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
    virtual void condition(const Expression *expression, const Statements *ifstatements, const  Statements *elsestatements) override;
    
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
     *  @param  name        Name of the template (this will be the module ID)
     *  @param  tree        The syntax tree
     */
    Bytecode(const char *name, const SyntaxTree &tree);
    
    /**
     *  Destructor
     */
    virtual ~Bytecode();
    
};
    
/**
 *  End namespace
 */
}
