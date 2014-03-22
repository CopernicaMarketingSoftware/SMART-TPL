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
     *  The variable that should be displayed
     *  @var    Variable
     */
    std::unique_ptr<Variable> _var;

public:
    /**
     *  Constructor
     *  @param  var
     */
    VarStatement(Variable *var) : _var(std::unique_ptr<Variable>(var)) {}
    
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
        generator->output(_var.get());
    }
};

/**
 *  End of namespace
 */
}

