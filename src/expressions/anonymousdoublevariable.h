/**
 *  AnonymousDoubleVariable.h
 * 
 *  Class that holds a double variable that does not have a name but rather is based
 *  on a literal, so that literals can be treated as variables (e.g. for usage
 *  with modifiers)
 * 
 *  @author     David van Erkelens <david.vanerkelens@copernica.com>
 *  @copyright  2019 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class AnonymousDoubleVariable : public AnonymousVariable
{
private:
    /**
     *  The actual value
     *  @var    double
     */
    const double _value;

public:
    /**
     *  Constructor
     *  @param  Token*      the value of the anonymous variable
     */
    AnonymousDoubleVariable(Token *token) :
        AnonymousVariable(Type::Double),
        _value(std::strtod(token->c_str(), nullptr))
    {
        // token is no longer required
        delete token;
    }

    /**
     *  Destructor
     */
    virtual ~AnonymousDoubleVariable() {}
 
    /**
     *  Generate the output that leaves a pointer to the variable
     *  @param  generator
     */
    virtual void pointer(Generator *generator) const override
    {
        // generate the code to get a variable pointer
        generator->pointerDouble(_value);
    }
};

/**
 *  End of namespace
 */
}}