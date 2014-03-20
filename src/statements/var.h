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
     *  @param  str     output stream
     */
    virtual void generate(std::ostream &str) const override
    {
        // we are going to generate the code that first get a pointer to the 
        // variable, and that then calls the write method on it
        _var->generateVariable(str);
        
        // call the write method on the generated pointer
        str << "->write();" << std::endl;
    }
};

/**
 *  End of namespace
 */
}

