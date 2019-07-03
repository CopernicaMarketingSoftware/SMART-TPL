/**
 *  BinaryMinus.h
 *
 *  Implementation of the binary minus operator
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
class BinaryMinusOperator : public BinaryArithmetricOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryMinusOperator(Expression *left, Expression *right) :
        BinaryArithmetricOperator(left, right) {}

    /**
     *  Destructor
     */
    virtual ~BinaryMinusOperator() {}

    /**
     *  Generate the operator to a numeric value
     *  @param  generator
     */
    virtual void toInteger(Generator *generator) const override
    {
        generator->integerMinus(_left.get(), _right.get());
    }

    /**
     *  Generate the operator to a double value
     *  @param  generator
     */
    virtual void toDouble(Generator *generator) const override
    {
        generator->doubleMinus(_left.get(), _right.get());
    }

    /**
     *  Generate the operator to a pointer value
     *  @param  generator
     */
    virtual void toPointer(Generator *generator) const override
    {
        generator->pointerMinus(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}}
