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
     *  Generate the operator to a numeric value
     *  @param  generator
     */
    virtual void toInteger(Generator *generator) const override
    {
        generator->integerModulo(_left.get(), _right.get());
    }

    /**
     *  Generate the operator to a double value
     *  @param  generator
     */
    virtual void toDouble(Generator *generator) const override
    {
        generator->integerModulo(_left.get(), _right.get());
    }

    /**
     *  Generate the operator to a pointer value
     *  @param  generator
     */
    virtual void toPointer(Generator *generator) const override
    {
        generator->pointerModulo(_left.get(), _right.get());
    }

    /**
     *  The return type of the expression
     *  @return Type
     */
    virtual Type type() const override 
    {
        // Modulo operations are always integer
        return Type::Integer;
    }

};

/**
 *  End of namespace
 */
}}
