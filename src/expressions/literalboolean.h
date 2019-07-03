/**
 *  Boolean.h
 *
 *  Implementation of a literal boolean value
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
class LiteralBoolean : public Literal
{
private:
    /**
     *  The actual value
     *  @var    bool
     */
    const bool _value;

public:
    /**
     *  Constructor
     *  @param  bool
     */
    LiteralBoolean(bool value) : _value(value) {}

    /**
     *  Destructor
     */
    virtual ~LiteralBoolean() {}

    /**
     *  The return type of the expression
     *  @return Type
     */
    Type type() const override { return Type::Boolean; }

    /**
     *  Generate the code to get the const char * to the expression
     *  @param  generator
     */
    virtual void toString(Generator *generator) const override
    {
        // create an empty string, booleans have no output
        generator->stringValue("");
    }

    /**
     *  Generate the code to get the boolean value of the expression
     *  @param  generator
     */
    virtual void toBoolean(Generator *generator) const override
    {
        // turn the value into 1 or 0 (in C there are no booleans)
        generator->integerValue(_value ? 1 : 0);
    }

    /**
     *  Generate the code to get the integer value of the expression
     *  @param  generator
     */
    virtual void toInteger(Generator *generator) const override
    {
        // turn the value into 1 or 0 (in C there are no booleans)
        generator->integerValue(_value ? 1 : 0);
    }

    /**
     *  Generate the expression as a double value
     *  @param  generator
     */
    virtual void toDouble(Generator *generator) const override
    {
        // turn the value into 1 or 0 (in C there are no booleans)
        generator->doubleValue(_value ? 1 : 0);
    }

    /**
     *  Generate expression as a pointer to the runtime space
     *  @param  generator
     */
    virtual void toPointer(Generator *generator) const override
    {
        // call the appropriate function in the generator
        generator->pointerBoolean(this);
    }
};

/**
 *  End namespace
 */
}}
