/**
 *  BinaryModuloOperator.h
 *
 *  Implementation of the binary modulo operator
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class BinaryModuloOperator : public BinaryArithmetricOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryModuloOperator(Expression *left, Expression *right) :
        BinaryArithmetricOperator(left, right) {}

    /**
     *  Destructor
     */
    virtual ~BinaryModuloOperator() {}

    /**
     *  Generate the operations
     *  @param  generator
     */
    void numeric(Generator *generator) const override
    {
        generator->modulo(_left.get(), _right.get());
    }

    /**
     *  Generate the instruction
     *  @param  generator
     */
    void boolean(Generator *generator) const override
    {
        generator->modulo(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}}