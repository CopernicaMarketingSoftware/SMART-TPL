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
    
};

/**
 *  End namespace
 */
}

