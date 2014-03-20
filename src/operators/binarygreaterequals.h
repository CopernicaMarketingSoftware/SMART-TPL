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
     *  Virtual method to generate the operator
     *  @param  str
     */
    virtual void generateOperator(std::ostream &str) const override
    {
        str << ">=";
    }
};

/**
 *  End of namespace
 */
}

