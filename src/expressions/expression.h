/**
 *  Expression.h
 *
 *  Base class for all sorts of expressions
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */
 
/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class Expression
{
protected:
    /**
     *  Constructor
     * 
     *  The constructor is protected, because an expression is always 
     *  implemented by one of its derived classes.
     */
    Expression() {}

public:
    /**
     *  Destructor
     */
    virtual ~Expression() {}
    
    /**
     *  Generate the code to get the const char * to the expression
     *  @param  str
     */
    virtual void generateString(std::ostream &str) const = 0;
    
    /**
     *  Generate the code to get the numeric value of the expression
     *  @param  str
     */
    virtual void generateNumeric(std::ostream &str) const = 0;
    
};

/**
 *  End namespace
 */
}

