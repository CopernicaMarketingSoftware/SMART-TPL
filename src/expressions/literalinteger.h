/**
 *  LiteralInteger.h
 *
 *  Implementation of a literal numeric value
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 - 2019 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class LiteralInteger : public Literal
{
private:
    /**
     *  The actual value
     *  @var    integer_t
     */
    const integer_t _value;

    /**
     *  The provided string representation of the literal
     *  @var    std::string
     */
    std::unique_ptr<const Token> _token;

public:
    /**
     *  Constructor
     *  @param  token
     */
    LiteralInteger(Token *token)
    : _value(std::strtoll(token->c_str(), nullptr, 10)), _token(token) {}

    /**
     *  Destructor
     */
    virtual ~LiteralInteger() {}

    /**
     *  The return type of the expression
     *  @return Type
     */
    Type type() const override { return Type::Integer; }

    /**
     *  Generate the code to get the const char * to the expression
     *  @param  generator
     */
    virtual void toString(Generator *generator) const override
    {
        // create string literal
        generator->stringValue(*_token);
    }

    /**
     *  Generate the code to get the boolean value of the expression
     *  @param  generator
     */
    virtual void toBoolean(Generator *generator) const override
    {
        // create numeric literal
        generator->integerValue(_value ? 1 : 0);
    }

    /**
     *  Generate the code to get the numeric value of the expression
     *  @param  generator
     */
    virtual void toInteger(Generator *generator) const override
    {
        // create numeric literal
        generator->integerValue(_value);
    }

    /**
     *  Generate the expression as a double value
     *  @param  generator
     */
    virtual void toDouble(Generator *generator) const override
    {
        // turn out numeric value into a double
        generator->doubleValue(_value);
    }

    /**
     *  Generate expression as a pointer to the runtime space
     *  @param  generator
     */
    virtual void toPointer(Generator *generator) const override
    {
        // call the appropriate function in the generator
        generator->pointerInteger(this);
    }
};

/**
 *  End namespace
 */
}}
