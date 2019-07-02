/**
 *  BinaryGreaterEquals.h
 *
 *  Implementation of the binary greater-or-equals operator
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class BinaryGreaterEqualsOperator : public BinaryCompareOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryGreaterEqualsOperator(Expression *left, Expression *right) :
        BinaryCompareOperator(left, right) {}

    /**
     *  Destructor
     */
    virtual ~BinaryGreaterEqualsOperator() {}

    /**
     *  Generate the instruction
     *  @param  generator
     */
    void numeric(Generator *generator) const override
    {
        generator->greaterEquals(_left.get(), _right.get());
    }

    /**
     *  Generate the instruction
     *  @param  generator
     */
    void boolean(Generator *generator) const override
    {
        generator->greaterEquals(_left.get(), _right.get());
    }

    /**
     *  Generate the expression as a runtime variable pointer
     *  @param  generator
     */
    void runtime_pointer(Generator *generator) const override
    {
        generator->greaterEquals(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}}