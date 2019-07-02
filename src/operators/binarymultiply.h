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
     *  Generate the operations
     *  @param  generator
     */
    virtual void toInteger(Generator *generator) const override
    {
        generator->multiply(_left.get(), _right.get());
    }

    /**
     *  Generate the instruction
     *  @param  generator
     */
    virtual void toBoolean(Generator *generator) const override
    {
        generator->multiply(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}}
