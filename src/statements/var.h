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
namespace SmartTpl { namespace Internal {

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
        // Check if the expression is a variable, if it is just output it, write it otherwise
        Variable* variable = dynamic_cast<Variable*>(_expression.get());
        if (variable)
        {
            generator->output(variable);
        }
        else
        {
            Filter *filter = dynamic_cast<Filter*>(_expression.get());
            if (filter)
            {
                generator->output(filter);
            }
            else
            {
                generator->write(_expression.get());
            }
        }
    }
};

/**
 *  End of namespace
 */
}}