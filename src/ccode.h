/**
 *  CCode.h
 *
 *  Class that turns a template syntax tree into C code that can be compiled
 *  into a shared library.
 *
 *  This class overrides from the Generator base class, because it is one
 *  of the generators of the SmartTpl library (the template-to-c-code generator)
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class CCode : public Generator
{
private:
    /**
     *  Output stream
     *  @var    std::ostream
     */
    std::ostringstream _out;
    
public:
    /**
     *  Constructor
     *  @param  tree        The abstract syntax tree of the template
     */
    CCode(const SyntaxTree &tree);
    
    /**
     *  Destructor
     */
    virtual ~CCode() {}

    /**
     *  Output raw data
     *  @param  buffer      buffer to output
     *  @param  size        buffer size
     */
    virtual void raw(const char *data, size_t size) override;
        


};

/**
 *  End namespace
 */
}

