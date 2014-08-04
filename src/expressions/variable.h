/**
 *  Variable.h
 *
 *  Expression that contains one variable.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
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
    virtual ~Variable() {}

    /**
     *  Generate the output that leaves a pointer to the variable
     *  @param  generator
     */
    virtual void pointer(Generator *generator) const = 0;

    /**
     *  Generate a numeric code for the variable
     *  @param  generator
     */
    virtual void numeric(Generator *generator) const override
    {
        generator->numericVariable(this);
    }

    /**
     *  Generate the expression as a double value
     *  @param  generator
     */
    virtual void double_type(Generator *generator) const override
    {
        // turn out numeric value into a double
        generator->doubleVariable(this);
    }

    /**
     *  Generate a boolean code for the variable
     *  @param  generator
     */
    virtual void boolean(Generator *generator) const override
    {
        generator->booleanVariable(this);
    }

    /**
     *  Generate a string for the variable
     *  @param  generator
     */
    virtual void string(Generator *generator) const override
    {
        generator->stringVariable(this);
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