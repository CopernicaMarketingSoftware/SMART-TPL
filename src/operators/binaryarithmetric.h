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
     *  The return type of the expression
     *  @return Type
     */
    virtual Type type() const override 
    { 
        // if both types are integer, so is the result of the operation
        if (_left->type() == Type::Integer && _right->type() == Type::Integer) return Type::Integer;

        // if one of the types is double, so is the entire operation
        if (_left->type() == Type::Double || _right->type() == Type::Double) return Type::Double;

        // otherwise, we have to determine at runtime
        return Type::Value;
    }
};

/**
 *  End namespace
 */
}}
