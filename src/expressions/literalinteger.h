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
    Type type() const override { return Type::Integer; }

    /**
     *  Generate the code to get the const char * to the expression
     *  @param  generator
     */
    void string(Generator *generator) const override
    {
        // create string literal
        generator->string(std::to_string(_value));
    }

    /**
     *  Generate the code to get the boolean value of the expression
     *  @param  generator
     */
    void boolean(Generator *generator) const override
    {
        // create numeric literal
        generator->numeric(_value ? 1 : 0);
    }

    /**
     *  Generate the code to get the numeric value of the expression
     *  @param  generator
     */
    void numeric(Generator *generator) const override
    {
        // create numeric literal
        generator->numeric(_value);
    }

    /**
     *  Generate the expression as a double value
     *  @param  generator
     */
    void double_type(Generator *generator) const override
    {
        // turn out numeric value into a double
        generator->double_type(_value);
    }
};

/**
 *  End namespace
 */
}}
