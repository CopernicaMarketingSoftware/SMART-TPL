/**
 *  Generator.h
 *
 *  After a template file is parsed, it is turned into a SyntaxTree, which is
 *  then either turned into a shared library by the template compiler, or into 
 *  a JIT compiled executable memory buffer.
 *
 *  This is the abstract base class of both the shared-library-compiler, and 
 *  the JIT-compiler.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Forwards
 */
class Variable;
class Expression;
class Statements;

/**
 *  Class definition
 */
class Generator
{
protected:
    /**
     *  The constructor is protected because only derived generators
     *  should be used
     */
    Generator() {}
    
public:
    /**
     *  Destructor
     */
    virtual ~Generator() {}

    /**
     *  Generate code to output raw data
     *  @param  buffer      buffer to output
     *  @param  size        buffer size
     */
    virtual void raw(const char *data, size_t size) = 0;
    
    /**
     *  Generate the code to output a variable
     *  @param  variable    the variable to output
     */
    virtual void output(const Variable *variable) = 0;

    /**
     *  Generate a conditional statement
     *  @param  expression          the expression to evaluate
     *  @param  ifstatements        the statements in the 'if' part
     *  @param  elsestatements      the statements in the 'else' part
     */
    virtual void conditional(const Expression *expression, const Statements *ifstatements, const  Statements *elsestatements) = 0;
};

/**
 *  End namespace
 */
}

