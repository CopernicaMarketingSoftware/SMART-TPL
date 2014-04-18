/**
 *  Generator.h
 *
 *  After a template file is parsed, it is turned into a SyntaxTree, which is
 *  then either turned into a shared library by the template compiler, or into 
 *  a JIT compiled executable memory buffer.
 *
 *  This is the abstract base class of both the shared-library-compiler, and 
 *  the JIT-compiler.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Forwards
 */
class Variable;
class Expression;
class Statements;
class Modifiers;

/**
 *  Class definition
 */
class Generator
{
protected:
    /**
     *  The constructor is protected because only derived generators
     *  should be used
     */
    Generator() {}
    
public:
    /**
     *  Destructor
     */
    virtual ~Generator() {}

    /**
     *  Generate code to output raw data
     *  @param  data                data to output
     */
    virtual void raw(const std::string &data) = 0;
    
    /**
     *  Generate the code to output a variable
     *  @param  variable           The variable to output
     */
    virtual void output(const Variable *variable) = 0;

    /**
     *  Generate the code to write an expression as a string
     *  @param  expression          the expression to write as a string
     */
    virtual void write(const Expression *expression) = 0;

    /**
     *  Generate a conditional statement
     *  @param  expression          the expression to evaluate
     *  @param  ifstatements        the statements in the 'if' part
     *  @param  elsestatements      the statements in the 'else' part
     */
    virtual void condition(const Expression *expression, const Statements *ifstatements, const  Statements *elsestatements) = 0;
    
    /**
     *  Generate the code to get a pointer to a variable
     *  There are three formats, to get a pointer to a literal variable by name,
     *  to get a pointer to a variable inside a table with a literal name, and
     *  to get a pointer to a variable with variable name
     *  @param  parent              parent variable from which the var is retrieved
     *  @param  name                name of the variable
     *  @param  expression          Expression that evaluates to a var name
     */
    virtual void varPointer(const Variable *parent, const std::string &name) = 0;
    virtual void varPointer(const Variable *parent, const Expression *expression) = 0;
    virtual void varPointer(const std::string &name) = 0;
    
    /**
     *  Create a string, numeric or boolean literal
     *  @param  value
     */
    virtual void string(const std::string &value) = 0;
    virtual void numeric(int value) = 0;
    //virtual void boolean(bool value) = 0;
    
    /**
     *  Create a string, numeric or boolean constant for a variable
     *  @param  variable
     */
    virtual void string(const Variable *variable) = 0;
    virtual void numeric(const Variable *variable) = 0;
    virtual void boolean(const Variable *variable) = 0;
    virtual void variable(const Variable *variable) = 0;
    
    /**
     *  Create a string literal from an expression that is known to return a numeric value,
     *  and a method to do this in the other direction
     *  @param  expression
     */
    virtual void numericToString(const Expression *expression) = 0;
    virtual void stringToNumeric(const Expression *expression) = 0;
    
    /**
     *  Arithmetric operations
     *  @param  left
     *  @param  right
     */
    virtual void plus(const Expression *left, const Expression *right) = 0;
    virtual void minus(const Expression *left, const Expression *right) = 0;
    virtual void divide(const Expression *left, const Expression *right) = 0;
    virtual void multiply(const Expression *left, const Expression *right) = 0;
  
    /**
     *  Comparison operators
     *  @param  left
     *  @param  right
     */
    virtual void equals(const Expression *left, const Expression *right) = 0;
    virtual void notEquals(const Expression *left, const Expression *right) = 0;
    virtual void greater(const Expression *left, const Expression *right) = 0;
    virtual void greaterEquals(const Expression *left, const Expression *right) = 0;
    virtual void lesser(const Expression *left, const Expression *right) = 0;
    virtual void lesserEquals(const Expression *left, const Expression *right) = 0;
    
    /**
     *  Boolean operators
     *  @param  left
     *  @param  right
     */
    virtual void booleanAnd(const Expression *left, const Expression *right) = 0;
    virtual void booleanOr(const Expression *left, const Expression *right) = 0;

    /**
     *  Generate the code to apply a set of modifiers on an expression
     *  @param  modifiers          The set of modifiers to apply
     *  @param  expression         The expression to apply to modifiers on
     */
    virtual void modifiers(const Modifiers* modifiers, const Expression *expression) = 0;
    
};

/**
 *  End namespace
 */
}

