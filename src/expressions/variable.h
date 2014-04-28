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
namespace SmartTpl {

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
        generator->numeric(this);
    }

    /**
     *  Generate a boolean code for the variable
     *  @param  generator
     */
    virtual void boolean(Generator *generator) const override
    {
        generator->boolean(this);
    }

    /**
     *  Generate a string for the variable
     *  @param  generator
     */
    virtual void string(Generator *generator) const override
    {
        generator->string(this);
    }
};

/**
 *  End of namespace
 */
}

