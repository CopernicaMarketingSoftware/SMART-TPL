/**
 *  BinaryMinus.h
 *
 *  Implementation of the binary minus operator
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
class BinaryMinusOperator : public BinaryArithmetricOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryMinusOperator(Expression *left, Expression *right) :
        BinaryArithmetricOperator(left, right) {}

    /**
     *  Destructor
     */
    virtual ~BinaryMinusOperator() {}

    /**
     *  Generate the operations
     *  @param  generator
     */
    void numeric(Generator *generator) const override
    {
        generator->minus(_left.get(), _right.get());
    }

    /**
     *  Generate the expression as a double value
     *  @param  generator
     */
    void double_type(Generator *generator) const override
    {
        generator->minus(_left.get(), _right.get());
    }

    /**
     *  Generate the instruction
     *  @param  generator
     */
    void boolean(Generator *generator) const override
    {
        generator->minus(_left.get(), _right.get());
    }

    /**
     *  Generate the expression as a runtime variable pointer
     *  @param  generator
     */
    void runtime_pointer(Generator *generator) const override
    {
        generator->minus(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}}