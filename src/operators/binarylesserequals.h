/**
 *  BinaryLesserEquals.h
 *
 *  Implementation of the binary lesser-or-equals operator
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
class BinaryLesserEqualsOperator : public BinaryCompareOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryLesserEqualsOperator(Expression *left, Expression *right) :
        BinaryCompareOperator(left, right) {}

    /**
     *  Destructor
     */
    virtual ~BinaryLesserEqualsOperator() {}

    /**
     *  Generate the instruction
     *  @param  generator
     */
    virtual void toInteger(Generator *generator) const override
    {
        generator->lesserEquals(_left.get(), _right.get());
    }

    /**
     *  Generate the instruction
     *  @param  generator
     */
    virtual void toBoolean(Generator *generator) const override
    {
        generator->lesserEquals(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}}
