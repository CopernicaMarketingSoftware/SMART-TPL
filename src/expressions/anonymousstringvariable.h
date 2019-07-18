/**
 *  AnonymousStringVariable.h
 * 
 *  Class that holds a string variable that does not have a name but rather is based
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
class AnonymousStringVariable : public AnonymousVariable
{
private:
    /**
     *  The actual value
     *  @var    std::string
     */
    std::unique_ptr<Token> _value;

public:
    /**
     *  Constructor
     *  @param  Token*      the value of the anonymous variable
     */
    AnonymousStringVariable(Token *contents) :
        AnonymousVariable(Type::String),
        _value(contents) {}

    /**
     *  Destructor
     */
    virtual ~AnonymousStringVariable() {}
 
    /**
     *  Generate the output that leaves a pointer to the variable
     *  @param  generator
     */
    virtual void pointer(Generator *generator) const override
    {
        // generate the code to get a variable pointer
        generator->pointerString(*_value);
    }


};

/**
 *  End of namespace
 */
}}