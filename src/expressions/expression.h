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
     *  Generate the expression as a numeric value
     *  @param  generator
     */
    virtual void numeric(Generator *generator) const = 0;
    
    /**
     *  Generate the expression as a boolean value
     *  @param  generator
     */
    virtual void boolean(Generator *generator) const = 0;
    
    /**
     *  Generate the expression as string value
     *  @param  generator
     */
    virtual void string(Generator *generator) const = 0;
    
};

/**
 *  End namespace
 */
}

