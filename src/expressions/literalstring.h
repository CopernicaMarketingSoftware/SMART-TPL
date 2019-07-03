/**
 *  String.h
 *
 *  Implementation of a literal string value
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
class LiteralString : public Literal
{
private:
    /**
     *  The actual value
     *  @var    std::string
     */
    std::unique_ptr<const Token> _value;

public:
    /**
     *  Constructor
     *  @param  std::string
     */
    LiteralString(Token *value) : _value(value) {}

    /**
     *  Destructor
     */
    virtual ~LiteralString() {}

    /**
     *  The return type of the expression
     *  @return Type
     */
    Type type() const override { return Type::String; }

    /**
     *  Generate the code to get the const char * to the expression
     *  @param  generator
     */
    virtual void toString(Generator *generator) const override
    {
        // generate our actual value
        generator->stringValue(*_value);
    }

    /**
     *  Generate the code to get the boolean value of the expression
     *  @param  generator
     */
    virtual void toBoolean(Generator *generator) const override
    {
        // call the numeric generator with wether we're empty or not
        generator->integerValue(!_value->empty());
    }

    /**
     *  Generate the code to get the integer value of the expression
     *  @param  generator
     */
    virtual void toInteger(Generator *generator) const override
    {
        try
        {
            // try to parse the string
            generator->integerValue(std::strtoll(_value->c_str(), nullptr, 10));
        }
        catch (...)
        {
            // if that doesn't work just return 0
            generator->integerValue(0);
        }
    }

    /**
     *  Generate the expression as a double value
     *  @param  generator
     */
    virtual void toDouble(Generator *generator) const override
    {
        try
        {
            // try to parse the string
            generator->doubleValue(std::strtod(_value->c_str(), nullptr));
        }
        catch (...)
        {
            // if that doesn't work just return 0
            generator->doubleValue(0);
        }
    }

    /**
     *  Generate expression as a pointer to the runtime space
     *  @param  generator
     */
    virtual void toPointer(Generator *generator) const override
    {
        // call the appropriate function in the generator
        generator->pointerString(this);
    }
};

/**
 *  End namespace
 */
}}
