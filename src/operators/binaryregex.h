/**
 *  BinaryRegex.h
 *
 *  Implementation of the binary regex operator ("=~")
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2018 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class BinaryRegexOperator : public BinaryCompareOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryRegexOperator(Expression *left, Expression *right) :
        BinaryCompareOperator(left, right) {}

    /**
     *  Destructor
     */
    virtual ~BinaryRegexOperator() = default;

    /**
     *  Generate the instruction
     *  @param  generator
     */
    void numeric(Generator *generator) const override
    {
        generator->regex(_left.get(), _right.get());
    }

    /**
     *  Generate the instruction
     *  @param  generator
     */
    void boolean(Generator *generator) const override
    {
        generator->regex(_left.get(), _right.get());
    }

    /**
     *  Generate the expression as a runtime variable pointer
     *  @param  generator
     */
    void runtime_pointer(Generator *generator) const override
    {
        generator->regex(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}}
