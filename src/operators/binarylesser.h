/**
 *  BinaryLesser.h
 *
 *  Implementation of the binary lesser operator
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
    void numeric(Generator *generator) const override
    {
        generator->lesser(_left.get(), _right.get());
    }

    /**
     *  Generate the instruction
     *  @param  generator
     */
    void boolean(Generator *generator) const override
    {
        generator->lesser(_left.get(), _right.get());
    }

    /**
     *  Generate the expression as a runtime variable pointer
     *  @param  generator
     */
    void runtime_pointer(Generator *generator) const override
    {
        generator->lesser(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}}