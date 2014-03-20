/**
 *  BinaryAnd.h
 *
 *  Implementation of the binary && operator
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
class BinaryAndOperator : public BinaryBooleanOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryAndOperator(Expression *left, Expression *right) :
        BinaryBooleanOperator(left, right) {}
        
    /**
     *  Destructor
     */
    virtual ~BinaryAndOperator() {}

    /**
     *  Virtual method to generate the operator
     *  @param  str
     */
    virtual void generateOperator(std::ostream &str) const override
    {
        str << "&&";
    }
};

/**
 *  End of namespace
 */
}

