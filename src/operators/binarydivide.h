/**
 *  BinaryDivide.h
 *
 *  Implementation of the binary divide operator
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
class BinaryDivideOperator : public BinaryArithmetricOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryDivideOperator(Expression *left, Expression *right) :
        BinaryArithmetricOperator(left, right) {}

    /**
     *  Destructor
     */
    virtual ~BinaryDivideOperator() {}

    /**
     *  Generate the operator to a numeric value
     *  @param  generator
     */
    virtual void toInteger(Generator *generator) const override
    {
        generator->integerDivide(_left.get(), _right.get());
    }

    /**
     *  Generate the operator to a double value
     *  @param  generator
     */
    virtual void toDouble(Generator *generator) const override
    {
        generator->doubleDivide(_left.get(), _right.get());
    }

    /**
     *  Generate the operator to a pointer value
     *  @param  generator
     */
    virtual void toPointer(Generator *generator) const override
    {
        generator->pointerDivide(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}}
