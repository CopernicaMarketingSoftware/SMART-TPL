/**
 *  BinaryBoolean.h
 *
 *  Base class for boolean operators
 *
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

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
     *  Virtual method to generate the operator
     *  @param  str
     */
    virtual void generateOperator(std::ostream &str) const = 0;

    /**
     *  Generate the code to get the const char * to the expression
     *  @param  str
     */
    virtual void generateString(std::ostream &str) const override
    {
        // booleans have no output, generate a string right away
        str << "\"\"";
    }
        
    /**
     *  Generate the code to get the numeric value of the expression
     *  @param  str
     */
    virtual void generateNumeric(std::ostream &str) const override
    {
        // generate the code that turns the left expression into a numeric value
        _left->generateNumeric(str);
        
        // generate the operator
        generateOperator(str);
        
        // generate the function that turns the right expression into a boolean value
        _right->generateNumeric(str);
    }

};

/**
 *  End namespace
 */
}
