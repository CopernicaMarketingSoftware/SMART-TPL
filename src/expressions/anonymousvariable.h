/**
 *  AnonymousVariable.h
 * 
 *  Class that holds a variable that does not have a name but rather is based
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
class AnonymousVariable : public Variable
{
private:
    /**
     *  The actual value
     *  @var    std::string
     */
    std::unique_ptr<Literal> _value;

public:
    /**
     *  Create a anonymous variable from a literal
     *  @param  literal
     */
    AnonymousVariable(Literal *contents) : _value(contents) {}

    /**
     *  Destructor
     */
    virtual ~AnonymousVariable() {}

    /**
     *  The return type of the expression (we force a string for the modifiers)
     *  @return Type
     */
    virtual Type type() const override { return Type::String; }

     /**
     *  Generate the output that leaves a pointer to the variable
     *  @param  generator
     */
    virtual void pointer(Generator *generator) const override
    {
        // generate the code to get a variable pointer to a string
        generator->pointerString(_value.get());
    }
};

/**
 *  End of namespace
 */
}}