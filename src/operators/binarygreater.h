/**
 *  BinaryGreater.h
 *
 *  Implementation of the binary greater operator
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
class BinaryGreaterOperator : public BinaryCompareOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryGreaterOperator(Expression *left, Expression *right) :
        BinaryCompareOperator(left, right) {}

    /**
     *  Destructor
     */
    virtual ~BinaryGreaterOperator() {}

    /**
     *  Generate the instruction
     *  @param  generator
     */
    virtual void toInteger(Generator *generator) const override
    {
        generator->greater(_left.get(), _right.get());
    }

    /**
     *  Generate the instruction
     *  @param  generator
     */
    virtual void toBoolean(Generator *generator) const override
    {
        generator->greater(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}}
