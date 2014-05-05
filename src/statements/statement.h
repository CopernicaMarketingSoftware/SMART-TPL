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
namespace SmartTpl { namespace Internal {

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

    /**
     *  Generate source code
     * 
     *  This method is passed a generator object that will be fed with all
     *  input elements, and that will generate either the shared library or
     *  the JIT representation.
     * 
     *  @param  generator
     */
    virtual void generate(Generator *generator) const = 0;

};

/**
 *  End namespace
 */
}}