/**
 *  BinaryDivide.h
 *
 *  Implementation of the binary divide operator
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
class BinaryDivideOperator : public BinaryArithmetricOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryDivideOperator(Expression *left, Expression *right) :
        BinaryArithmetricOperator(left, right) {}
        
    /**
     *  Destructor
     */
    virtual ~BinaryDivideOperator() {}

    /**
     *  Virtual method to generate the operator
     *  @param  str
     */
    virtual void generateOperator(std::ostream &str) const override
    {
        str << "/";
    }
};

/**
 *  End of namespace
 */
}

