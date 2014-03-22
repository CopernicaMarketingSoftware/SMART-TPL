/**
 *  BinaryArtithmetric.h
 *
 *  Class for arithmetric operators
 *
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class BinaryArithmetricOperator : public BinaryOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryArithmetricOperator(Expression *left, Expression *right) :
        BinaryOperator(left, right) {}
        
    /**
     *  Destructor
     */
    virtual ~BinaryArithmetricOperator() {}

    /**
     *  Generate the code to get the const char * to the expression
     *  @param  generator
     */
    virtual void string(Generator *generator) const override
    {
        // this needs to be casted to a string
        generator->numericToString(this);
    }
};

/**
 *  End namespace
 */
}
