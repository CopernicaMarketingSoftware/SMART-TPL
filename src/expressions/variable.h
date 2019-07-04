/**
 *  Variable.h
 *
 *  Expression that contains one variable.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 - 2019 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class Variable : public Expression
{
protected:
    /**
     *  Constructor
     */
    Variable() {}

public:
    /**
     *  Destructor
     */
    virtual ~Variable() = default;

    /**
     *  Generate the output that leaves a pointer to the variable
     *  @param  generator
     */
    virtual void pointer(Generator *generator) const = 0;

    /**
     *  Generate a numeric code for the variable
     *  @param  generator
     */
    virtual void toInteger(Generator *generator) const override
    {
        generator->integerVariable(this);
    }

    /**
     *  Generate the expression as a double value
     *  @param  generator
     */
    virtual void toDouble(Generator *generator) const override
    {
        // turn out numeric value into a double
        generator->doubleVariable(this);
    }

    /**
     *  Generate a boolean code for the variable
     *  @param  generator
     */
    virtual void toBoolean(Generator *generator) const override
    {
        generator->booleanVariable(this);
    }

    /**
     *  Generate a string for the variable
     *  @param  generator
     */
    virtual void toString(Generator *generator) const override
    {
        generator->stringVariable(this);
    }

    /**
     *  Generate a pointer for this variable
     *  @param  generator
     */
    virtual void toPointer(Generator *generator) const override
    {
        // equal to the other pointer method
        this->pointer(generator);
    }

    /**
     *  Generate the expression to output ourself
     *  @param  generator
     */
    virtual void output(Generator *generator) const override
    {
        generator->output(this);
    }
};

/**
 *  End of namespace
 */
}}
