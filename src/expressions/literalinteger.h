/**
 *  LiteralInteger.h
 *
 *  Implementation of a literal integer value
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
class LiteralInteger : public Literal
{
private:
    /**
     *  The actual value
     *  @var    numeric_t
     */
    const numeric_t _value;

public:
    /**
     *  Constructor
     *  @param  token
     */
    LiteralInteger(Token *token)
    : _value(std::strtoll(token->c_str(), nullptr, 10))
    {
        // we no longer need the token
        delete token;
    }

    /**
     *  Destructor
     */
    virtual ~LiteralInteger() {}

    /**
     *  The return type of the expression
     *  @return Type
     */
    virtual Type type() const { return Type::Numeric; }

    /**
     *  Generate the code to get the const char * to the expression
     *  @param  generator
     */
    virtual void string(Generator *generator) const override
    {
        // create string literal
        generator->string(std::to_string(_value));
    }

    /**
     *  Generate the code to get the boolean value of the expression
     *  @param  generator
     */
    virtual void boolean(Generator *generator) const override
    {
        // create numeric literal
        generator->numeric(_value ? 1 : 0);
    }

    /**
     *  Generate the code to get the numeric value of the expression
     *  @param  generator
     */
    virtual void numeric(Generator *generator) const override
    {
        // create numeric literal
        generator->numeric(_value);
    }
};

/**
 *  End namespace
 */
}}