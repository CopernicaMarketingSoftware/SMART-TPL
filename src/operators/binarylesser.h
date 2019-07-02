/**
 *  BinaryLesser.h
 *
 *  Implementation of the binary lesser operator
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
class BinaryLesserOperator : public BinaryCompareOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryLesserOperator(Expression *left, Expression *right) :
        BinaryCompareOperator(left, right) {}

    /**
     *  Destructor
     */
    virtual ~BinaryLesserOperator() {}

    /**
     *  Generate the instruction
     *  @param  generator
     */
    virtual void toInteger(Generator *generator) const override
    {
        generator->lesser(_left.get(), _right.get());
    }

    /**
     *  Generate the instruction
     *  @param  generator
     */
    virtual void toBoolean(Generator *generator) const override
    {
        generator->lesser(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}}
