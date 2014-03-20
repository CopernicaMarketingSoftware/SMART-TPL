/**
 *  BinaryMultiply.h
 *
 *  Implementation of the binary multiply operator
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
     *  Virtual method to generate the operator
     *  @param  str
     */
    virtual void generateOperator(std::ostream &str) const override
    {
        str << "*";
    }
};

/**
 *  End of namespace
 */
}

