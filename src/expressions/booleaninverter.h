/**
 *  BinaryInverter.h
 *
 *  Implementation of the boolean inverter, used to implement the not and !
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 - 2019 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class BooleanInverter : public Expression
{
private:
    /**
     *  The expression we're going to invert
     *  @var    Expression
     */
    std::unique_ptr<Expression> _expression;

public:
    /**
     *  Constructor
     *  @param  expression
     */
    BooleanInverter(Expression *expression) : _expression(expression) {}

    /**
     *  Destructor
     */
    virtual ~BooleanInverter() {}

    /**
     *  The return type of the expression
     *  @return Type
     */
    virtual Type type() const override { return Type::Boolean; };

    /**
     *  Generate the instruction
     *  @param  generator
     */
    virtual void toBoolean(Generator *generator) const override
    {
        // create an inverted generator
        generator->negateBoolean(_expression.get());
    }
};

/**
 *  End of namespace
 */
}}
