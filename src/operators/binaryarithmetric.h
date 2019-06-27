/**
 *  BinaryArtithmetric.h
 *
 *  Class for arithmetric operators
 *
 *  @copyright 2014 - 2019 Copernica BV
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

    /**
     *  The return type of the expression, which depends on the left and right expression
     *  @return Type
     */
    virtual Type type() const override 
    {
        // if both expressions are numeric, so is the entire operation
        if (_left->type() == Type::Numeric && _right->type() == Type::Numeric) return Type::Numeric;

        // For now, we'll assume the operation to be double until we have proper runtime evaluation
        return Type::Double;
    }
};

/**
 *  End namespace
 */
}}