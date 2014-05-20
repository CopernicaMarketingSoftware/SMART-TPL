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
namespace SmartTpl { namespace Internal {

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
};

/**
 *  End namespace
 */
}}