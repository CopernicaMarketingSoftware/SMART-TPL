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
 *  @copyright 2014 - 2018 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Forwards
 */
class Variable;
class Expression;
class Statements;
class Modifiers;
class Filter;
class Parameters;

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
     *  Generate the code to output the output of a filter
     *  @param  filter             The filter to eventually output
     */
    virtual void output(const Filter *filter) = 0;

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
    virtual void numeric(numeric_t value) = 0;
    virtual void double_type(double value) = 0;

    /**
     *  Create a string, numeric or boolean constant for a variable
     *  @param  variable
     */
    virtual void stringVariable(const Variable *variable) = 0;
    virtual void numericVariable(const Variable *variable) = 0;
    virtual void booleanVariable(const Variable *variable) = 0;
    virtual void doubleVariable(const Variable *variable) = 0;
    virtual void variable(const Variable *variable) = 0;

    /**
     *  Negate the boolean expression
     *  @param  expression
     */
    virtual void negateBoolean(const Expression *expression) = 0;

    /**
     *  Arithmetric operations
     *  @param  left
     *  @param  right
     */
    virtual void plus(const Expression *left, const Expression *right) = 0;
    virtual void minus(const Expression *left, const Expression *right) = 0;
    virtual void divide(const Expression *left, const Expression *right) = 0;
    virtual void multiply(const Expression *left, const Expression *right) = 0;
    virtual void modulo(const Expression *left, const Expression *right) = 0;

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
    virtual void regex(const Expression *left, const Expression *right) = 0;

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
     *  @param  variable           The variable to apply to modifers to
     */
    virtual void modifiers(const Modifiers *modifiers, const Variable *variable) = 0;
    /**
     *  Generate the code to apply a set of modifiers on an expression and turn it into a boolean
     *  @param  modifiers          The set of modifiers to apply
     *  @param  variable           The variable to apply the modifers to
     */
    virtual void modifiersBoolean(const Modifiers *modifers, const Variable *variable) = 0;
    /**
     *  Generate the code to apply a set of modifiers on an expression and turn it into a double
     *  @param  modifiers          The set of modifiers to apply
     *  @param  variable           The variable to apply the modifiers to
     */
    virtual void modifiersDouble(const Modifiers *modifiers, const Variable *variable) = 0;

    /**
     *  Generate the code to construct the following parameters
     *  @param  parameters         The parameters to construct
     *  @note Construct as in, generate the code so the runtime can construct them
     */
    virtual void parameters(const Parameters *parameters) = 0;

    /**
     *  Generate the code to do a foreach loop over variable
     *  @param variable         The variable object to iterate over
     *  @param key              The magic variable name for the keys
     *  @param value            The magic variable name for the values
     *  @param statements       The statements to execute on each iteration
     *  @param else_statements  The statements to execute if there was nothing to loop through
     */
    virtual void foreach(const Variable *variable, const std::string &key, const std::string &value, const Statements *statements, const Statements *else_statements) = 0;

    /**
     *  Generate the code to assign the output of an expression to a key
     *  @param key                  The key to assign the output to
     *  @param expression           The expression to evaluate
     */
    virtual void assign(const std::string &key, const Expression *expression) = 0;
};

/**
 *  End namespace
 */
}}
