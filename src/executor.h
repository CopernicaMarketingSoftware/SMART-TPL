/**
 *  Executor.h
 *
 *  Base class that is used for executing templates. This executor is
 *  implemented by ByteCode (which compiles a template on the fly) and by
 *  SharedLibrary (which loads a shared library)
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
class Executor
{
protected:
    /**
     *  Protected constructor
     */
    Executor() {}

public:
    /**
     *  Destructor
     */
    virtual ~Executor() {}

    /**
     *  Execute the template given a certain data source
     *  @param  data
     */
    virtual void process(Handler &handler) = 0;

    /**
     *  Compile the template into C code
     *  @return std::string
     */
    virtual std::string compile() = 0;

};

/**
 *  End namespace
 */
}

