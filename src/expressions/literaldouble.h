/**
 *  LiteralDouble.h
 *
 *  Implementation of a literal integer value
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 - 2019 Copernica BV
 */

/**
 *  Dependencies
 */
#include <locale>

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
    double _value;

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
    LiteralDouble(Token *token): _token(token) 
    {
        // The current system we're running on might be set to another locale, 
        // which has comma separators instead of dots. To ensure correct
        // parsing of the floating point number, we temporarily reset the locale
        // First, get the current locale setting
        auto current = setlocale(LC_NUMERIC, NULL);

        // force en_US locale for numeric values
        setlocale(LC_NUMERIC, "en_US");

        // parse the token
        _value = std::strtod(token->c_str(), nullptr);

        // reset locale
        setlocale(LC_NUMERIC, current);
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
        // create numeric literal (We actually don't really want to reach this I think)
        generator->integerValue(_value);
    }

    /**
     *  Generate the expression as a double value
     *  @param  generator
     */
    virtual void toDouble(Generator *generator) const override
    {
        // create a double type
        generator->doubleValue(_value);
    }

    /**
     *  Generate expression as a pointer to the runtime space
     *  @param  generator
     */
    virtual void toPointer(Generator *generator) const override
    {
        // call the appropriate function in the generator
        generator->pointerDouble(this);
    }
};

/**
 *  End namespace
 */
}}
