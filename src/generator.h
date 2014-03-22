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
     *  Output raw data
     *  @param  buffer      buffer to output
     *  @param  size        buffer size
     */
    virtual void raw(const char *data, size_t size) = 0;

};

/**
 *  End namespace
 */
}

