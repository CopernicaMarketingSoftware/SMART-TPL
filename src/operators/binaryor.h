/**
 *  BinaryOr.h
 *
 *  Implementation of the binary || operator
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
class BinaryOrOperator : public BinaryBooleanOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryOrOperator(Expression *left, Expression *right) :
        BinaryBooleanOperator(left, right) {}
        
    /**
     *  Destructor
     */
    virtual ~BinaryOrOperator() {}

    /**
     *  Generate the instruction
     *  @param  generator
     */
    virtual void numeric(Generator *generator) const override
    {
        generator->booleanOr(_left.get(), _right.get());
    }

    /**
     *  Generate the instruction
     *  @param  generator
     */
    virtual void boolean(Generator *generator) const override
    {
        generator->booleanOr(_left.get(), _right.get());
    }

    virtual void variable(Generator *generator) const override
    {
        boolean(generator);
    }
};

/**
 *  End of namespace
 */
}

