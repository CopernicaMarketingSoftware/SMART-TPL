/**
 *  VarStatement.h
 *
 *  Statement to echo output of a {$variable}.
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
class VarStatement : public Statement
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
    VarStatement(Expression *expression) : _expression(std::unique_ptr<Expression>(expression)) {}
    
    /**
     *  Destructor
     */
    virtual ~VarStatement() {}

    /**
     *  Generate the output of this statement
     *  @param  generator
     */
    virtual void generate(Generator *generator) const override
    {
        // tell the generator to evaluate an expression, and output it
        generator->output(_expression.get());
    }
};

/**
 *  End of namespace
 */
}

