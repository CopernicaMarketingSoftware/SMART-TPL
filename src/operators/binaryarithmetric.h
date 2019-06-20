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
        // If one of both expression types is double, so is the complete expression
        if (_left->type() == Type::Double || _right->type() == Type::Double) return Type::Double;

        // Otherwise, assume numeric (if a boolean or string was provided)
        return Type::Numeric;
    }
};

/**
 *  End namespace
 */
}}