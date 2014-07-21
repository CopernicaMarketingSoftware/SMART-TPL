/**
 *  Expression.h
 *
 *  Statement to echo the output of an expression
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
class ExpressionStatement : public Statement
{
private:
    /**
     *  The expression that should be executed
     *  @var    Expression
     */
    std::unique_ptr<Expression> _expression;

public:
    /**
     *  Constructor
     *  @param  expression
     */
    ExpressionStatement(Expression *expression) : _expression(expression) {}

    /**
     *  Destructor
     */
    virtual ~ExpressionStatement() {}

    /**
     *  Generate the output of this statement
     *  @param  generator
     */
    virtual void generate(Generator *generator) const override
    {
        _expression->output(generator);
    }
};

/**
 *  End of namespace
 */
}}