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
namespace SmartTpl {

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
        _left(std::unique_ptr<Expression>(left)),
        _right(std::unique_ptr<Expression>(right)) {}
        
    /**
     *  Destructor
     */
    virtual ~BinaryOperator() {}

    /**
     *  The return type of the expression
     *  @return Type
     */
    virtual Type type() const { return Type::Boolean; }
};

/**
 *  End namespace
 */
}


 