/**
 *  BinaryMultiply.h
 *
 *  Implementation of the binary multiply operator
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
class BinaryMultiplyOperator : public BinaryArithmetricOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryMultiplyOperator(Expression *left, Expression *right) :
        BinaryArithmetricOperator(left, right) {}

    /**
     *  Destructor
     */
    virtual ~BinaryMultiplyOperator() {}

    /**
     *  Generate the operator to a numeric value
     *  @param  generator
     */
    virtual void toInteger(Generator *generator) const override
    {
        generator->integerMultiply(_left.get(), _right.get());
    }

    /**
     *  Generate the operator to a double value
     *  @param  generator
     */
    virtual void toDouble(Generator *generator) const override
    {
        generator->doubleMultiply(_left.get(), _right.get());
    }

    /**
     *  Generate the operator to a pointer value
     *  @param  generator
     */
    virtual void toPointer(Generator *generator) const override
    {
        generator->pointerMultiply(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}}
