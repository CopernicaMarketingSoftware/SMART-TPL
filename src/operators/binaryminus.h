/**
 *  BinaryMinus.h
 *
 *  Implementation of the binary minus operator
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
     *  Generate the operations
     *  @param  generator
     */
    virtual void numeric(Generator *generator) const override
    {
        generator->minus(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}

