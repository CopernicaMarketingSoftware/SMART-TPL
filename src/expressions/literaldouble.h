/**
 *  LiteralDouble.h
 *
 *  Implementation of a literal integer value
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
class LiteralDouble : public Literal
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
     *  @param  token
     */
    LiteralDouble(Token *token)
    : _value(std::strtod(token->c_str(), nullptr))
    {
        // we no longer need the token
        delete token;
    }

    /**
     *  Destructor
     */
    virtual ~LiteralDouble() {}

    /**
     *  The return type of the expression
     *  @return Type
     */
    Type type() const override { return Type::Double; }

    /**
     *  Generate the code to get the const char * to the expression
     *  @param  generator
     */
    void string(Generator *generator) const override
    {
        // create string literal
        generator->stringValue(std::to_string(_value));
    }

    /**
     *  Generate the code to get the boolean value of the expression
     *  @param  generator
     */
    void boolean(Generator *generator) const override
    {
        // create numeric literal
        generator->integerValue(_value ? 1 : 0);
    }

    /**
     *  Generate the code to get the numeric value of the expression
     *  @param  generator
     */
    void numeric(Generator *generator) const override
    {
        // create numeric literal (We actually don't really want to reach this I think)
        generator->integerValue(_value);
    }

    /**
     *  Generate the expression as a double value
     *  @param  generator
     */
    void double_type(Generator *generator) const override
    {
        // create a double type
        generator->doubleValue(_value);
    }
};

/**
 *  End namespace
 */
}}
