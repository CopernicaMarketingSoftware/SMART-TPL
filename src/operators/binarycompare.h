/**
 *  BinaryCompare.h
 *
 *  Base class for comparison operators
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
class BinaryCompareOperator : public BinaryOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryCompareOperator(Expression *left, Expression *right) :
        BinaryOperator(left, right) {}

    /**
     *  Destructor
     */
    virtual ~BinaryCompareOperator() {}
};

/**
 *  End namespace
 */
}}