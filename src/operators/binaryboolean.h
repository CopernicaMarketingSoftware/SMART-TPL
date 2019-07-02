/**
 *  BinaryBoolean.h
 *
 *  Base class for boolean operators
 *
 *  @copyright 2014 - 2019 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class BinaryBooleanOperator : public BinaryOperator
{
public:
    /**
     *  Constructor
     *  @param  left
     *  @param  right
     */
    BinaryBooleanOperator(Expression *left, Expression *right) :
        BinaryOperator(left, right) {}

    /**
     *  Destructor
     */
    virtual ~BinaryBooleanOperator() {}

    /**
     *  Generate the code to get the const char * to the expression
     *  @param  generator
     */
    virtual void string(Generator *generator) const override
    {
        // this is wrong, because we can send "true" or "false" to the output, but
        // inside ByteCode.cpp and CCode.cpp we have a special case for boolean output
        generator->stringValue("");
    }
};

/**
 *  End namespace
 */
}}
