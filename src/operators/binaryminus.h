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
     *  Virtual method to generate the operator
     *  @param  str
     */
    virtual void generateOperator(std::ostream &str) const override
    {
        str << "-";
    }
};

/**
 *  End of namespace
 */
}

