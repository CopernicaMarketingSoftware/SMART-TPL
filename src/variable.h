/**
 *  Variable.h
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
class Variable : public Expression
{
private:
    /**
     *  Name of the variable
     *  @var    std::string
     */
    std::string _name;
    
public:
    /**
     *  Constructor
     *  @param  token
     */
    Variable(const Token *token) : _name(token->value, token->size) {}
    
    /**
     *  Destructor
     */
    virtual ~Variable() {}
};

/**
 *  End of namespace
 */
}

