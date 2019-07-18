/**
 *  AnonymousIntegerVariable.h
 * 
 *  Class that holds an integer variable that does not have a name but rather is based
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
class AnonymousIntegerVariable : public AnonymousVariable
{
private:
    /**
     *  The actual value
     *  @var    integer_t
     */
    const integer_t _value;

public:
    /**
     *  Constructor
     *  @param  Token*      the value of the anonymous variable
     */
    AnonymousIntegerVariable(const Token *contents) :
        AnonymousVariable(Type::Integer),
        _value(std::strtoll(contents->c_str(), nullptr, 10)) {}

    /**
     *  Destructor
     */
    virtual ~AnonymousIntegerVariable() {}
 
    /**
     *  Generate the output that leaves a pointer to the variable
     *  @param  generator
     */
    void pointer(Generator *generator) const override
    {
        // generate the code to get a variable pointer
        generator->pointerInteger(_value);
    }


};

/**
 *  End of namespace
 */
}}