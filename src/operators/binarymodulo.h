/**
 *  BinaryModuloOperator.h
 *
 *  Implementation of the binary modulo operator
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
     *  The return type of the expression
     *  @return Type
     */
    virtual Type type() const override 
    {
        // the modulo operator is always numeric
        return Type::Numeric;
    }

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
    
    /**
     *  Generate the expression as a runtime variable pointer
     *  @param  generator
     */
    void runtime_pointer(Generator *generator) const override
    {
        generator->modulo(_left.get(), _right.get());
    }
};

/**
 *  End of namespace
 */
}}