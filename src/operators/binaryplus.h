/**
 *  BinaryPlus.h
 *
 *  Implementation of the binary plus operator
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
     *  @param  Generator *generator
     */
    virtual void numeric(Generator *generator) const override
    {
        generator->plus(_left.get(), _right.get());
    }

    /**
     *  Generate the instruction
     *  @param  generator
     */
    virtual void boolean(Generator *generator) const override
    {
        generator->plus(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}

