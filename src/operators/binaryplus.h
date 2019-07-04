/**
 *  BinaryPlus.h
 *
 *  Implementation of the binary plus operator
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
class BinaryPlusOperator : public BinaryArithmetricOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryPlusOperator(Expression *left, Expression *right) :
        BinaryArithmetricOperator(left, right) {}

    /**
     *  Destructor
     */
    virtual ~BinaryPlusOperator() {}

    /**
     *  Generate the operator to a numeric value
     *  @param  generator
     */
    virtual void toInteger(Generator *generator) const override
    {
        generator->integerPlus(_left.get(), _right.get());
    }

    /**
     *  Generate the operator to a double value
     *  @param  generator
     */
    virtual void toDouble(Generator *generator) const override
    {
        generator->doublePlus(_left.get(), _right.get());
    }

    /**
     *  Generate the operator to a pointer value
     *  @param  generator
     */
    virtual void toPointer(Generator *generator) const override
    {
        generator->pointerPlus(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}}
