/**
 *  ModifierExpression.h
 *
 *  A single modifier that is applied to an expression ("$a|modifier")
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class ModifierExpression
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
    ModifierExpression(const Token *name) : _name(name) {}

    /**
     *  Constructor
     *  @param  name
     *  @param  parameters
     */
    ModifierExpression(const Token *name, const Parameters *parameters) : _name(name), _parameters(parameters) {}

    /**
     *  Destructor
     */
    virtual ~ModifierExpression() {}

    /**
     *  The name of the modifier
     *  @return const std::string
     */
    const std::string token() const { return *_name; };

    /**
     *  Returns the internal Parameters object
     */
    const Parameters *parameters() const { return _parameters.get(); };

};

/**
 *  End namespace
 */
}}