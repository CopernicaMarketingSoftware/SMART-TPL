/**
 *  BinaryOr.h
 *
 *  Implementation of the binary || operator
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
class BinaryOrOperator : public BinaryBooleanOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryOrOperator(Expression *left, Expression *right) :
        BinaryBooleanOperator(left, right) {}
        
    /**
     *  Destructor
     */
    virtual ~BinaryOrOperator() {}

    /**
     *  Virtual method to generate the operator
     *  @param  str
     */
    virtual void generateOperator(std::ostream &str) const override
    {
        str << "||";
    }
};

/**
 *  End of namespace
 */
}

