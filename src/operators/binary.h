/**
 *  Binary.h
 *
 *  Base class for binary operators.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class BinaryOperator : public Operator
{
protected:
    /**
     *  Left side of the operator
     *  @var    Expression
     */
    std::unique_ptr<Expression> _left;

    /**
     *  Right side of the operator
     *  @var    Expression
     */
    std::unique_ptr<Expression> _right;


public:
    /**
     *  Protected constructor because this is just a base class
     *  @param  left
     *  @param  right
     */
    BinaryOperator(Expression *left, Expression *right) :
        _left(left),
        _right(right) {}

    /**
     *  Destructor
     */
    virtual ~BinaryOperator() {}

    /**
     *  The return type of the expression
     *  @return Type
     */
    virtual Type type() const override { return Type::Boolean; }

    /**
     *  Binary operators are not atomic
     *  @return bool
     */
    virtual bool is_atomic() const override { return false; }
};

/**
 *  End namespace
 */
}}