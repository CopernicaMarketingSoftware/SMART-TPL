/**
 *  BinaryGreaterEquals.h
 *
 *  Implementation of the binary greater-or-equals operator
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
class BinaryGreaterEqualsOperator : public BinaryCompareOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryGreaterEqualsOperator(Expression *left, Expression *right) :
        BinaryCompareOperator(left, right) {}
        
    /**
     *  Destructor
     */
    virtual ~BinaryGreaterEqualsOperator() {}

    /**
     *  Generate the instruction
     *  @param  generator
     */
    virtual void numeric(Generator *generator) const override
    {
        generator->greaterEquals(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}

