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
private:

    /**
     *  The type of the operator expression
     *  @var Type
     */
    Type _type = Type::Numeric;


public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryArithmetricOperator(Expression *left, Expression *right) :
        BinaryOperator(left, right) 
    {
        // if one of the expression is a double, so is the entire expression
        if (left->type() == Type::Double || right->type() == Type::Double) _type = Type::Double;

        // if one of the expressions is a value, we also treat the expression as a double type
        if (left->type() == Type::Value || right->type() == Type::Value) _type = Type::Double;
    }

    /**
     *  Destructor
     */
    virtual ~BinaryArithmetricOperator() {}

    /**
     *  The return type of the expression
     *  @return Type
     */
    virtual Type type() const override { return _type; }
};

/**
 *  End namespace
 */
}}