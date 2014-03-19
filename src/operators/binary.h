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
};

using BinaryOperatorPlus            =   BinaryOperator;
using BinaryOperatorMinus           =   BinaryOperator;
using BinaryOperatorMultiply        =   BinaryOperator;
using BinaryOperatorDivide          =   BinaryOperator;
using BinaryOperatorOr              =   BinaryOperator;
using BinaryOperatorAnd             =   BinaryOperator;
using BinaryOperatorEquals          =   BinaryOperator;
using BinaryOperatorNotEquals       =   BinaryOperator;
using BinaryOperatorGreater         =   BinaryOperator;
using BinaryOperatorGreaterEquals   =   BinaryOperator;
using BinaryOperatorLesser          =   BinaryOperator;
using BinaryOperatorLesserEquals    =   BinaryOperator;

/**
 *  End namespace
 */
}


 