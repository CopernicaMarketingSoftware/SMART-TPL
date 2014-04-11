/**
 *  Modifier.h
 *
 *  A single modifier that is applied to an expression ("$a|modifier")
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class Modifier
{
private:
    /**
     *  Name of the variable
     *  @var    Token
     */
    std::unique_ptr<const Token> _name;

    /**
     *  Optional additional parameters
     *  @var    Parameters
     */
    std::unique_ptr<const Parameters> _parameters;

public:    
    /**
     *  Constructor
     *  @param  name
     */
    Modifier(const Token *name) : _name(name) {}

    /**
     *  Constructor
     *  @param  name
     *  @param  parameters
     */
    Modifier(const Token *name, const Parameters *parameters) : _name(name), _parameters(parameters) {}
    
    /** 
     *  Destructor
     */
    virtual ~Modifier() {}
    
};

/**
 *  End namespace
 */
}

