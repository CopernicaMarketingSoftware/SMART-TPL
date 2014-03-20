/**
 *  BinaryLesserEquals.h
 *
 *  Implementation of the binary lesser-or-equals operator
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
class BinaryLesserEqualsOperator : public BinaryCompareOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryLesserEqualsOperator(Expression *left, Expression *right) :
        BinaryCompareOperator(left, right) {}
        
    /**
     *  Destructor
     */
    virtual ~BinaryLesserEqualsOperator() {}

    /**
     *  Virtual method to generate the operator
     *  @param  str
     */
    virtual void generateOperator(std::ostream &str) const override
    {
        str << "<=";
    }
};

/**
 *  End of namespace
 */
}

