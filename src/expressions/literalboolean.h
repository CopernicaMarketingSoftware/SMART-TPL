/**
 *  Boolean.h
 *
 *  Implementation of a literal boolean value
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl {

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
    bool _value;
    
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
     *  Generate the code to get the const char * to the expression
     *  @param  generator
     */
    virtual void string(Generator *generator) const override
    {
        // create an empty string, booleans have no output
        generator->string("");
    }

    /**
     *  Generate the code to get the boolean value of the expression
     *  @param  generator
     */
    virtual void boolean(Generator *generator) const override
    {
        // turn the value into 1 or 0 (in C there are no booleans)
        generator->numeric(_value ? 1 : 0);
    }
    
    /**
     *  Generate the code to get the integer value of the expression
     *  @param  generator
     */
    virtual void numeric(Generator *generator) const override
    {
        // turn the value into 1 or 0 (in C there are no booleans)
        generator->numeric(_value ? 1 : 0);
    }

    virtual void variable(Generator *generator) const override
    {
        boolean(generator);
    }
};

/**
 *  End namespace
 */
}

