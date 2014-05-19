/**
 *  Assign.h
 *
 *  Statement to assign the output of an expression to a variable
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class AssignStatement : public Statement
{
private:
    /**
     *  The variable we'll assign to
     */
    std::unique_ptr<Token> _var;

    /**
     *  The expression we would like to assign
     */
    std::unique_ptr<Expression> _expression;

public:
    /**
     *  Constructor
     *  @param expression          The expression we would like to assign to a variable
     *  @param var                 The variable we would like to assign it to
     *  @throws std::runtime_error In case the variable is not of type LiteralVariable
     */
    AssignStatement(Expression *expression, Token *var)
    : _var(var)
    , _expression(expression) {}

    /**
     *  Destructor
     */
    virtual ~AssignStatement() {}

    /**
     *  Generate the output of this statement
     *  @param  generator
     */
    virtual void generate(Generator *generator) const override
    {
        generator->assign(*_var, _expression.get());
    }
};

/**
 *  End of namespace
 */
}}