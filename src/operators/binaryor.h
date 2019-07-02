/**
 *  BinaryOr.h
 *
 *  Implementation of the binary || operator
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 - 2019 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class BinaryOrOperator : public BinaryBooleanOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryOrOperator(Expression *left, Expression *right) :
        BinaryBooleanOperator(left, right) {}

    /**
     *  Destructor
     */
    virtual ~BinaryOrOperator() {}

    /**
     *  Generate the instruction
     *  @param  generator
     */
    virtual void toInteger(Generator *generator) const override
    {
        generator->booleanOr(_left.get(), _right.get());
    }

    /**
     *  Generate the instruction
     *  @param  generator
     */
    virtual void toBoolean(Generator *generator) const override
    {
        generator->booleanOr(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}}
