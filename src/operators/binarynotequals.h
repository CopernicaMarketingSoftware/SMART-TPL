/**
 *  BinaryNotEquals.h
 *
 *  Implementation of the binary not-equals operator
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
class BinaryNotEqualsOperator : public BinaryCompareOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryNotEqualsOperator(Expression *left, Expression *right) :
        BinaryCompareOperator(left, right) {}
        
    /**
     *  Destructor
     */
    virtual ~BinaryNotEqualsOperator() {}

    /**
     *  Virtual method to generate the operator
     *  @param  str
     */
    virtual void generateOperator(std::ostream &str) const override
    {
        str << "!=";
    }
};

/**
 *  End of namespace
 */
}

