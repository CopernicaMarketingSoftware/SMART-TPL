/**
 *  CCode.h
 *
 *  Class that turns a template syntax tree into C code that can be compiled
 *  into a shared library.
 *
 *  This class overrides from the Generator base class, because it is one
 *  of the generators of the SmartTpl library (the template-to-c-code generator)
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 - 2018 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class CCode : public Generator
{
private:
    /**
     *  Output stream
     *  @var    std::ostream
     */
    std::ostringstream _out;

    /**
     *  Output raw data
     *  @param  data        buffer to output
     */
    virtual void raw(const std::string &data) override;

    /**
     *  Generate the code to output a variable
     *  @param  variable           The variable to output
     */
    virtual void output(const Variable *variable) override;

    /**
     *  Generate the code to output the output of a filter
     *  @param  filter             The filter to eventually output
     */
    virtual void output(const Filter *filter) override;

    /**
     *  Generate the code to write an expression as a string
     *  @param  expression          the expression to write as a string
     */
    virtual void write(const Expression *expression) override;

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
    virtual void numeric(numeric_t value) override;
    virtual void double_type(double value) override;

    /**
     *  Create a string, numeric or boolean constant for a variable
     *  @param  variable
     */
    virtual void stringVariable(const Variable *variable) override;
    virtual void numericVariable(const Variable *variable) override;
    virtual void booleanVariable(const Variable *variable) override;
    virtual void doubleVariable(const Variable *variable) override;
    virtual void variable(const Variable *variable) override;

    /**
     *  Negate the boolean expression
     *  @param  expression
     */
    virtual void negateBoolean(const Expression *expression) override;

    /**
     *  Arithmetric operations
     *  @param  left
     *  @param  right
     */
    virtual void plus(const Expression *left, const Expression *right) override;
    virtual void minus(const Expression *left, const Expression *right) override;
    virtual void divide(const Expression *left, const Expression *right) override;
    virtual void multiply(const Expression *left, const Expression *right) override;
    virtual void modulo(const Expression *left, const Expression *right) override;

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
    virtual void regex(const Expression *left, const Expression *right) override;

    /**
     *  Boolean operators
     *  @param  left
     *  @param  right
     */
    virtual void booleanAnd(const Expression *left, const Expression *right) override;
    virtual void booleanOr(const Expression *left, const Expression *right) override;

    /**
     *  Generate the code to apply a set of modifiers on an expression
     *  @param  modifiers          The set of modifiers to apply
     *  @param  expression         The expression to apply to modifiers on
     */
    virtual void modifiers(const Modifiers *modifiers, const Variable *variable) override;

    /**
     *  Generate the code to apply a set of modifiers on an expression and turn it into a scalar
     *  @param  modifiers          The set of modifiers to apply
     *  @param  variable           The variable to apply to modifers to
     */
    virtual void modifiersString(const Modifiers *modifiers, const Variable *variable) override;
    virtual void modifiersBoolean(const Modifiers *modifiers, const Variable *variable) override;
    virtual void modifiersDouble(const Modifiers *modifiers, const Variable *variable) override;

    /**
     *  Generate the code to construct the following parameters
     *  @param  parameters         The parameters to construct
     *  @note Construct as in, generate the code so the runtime can construct them
     */
    virtual void parameters(const Parameters *parameters) override;

    /**
     *  Generate the code to do a foreach loop over variable
     *  @param variable         The variable object to iterate over
     *  @param key              The magic variable name for the keys
     *  @param value            The magic variable name for the values
     *  @param statements       The statements to execute on each iteration
     *  @param else_statements  The statements to execute if there was nothing to loop through
     */
    virtual void foreach(const Variable *variable, const std::string &key, const std::string &value, const Statements *statements, const Statements *else_statements) override;

    /**
     *  Generate the code to assign the output of an expression to a key
     *  @param key                  The key to assign the output to
     *  @param expression           The expression to evaluate
     */
    virtual void assign(const std::string &key, const Expression *expression) override;

public:
    /**
     *  Constructor
     *  @param  tree        The abstract syntax tree of the template
     */
    CCode(const SyntaxTree &tree);

    /**
     *  Constructor
     *  @param  source      The source to generate our C Code from
     */
    CCode(const Source& source);

    /**
     *  Destructor
     */
    virtual ~CCode() {}

    /**
     *  Retrieve the C source as string
     *  @return std::string
     */
    std::string asString() const
    {
        return _out.str();
    }
};

/**
 *  Custom output stream operator
 *  @param  stream
 *  @param  value
 *  @return ostream
 */
inline std::ostream &operator<<(std::ostream &stream, const CCode &value)
{
    return stream << value.asString();
}

/**
 *  End namespace
 */
}}
