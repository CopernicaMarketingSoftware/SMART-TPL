/**
 *  Statement.h
 *
 *  Base class that is used by all statements
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
class Statement
{
protected:
    /**
     *  Constructor
     * 
     *  This constructor is protected, because a statement is never constructed
     *  by its own, but always through a derived class (like 'IfStatement')
     */
    Statement() {}

public:
    /**
     *  Destructor
     */
    virtual ~Statement() {}
};
    
/**
 *  End namespace
 */
}

