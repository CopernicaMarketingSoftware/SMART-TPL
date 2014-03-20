/**
 *  LiteralVariable.h
 *
 *  Expression that contains one variable.
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
class LiteralVariable : public Variable
{
private:
    /**
     *  Name of the variable
     *  @var    std::unique_ptr
     */
    std::unique_ptr<Token> _name;
    
public:
    /**
     *  Constructor
     *  @param  token
     */
    LiteralVariable(Token *token) : 
        _name(token) {}
    
    /**
     *  Destructor
     */
    virtual ~LiteralVariable() {}
    
    /**
     *  Generate the output that leaves a pointer to the variable
     *  @param  str
     */
    virtual void generateVariable(std::ostream &str) const override
    {
        // call the callback to get the variable
        str << "callbacks->variable(\"" << *_name << "\"," << _name->size() << ")";
    }
};

/**
 *  End of namespace
 */
}

