/**
 *  BinaryEquals.h
 *
 *  Implementation of the binary equals operator
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
class BinaryEqualsOperator : public BinaryCompareOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryEqualsOperator(Expression *left, Expression *right) :
        BinaryCompareOperator(left, right) {}
        
    /**
     *  Destructor
     */
    virtual ~BinaryEqualsOperator() {}

    /**
     *  Generate the instruction
     *  @param  generator
     */
    virtual void numeric(Generator *generator) const override
    {
        generator->equals(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}

