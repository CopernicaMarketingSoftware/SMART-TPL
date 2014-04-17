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
     *  The variable
     *  @var    Variable
     */
    std::unique_ptr<Variable> _variable;

public:
    /**
     *  Constructor
     *  @param  expression
     */
    VarStatement(Variable *variable) : _variable(std::unique_ptr<Variable>(variable)) {}
    
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
        generator->output(_variable.get());
    }
};

/**
 *  End of namespace
 */
}

