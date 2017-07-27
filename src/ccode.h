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
 *  @copyright 2014 - 2017 Copernica BV
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
    void condition(const Expression *expression, const Statements *ifstatements, const  Statements *elsestatements) override;

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
    void double_type(double value) override;

    /**
     *  Create a string, numeric or boolean constant for a variable
     *  @param  variable
     */
    void stringVariable(const Variable *variable) override;
    void numericVariable(const Variable *variable) override;
    void booleanVariable(const Variable *variable) override;
    void doubleVariable(const Variable *variable) override;
    void variable(const Variable *variable) override;

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
     *  Generate the code to apply a set of modifiers on an expression and turn it into a boolean
     *  @param  modifiers          The set of modifiers to apply
     *  @param  variable           The variable to apply to modifers to
     */
    void modifiersBoolean(const Modifiers *modifiers, const Variable *variable) override;
    /**
     *  Generate the code to apply a set of modifiers on an expression and turn it into a double
     *  @param  modifiers          The set of modifiers to apply
     *  @param  variable           The variable to apply the modifiers to
     */
    void modifiersDouble(const Modifiers *modifiers, const Variable *variable) override;

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
